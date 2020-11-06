# CardGameExercise
A C++ card game exercise that features a framework to implement Card Games that can be played on the command line.

**Working Period: 09/20 - 11/20**

This exercise includes:
 - Creating an easy framework to manipulate (e.g. shuffle) a deck of cards
 - Saving Cards and Decks in binary format to a file to be read in from the program again (or sent across a network)
 - Creating a framework to implement multiple different card games
 - Implementing several extensible command line interpreters 
 - Playing around with rvalue references and move semantics
 - Trying out multi-threading
 - Trying out the factory design pattern to help manage creation of commands for the command line

### Ideas for improvement
 - Use the asio library to implement multiplayer card games
 - Improve performance through better use of move semantics and optimized function calls

### A big Networking Update is underway! Network Architecture is being worked on.

## Contents

The src folder includes the following sub-folders:
 - **Cards** <p>
 This folder contains the framework for Cards, Decks and Hands.
 </p>
 - **Commands** <p>
 In this folder, everything related to commands and command parsing is contained.
 </p>
 - **Exceptions** <p>
 Folder containing Runtime Exceptions that are thrown by various classes.
 </p>
 - **Game** <p>
 In the future, this folder will hold the entry executable as well as all Card Games.
 </p>
 - **IO** <p>
 This folder contains everything related to user input and file writing/reading, as well as Network related classes in the future.
 </p>
 - **Shuffling** <p>
 Contains classes that can shuffle Decks, simulating real life shuffling methods.
 </p>
