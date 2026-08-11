# Purpose
- Read Motor current rmp from VESC and send to jetson
- Jetson send cmd to control both servo and motor, and human could interrupt both
- Code structure re-structured, fix servo jittering, and add button interrupt to reset to jetson mode without reset stm32 itself



## Test:
- For STM32 settings and explanation. See [STM config](../docs/STM32/README.md)
- Step:
1. Replace /inc and /src  (STM32)
2. Copy `Phase3` to your Jetson's repository.
4. Build and run:

   ```shell
   make
   ./main 
   ```
5. Should see the wheel spinning while servo also oscillate between right and left. At the same time you can read the feedback from the jetson. Also, you could use transmitor to interrupt current jetson and give control back to jetson by pressing the blue button
<video src="../Video/VehicleTest/FullSysTest.mp4" controls width="600"></video>