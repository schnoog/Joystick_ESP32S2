// This sketch created a basic joystick with the custom PID / VID set within setup()
// For this to work you have to DISABLE USB CDC on boot
// In the Arduino IDE you can set this in the Tools menue
// In platformio you can archieve that by adding
// build_flags =  -DARDUINO_USB_CDC_ON_BOOT=0 
// to your platformio.ini project file
// 
// please be aware that by disabling CDC on boot the serial adapter will not be started anymore
// To upload a new sketch you need to bring the ESP into upload mode by yourself (most cases keep the "boot" button pressed while resetting the device)
//------------------------------------------------------------

#include <Joystick_ESP32S2.h>

Joystick_ Joystick;

int js = 0;
void setup() {

USB.PID(0x8211);
USB.VID(0x303b);
USB.productName("My product name");
USB.manufacturerName("My company name");
USB.begin();


  Joystick.setXAxisRange(-127, 127);
  Joystick.setYAxisRange(-127, 127);
  Joystick.setZAxisRange(-127, 127);
  Joystick.setThrottleRange(0, 255);
  Joystick.setRudderRange(0, 255);
  Joystick.begin(false);
}

void loop() {
      if(js == 0){
        Joystick.pressButton(1);
        js = 1;
      }else{
        js = 0;
        Joystick.releaseButton(1);        
      }


      Joystick.sendState();
      delay(1000);
}
