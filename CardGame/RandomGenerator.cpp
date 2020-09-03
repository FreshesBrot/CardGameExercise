#include "RandomGenerator.h"

RandomGenerator* RandomGenerator::getInstance() {
	if (!instance)
		instance = new RandomGenerator();

	return instance;
}

float RandomGenerator::get() {
	std::default_random_engine engine;
	engine.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());

	return generator(engine);
}

RandomGenerator::RandomGenerator() : generator(0,1) { }

RandomGenerator* RandomGenerator::instance = nullptr;
