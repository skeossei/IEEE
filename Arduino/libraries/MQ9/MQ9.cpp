#include "Arduino.h"
#include "MQ9.h"

MQ9::MQ9(int pin) {
      _pin = pin;
   }
void MQ9::begin(){
    Ro = MQCalibration();
    Serial.print("Ro: ");
    Serial.print(Ro);
    Serial.println(" kohm");
}

float MQ9::read(bool print){

   co = MQGetGasPercentage(MQRead()/Ro,GAS_CO);

   if (print){
       Serial.print("CO:");
       Serial.print(co);
       Serial.print( "ppm" );
       Serial.print("\n");
   }
   lastReadTime = millis();
   return co;
}

float MQ9::readCO(){
    if (millis()<(lastReadTime + 10000) && co != 0){
        return co;
    }else{
        return co = MQGetGasPercentage(MQRead()/10,GAS_CO);
    }
}

float MQ9::MQResistanceCalculation(int raw_adc) {
   return (((float)RL_VALUE*(1023-raw_adc)/raw_adc));
}

float MQ9::MQCalibration() {
  float val=0;
 
  for (int i=0;i<CALIBARAION_SAMPLE_TIMES;i++) {            //take multiple samples
    val += MQResistanceCalculation(analogRead(_pin));
    delay(CALIBRATION_SAMPLE_INTERVAL);
  }
  val = val/CALIBARAION_SAMPLE_TIMES;                   //calculate the average value
 
  val = val/RO_CLEAN_AIR_FACTOR;                        //divided by RO_CLEAN_AIR_FACTOR yields the Ro 
                                                        //according to the chart in the datasheet 
  return val; 
}
float MQ9::MQRead() {
  int i;
  float rs=0;
  int val = analogRead(_pin);

  for (i=0;i<READ_SAMPLE_TIMES;i++) {
    rs += MQResistanceCalculation(val);
    delay(READ_SAMPLE_INTERVAL);
  }
 
  rs = rs/READ_SAMPLE_TIMES;
  return rs;  
}
float MQ9::MQGetGasPercentage(float rs_ro_ratio, int gas_id) {
  if ( gas_id == GAS_CO ) {
     return MQGetPercentage(rs_ro_ratio,COCurve);
  }    
  return 0;
}
int MQ9::MQGetPercentage(float rs_ro_ratio, float *pcurve) {
  return (pow(10,(((log(rs_ro_ratio)-pcurve[1])/pcurve[2]) + pcurve[0])));
}
