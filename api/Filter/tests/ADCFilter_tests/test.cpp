#include "pch.h"
#include "../../FilterEMA.h"
#include "../../FilterEMA.c"
#include "../../FilterRMS.h"
#include "../../FilterRMS.c"

FilterEMA_t adc;
uint32_t raw = 0;

TEST(FilterEMA, ADC_Between_50_100) {
	uint16_t newSample = 100;
	FilterEMA_Init(&adc, 2);
	for (uint32_t i = 0; i < 5; i++) {
		FilterEMA_AddSample(&adc, newSample);
		raw = FilterEMA_Read(&adc);
	}

	//EXPECT_EQ(100, raw);
	EXPECT_TRUE(raw < 100 && raw > 50);
}

TEST(FilterEMA, ADC_2500) {
	uint16_t newSample = 2500;
	FilterEMA_Init(&adc, 2);
	for (uint32_t i = 0; i < 30; i++) {
		FilterEMA_AddSample(&adc, newSample);
		raw = FilterEMA_Read(&adc);
	}

	EXPECT_EQ(newSample, raw);
	//EXPECT_TRUE(raw < 100);
}

TEST(FilterEMA, ADC_512) {
	uint16_t newSample = 512;
	FilterEMA_Init(&adc, 2);
	for (uint32_t i = 0; i < 30; i++) {
		FilterEMA_AddSample(&adc, newSample);
		raw = FilterEMA_Read(&adc);
	}

	EXPECT_EQ(newSample, raw);
	//EXPECT_TRUE(raw < 100);
}

TEST(FilterEMA, ADC_300) {
	uint16_t newSample = 300;
	FilterEMA_Init(&adc, 2);
	for (uint32_t i = 0; i < 30; i++) {
		FilterEMA_AddSample(&adc, newSample);
		raw = FilterEMA_Read(&adc);
	}

	EXPECT_EQ(newSample, raw);
	//EXPECT_TRUE(raw < 100);
}
TEST(FilterEMA, ADC_up_down) {
	uint16_t newSample = 300;
	FilterEMA_Init(&adc, 2);
	for (uint32_t i = 0; i < 30; i++) {
		FilterEMA_AddSample(&adc, newSample);
		raw = FilterEMA_Read(&adc);
	}

	EXPECT_EQ(newSample, raw);
	for (uint32_t i = 0; i < 30; i++) {
		FilterEMA_AddSample(&adc, newSample);
		raw = FilterEMA_Read(&adc);
	}

	//EXPECT_EQ(10, raw);

	//EXPECT_TRUE(raw < 100);
}

TEST(FilterEMA, SineWaveFilter) {
	uint16_t newSample;
	uint16_t totalTime = 1;
	uint32_t totalCycle = totalTime * 1800;

	FilterEMA_Init(&adc, 8);

	for (uint16_t i = 0; i < totalCycle; i++) {
		double absSineValue = abs(sin(i * 3.1415 * 10 / 180));
		newSample = uint16_t(absSineValue * 1000);
		FilterEMA_AddSample(&adc, newSample);
		raw = FilterEMA_Read(&adc);
	}

	EXPECT_TRUE(raw < 640 && raw > 633);
	//EXPECT_EQ(637, raw);
}

TEST(FilterEMA, HighPrecision) {
	uint16_t newSample = 3000;
	FilterEMA_Init(&adc, 3);
	for (uint32_t i = 0; i < 100; i++) {
		FilterEMA_AddSample(&adc, newSample);
		raw = FilterEMA_Read(&adc);
	}

	EXPECT_EQ(3000, raw);
}

TEST(FilterRMS, SineWaveFilter) {
	FilterRMS_t adc;
	uint16_t newSample;
	uint16_t totalTime = 1;
	uint32_t totalCycle = totalTime * 1800;

	FilterRMS_Init(&adc, 8);

	for (uint16_t i = 0; i < totalCycle; i++) {
		double absSineValue = abs(sin(i * 3.1415 * 10 / 180));
		newSample = uint16_t(absSineValue * 1000);
		FilterRMS_AddSample(&adc, newSample);
		raw = FilterRMS_Read(&adc);
	}

	//EXPECT_TRUE(raw < 710 && raw > 700);
	EXPECT_EQ(707, raw);
}