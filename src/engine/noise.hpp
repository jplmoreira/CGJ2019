#pragma once

#define noiseWidth 128
#define noiseHeight 128

namespace engine {
	class noise {
		float noise_array[noiseHeight][noiseWidth]; //the noise array

		noise();
		~noise();

		float smooth_noise(float x, float y);
		float turbulence(float x, float y, float size);
	};
}