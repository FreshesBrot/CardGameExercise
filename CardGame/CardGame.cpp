// CardGame.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
// Language Standard: C++17

#include <iostream>
#define OUT std::cout
//#define TESTING

#include "Hand.h"
#include "Deck.h"
#include "DeckLoader.h"
#include "ShuffleEngine.h"
#include "IOParser.h"
#include "HigherGame.h"
#define NL "\n"


#ifndef TESTING

#define DECKFILE "deck.deckf"
#define CARDCODE(code) printf("0x%02X\n", code)
typedef Command::Options Options;

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
	IOParser parser("TopLevelParser");
	Game* curGame = 0x0;

	COMMAND(play, 0);
	play.descr = "Starts the HigherGame.";
	COMMAND(help, 0);
	help.descr = "Prints the helper message. This message is also printed if an unknown command is given to the interpreter.";
	COMMAND(exit, 0);
	exit.descr = "Exits and terminates the program";
	
	Commands commands;
	commands.push_back(play);
	commands.push_back(help);
	commands.push_back(exit);
	

	parser.setCommands(std::move(commands));

	OUT << "Welcome! Type \"play\" to play the HigherGame. Type \"help\" to view the currently active list of commands." << NL;

	const std::string& helperMessage = IOParser::HelperPrinter(parser);

	while (true) {
		try {
			parser.askInput();

			Command cmd = parser.getCommand();
			
			if (cmd == "play") {
				Deck deck;
				curGame = new HigherGame(deck);
				curGame->start();
				delete curGame;
				continue;

			}

			if (cmd == "help") {
				OUT << helperMessage;
				continue;
			}

			if (cmd == "exit") break;

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