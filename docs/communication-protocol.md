# communication-protocol
### UART
(TODO)
### SBUS Bus
(TODO)
### I2C 
(TODO)
### CAN Bus

- A bit is build up by sync TQ, BS1 TQ, and BS2 TQ, and sync TQ usually is 1 TQ.
- Sample point is at (sync + BS1)
```
Below is an full bit
0%                                         100%
| Sync |----------- BS1 -----------|--- BS2 ---|
                                   ^
                                sample
```