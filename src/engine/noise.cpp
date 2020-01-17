#include "noise.hpp"
#include <cmath>

engine::noise::noise() {
	for (int y = 0; y < noiseHeight; y++)
		for (int x = 0; x < noiseWidth; x++) {
			noise_array[y][x] = (rand() % 32768) / 32768.0;
		}
}

engine::noise::~noise() {}

float engine::noise::smooth_noise(float x, float y) {
	//get fractional part of x and y
	float fractX = x - int(x);
	float fractY = y - int(y);

	//wrap around
	int x1 = (int(x) + noiseWidth) % noiseWidth;
	int y1 = (int(y) + noiseHeight) % noiseHeight;

	//neighbor values
	int x2 = (x1 + noiseWidth - 1) % noiseWidth;
	int y2 = (y1 + noiseHeight - 1) % noiseHeight;

	//smooth the noise with bilinear interpolation
	float value = 0.0f;
	value += fractX * fractY * noise_array[y1][x1];
	value += (1 - fractX) * fractY * noise_array[y1][x2];
	value += fractX * (1 - fractY) * noise_array[y2][x1];
	value += (1 - fractX) * (1 - fractY) * noise_array[y2][x2];

	return value;
}

float engine::noise::turbulence(float x, float y, float size) {
	float value = 0.0f;
	float initial_size = size;

	while (size >= 1) {
		value += engine::noise::smooth_noise(x / size, y / size) * size;
		size /= 2.0;
	}

	return(128.0 * value / initial_size);
}
