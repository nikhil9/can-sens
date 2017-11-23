## General Instructions ##

Make sure BOOT0 jumper/switch is on while powering up the mcu.
BOOT0 -> HIGH
BOOT1 -> LOW


## Windows ## 


*Download Zadig from http://zadig.akeo.ie/
*Connect STM32 in DFU mode.
*Open Zadig and check 'List all device' from 'Options' menu.
*Select STM32 device form drop down menu
*Hit replace driver
*This process is USB port dependant. So you have to do this again if you connect it to different port.


#### Command Prompt Instructions ###
Check if mcu is connected in dfu mode using following command in command prompt

dfu-util --list

Command to flash mcu in dfu mode (pay attention to PATH)

dfu-util -d 0483:df11 -c 1 -i 0 -a 0 -s 0x08000000 -D /PATH/TO.bin

Execute following command (from this folder) to flash firmware

dfu-util -d 0483:df11 -c 1 -i 0 -a 0 -s 0x08000000 -D ..\build\FW.bin

### Eclipse Instructions ###

*Run > External Tool > External Tool Config > New Program
*Select location of dfu-util.exe at 'Location'
*select build directory location at 'Working Directory'
*Put following lines in Argument tab

-d 0483:df11 -c 1 -i 0 -a 0 -s 0x08000000 -D FW.bin

*Disable AutoBuild from Build tab.

Once done, launch this from external tool menu to flash.


## LINUX ##

Follow build "Get the source code and build it" on following link

http://dfu-util.gnumonks.org/build.html

Execute following command (from anywhere) to flash firmware (pay attention to PATH)

dfu-util -d 0483:df11 -c 1 -i 0 -a 0 -s 0x08000000 -D /PATH/TO.bin

#Add udev rules

sudo gedit /etc/udev/rules.d/stm32.rules

Copy paste following content and save:
#STM32F4 Dsicovery in USB Serial Mode (CN5)
ATTRS{idVendor}=="0483", ATTRS{idProduct}=="5740", ENV{ID_MM_DEVICE_IGNORE}="1"
ATTRS{idVendor}=="0483", ATTRS{idProduct}=="5740", ENV{MTP_NO_PROBE}="1"
SUBSYSTEMS=="usb", ATTRS{idVendor}=="0483", ATTRS{idProduct}=="5740", MODE:="0666"
KERNEL=="ttyACM*", ATTRS{idVendor}=="0483", ATTRS{idProduct}=="5740", MODE:="0666"
# 0483:df11 - STM32F4 Discovery in DFU mode (CN5)
SUBSYSTEMS=="usb", ATTRS{idVendor}=="0483", ATTRS{idProduct}=="df11", MODE:="0666"

sudo restart udev


