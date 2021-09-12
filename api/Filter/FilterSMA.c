#include "FilterSMA.h"

void FilterSMA_Init(FilterSMA_t* _input, uint8_t _filter_factor_level) {
    if (_filter_factor_level > MAX_FILTER_LEVEL) {
        _filter_factor_level = MAX_FILTER_LEVEL;
    }

    _input->filter_factor_level = _filter_factor_level;
    _input->adc_average = 1;
}

uint32_t FilterSMA_GetValue(const FilterSMA_t* _input) {
    return (_input->adc_average >> _input->filter_factor_level);
}

void FilterSMA_AddSample(FilterSMA_t* _input, uint16_t _new_sample) {
    _input->adc_average -= _input->adc_average >> _input->filter_factor_level;
    _input->adc_average += _new_sample;
}