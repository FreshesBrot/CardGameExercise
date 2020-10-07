#include "DeckLoader.h"

DeckLoader::DeckLoader(FILENAME fileName) : fileName(fileName) { }

Deck DeckLoader::loadDeck() {
	
		FileReader fr(fileName);
		fr.Read();
		size_t blockSize = fr.getBlockSize();
		byte* code = new byte[blockSize];
		fr.readBlock(code, blockSize);
		fr.Close();

		DeckDecoder decoder(code,blockSize);
		std::cout << "Deck loaded from " << fileName << "\n";
		return decoder.Decode();

}

void DeckLoader::saveDeck(Deck& deck) {
	
	DeckEncoder encoder(deck);
	encoder.encodeDeck();

	FileWriter fw(fileName);
	fw.Write();
	fw.writeData(encoder.getData(), encoder.getBlockSize());
	fw.Close();

	std::cout << "Deck saved to " << fileName << "\n";
}
