#include "ch.h"
#include "hal.h"

#include "shell.h"

#include "usbcfg.h"

#include "custom_util.h"


static THD_WORKING_AREA(waThread2, 128);
static THD_FUNCTION(Thread2, arg) {

  (void)arg;
  chRegSetThreadName("blinker2");
  while (true) {

    delay(250);

    delay(250);
  }
}

#define SHELL_WA_SIZE   THD_WORKING_AREA_SIZE(2048)

static const ShellCommand commands[] = {
  {NULL, NULL}
};

static const ShellConfig shell_cfg1 = {
  (BaseSequentialStream *)&SDU1,
  commands
};

int main(void) {

	  halInit();
	  chSysInit();

	  shellInit();

	  start_usb();
	  delay(20);

	  chThdCreateStatic(waThread2, sizeof(waThread2),
	                    NORMALPRIO + 10, Thread2, NULL);

	  while (true) {
	    if (SDU1.config->usbp->state == USB_ACTIVE) {
	      thread_t *shelltp = chThdCreateFromHeap(NULL, SHELL_WA_SIZE,
	                                              "shell", NORMALPRIO + 1,
	                                              shellThread, (void *)&shell_cfg1);
	      chThdWait(shelltp);               /* Waiting termination.             */
	    }
	    delay(1000);
	  }

	  return 0;
}
