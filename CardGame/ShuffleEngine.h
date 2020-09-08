#pragma once
#include "Shuffler.h"
#include "CutShuffle.h"
#include "RiffleShuffle.h"
#include <vector>

//this class will shuffle a deck in randomly different ways
class ShuffleEngine {
public:

	ShuffleEngine(int shuffles = 5);
	ShuffleEngine(const ShuffleEngine&) = delete;
	ShuffleEngine(ShuffleEngine&&) = delete;

	//function that takes a reference to a deck that will be shuffled in random ways
	void ShuffleDeck(Deck& deck);

private:
	const int shuffles; // number of different shuffles that will happen
	std::vector<Shuffler*> shuffleCycle; //contains all shuffler objects

	static const std::vector<Shuffler*> allShufflers; //contains all possible shufflers
};
