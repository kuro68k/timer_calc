// timer_calc.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdint.h>
#include <math.h>

#define CPU_FREQ	16000000UL
#define	PER_MAX		0xFFFF

const uint16_t prescalers[] = { 1, 2, 4, 8, 64, 256, 1024 };

void calc_timer(float freq)
{
	uint32_t	cycles;
	uint32_t	per;
	uint32_t	lowest_error = UINT32_MAX;
	int16_t		best_prescaler = -1;
	uint16_t	best_per = 0;

	cycles = CPU_FREQ / freq;

	// find best prescaler
	for (int i = 0; i < (sizeof(prescalers) / sizeof(uint16_t)); i++)
	{
		per = cycles / prescalers[i];
		per--;
		if (per > PER_MAX)	// unusable
			continue;

		uint32_t error;
		error = abs((int32_t)cycles - (int32_t)((per + 1) * prescalers[i]));
		if (error < lowest_error)
		{
			lowest_error = error;
			best_prescaler = prescalers[i];
			best_per = per;
		}
	}

	float real_freq;
	float real_error;
	real_freq = (best_per + 1) * best_prescaler;
	real_freq /= CPU_FREQ;
	real_freq = 1 / real_freq;
	real_error = 1 - (real_freq / freq);
	real_error *= 100;

	printf("%5.1f Hz:\tPER: %04X\tdiv: %3d\t%.5f Hz\t%+.5f%%\n", freq, best_per, best_prescaler, real_freq, real_error);
}

int _tmain(int argc, _TCHAR* argv[])
{
	for (uint8_t freq = 1; freq <= 120; freq++)
		calc_timer(freq);
	printf("\n");

	for (float freq = 1; freq < 15; freq += 0.5)
		calc_timer(freq);

	return 0;
}

