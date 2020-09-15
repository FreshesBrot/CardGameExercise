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
#define NL "\n"


#ifndef TESTING

#define DECKFILE "deck.deckf"
#define CARDCODE(code) printf("0x%02X\n", code)
#define IO_CONTAINS(elem) IOParser::containsElement(cmd.options, Token(elem))
typedef IOParser::Tokens Tokens;
typedef IOParser::Token Token;

#pragma region Card/Deck Functions
void showHand(Hand& hand) {
	OUT << "Current Hand: " << NL;
	auto cards = hand.getCards();
	for (int i = 0; i < hand.getRemainingCards(); i++)
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
	for (auto& c : deck.getCards()) {
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
	IOParser interpreter("interpreter");
	std::vector<Command> commands;
	
	Command cmd1;
	Tokens opt1;
	opt1.push_back("-r");
	opt1.push_back("-v");
	cmd1.name = "foo";
	cmd1.options = opt1;

	Command cmd2(true);
	cmd2.name = "show";
	
	Command cmd3;
	cmd3.name = "exit";

	commands.push_back(cmd1);
	commands.push_back(cmd2);
	commands.push_back(cmd3);

	interpreter.setCommands(std::move(commands));
	IOReader io1("io1");
	io1.start();

	OUT << "Welcome!" << NL;

	while (true) {
		interpreter.askInput();

		if (!interpreter.isCommand())
			OUT << "unknown command or bad syntax." << NL;

		else {
			Command cmd = interpreter.getCommand();
			
			//procedure for foo
			if (cmd == "foo") {
				if (cmd.optCount) {
					if (IO_CONTAINS("-v"))
						continue;
					if (IO_CONTAINS("-r")) 
						OUT << "bar" << NL;
				}

				std::cout << "bar" << NL;

			}

			//procedure for show
			if (cmd == "show") {
				Tokens& options = cmd.options;
				Tokens& params = cmd.parameters;

				OUT << cmd.optCount << " Options:" << NL;
				for (auto& tk : options)
					OUT << tk << " ";
				OUT << NL;
				OUT << cmd.paramCount << " Paramters:" << NL;
				for (auto& tk : params)
					OUT << tk << " ";
				OUT << NL;
			}
			//procedure for exit
			if (cmd == "exit") break;
		}
	}

	OUT << "byebye" << NL;
}
#else

int main() {
	char test[20];
	for (int i = 0; i < 19; i++)
		test[i] = 'd';
	test[19] = 0x0;

	OUT << test << NL;

	test[9] = 0x0;
	OUT << test << NL;
}


#endif