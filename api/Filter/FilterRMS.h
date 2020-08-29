/**
 * @file FilterEMA.h
 * @brief Exponential Moving Average (EMA). this header file will contain all required
 * definitions and basic utilities functions.
 *
 * @author Berran Remzi
 *
 * @date 18.02.2019
 */
#ifndef ADC_FILTER_H
#define ADC_FILTER_H

#include <stdint.h>

#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif

#define MAX_FILTER_LEVEL 20
#define MAX_PRECISION 100

	/**
	  Section: Global Variables Definitions
	 */
	typedef struct Filter {
		///This will hold the passed filter factor level value
		uint8_t filter_factor_level;
		///This will hold the themporary value for averaging
		uint32_t adc_average;	

		uint32_t sum_squares;
	} Filter;


	/**
	 * This method will be used for initialize ADCFiler module.
	 * @author Berran Remzi
	 * @param _input The struct that contains adc_average and filterLevel
	 * @param _filter_factor_level Value for averaging level of ADC filter
	 * @date 18.02.2019
	 */
	void Filter_Init(Filter * _input, uint8_t _filter_factor_level);


	/**
	 * This method will be used for calculating average value of ADC reading.
	 *
	 * @param _input The struct that contains adc_average and filterLevel
	 * @param _new_sample New value of ADC mesurement
	 * @return Function returns averaged value
	 *
	 * <b>Example showing how to use Filter API</b>
	 * @code
	 * #include "mcc_generated_files/mcc.h"
	 * #include <ADCFilter/ADCFilter.h>
	 *
	 * Filter adc1;
	 * void main(void) {
	 *
	 *        SYSTEM_Initialize();
	 *
	 *        Filter_Init(&adc1, 5);
	 *
	 *        uint16_t new_sample;
	 *        uint32_t average;
	 *        while (1) {
	 *            new_sample = ADC_GetConvesation(ADC1);
	 *            average = Filter_Read(&adc1, new_sample);
	 *            __delay_ms(100);
	 *        }
	 * }
	 * @endcode
	 * @author Berran Remzi.
	 * @date 18.02.2019
	 */
	uint32_t Filter_Read(Filter *_input);

	void Filter_LoadSample(Filter* _input, uint16_t _new_sample);

#ifdef __cplusplus  // Provide C++ Compatibility

}

#endif

#endif // ADC_FILTER_H
/**
 End of File
 */
