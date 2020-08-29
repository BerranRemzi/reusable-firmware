#include "FilterEMA.h"

void Filter_Init(Filter* _input, uint8_t _filter_factor_level) {
    if (_filter_factor_level > MAX_FILTER_LEVEL) {
        _filter_factor_level = MAX_FILTER_LEVEL;
    }

    _input->filter_factor_level = _filter_factor_level;
    _input->adc_average = 1;
}

uint32_t Filter_Read(const Filter* _input) {
    return (_input->adc_average >> _input->filter_factor_level);
}

void Filter_LoadSample(Filter* _input, uint16_t _new_sample) {
    _input->adc_average -= _input->adc_average >> _input->filter_factor_level;
    _input->adc_average += _new_sample;
}