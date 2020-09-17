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
#define IO_CONTAINS(elem) IOParser::containsOption(cmd.options, elem)
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

#pragma region Programs

void foo(Command& cmd) {
	if (cmd.optCount) {
		if (IO_CONTAINS("-v"))
			return;
		if (IO_CONTAINS("-r")) {
			TokenVector parameters = cmd.getOption("-r").parameters;
			for (int i = 0; i < std::stoi(parameters[0]); i++)
				OUT << "bar" << NL;
			return;
		}
	}

	std::cout << "bar" << NL;

}

void show(Command& cmd) {
	Options& options = cmd.options;
	TokenVector& params = cmd.parameters;

	OUT << cmd.optCount << " Options:" << NL;
	for (auto& tk : options)
		OUT << tk.name << ", ";
	OUT << NL;
	OUT << cmd.paramCount << " Paramters:" << NL;
	for (auto& tk : params)
		OUT << tk << " ";
	OUT << NL;
}

void save(Command& cmd) {
	Deck deck;
	using LdMode = DeckLoader::LoaderMode;
	DeckLoader saver(DECKFILE, LdMode::SAVE);

	if (IO_CONTAINS("-s")) {
		ShuffleEngine engine;
		engine.ShuffleDeck(deck);
	}

	saver.saveDeck(deck);
}

void load(Command& cmd) {
	using LdMode = DeckLoader::LoaderMode;
	DeckLoader loader(DECKFILE, LdMode::LOAD);
	Deck deck = loader.loadDeck();

	if (IO_CONTAINS("-s"))
		peekDeck(deck);
}

#pragma endregion


int main() {
	IOParser interpreter("interpreter");
	std::vector<Command> commands;
	
	Command cmd1(0);
	Options opt1;
	opt1.push_back({ "-r",1 }); //repeat bar n times
	opt1.push_back({ "-v",0 }); //dont respond
	cmd1.name = "foo";
	cmd1.options = std::move(opt1);

	Command cmd2(0,true);
	cmd2.name = "show";
	
	Command cmd3(0);
	cmd3.name = "exit";

	Command cmd4(0);
	Options opt2;
	cmd4.name = "save";
	opt2.push_back({"-s",1});
	cmd4.options = std::move(opt2);

	Command cmd5(1); //takes (!relative!) path to the file
	Options opt3;
	cmd5.name = "load";
	opt3.push_back({"-s",0}); //peekDeck
	cmd5.options = std::move(opt3);

	commands.push_back(cmd1);
	commands.push_back(cmd2);
	commands.push_back(cmd4);
	commands.push_back(cmd5);
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
			if (cmd == "foo")
				foo(cmd);

			//procedure for show
			if (cmd == "show")
				show(cmd);

			//procedure for saving a deck
			if (cmd == "save")
				save(cmd);

			//procedure for loading a deck
			if (cmd == "load")
				load(cmd);

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