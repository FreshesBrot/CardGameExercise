#include "HigherGame.h"
//helper macro that encapsulates a function within the while block to continue later
#define IF_CMD(str,body) if(curCmd == str) {body continue;}

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

					Command curCmd = menuParser.getCommand();
					
					
					if (curCmd == "start") {
						try {
							if (curCmd.optCount) {
								numLives = std::stoi(curCmd.getOption("-lives").parameters[0]);
							} else numLives = defaultLives;
						} catch (Exception& e) {
							std::cout << e.what() << "\n";
							std::cout << "Option parameter for \"-lives\" expected an Integer, but got \"" << curCmd.getOption("-lives").parameters[0];
						}
						std::cout << "Lets play! Number of lives: " << numLives << ".\n";
						numOfCards = 0;
						Game::shuffleEngine.ShuffleDeck(playingDeck, 2);
						curState = GameState::DRAWING;
					}

					if (curCmd == "quit") {
						std::cout << "Goodbye!\n";
						b_isRunning = false;
						return;
					}

					if (curCmd == "help")
						std::cout << helperMessages[0] << "\n";

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
					
					Command curCmd = gameParser.getCommand();
						
					if (curCmd == "guess") {
						Token& guess = curCmd.parameters[0];
						
						
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
							int shuffles = std::stoi(curCmd.parameters[0]);
							if (!shuffles) 
								std::cout << "Shuffling 0 times doesnt make sense! Guess higher or lower or shuffle at least once!\n";
							else {
								std::cout << "Shuffling deck " << curCmd.parameters[0] << " times before drawing!...\n";
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

					break;
				}
			}

		} catch (CommandException& e) {
			std::cout << "Unknown command or bad syntax.\n" << e.what() << "\n";
			continue;
		}
		catch (Exception& e) {
			std::cout << "Something went wrong!\n" << e.what() << "\n";
		}
	}
}

void HigherGame::setup() {
	COMMAND(start, 0); //start the game
	start.descr = "Starts the HigherGame! Default amount of lives is 3.";
	Option opt = { "-lives", 1 };
	opt.descr = "Sets a different number of lives for the next game. Expects one parameter containing the new number of lives.";
	start.options.push_back(opt); //amount of tries for this game
	COMMAND(quit, 0); //exit the game and return to the main loop
	quit.descr = "Quits the HigherGame and returns back to the Main Program Loop.";

	COMMAND(guess, 1); //used to guess the next card. takes "higher" or "lower" as parameters
	guess.descr = "Takes a guess, and expects either \"higher\" or \"lower\" as a paremeter.";
	COMMAND(shuffle,1); //shuffles the deck again. takes number of shuffles as a parameter
	shuffle.descr = "Shuffle the deck before guessing. Takes the number of shuffles as a parameter.";
	COMMAND(giveup,0); //give up and try again
	giveup.descr = "Give up this session of the HigherGame and go back to the menu.";
	
	COMMAND(help, 0); //prints the help menu. prints by default if wrong command is typed
	help.descr = "Prints the helper message.";

	Commands commandsMenu;
	Commands commandsGame;

	IOParser parserMenu("HigherGameParserMenu");
	IOParser parserGame("HigherGameParserGame");

	commandsMenu.push_back(start);
	commandsMenu.push_back(quit);
	commandsMenu.push_back(help);

	commandsGame.push_back(guess);
	commandsGame.push_back(shuffle);
	commandsGame.push_back(giveup);
	commandsGame.push_back(help);
	
	parserMenu.setCommands(std::move(commandsMenu));
	parserGame.setCommands(std::move(commandsGame));

	helperMessages.push_back(IOParser::HelperPrinter(parserMenu));
	helperMessages.push_back(IOParser::HelperPrinter(parserGame));

	GameStates gameStates;
	gameStates.push_back(std::move(parserMenu));
	gameStates.push_back(std::move(parserGame));

	commandParser = std::move(gameStates);
}