#include "ch.h"
#include "hal.h"

#include "custom_util.h"

int main(void) {

	  halInit();
	  chSysInit();

	  delay(20);

	  return 0;
}
