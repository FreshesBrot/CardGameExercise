// CardGame - A test to see if i could make a interactive card game over the command line
// working period: 09/2020-10/2020
#pragma once
#include <iostream>
#include <new>


#include "src/IO/DeckLoader.h"
#include "src/Shuffling/ShuffleEngine.h"
#include "src/Commands/Parsing/CommandParser.h"
#include "src/Game/HigherGame.h"
#include "src/Commands/ParserFactory.h"
#include "src/Network/Client.h"

#define TESTING
#define COUT std::cout
#define NL std::endl


namespace globals {

	static int counter = 0;
	static int count = counter;
	
	static int countDiff = 0;
	
	
	static bool b_run = true;
	static bool b_greet = true;
}

//void* operator new(std::size_t size) {
//	globals::counter++;
//	return malloc(size);
//}


#define DECKFILE "deck.deckf"
#define CARDCODE(code) printf("0x%02X\n", code)


#ifndef TESTING
#pragma region Card/Deck Functions
void showHand(Hand& hand) {
	COUT << "Current Hand: " << NL;
	auto cards = hand.getCards();
	for (uint32_t i = 0; i < hand.getRemainingCards(); i++)
		COUT << cards[i].shortString() << " ";

	COUT << NL;
}

void drawDeck(Deck& deck) {
	int count = 12;
	while (!deck.isEmpty()) {
		COUT << deck.drawTopCard().shortString() << " " ;

		if (--count < 0) {
			COUT << NL;
			count = 12;
		}
	}

	COUT << NL;
}

void peekDeck(Deck& deck) {
	int count = 12;
	for (auto& c : deck) {
		COUT << c.shortString() << " ";

		if (--count < 0) {
			COUT << NL;
			count = 12;
		}
	}

	COUT << NL;
}
#pragma endregion


int main() {
	Token herlperMessage;

	using namespace globals;

	CommandParser parser = ParserFactory(3).putName("TopLevelParser").putCommand (
		//play command
		CommandFactory().putName("play").putDescription("Starts the HigherGame.").putFunction(
			Executor([&](Command&) -> void {
				Deck deck = Deck::defaultDeck();
				parser.suspend();
				HigherGame(std::move(deck)).start();
				parser.restart();
				b_greet = true;
			})
		)
	).putCommand(
		//help command
		CommandFactory().putName("help").putDescription("Prints the helper message. This message is also printed if"
														" an unknown command is given to the interpreter.").putFunction(
			Executor([&](Command&) -> void {
				COUT << parser.getHelperMessage() << NL;
			})
		)
	).putCommand(
		//exit command
		CommandFactory().putName("exit").putDescription("Exits and terminates the program").putFunction(
			Executor([&](Command&) -> void {
				COUT << "Goodbye!\n";
				b_run = false;
			})
		)
	).putCommand(
		//allocs command
		CommandFactory().putName("allocs").putDescription("Shows how many allocations total and since last call have been made.").putFunction(
			Executor([&](Command&) -> void {
					COUT << "Total allocations: " << counter << NL;
					countDiff = counter - count;
					COUT << "Total new allocations: " << countDiff << NL;
					count = counter;
				})
		)
	).finish();

	
	while (b_run) {

		if (b_greet) {
			COUT << "Welcome! Type \"play\" to play the HigherGame. Type \"help\" to view the currently active list of commands." << NL;
			b_greet = false;
		}

		try {
			parser.askInput();
		} catch (CommandException& e) {
			COUT << "Unknown command or bad syntax:" << NL << e.what() << NL;
			continue;
		}
	}

	COUT << "Press enter to exit the program!" << NL;
	std::cin.get();
}

#else
#include <chrono>

#include "../Protocol/Protocol.h"

class Timer {
public:
	Timer(double&& ratio = 1.0f, std::string&& measure = "micros") : ratio(std::move(ratio)), measure(std::move(measure)) {
		//get current time as a timepoint
		start = std::chrono::high_resolution_clock::now();
	};

	~Timer() {
		//on destruction, get current time as a timepoint
		auto end = std::chrono::high_resolution_clock::now();

		auto startTime = std::chrono::time_point_cast<std::chrono::microseconds>(start).time_since_epoch().count();
		auto endTime = std::chrono::time_point_cast<std::chrono::microseconds>(end).time_since_epoch().count();

		std::cout << "Total time: " << (endTime - startTime) * ratio << measure << NL;
	};
private:
	double ratio;
	std::string measure;
	std::chrono::time_point<std::chrono::steady_clock> start;

};

int main() {

	Deck deck = Deck::defaultDeck();

	COUT << "Measuring CutShuffle.." << NL;
	{
		Timer t;
		CutShuffle().shuffleDeck(deck);

	}
	COUT << "Measuring RiffleShuffle.." << NL;
	{
		Timer t;
		RiffleShuffle().shuffleDeck(deck);
	}
	COUT << "Measuring ShuffleEngine with 2 total cycles.." << NL;
	{
		Timer t;
		ShuffleEngine().ShuffleDeck(deck, 2);
	}
	COUT << "Measuring ShuffleEngine with 100 total cycles in milliseconds.." << NL;
	{
		Timer t(1e-3,"ms");
		ShuffleEngine().ShuffleDeck(deck, 100);
	}
	COUT << "Measuring ShuffleEngine with 1000 total cycles in milliseconds .." << NL;
	{
		Timer t(1e-3,"ms");
		ShuffleEngine().ShuffleDeck(deck, 1000);
	}
	COUT << "Measuring ShuffleEngine with 10000 total cycles in seconds .." << NL;
	{
		Timer t(1e-6, "s");
		ShuffleEngine().ShuffleDeck(deck, 10000);
	}
}

#endif