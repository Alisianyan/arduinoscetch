#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
/*map<string, int> LEDcolor;
LEDcolor["RED"] = 0
LEDcolor["GREEN"] = 1
LEDcolor["Blue"] = 2 */

// called this way, it uses the default address 0x40
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);
// you can also call it with a different address and I2C interface
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(0x41, Wire);

void setup() {
  Serial.begin(9600);
  Serial.println("16 channel PWM test!");

  pwm.begin();
  pwm2.begin();
  /*
   * In theory the internal oscillator (clock) is 25MHz but it really isn't
   * that precise. You can 'calibrate' this by tweaking this number until
   * you get the PWM update frequency you're expecting!
   * The int.osc. for the PCA9685 chip is a range between about 23-27MHz and
   * is used for calculating things like writeMicroseconds()
   * Analog servos run at ~50 Hz updates, It is importaint to use an
   * oscilloscope in setting the int.osc frequency for the I2C PCA9685 chip.
   * 1) Attach the oscilloscope to one of the PWM signal pins and ground on
   *    the I2C PCA9685 chip you are setting the value for.
   * 2) Adjust setOscillatorFrequency() until the PWM update frequency is the
   *    expected value (50Hz for most ESCs)
   * Setting the value here is specific to each individual I2C PCA9685 chip and
   * affects the calculations for the PWM update frequency. 
   * Failure to correctly set the int.osc value will cause unexpected PWM results
   */
  pwm.setOscillatorFrequency(27000000);
  pwm2.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(1600);  // This is the maximum PWM frequency
  pwm2.setPWMFreq(1600);

  // if you want to really speed stuff up, you can go into 'fast 400khz I2C' mode
  // some i2c devices dont like this so much so if you're sharing the bus, watch
  // out for this!
  Wire.setClock(400000);
}

void loop() { 
  
 for (int i = 0; i < 3; i++) {
  pwm.setPWM(i, 0, 4095);
  delay(500);
  pwm.setPWM(i, 0, 0);
}

for (int i = 0; i < 3; i++) {
  pwm2.setPWM(i, 0, 4095);
  delay(500);
  pwm2.setPWM(i, 0, 0);
} */

)
