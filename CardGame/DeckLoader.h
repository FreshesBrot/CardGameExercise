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
	DeckLoader(FILENAME fileName);

	Deck loadDeck();
	void saveDeck(Deck& deck);
	
private:
	FILENAME fileName; //the file name to load/save decks to
	
};

