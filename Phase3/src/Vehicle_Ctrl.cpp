#include "Vehicle_Ctrl.h"

#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstring>
#include <iostream>

namespace {
constexpr uint8_t CONTROL_HEADER_1  = 0xAB;
constexpr uint8_t CONTROL_HEADER_2  = 0x55;

constexpr uint8_t FEEDBACK_HEADER_1 = 0xCD;
constexpr uint8_t FEEDBACK_HEADER_2 = 0xEF;

constexpr auto TX_PERIOD = std::chrono::milliseconds(100); // 10 H
} 

Car::Car()
    : running_(false),
      desired_steering_(CENTER),
      desired_throttle_(FULL_STOP),
      desired_mode_(1),   // default auto mode
      tx_sequence_(0),    
      latest_feedback_{},
      feedback_valid_(false)
{
}

Car::~Car()
{
    Stop();
}

bool Car::Start(const char* device, int baud_rate)
{
    if (running_.load()) {
        return true;
    }

    if (!uart_.openPort(device, baud_rate)) {
        std::cerr << "Failed to open UART device: "
                  << device << '\n';
        return false;
    }

    // Start with a safe command.
    desired_steering_.store(CENTER);
    desired_throttle_.store(FULL_STOP);
    desired_mode_.store(1);
    tx_sequence_ = 0;
    // All thread running
    running_.store(true);

    // Start thread
    try {
        tx_thread_ = std::thread(&Car::TxLoop, this);
        rx_thread_ = std::thread(&Car::RxLoop, this);
    } catch (const std::exception& e) {
        std::cerr << "Failed to create UART threads: "
                  << e.what() << '\n';
        // All thread stop
        running_.store(false);

        if (tx_thread_.joinable()) {
            tx_thread_.join();
        }

        if (rx_thread_.joinable()) {
            rx_thread_.join();
        }

        return false;
    }

    return true;
}

void Car::Stop()
{
    const bool was_running = running_.exchange(false);

    if (!was_running) {
        return;
    }

    /*
     * Important:
     * RxLoop must not be permanently blocked inside read().
     *
     * Configure Uart_Jetson with:
     *   - termios VMIN/VTIME timeout, or
     *   - O_NONBLOCK, or
     *   - poll() timeout.
     */

    if (tx_thread_.joinable()) {
        tx_thread_.join();
    }

    if (rx_thread_.joinable()) {
        rx_thread_.join();
    }
}

void Car::SetThrottle(int16_t rpm)
{
    rpm = std::clamp(
        rpm,
        FULL_BACKWARD,
        FULL_FORWARD);

    desired_throttle_.store(rpm);
}

void Car::SetSteering(int16_t pulse_width)
{
    pulse_width = std::clamp(
        pulse_width,
        FULL_LEFT,
        FULL_RIGHT);

    desired_steering_.store(pulse_width);
}

void Car::SetMode(uint8_t mode)
{
    if (mode > 2) {
        mode = 2;
    }

    desired_mode_.store(mode);
}

void Car::EmergencyStop()
{
    desired_throttle_.store(FULL_STOP);
    desired_steering_.store(CENTER);
    desired_mode_.store(2);
}

bool Car::IsRunning() const
{
    return running_.load();
}

Feedback Car::GetLatestFeedback() const
{
    std::lock_guard<std::mutex> lock(feedback_mutex_);
    return latest_feedback_;
}

void Car::TxLoop()
{
    auto next_send = std::chrono::steady_clock::now();
    while (running_.load()) {
        next_send += TX_PERIOD;

        ControlCmd cmd{};
        cmd.header1  = CONTROL_HEADER_1;
        cmd.header2  = CONTROL_HEADER_2;
        cmd.steering = desired_steering_.load();
        cmd.throttle = desired_throttle_.load();
        cmd.mode     = desired_mode_.load();
        cmd.seq      = tx_sequence_++;
        cmd.crc      = 0; // Replace with actual CRC.

        uint8_t tx_buffer[sizeof(ControlCmd)];

        std::memcpy(tx_buffer, &cmd, sizeof(cmd));

        if (!WriteFullPacket(tx_buffer, sizeof(tx_buffer))) {
            std::cerr << "UART command transmission failed\n";
            running_.store(false);
            break;
        }

        // similar to usleep(100000)
        std::this_thread::sleep_until(next_send);
    }
}
void Car::CmdTest(uint8_t *data, uint32_t sz){
        size_t total_read = 0;
        while (total_read < sz) {
            int n = uart_.readBytes(data + total_read, 4 - total_read);
            if (n < 0) {
                std::cerr << "read failed\n";
                return;
            }
            if (n == 0) {
                continue;
            }
            total_read += n;
        }
    
        if (total_read == 4) {
            uint16_t steering = 0;
            int16_t throttle = 0;
            memcpy(&throttle, &data[0], 2);
            memcpy(&steering, &data[2], 2);

            printf("steering = %u, throttle = %d\n", steering, throttle);
        } else {
            printf("incomplete packet\n");
        }
}
void Car::RxLoop()
{
    while (running_.load()) {
        Feedback feedback{};

        if (!ReadFeedbackPacket(feedback)) {
            /*
             * A read timeout is not necessarily a fatal error.
             * ReadFeedbackPacket() returns true/false according to
             * your Uart_Jetson read behavior.
             */
            continue;
        }
        // Get Feedback
        {
            std::lock_guard<std::mutex> lock(feedback_mutex_);
            latest_feedback_ = feedback;
            feedback_valid_ = true;
        }

        std::printf(
            "telemetry_seq=%u, last_cmd_seq=%u, "
            "erpm=%d, current=%.1f A, duty=%.3f, time=%u ms\n",
            static_cast<unsigned>(feedback.telemetry_seq),
            static_cast<unsigned>(feedback.last_cmd_seq),
            feedback.erpm,
            static_cast<double>(feedback.motor_current_x10) / 10.0,
            static_cast<double>(feedback.duty_x1000) / 1000.0,
            feedback.stm32_timestamp_ms);

        // For Debug Usage
        // #if 1  
        //     uint8_t rx_buf[4];
        //     memset(rx_buf, 0, 4);
        //     CmdTest(rx_buf, sizeof(rx_buf)/sizeof(uint8_t));

        // #endif
    }
}

bool Car::WriteFullPacket(const uint8_t* data, std::size_t size)
{
    std::size_t total_written = 0;

    while (total_written < size && running_.load()) {
        const int n = uart_.writeBytes(
            data + total_written,
            size - total_written);

        if (n < 0) {
            std::cerr << "UART write failed\n";
            return false;
        }

        if (n == 0) {
            std::this_thread::sleep_for(
                std::chrono::milliseconds(1));

            continue;
        }

        total_written += static_cast<std::size_t>(n);
    }
 
    return total_written == size;
}

bool Car::ReadFeedbackPacket(Feedback& feedback)
{
    enum class RxState {
        WaitHeader1,
        WaitHeader2,
        ReadRemaining
    };

    RxState state = RxState::WaitHeader1;

    uint8_t buffer[sizeof(Feedback)]{};
    std::size_t received = 0;

    while (running_.load()) {
        uint8_t byte = 0;

        const int n = uart_.readBytes(&byte, 1);

        if (n < 0) {
            std::cerr << "UART read failed\n";
            return false;
        }

        if (n == 0) {
            /*
             * Expected when UART is configured with a timeout
             * or nonblocking operation.
             */
            continue;
        }

        switch (state) {
        case RxState::WaitHeader1:
            if (byte == FEEDBACK_HEADER_1) {
                buffer[0] = byte;
                state = RxState::WaitHeader2;
            }
            break;

        case RxState::WaitHeader2:
            if (byte == FEEDBACK_HEADER_2) {
                buffer[1] = byte;
                received = 2;
                state = RxState::ReadRemaining;
            } else if (byte == FEEDBACK_HEADER_1) {
                /*
                 * This byte might be the beginning of another
                 * valid header.
                 */
                buffer[0] = byte;
            } else {
                state = RxState::WaitHeader1;
            }
            break;

        case RxState::ReadRemaining:
            buffer[received++] = byte;

            if (received == sizeof(Feedback)) {
                std::memcpy(
                    &feedback,
                    buffer,
                    sizeof(feedback));

                if (feedback.header1 != FEEDBACK_HEADER_1 ||
                    feedback.header2 != FEEDBACK_HEADER_2) {
                    return false;
                }

                // Add CRC verification here.(TODO)
                return true;
            }

            break;
        }
    }

    return false;
}