#include "pch.h"
#include "../Filter.h"
#include "../Filter.c"

Filter adc;
uint32_t raw = 0;

TEST(Filter, ADC_Between_50_100) {

	Filter_Init(&adc, 2, 0);
	for (uint32_t i = 0; i < 5; i++) {
		raw = Filter_ReadAverage(&adc, 100);
	}

	//EXPECT_EQ(100, raw);
	EXPECT_TRUE(raw < 100 && raw > 50);
}

TEST(Filter, ADC_2500) {
	uint16_t newSample = 2500;
	Filter_Init(&adc, 2, 0);
	for (uint32_t i = 0; i < 30; i++) {
		raw = Filter_ReadAverage(&adc, newSample);
	}

	EXPECT_EQ(newSample, raw);
	//EXPECT_TRUE(raw < 100);
}

TEST(Filter, ADC_512) {
	uint16_t newSample = 512;
	Filter_Init(&adc, 2, 0);
	for (uint32_t i = 0; i < 30; i++) {
		raw = Filter_ReadAverage(&adc, newSample);
	}

	EXPECT_EQ(newSample, raw);
	//EXPECT_TRUE(raw < 100);
}

TEST(Filter, ADC_300) {
	uint16_t newSample = 300;
	Filter_Init(&adc, 2, 0);
	for (uint32_t i = 0; i < 30; i++) {
		raw = Filter_ReadAverage(&adc, newSample);
	}

	EXPECT_EQ(newSample, raw);
	//EXPECT_TRUE(raw < 100);
}
TEST(Filter, ADC_up_down) {
	uint16_t newSample = 300;
	Filter_Init(&adc, 2, 0);
	for (uint32_t i = 0; i < 30; i++) {
		raw = Filter_ReadAverage(&adc, newSample);
	}

	EXPECT_EQ(newSample, raw);
	for (uint32_t i = 0; i < 30; i++) {
		raw = Filter_ReadAverage(&adc, 10);
	}

	EXPECT_EQ(10, raw);

	//EXPECT_TRUE(raw < 100);
}

TEST(Filter, SineWaveFilter) {
	uint16_t newSample;
	uint16_t totalTime = 1;
	uint32_t totalCycle = totalTime * 1800;

	Filter_Init(&adc, 8, 0);

	for (uint16_t i = 0; i < totalCycle; i++) {
		double absSineValue = abs(sin(i*3.1415 * 10 / 180));
		newSample = uint16_t(absSineValue * 1000);
		raw = Filter_ReadAverage(&adc, newSample);
	}

	EXPECT_TRUE(raw < 640 && raw > 633);
	//EXPECT_EQ(637, raw);
}

TEST(Filter, HighPrecision) {
	uint16_t newSample = 300;
	Filter_Init(&adc, 3, 10);
	for (uint32_t i = 0; i < 50; i++) {
		raw = Filter_ReadAverage(&adc, newSample);
	}

	EXPECT_EQ(3000, raw);
}