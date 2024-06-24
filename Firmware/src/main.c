//#pragma src

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include "main.h"
#include "InitDevice.h"

int8_t getTemperature(void) {
    uint8_t i;
    uint16_t adcraw = 0; // raw data from ADC
    int8_t tmp; // temperature in degrees
    // read temperature ADC
    for(i=0;i<10;i++){
        ADC0CN0_ADBUSY = 1; // start the conversion
        while(!ADC0CN0_ADINT);
        adcraw +=ADC0;
        ADC0CN0_ADINT = 0;
    }
    // 1878.736 ADC value for temperature offset voltage (757 mV from datasheet).
    // 10 samples measured against 1.65V vref with 12 bit resolution.
    // The slope coefficient is 7.0732 at 1.65V vref (2.85 mV/°C from datasheet).
    tmp = (int8_t)((((float)adcraw / 10.0) - 1878.736) / 7.0732);
    return tmp;
}

void setPWM(uint8_t ppwm){
  // convert percent (0-100) to real pwm (255 - 0). 0 means full speed (100%)
  uint8_t rawpwm = 255 - ((uint16_t)ppwm * 255 / 100);
  // set new PWM value for the fan.
  PCA0CPH0 = rawpwm;
  PCA0CPH1 = rawpwm;
}


typedef struct t_struct {
   int8_t temp;
   uint8_t ppwm;
} TEMP_PWM;

// Temperature -- PWM table
TEMP_PWM code temp_pwm_table[22] = {
    {30, 30},
    {31, 31},
    {32, 32},
    {33, 33},
    {34, 34},
    {35, 35},
    {36, 36},
    {37, 37},
    {38, 38},
    {39, 39},
    {40, 40},
    {42, 43},
    {44, 48},
    {46, 58},
    {48, 70},
    {50, 80},
    {51, 82},
    {52, 84},
    {53, 86},
    {54, 88},
    {55, 90},
    {125, 100},
 };

 void main_routine(void){
    int8_t temperature;
    uint8_t i;

    PCON0 |= 0x01; // set IDLE bit
    PCON0 = PCON0; // ... followed by a 3-cycle dummy instruction

    temperature = getTemperature();
    // set pwm according to temperature
    for(i=0;i<22;i++){
        if(temperature <= temp_pwm_table[i].temp) {
            setPWM(temp_pwm_table[i].ppwm);
            break;
        }
    }

}


//-----------------------------------------------------------------------------
// main() Routine
// ----------------------------------------------------------------------------
int main(void) {
  // Call hardware initialization routine
  enter_DefaultMode_from_RESET();
  
  getTemperature(); // initialize ADC

  while(1){
      main_routine();
	}

}
