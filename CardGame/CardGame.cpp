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

void* operator new(std::size_t size) {
	globals::counter++;
	return malloc(size);
}


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
				Deck deck;
				parser.suspend();
				HigherGame(deck).start();
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

#include "../Protocol/Protocol.h"
#include "Client.h"

enum TEST {
	ONE = 1,
	TWO
};

int main() {
	asio::io_context context;
	asio::io_context::work idleWork(context);

	std::thread worker = std::thread([&]() { context.run(); });

	//create a client instance with this context
	Client client(context);
	try {
		client.connect();
	} catch (std::exception& e) {
		COUT << e.what() << NL;
	}

	context.stop();
	if (worker.joinable()) worker.join();

	COUT << "Done!" << NL;

}

#endif