#include "ch.h"
#include "hal.h"

#include "custom_util.h"
#include "drv_hmc.h"

static THD_WORKING_AREA(waThread1, 128);
static THD_FUNCTION(Thread1, arg) {

	(void)arg;
	chRegSetThreadName("blinker1");
	while (true) {

		delay(250);
		//TODO LED Blink
		delay(250);
	}
}


int main(void) {

	halInit();
	chSysInit();

	chThdCreateStatic(waThread1, sizeof(waThread1),
					NORMALPRIO + 10, Thread1, NULL);

	start_custom_shell();

	start_hmc();

	while (true) {

		delay(1000);
	}

	return 0;
}
