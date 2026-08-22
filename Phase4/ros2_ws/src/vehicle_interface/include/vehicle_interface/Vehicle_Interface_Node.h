#ifndef Vehicle_Interface_Node_HPP
#define Vehicle_Interface_Node_HPP

#include <atomic>
#include <cstdint>
#include <mutex>
#include <thread>
#include <vehicle_interface/Uart_drv.hpp>
#include "rclcpp/rclcpp.hpp"
#include "vehicle_interface/msg/vehicle_feedback.hpp"
#include "vehicle_interface/msg/vehicle_command.hpp"
#include <memory>
typedef struct  {
    uint8_t  header1;      // 0xAB
    uint8_t  header2;      // 0x55
    int16_t  steering;     // 1320 ~ 1720
    int16_t  throttle;     // -3000 ~ 3000
    uint8_t  mode;         // 0=manual, 1=auto, 2=estop
    uint8_t  seq;          // packet counter, current not used 
    uint16_t crc;          // CRC16 or simple checksum, current not used 
}  __attribute__((packed)) ControlCmd;

typedef struct {
    uint8_t header1;              // 0xCD
    uint8_t header2;              // 0xEF

    uint16_t telemetry_seq;       // Stm32 packet counter
    uint16_t last_cmd_seq;        // Jetson packet counter

    uint32_t stm32_timestamp_ms;  // STM32 HAL_GetTick

    int32_t erpm;                 // VESC Status 1
    int16_t motor_current_x10;    // A * 10
    int16_t duty_x1000;           // duty * 1000

    uint16_t crc;                 // CRC16 
} __attribute__((packed)) Feedback;

// ENV check
static_assert(sizeof(ControlCmd) == 10, "ControlCmd must be exactly 10 bytes");
static_assert(sizeof(Feedback) == 20, "Feedback must be exactly 20 bytes");

class Car : public rclcpp::Node 
{
//Ros2 Node
private:
    rclcpp::Publisher<vehicle_interface::msg::VehicleFeedback>::SharedPtr feedback_pub_;
    rclcpp::Subscription<vehicle_interface::msg::VehicleCommand>::SharedPtr command_sub_;
    void command_callback(const vehicle_interface::msg::VehicleCommand::SharedPtr msg);

// Car member functions
private:
    void TxLoop();
    void RxLoop();
    bool WriteFullPacket(const uint8_t* data, std::size_t size);
    bool ReadFeedbackPacket(Feedback& feedback);
    void CmdTest(uint8_t *data, uint32_t sz);

private:
    Uart_Jetson uart_;
    // Status of started or not
    std::atomic<bool> running_;

    // Shared command values.
    std::atomic<int16_t> desired_steering_;
    std::atomic<int16_t> desired_throttle_;
    std::atomic<uint8_t> desired_mode_;

    uint8_t tx_sequence_;

    // Feedback is a multi-field object, so protect its snapshot.
    mutable std::mutex feedback_mutex_;
    Feedback latest_feedback_;
    bool feedback_valid_;

    // Send and receive threads
    std::thread tx_thread_;
    std::thread rx_thread_;
public:
    // Servo
    static constexpr int16_t CENTER        = 1520;
    static constexpr int16_t FULL_LEFT     = 1320;
    static constexpr int16_t FULL_RIGHT    = 1720;
    // Motor
    static constexpr int16_t FULL_STOP     = 0;
    static constexpr int16_t FULL_FORWARD  = 3000;
    static constexpr int16_t FULL_BACKWARD = -3000;

    Car();
    ~Car();

    // Do not allow copy or assignment, since this class manages threads and a UART port.
    Car(const Car&) = delete;
    Car& operator=(const Car&) = delete;

    bool Start(const char* device = "/dev/ttyTHS1", int baud_rate = 115200);
    void Stop();

    // Set CMD
    void SetThrottle(int16_t rpm);
    void SetSteering(int16_t pulse_width);
    void SetMode(uint8_t mode);

    void EmergencyStop();

    // Check
    bool IsRunning() const;

    Feedback GetLatestFeedback() const;
};
#endif
