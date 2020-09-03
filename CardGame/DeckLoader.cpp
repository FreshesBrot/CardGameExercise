#include "DeckLoader.h"

DeckLoader::DeckLoader(FILENAME fileName, byte mode) : fileName(fileName), __mode(LoaderMode(mode)) { }

Deck DeckLoader::loadDeck() {
	if (!(__mode & 0x1))
		std::cout << "DeckLoader is not in loading mode!";

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
	if (!(__mode & 0x2))
		std::cout << "DeckLoader is not in loading mode!";

	DeckEncoder encoder(deck);
	encoder.encodeDeck();

	FileWriter fw(fileName);
	fw.Write();
	fw.writeData(encoder.getData(), encoder.getBlockSize());
	fw.Close();

	std::cout << "Deck saved to " << fileName << "\n";
}
