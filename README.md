# Word Dictionary Game

This project is a **Word Dictionary Game** developed as part of the SWE 101 Problem Solving in Software Engineering course (2024-2025 Fall). The program is written in **C++** and is designed to interact with a predefined dictionary file (`dictionary.txt`). The game provides options to play a translation game, list words, add new words, and exit the program.

## Features

1. **Starting Screen**:
   - **Start Playing**: Begin the word translation game.
   - **List Words**: Display all words in the dictionary file.
   - **Add New Word**: Add a new word to the dictionary (alphabetically).
   - **Exit**: Terminate the program.

2. **Game Mechanics**:
   - A random word is selected (Turkish or English), and the player chooses the correct translation from four options.
   - Scoring system:
     - +3 points for each correct answer.
     - -1 point for each incorrect answer.
   - End of game:
     - After 3 mistakes or 10 words, the total score is displayed.
     - Options to replay, return to the main menu, or exit.

3. **File Handling**:
   - `dictionary.txt` is used as the default word list.
   - New words are added to this file alphabetically.

4. **Prohibited Features**:
   - Usage of `goto` statements is strictly disallowed.

## Setup Instructions

  1. Copy the `dictionary.txt` file to the project folder.
  2. Compile the code using **Microsoft Visual Studio 2022**. If using a different compiler, ensure compatibility by testing before submission.
  3. Use relative file paths to ensure the program reads `dictionary.txt` correctly.

## How to Run

  1. Compile the C++ file.
  2. Run the executable to access the starting screen.
  3. Follow on-screen prompts to play the game or manage the dictionary.
