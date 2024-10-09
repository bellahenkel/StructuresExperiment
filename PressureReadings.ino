
#include "HX711.h"

#define calibration_factor -1090.0 //This value is obtained using the SparkFun_HX711_Calibration sketch

#define LOADCELL_DOUT_PIN  3
#define LOADCELL_SCK_PIN  2

//change depending on chamber dimensions
const float wall_thickness_in  = 0.065;
const float chamber_diameter_in = 2.23;

//change depending on chamber material
const float youngs_modulus_psi = 29730000;
const float poissons_ratio  = 0.35;



HX711 scale;

void setup() {
  Serial.begin(57600);
  Serial.println("HX711 scale demo");

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0

  Serial.println("Readings:");
}

void loop() {

  float microstrain = get_microstrain();
  get_pressure(microstrain);
  delay(5000);
  //Serial.println(microstrain);
  //Serial.println(get_pressure(microstrain));
  //Serial.print("Reading: ");
  //Serial.print(scale.get_units(), 1); //scale.get_units() returns a float
  //Serial.print(" microstrain"); //You can change this to kg but you'll need to refactor the calibration_factor
  //Serial.println();
  

}
float get_pressure(float strain){
    Serial.print(strain * pow(10, 6));
    
    float pressure_difference = (youngs_modulus_psi * wall_thickness_in * strain) / (chamber_diameter_in * (1 - (poissons_ratio / 2)));
    Serial.println(pressure_difference);
    return pressure_difference;
   }
float get_microstrain(){
  float microstrain = round(scale.get_units());
  float strain = microstrain * pow(10, -6);
  return strain;
}
