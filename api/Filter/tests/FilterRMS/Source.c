#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "../../FilterRMS.h"

void PrintData(const uint32_t _input[], uint8_t _size);
void SineWaveFilter(void);


int main(void) {

    SineWaveFilter();

    return 0;
}

#define FILTER_FACTOR_LEVEL 8
#define PRINT_SIZE 1720
void SineWaveFilter(void) {
    FilterRMS_t adc;

    uint16_t totalTime = 1;
    uint32_t totalCycle = totalTime * 1800;
    uint32_t buffer[3];
    uint32_t output = 0;
    uint16_t input;

    FilterRMS_Init(&adc, FILTER_FACTOR_LEVEL);
    for (uint16_t i = 0; i < totalCycle; i++) {

        double absSineValue = sin(i * 3.1415 * 10 / 180);
        input = abs((int32_t)(absSineValue * 1000.0));

        FilterRMS_AddSample(&adc, input);
        output = FilterRMS_Read(&adc);

        buffer[0] = input;
        buffer[1] = output;
        if (i > PRINT_SIZE) {
            PrintData(buffer, 2);
        }
    }
}

void PrintData(const uint32_t _input[], uint8_t _size) {
    static uint16_t line = 0;
    printf("%d,", line);
    line++;
    for (uint8_t i = 0; i < _size; i++) {
        printf("%d", _input[i]);
        if (i < _size - 1) {
            printf(",");
        }
        else {
            printf("\n");
        }
    }
}