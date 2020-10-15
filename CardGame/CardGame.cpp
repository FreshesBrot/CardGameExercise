// CardGame - A test to see if i could make a interactive card game over the command line
// working period: 09/2020-10/2020
#pragma once
#include <iostream>
#include <new>
//#define TESTING

#include "DeckLoader.h"
#include "ShuffleEngine.h"
#include "IOParser.h"
#include "HigherGame.h"
#define OUT std::cout
#define NL std::endl


static int counter = 0;
void* operator new(std::size_t size) {
	counter++;
	return malloc(size);
}


#define DECKFILE "deck.deckf"
#define CARDCODE(code) printf("0x%02X\n", code)

#pragma region Card/Deck Functions
void showHand(Hand& hand) {
	OUT << "Current Hand: " << NL;
	auto cards = hand.getCards();
	for (uint32_t i = 0; i < hand.getRemainingCards(); i++)
		OUT << cards[i].shortString() << " ";

	OUT << NL;
}

void drawDeck(Deck& deck) {
	int count = 12;
	while (!deck.isEmpty()) {
		OUT << deck.drawTopCard().shortString() << " " ;

		if (--count < 0) {
			OUT << NL;
			count = 12;
		}
	}

	OUT << NL;
}

void peekDeck(Deck& deck) {
	int count = 12;
	for (auto& c : deck) {
		OUT << c.shortString() << " ";

		if (--count < 0) {
			OUT << NL;
			count = 12;
		}
	}

	OUT << NL;
}
#pragma endregion

void countAllocs() {


}

#ifndef TESTING
int main() {
	Token herlperMessage;

	bool b_run = true;
	bool b_greet = true;
	int count = counter;
	int countDiff = 0;

	IOParser parser = ParserFactory(3).putName("TopLevelParser").putCommand (
		//play command
		CommandFactory().putName("play").putDescription("Starts the HigherGame.").putFunction(
			Executor([&parser, &b_greet](Command&) -> void {
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
			Executor([&herlperMessage](Command&) -> void {
				OUT << herlperMessage << NL;
			})
		)
	).putCommand(
		//exit command
		CommandFactory().putName("exit").putDescription("Exits and terminates the program").putFunction(
			Executor([&b_run](Command&) -> void {
				OUT << "Goodbye!\n";
				b_run = false;
			})
		)
	).putCommand(
		CommandFactory().putName("allocs").putDescription("Shows how many allocations total and since last call have been made.").putFunction(
			Executor([&count,&countDiff](Command&) -> void {
					OUT << "Total allocations: " << counter << NL;
					countDiff = counter - count;
					OUT << "Total new allocations: " << countDiff << NL;
					count = counter;
				})
		)
	).finish();

	herlperMessage = IOParser::HelperPrinter(parser);

	
	while (b_run) {

		if (b_greet) {
			OUT << "Welcome! Type \"play\" to play the HigherGame. Type \"help\" to view the currently active list of commands." << NL;
			b_greet = false;
		}

		try {
			parser.askInput();
		} catch (CommandException& e) {
			OUT << "Unknown command or bad syntax:" << NL << e.what() << NL;
			continue;
		}
	}

	OUT << "Press enter to exit the program!" << NL;
	std::cin.get();
}

#else

int main() {
	Deck deck;
	OUT << "Allocations:\n " << counter << NL;

	CutShuffle shuffler;
	shuffler.shuffleDeck(deck);

	peekDeck(deck);

	OUT << counter << NL;

}


#endif