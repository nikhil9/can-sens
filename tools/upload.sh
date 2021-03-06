#!/bin/bash


BASEDIR=`pwd`

SYSTYPE=`uname -s`

sleep 1
echo ""
echo "creating .px4"
echo ""

python $BASEDIR/tools/px_mkfw.py --prototype $BASEDIR/tools/px4.prototype --git_identity $BASEDIR --image $BASEDIR/build/can_sens.bin > $BASEDIR/build/can_sens.px4

echo ""
echo "connecting to flash tool"
echo ""
sleep 1

#
# Serial port defaults.
#
# XXX The uploader should be smarter than this.
#
if [ $SYSTYPE = "Darwin" ];
then
SERIAL_PORTS="/dev/tty.usbmodemPX*,/dev/tty.usbmodem*"
fi

if [ $SYSTYPE = "Linux" ];
then
SERIAL_PORTS="/dev/serial/by-id/*_PX4_*,/dev/serial/by-id/usb-3D_Robotics*,/dev/serial/by-id/usb-The_Autopilot*,/dev/serial/by-id/usb-Bitcraze*,/dev/serial/by-id/pci-Bitcraze*,"
fi

if [ $SYSTYPE = "" ];
then
SERIAL_PORTS="COM32,COM31,COM30,COM29,COM28,COM27,COM26,COM25,COM24,COM23,COM22,COM21,COM20,COM19,COM18,COM17,COM16,COM15,COM14,COM13,COM12,COM11,COM10,COM9,COM8,COM7,COM6,COM5,COM4,COM3,COM2,COM1,COM0"
fi

python $BASEDIR/tools/px_uploader.py --port $SERIAL_PORTS $BASEDIR/build/can_sens.px4



