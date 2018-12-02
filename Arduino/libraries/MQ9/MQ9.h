#ifndef MQ9_h
#define MQ9_h

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#endif

class MQ9 {
public: 
	MQ9(int pin);
	float read(bool print);
	float readCO();
	void begin();
private:
	int _pin;
	int RL_VALUE = 5;     //define the load resistance on the board, in kilo ohms
	int RO_CLEAN_AIR_FACTOR = 9.83;  
	int CALIBARAION_SAMPLE_TIMES = 5; 
	int CALIBRATION_SAMPLE_INTERVAL = 50;
	int READ_SAMPLE_INTERVAL = 50;
	int READ_SAMPLE_TIMES = 5;

	float COCurve[3]  =  {2.3,0.72,-0.34};   
	float Ro = 10;             
 
	int GAS_CO = 1;

	float co = 0;
	
	float MQRead();
	float MQGetGasPercentage(float rs_ro_ratio, int gas_id);
	int MQGetPercentage(float rs_ro_ratio, float *pcurve);
	float MQCalibration();
	float MQResistanceCalculation(int raw_adc);

	int lastReadTime = 0;
};

//#endif
