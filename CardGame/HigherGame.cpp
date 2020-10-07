#include "HigherGame.h"
//helper macro that wraps a executor function call into a single macro for readability
#define EXECUTOR(body) Executor([this](Command& cmd) -> void {body})

HigherGame::HigherGame(Deck& deck) : 
										Game(deck, Players()), numLives(defaultLives), numOfCards(0), b_greeting(true),
										discardPile(Deck::emptyDeck()), curCard(Card::Invalid()), curState(GameState::MENU)
{ 
	setup();
}

HigherGame::~HigherGame() { end(); Game::~Game(); }

void HigherGame::start() {
	b_isRunning = true;
	gameLoop();
}

void HigherGame::end() {
	b_isRunning = false;
}

void HigherGame::gameLoop() {
	//main game loop
	
	
	while (b_isRunning) {
		try {
			switch (curState) {
				//menu procedure
				case GameState::MENU: {
					if (b_greeting) {
						std::cout << "Welcome to the HigherGame! Type \"start\" to play the game.\n";
						b_greeting = false;
					}
					
					IOParser& menuParser = commandParser[0];
					menuParser.askInput();
					break;
					
				}
				//drawing procedure
				case GameState::DRAWING: {
					if (numOfCards++ == 0) {
						curCard = playingDeck.drawTopCard();
						std::cout << "The first card is: " << curCard.shortString() << "\n";
					}
					else 
						std::cout << "Card Nr. " << numOfCards << " is: " << curCard.shortString() << "\n";
					
					curState = GameState::GUESSING;
					
					std::cout << "Will the next card be higher or lower?\n";
					break;
				}
				//guessing procedure
				case GameState::GUESSING: {
					
					IOParser& gameParser = commandParser[1];
					gameParser.askInput();

					/*
					
					Command curCmd = gameParser.getCommand();
						
					if (curCmd == "guess") {
						Token& guess = curCmd.arguments[0];
						
						
						if (guess != "higher" && guess != "lower") {
							std::cout << guess << " is not a valid answer! Type \"higher\" or \"lower\" to guess!\n";
							continue;
						}

						bool isHigher = guess == "higher"; //will be 0 in other case
						
						//make sure to catch an empty deck
						try {
							Card nextCard = playingDeck.drawTopCard();
							std::cout << "The next card is " << nextCard.shortString() << "...";
						
							bool higherCard = Card::higherNumber(nextCard, curCard); //will be 0 if next card is not higher

							if (isHigher == higherCard) {
								std::cout << "Correct guess!\n";
							} else {
								std::cout << "Wrong guess.." << --numLives << " lives remaining..\n";
								if (!numLives) {
									std::cout << "Game Over! Maybe next time!\n Total number of cards: " << numOfCards << "\n";
									
									discardPile.addCard(curCard);
									discardPile.addCard(nextCard);
									playingDeck.mergeDecks(discardPile);
									curState = GameState::MENU;
									
									b_greeting = true;
									std::cout << "Press Enter to go back to the main menu.";
									std::cin.get();

									continue;
								}
							}
							
							discardPile.addCard(curCard);
							curCard = nextCard;
							curState = GameState::DRAWING;
							continue;

						} catch (DeckException& e) {
							std::cout << e.what() << " Time to shuffle the deck and keep going!\n";
							playingDeck.mergeDecks(discardPile);
							shuffleEngine.ShuffleDeck(playingDeck);
							continue;
						}

					}

					if (curCmd == "shuffle") {
						try {
							int shuffles = std::stoi(curCmd.arguments[0]);
							if (!shuffles) 
								std::cout << "Shuffling 0 times doesnt make sense! Guess higher or lower or shuffle at least once!\n";
							else {
								std::cout << "Shuffling deck " << curCmd.arguments[0] << " times before drawing!...\n";
								shuffleEngine.ShuffleDeck(playingDeck, shuffles);
							
								std::cout << "Deck is nice and shuffled!\n";
							}

						} catch (Exception& e) {
							std::cout << e.what() << "\n";
						}
						continue;
					}

					if (curCmd == "giveup") {
						discardPile.addCard(curCard);
						playingDeck.mergeDecks(discardPile);
						std::cout << "Lets restart then...\n";
						curState = GameState::MENU;
						b_greeting = true;
						continue;
					}

					if (curCmd == "help")
						std::cout << helperMessages[1] << "\n";
					*/

					break;
				}
			}

		} catch (CommandException& e) {
			std::cout << "Unknown command or bad syntax.\n" << e.what() << "\n";
		}
		catch (Exception& e) {
			std::cout << "Something went wrong!\n" << e.what() << "\n";
		}
	}
}


void HigherGame::setup() {

	Token startDescr = "Starts the HigherGame! Default amount of lives is 3.";
	Token optLivesDescr = "Sets a different number of lives for the next game. Expects one parameter containing the new number of lives.";
	Token quitDescr = "Quits the HigherGame and returns back to the Main Program Loop.";
	
	Token guessDescr = "Takes a guess, and expects either \"higher\" or \"lower\" as a paremeter.";
	Token shuffleDescr = "Shuffle the deck before guessing. Takes the number of shuffles as a parameter.";
	Token giveupDescr = "Give up this session of the HigherGame and go back to the menu.";

	Token helpDescr = "Prints the helper message.";

	auto parserMenu = ParserFactory(3).putName("HigherGameParserMenu").putCommand(

		//start command
		CommandFactory().putName("start").putDescription(&startDescr).putOption(
			OptionFactory().putName("-lives").putArguments({ ArgType::INT }).putDescription(&optLivesDescr)
		).putFunction(
			Executor([this](Command& curCmd) -> void {
				if (curCmd.optCount)
					numLives = Command::getArgument<int>(curCmd.getOption("-lives"), 0);
				else numLives = defaultLives;

				std::cout << "Lets play! Number of lives: " << numLives << ".\n";
				numOfCards = 0;
				Game::shuffleEngine.ShuffleDeck(playingDeck, 2);
				curState = GameState::DRAWING;
			})
		)
	).putCommand(
		//quit command
		CommandFactory().putName("quit").putDescription(&quitDescr).putFunction(
			Executor([this](Command&) -> void {
				std::cout << "Goodbye!\n";
				b_isRunning = false;
			})
		)
	).putCommand(
		//help command
		CommandFactory().putName("help").putDescription(&helpDescr).putFunction(
			Executor([this](Command&) -> void {
				std::cout << helperMessages[0]; //this in a lambda capture adds "this->" to members implicitly
			})
		)
	);

	auto parserGame = ParserFactory(4).putName("HigherGameParserGame").putCommand(
		//guess command
		CommandFactory().putName("guess").putDescription(&guessDescr).putArguments({ ArgType::STRING }).putFunction(
			Executor([this](Command& cmd) -> void {
				Token& guess = Command::getArgument<Token>(cmd, 0);

				if (guess != "higher" && guess != "lower") {
					std::cout << guess << " is not a valid answer! Type \"higher\" or \"lower\" to guess!\n";
					return;
				}

				bool isHigher = guess == "higher"; //will be 0 in other case

				//make sure to catch an empty deck
				try {
					Card nextCard = playingDeck.drawTopCard();
					std::cout << "The next card is " << nextCard.shortString() << "...";

					bool higherCard = Card::higherNumber(nextCard, curCard); //will be 0 if next card is not higher

					if (isHigher == higherCard) {
						std::cout << "Correct guess!\n";
					}
					else {
						std::cout << "Wrong guess.." << --numLives << " lives remaining..\n";
						if (!numLives) {
							std::cout << "Game Over! Maybe next time!\n Total number of cards: " << numOfCards << "\n";

							discardPile.addCard(curCard);
							discardPile.addCard(nextCard);
							playingDeck.mergeDecks(discardPile);
							curState = GameState::MENU;

							b_greeting = true;
							std::cout << "Press Enter to go back to the main menu.";
							std::cin.get();
							return;
						}
					}
					discardPile.addCard(curCard);
					curCard = nextCard;
					curState = GameState::DRAWING;
				
				} catch (DeckException& e) {
					std::cout << e.what() << " Time to shuffle the deck and keep going!\n";
					playingDeck.mergeDecks(discardPile);
					shuffleEngine.ShuffleDeck(playingDeck);
				}
			})
		)
	).putCommand(
		//shuffle command
		CommandFactory().putName("shuffle").putDescription(&shuffleDescr).putArguments({ ArgType::INT }).putFunction(
			Executor([this](Command& cmd) {
				int& shuffles = Command::getArgument<int>(cmd, 0);
				if (!shuffles)
					std::cout << "Shuffling 0 times doesnt make sense! Guess higher or lower or shuffle at least once!\n";
				else {
					std::cout << "Shuffling deck " << shuffles << " times before drawing!...\n";
					shuffleEngine.ShuffleDeck(playingDeck, shuffles);

					std::cout << "Deck is nice and shuffled!\n";
				}
			})
		)
	).putCommand(
		//giveup command
		CommandFactory().putName("giveup").putDescription(&giveupDescr).putFunction([this](Command&) -> void {
				discardPile.addCard(curCard);
				playingDeck.mergeDecks(discardPile);
				std::cout << "Lets restart then...\n";
				curState = GameState::MENU;
				b_greeting = true;
	
			})
	).putCommand(
		//help command
		CommandFactory().putName("help").putDescription(&helpDescr).putFunction(
			Executor([this](Command&) -> void {
				std::cout << helperMessages[1]; 
				})
		)
	);

	commandParser.push_back(parserMenu.finish());
	helperMessages.push_back(IOParser::HelperPrinter(commandParser[0]));
	commandParser.push_back(parserGame.finish());
	helperMessages.push_back(IOParser::HelperPrinter(commandParser[1]));

}