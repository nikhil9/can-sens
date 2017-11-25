
#include "ch.h"
#include "hal.h"

#include "shell.h"
#include "usbcfg.h"
#include "custom_util.h"

#define SHELL_WA_SIZE   THD_WORKING_AREA_SIZE(2048)

static const ShellCommand commands[] = {
  {NULL, NULL}
};

static const ShellConfig shell_cfg1 = {
  (BaseSequentialStream *)&SDU1,
  commands
};

static THD_WORKING_AREA(waThread2, 4096);
static THD_FUNCTION(Thread2, arg) {

	(void)arg;
	chRegSetThreadName("shell_thd");

	shellInit();

	start_usb();

	delay(20);

	while(true){
		if (SDU1.config->usbp->state == USB_ACTIVE) {
		  thread_t *shelltp = chThdCreateFromHeap(NULL, SHELL_WA_SIZE,
				  "shell", NORMALPRIO + 1,
				  shellThread, (void *)&shell_cfg1);
		  chThdWait(shelltp);
		}
		delay(100);
	}
}

void start_custom_shell(void){
	chThdCreateStatic(waThread2, sizeof(waThread2),
					NORMALPRIO + 10, Thread2, NULL);
}


