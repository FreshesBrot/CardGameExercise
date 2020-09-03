#pragma once
#include "DeckEncoder.h"
#include "DeckDecoder.h"
#include "FileReader.h"
#include "FileWriter.h"
#include <iostream>

//this class handles deck loading/storing from and to a file all by itself
class DeckLoader {
public:
	//initializes loading the deck specified by the filename. 
	DeckLoader(FILENAME fileName, byte mode);

	Deck loadDeck();
	void saveDeck(Deck& deck);
	
	//this enum holds the mode
	enum LoaderMode {
		LOAD = 1,
		SAVE = 2
	};

private:
	FILENAME fileName; //the file name to load/save decks to
	LoaderMode __mode; //stores the mode of the loader

};

