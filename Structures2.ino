#include "HX711.h"

#define strain_calibration_factor -1090.0 //This value is obtained using the SparkFun_HX711_Calibration sketch
#define scale_calibration_factor 1020

#define STRAINGAUGE_DOUT_PIN  3
#define STRAINGAUGE_SCK_PIN  2

#define LOADCELL_DOUT_PIN  5
#define LOADCELL_SCK_PIN  4

//change depending on chamber dimensions
const float wall_thickness_in  = 0.065;
const float chamber_diameter_in = 2.23;

//change depending on chamber material
const float youngs_modulus_psi = 29730000;
const float poissons_ratio  = 0.35;



HX711 scale;
HX711 strain;

void setup() {
  Serial.begin(57600);
  Serial.println("HX711 scale demo");

  strain.begin(STRAINGAUGE_DOUT_PIN, STRAINGAUGE_SCK_PIN);
  strain.set_scale(strain_calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  strain.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(scale_calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0

  Serial.println("Readings:");
}

void loop() {

  float microstrain = get_microstrain();
  get_pressure(microstrain);
  //delay(500);
  Serial.print("Strain Reading:");
  Serial.print(microstrain * pow(10, 6));
  Serial.print(",");
  Serial.print("Pressure:");
  Serial.print(get_pressure(microstrain));
  Serial.print(",");
  Serial.print("Mass (g):");
  Serial.println(scale.get_units(), 1);
  

  

}
float get_pressure(float strain){
   // Serial.print(strain * pow(10, 6));
    
    float pressure_difference = (youngs_modulus_psi * wall_thickness_in * strain) / (chamber_diameter_in * (1 - (poissons_ratio / 2)));
    //Serial.println(pressure_difference);
    return pressure_difference;
   }
float get_microstrain(){
  float microstrain = round(strain.get_units());
  float strain = microstrain * pow(10, -6);
  return strain;
}
