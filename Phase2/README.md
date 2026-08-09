# Purpose
- Config CAN bus and control motor using current mode and rpm mode
- Read motor rpm feedback using jetson

## Test:
- For STM32 settings and explanation. See [STM config](../docs/STM32/README.md)
- Step:
1. Replace main.c with motortest.c  (STM32)
2. Copy `Phase2` to your Jetson's repository.
4. Build and run:

   ```shell
   make
   ./vesc_test 
   ```
5. Should see the wheel spinning and jetson receive feedback rpm around 2000 and last_rx_ms with 20ms time gap.
