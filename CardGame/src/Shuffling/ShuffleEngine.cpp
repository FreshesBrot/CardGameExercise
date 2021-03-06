#include "ShuffleEngine.h"
#define RAND_INT int(RandomGenerator::getInstance()->get() * maxRand)

ShuffleEngine::ShuffleEngine(int shuffles) : shuffles(shuffles), shuffleCycle(shuffles) { 
	int maxRand = allShufflers.size();

	for (int i = 0; i < shuffles; i++)
		shuffleCycle[i] = allShufflers[RAND_INT];
}

void ShuffleEngine::ShuffleDeck(Deck& deck, uint32_t times) {
	for(uint32_t i = 0; i < times; i++)
		for (Shuffler* ptr : shuffleCycle)
			ptr->shuffleDeck(deck);
}

//const std::vector<Shuffler*> ShuffleEngine::allShufflers = {new CutShuffle(), new RiffleShuffle()};