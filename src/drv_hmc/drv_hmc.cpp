
#include "custom_util.h"
#include "drv_hmc.h"

HMC hmc;

static THD_WORKING_AREA(waThread3, 128);
static THD_FUNCTION(Thread3, arg) {

	(void)arg;
	chRegSetThreadName("drv_hmc");
	while (true) {


		delay(20);
	}
}


void HMC::init(void){

}

void HMC::update(void){

}

void start_hmc(void){

	hmc.init();

	chThdCreateStatic(waThread3, sizeof(waThread3),
					NORMALPRIO + 20, Thread3, NULL);

}

