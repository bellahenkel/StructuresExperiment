#include "HX711.h"

#define LOADCELL_DOUT_PIN  3
#define LOADCELL_SCK_PIN  2

HX711 scale;

float calibration_factor = 1020; //-7050 worked for my 440lb max scale setup

void setup() {
  Serial.begin(9600);

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale();
  scale.tare(); //Reset the scale to 0

  long zero_factor = scale.read_average(); //Get a baseline reading
}

void loop() {

  scale.set_scale(calibration_factor); //Adjust to this calibration factor
  Serial.print(0); // To freeze the lower limit
  Serial.print(" ");
  Serial.print(1000); // To freeze the upper limit
  Serial.print(" ");
  Serial.print(scale.get_units(), 1);
  Serial.println();

  // if(Serial.available())
  // {
  // char temp = Serial.read();
  //   if(temp == '+' || temp == 'a'){
  //    calibration_factor += 10;
  //  }
  //  else if(temp == '-' || temp == 'z'){
  //    calibration_factor -= 10;
  //   }
  //}
}
