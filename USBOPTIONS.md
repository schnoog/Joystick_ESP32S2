# ESP32-S2/S3 Joystick Library

## USB mode, PID, VID and more

To enable the joystick, the USB device needs to be started. This can be done in 2 ways. Each one has its own benefits and trade off

### Enable USB CDC on boot

It's the easy way to do it. You can choose the option in the
 
**Arduino IDE Tools menue**
 
or if you are using PlatformIO you can add the 
```
-DARDUINO_USB_CDC_ON_BOOT=1
```
to your build_flags in the platformio.ini project file

* **Benefits:** This ensures that the serial device as well as the joystick will start as soon as ESP is powered on.


* **Trade-off:** To set a custom VID/PID you need to change either the platformio.ini (which requires a complete re-compilation of the project ever time you change it)
or a core library file for Arduino IDE





### Start the USB device manually
To start the USB device manually, you need to start it within your program setup() routine
```
void setup() {
	USB.PID(0x8211);
	USB.VID(0x303b);
	USB.productName("My product name");
	USB.manufacturerName("My company name");
	USB.begin();
}
```
Yes, a lot of code to start the device, but for sure you noticed that with this approach we are able to set the USB PID, VID, Product Name as well as Manufacturer Name within our sketch.

* **Benefits:** See the last sentence. Really easy to change PID/VID and so on
* **Trade-off:** The serial device will not be started on its own. To flash a new sketch you need to put your device into upload mode by yourself (most cases: press and keep pressed the "boot" switch while resetting/repowering the ESP)

## Set you own PID, VID, Product Name and Company name
### Manually stared USB device 
All you need to do id to set the parameters within your setup() routine
### USB CDC on boot enabled USB device
#### Arduino IDE
Unfortunately I have not found an easier way to do so than editing

`C:\Users\<UserName>\AppData\Local\Arduino15\packages\esp32\hardware\esp32\<Version>\cores\esp32\USB.cpp`

by adding

```
#define USB_VID 0xFO11
#define USB_PID 0xF011
#define USB_MANUFACTURER "My company name"
#define USB_PRODUCT MyProductName
```
right after

`#include "StreamString.h"`

That means you have to reapply the changes with each new version of the ESP core library.

#### PlatformIO
Add the PID and VID build flags to your platformio.ini file
```
build_flags =
	....
    -DARDUINO_USB_CDC_ON_BOOT=1
    -DUSB_VID=0xF011
    -DUSB_PID=0xF011
    -DUSB_PRODUCT="My Product Name"
    -DUSB_MANUFACTURER="My company name"
```





