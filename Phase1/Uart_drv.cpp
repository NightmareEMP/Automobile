#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <cstring>
#include <cstdio>
#include "Uart_drv.hpp"
Uart_Jetson::Uart_Jetson() : fd_(-1) {}

Uart_Jetson::~Uart_Jetson() {
    closePort();
}

static speed_t to_speed(int baudrate) {
    switch (baudrate) {
        case 115200: return B115200;
        case 57600:  return B57600;
        case 38400:  return B38400;
        case 9600:   return B9600;
        default:     return static_cast<speed_t>(baudrate);
    }
}

bool Uart_Jetson::openPort(const std::string& device, uint32_t baudrate) {
    fd_ = open(device.c_str(), O_RDWR | O_NOCTTY);
    if (fd_ < 0) {
        perror("open");
        return false;
    }

    struct termios tty;
    std::memset(&tty, 0, sizeof(tty));

    if (tcgetattr(fd_, &tty) != 0) {
        perror("tcgetattr");
        closePort();
        return false;
    }

    cfsetispeed(&tty, to_speed(baudrate));
    cfsetospeed(&tty, to_speed(baudrate));

    tty.c_cflag |= (CLOCAL | CREAD);
    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;
    tty.c_cflag &= ~CRTSCTS;

    tty.c_iflag = 0;
    tty.c_oflag = 0;
    tty.c_lflag = 0;

    tty.c_cc[VMIN]  = 0;
    tty.c_cc[VTIME] = 10;

    if (tcsetattr(fd_, TCSANOW, &tty) != 0) {
        perror("tcsetattr");
        closePort();
        return false;
    }

    return true;
}

void Uart_Jetson::closePort() {
    if (fd_ >= 0) {
        close(fd_);
        fd_ = -1;
    }
}

int Uart_Jetson::writeBytes(const uint8_t* data, size_t len) {
    if (fd_ < 0 || data == nullptr) {
        return false;
    }

    return static_cast<int>(write(fd_, data, len));
}

int Uart_Jetson::readBytes(uint8_t* buf, size_t len) {
    if (fd_ < 0 || buf == nullptr) {
        return -1;
    }

    return static_cast<int>(read(fd_, buf, len));
}

bool Uart_Jetson::isOpen() const {
    return fd_ >= 0;
}