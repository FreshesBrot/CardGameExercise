#pragma once
#include <random>
#include <chrono>

//this class is used as a singleton to return a random number
class RandomGenerator {
public:
	//returns the single instance of the randomizer from the heap.
	static RandomGenerator* getInstance();
	
	//returns a random float value.
	float get();

private:
	//intializes the random engine
	RandomGenerator();
	~RandomGenerator() {};
	RandomGenerator(const RandomGenerator&) = delete;
	RandomGenerator(RandomGenerator&&) = delete;


	static RandomGenerator* instance;

	const std::default_random_engine engine;
	const std::uniform_real_distribution<float> generator;

};

