#pragma once

#include <glm/glm.hpp>

#include <random>

class Random {
public:
	static float Float(float min, float max) {
		float r = min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
		return r;
	}

	static glm::vec2 Vec2(float min, float max) {
		float r1 = Float(min, max);
		float r2 = Float(min, max);
		return glm::vec2(r1, r2);
	}

	static glm::vec3 Vec3(float min, float max) {
		float r1 = Float(min, max);
		float r2 = Float(min, max);
		float r3 = Float(min, max);
		return glm::vec3(r1, r2, r3);
	}

	static int Int(int min, int max) {
		std::random_device rd;
		std::mt19937 rng(rd());

		std::uniform_int_distribution<int> distribution(min, max);

		return distribution(rng);
	}
};