#ifndef UART_DRV_HPP
#define UART_DRV_HPP

#include <string>
#include <cstddef>

class Uart_Jetson {
public:
    Uart_Jetson();
    ~Uart_Jetson();

    bool openPort(const std::string& device, uint32_t baudrate);
    void closePort();

    int writeBytes(const uint8_t* data, size_t len);
    int  readBytes(uint8_t* buf, size_t len);

    bool isOpen() const;
    int fd_;
private:
};

#endif