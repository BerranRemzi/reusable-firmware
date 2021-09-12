#include "FilterBA.h"

void FilterBA_Init(FilterBA_t* _input, uint8_t _filter_factor_level) {
    if (_filter_factor_level > MAX_FILTER_LEVEL) {
        _filter_factor_level = MAX_FILTER_LEVEL;
    }

    _input->filter_factor_level = _filter_factor_level;
    _input->adc_average = 1;
}

uint32_t FilterBA_GetValue(const FilterBA_t* _input) {
    int16_t average = _input->blockSum / _input->numSamples;

    ave->blockSum = 0;
    ave->numSamples = 0;

    return average;
}

void FilterBA_AddSample(FilterBA_t* _input, uint16_t _newSample) {
    _input->blockSum += _newSample;
    _input->numSamples++;
}