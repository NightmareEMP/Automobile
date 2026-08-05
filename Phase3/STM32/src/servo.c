#include "servo.h"
#include <stdint.h>
#include "main.h"

static uint16_t Servo_map_range(uint16_t x, uint16_t in_min, uint16_t in_max, uint16_t out_min, uint16_t out_max){
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void Servo_Subs2PWM(const uint16_t *steering, uint16_t *steering_PWM){
	if (steering == NULL || steering_PWM == NULL) {
		return;
	}
	uint16_t steering_SBUS = *steering;
	if(steering_SBUS >= ST_FULL_RIGHT && steering_SBUS <= ST_FULL_LEFT){
		if(steering_SBUS <= ST_IDLE_UPPER_BOUNDARY && steering_SBUS >= ST_IDLE_LOWER_BOUNDARY) {
			*steering_PWM = CENTER;
		}
		else {
			// Right
			if (steering_SBUS > ST_IDLE_UPPER_BOUNDARY) {

				*steering_PWM = Servo_map_range(steering_SBUS, ST_IDLE_UPPER_BOUNDARY, ST_FULL_LEFT, CENTER, FULL_LEFT);
			}
			// left
			else {
				*steering_PWM = Servo_map_range(steering_SBUS, ST_FULL_RIGHT, ST_IDLE_LOWER_BOUNDARY, FULL_RIGHT, CENTER);
			}
		}
	}
	return;

}
