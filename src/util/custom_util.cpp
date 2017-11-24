
#include "ch.h"
#include "hal.h"

void delay(uint32_t _time){
	chThdSleepMilliseconds(_time);
}
