# STM32 Settings

### Phase 1
##### PWM: Timer2 (PA0)
- CLOCK: HCLK->180MHZ
- CLOCK SOURCE: Internal
- CHANNEL1: PWM Generation CH1
- PRESCALER: 89
- Counter: 3002

My servo accept 333Hz PWM. For prescaler at 89, time counter is 1Mhz (90M/(89+1)), and 1 tick is 1us.
For 333Hz servo, one period is 3003us (1/333).
Hence, you need 3003 (3002+1) tick  for current clock counter


##### Jetson: UART1
- Mode: Asynchronous
- DMA: RX On, Circular
- Baudrate: 115200
- Word bits: 8 bits
- Parity : None
- Stop bit: 1
##### SUBS2: UART6
[SBUS2 protocol](https://github.com/Reefwing-Software/Reefwing-SBUS/blob/main/README.md)
- Mode: Asynchronous
- DMA: RX On, Circular
- Baudrate: 100000
- Word bits: 9 bits
- Parity : Even
- Stop bit: 2