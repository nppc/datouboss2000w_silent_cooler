//#pragma src

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include "main.h"
#include "InitDevice.h"

typedef struct t_struct {
   int8_t temp;
   uint8_t ppwm0;
   uint8_t ppwm1;
} TEMP_PWM;

// Temperature -- PWM table
/*
TEMP_PWM code temp_pwm_table[22] = {
    {30, 5},
    {31, 6},
    {32, 7},
    {33, 8},
    {34, 9},
    {35, 10},
    {36, 12},
    {37, 14},
    {38, 16},
    {39, 18},
    {40, 22},
    {42, 32},
    {44, 42},
    {46, 52},
    {48, 62},
    {50, 72},
    {51, 82},
    {52, 92},
    {53, 94},
    {54, 96},
    {55, 98},
    {125, 100},
 };
*/

TEMP_PWM code temp_pwm_table[17] = {
{34, 5, 4},
{35, 8, 4},
{36, 10, 4},
{37, 12, 4},
{39, 14, 4},
{40, 16, 5},
{42, 20, 6},
{44, 25, 7},
{46, 30, 9},
{48, 35, 15},
{50, 45, 25},
{51, 55, 36},
{52, 65, 48},
{53, 80, 62},
{54, 90, 74},
{55, 95, 86},
{125, 100, 100},
};

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

void setPWM(uint8_t i){
  // convert percent (0-100) to real pwm (255 - 0). 0 means full speed (100%)
  uint8_t rawpwm0 = 255 - ((uint16_t)temp_pwm_table[i].ppwm0 * 255 / 100);
  uint8_t rawpwm1 = 255 - ((uint16_t)temp_pwm_table[i].ppwm1 * 255 / 100);
  // set new PWM value for the fan.
  PCA0CPH0 = rawpwm0;
  PCA0CPH1 = rawpwm1;
}



 void main_routine(void){
    int8_t temperature;
    uint8_t i;

    PCON0 |= 0x01; // set IDLE bit
    PCON0 = PCON0; // ... followed by a 3-cycle dummy instruction

    temperature = getTemperature();
    // set pwm according to temperature
    for(i=0;i<17;i++){
        if(temperature <= temp_pwm_table[i].temp) {
            setPWM(i);
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
  
  setPWM(0); // set minimum speed

  getTemperature(); // initialize ADC

  while(1){

      main_routine();
	}

}
