#ifndef SERVO_H
#define SERVO_H
#include <stdint.h>

#define CENTER     1520U
#define FULL_LEFT  1300U
#define FULL_RIGHT 1740U

void Servo_Subs2PWM(const uint16_t *steering, uint16_t *steering_PWM);



#endif /* SERVO_H */
