// CardGame - A test to see if i could make a interactive card game over the command line
// working period: 09/2020
#pragma once
#include <iostream>
//#define TESTING

#include "DeckLoader.h"
#include "ShuffleEngine.h"
#include "IOParser.h"
#include "HigherGame.h"
#define OUT std::cout
#define NL "\n"


#ifndef TESTING

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

int main() {
	Token playDescr = "Starts the HigherGame.";

	Token helpDescr = "Prints the helper message. This message is also printed if an unknown command is given to the interpreter.";

	Token exitDescr = "Exits and terminates the program";
	
	Token herlperMessage;

	bool b_run = true;

	IOParser parser = ParserFactory(3).putName("TopLevelParser").putCommand (
		//play command
		CommandFactory().putName("play").putDescription(&playDescr).putFunction( 
			Executor([](Command&) -> void {
				Deck deck;
				Game* curGame = new HigherGame(deck);
				curGame->start();
				delete curGame;
			})
		)
	).putCommand(
		//help command
		CommandFactory().putName("help").putDescription(&helpDescr).putFunction(
			Executor([&herlperMessage](Command&) -> void {
				OUT << herlperMessage << NL;
			})
		)
	).putCommand(
		//exit command
		CommandFactory().putName("exit").putDescription(&exitDescr).putFunction(
			Executor([&b_run](Command&) -> void {
				OUT << "Goodbye!\n";
				b_run = false;
			})
		)
	).finish();

	herlperMessage = IOParser::HelperPrinter(parser);

	OUT << "Welcome! Type \"play\" to play the HigherGame. Type \"help\" to view the currently active list of commands." << NL;

	while (b_run) {
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

}


#endif