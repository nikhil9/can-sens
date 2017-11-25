
#include "custom_util.h"
#include "drv_hmc.h"

#define I2C_HMC			I2CD1

#define COMPASS_ADDRESS      0x1E
#define ConfigRegA           0x00
#define ConfigRegB           0x01
#define magGain              0x20
#define PositiveBiasConfig   0x11
#define NegativeBiasConfig   0x12
#define NormalOperation      0x10
#define ModeRegister         0x02
#define ContinuousConversion 0x00
#define SingleConversion     0x01

// ConfigRegA valid sample averaging for 5883L
#define SampleAveraging_1    0x00
#define SampleAveraging_2    0x01
#define SampleAveraging_4    0x02
#define SampleAveraging_8    0x03

// ConfigRegA valid data output rates for 5883L
#define DataOutputRate_0_75HZ 0x00
#define DataOutputRate_1_5HZ  0x01
#define DataOutputRate_3HZ    0x02
#define DataOutputRate_7_5HZ  0x03
#define DataOutputRate_15HZ   0x04
#define DataOutputRate_30HZ   0x05
#define DataOutputRate_75HZ   0x06

HMC hmc;

static const I2CConfig i2cfg1 = {
	OPMODE_I2C,
	400000,
	FAST_DUTY_CYCLE_2,
};

static THD_WORKING_AREA(waThread3, 128);
static THD_FUNCTION(Thread3, arg) {

	(void)arg;
	chRegSetThreadName("drv_hmc");
	while (true) {


		delay(20);
	}
}

void HMC::init(void){

	i2cStart(&I2C_HMC, &i2cfg1);
	debug("I2CD1 Started");
	delay(100);

	health = _write_reg(ConfigRegA, SampleAveraging_8<<5 | DataOutputRate_75HZ<<2 | NormalOperation);
	health = _write_reg(0x02, 0x00);

	debug("health %x", health);

}

void HMC::update(void){

	if(!health)return;


}

bool HMC::_write_reg(uint8_t address, uint8_t value){

	msg_t status = MSG_OK;
	uint8_t rxbuf[6];
	uint8_t txbuf[2];

	txbuf[0] = address;
	txbuf[1] = value;

	i2cAcquireBus(&I2C_HMC);
	status = i2cMasterTransmit(&I2C_HMC, COMPASS_ADDRESS, txbuf, 2, rxbuf, 0);
	i2cReleaseBus(&I2C_HMC);
	if(status != MSG_OK){
		debug("Compass write failure at %u, %u", address, value);
		return false;
	}
    return true;
}


void start_hmc(void){

	hmc.init();

	chThdCreateStatic(waThread3, sizeof(waThread3),
					NORMALPRIO + 20, Thread3, NULL);

}

