#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <windows.h>

using namespace std;

enum enStartingMenu {
    _startPlaying = 1, //Starts playing the game
    _listWord, //Lists all words on the screen in the file
    _addNewWord, //Creates us to add a new word to the dictionary
    _exitMenu//Terminates the program 
};
enum enEndGameMenu {
    _replayTheGame = 1, //Starts playing the game  again
    _perviousMenu, //Turns back to the starting screen  
    __exitMenu //Terminates the program 
};

const int ARRSIZE = 75;
const short COLUMN = 2;
const short ANSWERS_COUNT = 4;

// a procedure to print '\t' for specific amount taken as parameter
void setTabs(int);

// general procedure to print 2D array's element.
void print2DimArray(string arr[][COLUMN], int arrRow, int arrColumn);

// general procedure to print a header w/ main text only.
void printHeader(string);

// general procedure to print a header w/ main text & sub text.
void printTwoLineHeader(string, string);

// a procedure to make array's semi-dynamic. 
void addElement(string str, string arr[], int& arrSize);

// a procedure to convert the text files line into array elements. 
void txtToArray(string& fileName, string arr[], int& arrSize);

// a procedure to divide the dictionary array into to arrays one for English language & Turkish language. 
void dividingDictionaryIntoTwo(string wordLists[], string arrEnglish[], string arrTurkish[], int WordListSize, int& wordsSize);

// a procedure to concatenate the two transitions in 2d array.
void convertWordTo2DimArray(string wordList[][::COLUMN], string arrEnglish[], string arrTurkish[], int WordListSize);

// a procedure uses two procedures (printHeader() & print2DimArray()) to print all the words in the 2 dimensional array
void listWords(string wordList[][COLUMN], int arrRow, int arrColumn);

// general function for reading number.
int readDigit(int from, int to, string message);

int generateRandom(int, int);

void generateTwoRandomIndex(int&, int&, int, int);

void startPlaying(string wordList[][2], int, int);

enStartingMenu startingScreen();

enStartingMenu startingMenuChoice();

void selectAWord(string wordList[][::COLUMN], int&, int&, int, int, string&, string&);

void generateAnswers(string answers[], int answersCount, string wordList[][::COLUMN], int& row, int& column, int arrRow, int arrColumn, string& word, string& meaning);

bool checkAnswer(string, string);

void printQuestion(string, string answers[], int, int);

void addNewWord(string wordList[][COLUMN], int& arrRow, int arrColumn, string& fileName);

void exitGame();

void readEngAndTur(string& englishWord, string& turkishWord);

void shiftElements(string wordList[][COLUMN], int arrRow, int arrColumn, int insertIndex);

int findInsertIndex(string wordList[][COLUMN], int arrRow, int arrColumn, string englishWord);

void addWordToArray(string wordList[][COLUMN], int& arrRow, int arrColumn, string& englishWord, string& turkishWord, int insertIndex);

void updateTxtFile(string& fileName, string wordList[][COLUMN], int& arrRow, int arrColumn);

void printRoundResult(bool isCurrect, string questionWord, string wordMeaning);

void winOrLoseCounter(bool isCurrect, int& score, int& falseCount);

void printRound(int roundNumber, string wordList[][::COLUMN], int arrRow, int arrColumn, int& score, int& falseCount);

enEndGameMenu gameOverMenuChoice();

void gameOverScreen(string wordList[][2], int arrRow, int arrColumn);

void gamePlay();

bool isItAllLetters(string word);

int main() {

    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    srand(time(NULL));

    gamePlay();

}

void setTabs(int tabCount) {

    // print's tabs for a  certain amount.
    for (int i = 0; i < tabCount; i++)
        cout << '\t';

}

void printHeader(string headerTextHead) {

    string divider, headerText;

    /* a loop to formate the text into a letter than space etc.
    ex : input = "AMMAR" - > output = "A M M A R"
    */
    for (int i = 0; i < headerTextHead.length(); i++) {
        headerText += headerTextHead[i];
        headerText += ' ';
    }

    // adds tow spaces to each side ex : "  A M M A R  "
    headerText = "  " + headerText + "  ";

    /* if statmemnet to check if the final formatted text length is even or odd
    if it's odd it take's (63 * '-' + \0 = [64]) to match the formating
    if it's odd it take's (62 * '-' + \0 = [63]) to match the formating
    */
    if (headerText.length() % 2 == 1)
        divider = "---------------------------------------------------------------"; // 63 * '-' + \0 = [64]
    else
        divider = "--------------------------------------------------------------";  // 62 * '-' + \0 = [63]

    // while the text length is smaller than the length of divider add '-' symbol to each side of the text.
    while (headerText.length() < divider.length())
        headerText = "-" + headerText + "-";

    setTabs(3);
    cout << divider << endl;
    setTabs(3);
    cout << headerText << endl;
    setTabs(3);
    cout << divider << endl;
}

// This function is the same as printHeader function but to print 2 text line insted of one
void printTwoLineHeader(string correctOrFalse, string textSecondLine) {

    string divider, firstLine, secondLine;

    // a loop to formate the text into a letter than space etc.
    for (int i = 0; i < correctOrFalse.length(); i++) {
        firstLine += correctOrFalse[i];
        firstLine += ' ';
    }

    firstLine = "  " + firstLine + "  ";

    secondLine = "  " + textSecondLine + "  ";

    if (firstLine.length() % 2 == 1)
        divider = "---------------------------------------------------------------"; // 63 * '-' + \0 = [64]
    else
        divider = "--------------------------------------------------------------";  // 62 * '-' + \0 = [63]

    while (firstLine.length() < divider.length())
        firstLine = "-" + firstLine + "-";

    while (secondLine.length() < divider.length())
        secondLine = "-" + secondLine + "-";

    setTabs(3);
    cout << divider << endl;
    setTabs(3);
    cout << firstLine << endl;
    setTabs(3);
    cout << divider << endl;
    setTabs(3);
    cout << secondLine << endl;
    setTabs(3);
    cout << divider << endl;
}

void convertWordTo2DimArray(string wordList[][::COLUMN], string arrEnglish[], string arrTurkish[], int WordListSize) {

    // loop to go through all rows
    for (int i = 0; i < WordListSize; i++) {
        // loop to go through all columns
        for (int j = 0; j < ::COLUMN; j++) {

            // if statement to take all english words to the first column
            if (j == 0)
                wordList[i][j] = arrEnglish[i];

            // if statement to take all turkish words to the first column
            if (j == 1)
                wordList[i][j] = arrTurkish[i];

        }

    }
}

void print2DimArray(string arr[][COLUMN], int arrRow, int arrColumn) {

    /*
    goes through all eng words first to determine the longest word length
    then goes to turkish and do the same.
    */
    int maxColWidth[COLUMN] = { 0 }; // declared 0 at first to get the max
    for (int i = 0; i < arrColumn; i++) // go through columns
        for (int j = 0; j < arrRow; j++) // go through rows
            if (maxColWidth[i] < arr[j][i].length()) //like max func
                maxColWidth[i] = arr[j][i].length();

    //loop to go through all rows 
    for (int i = 0; i < arrRow; i++) {

        setTabs(2);
        cout << "[" << i + 1 << "]";

        /*if...else statements for formating
        if i < 9 so it has one digit so I add more spaces to mach if number has more then one digit
        ex :
        "[1]   :  "
        ...
        ...
        "[100] :  "

        */
        if (i < 9)
            cout << "   :   ";
        else if (i < 99)
            cout << "  :   ";
        else if (i < 999)
            cout << " :   ";
        else
            cout << ":  ";

        // loop to  go through all columns
        for (int j = 0; j < arrColumn; j++) {
            // if statement if we arr in the first column right setw for the biggest word length we found in this column. 
            if (j == 0)
                cout << right << setw(maxColWidth[j]) << arr[i][j];
            // if statement if we arr in the second column left setw for the biggest word length we found in this column. 
            else
                cout << left << setw(maxColWidth[j]) << arr[i][j];
            // if we are not at the last word add '|' for formating
            if (j != arrColumn - 1) cout << " | ";
        }
        cout << endl;
    }
}

void txtToArray(string& fileName, string arr[], int& arrSize) {

    ifstream inputFile(fileName);
    string line;
    arrSize = 0;

    // a loop to go through all lines
    while (getline(inputFile, line)) {

        // adding each line to the choosen array in the procedure.
        addElement(line, arr, arrSize);

    }

}

void dividingDictionaryIntoTwo(string wordLists[], string arrEnglish[], string arrTurkish[], int WordListSize, int& wordsSize) {

    int turkishSize, englishSize;

    turkishSize = englishSize = wordsSize = 0;

    // a loop goes through all elements in the big array
    for (int i = 0; i < WordListSize; i++) {

        string word = wordLists[i]; // assign the line to a new variable called word
        string tempWord = ""; // a temporary to use to divide the line
        string englishWord = "";
        string turkishWord = "";

        // a loop to go through all letters in the word variable (the line in the big array)
        for (int j = 0; j < word.length(); j++) {

            // if we haven't came to the spacial char ':' add the word to tempWord variable
            if (word[j] != ':')
                tempWord += word[j];
            /*if we came to the spacial char ':' add the tempWord to englishWord variable
            as the file was the word befor char ':' is english
            */
            if (word[j] == ':') {
                englishWord = tempWord;
                /*we empty the temp word since the loop will continue adding the letters after the char ':'
                to the tempWord variable which is the turkish word so when we finish the inner loop we will
                have in the tempWord the turkishWord
                */
                tempWord = "";
            }

        }

        //than assign the tempWord to turkishWord variable
        turkishWord = tempWord;

        addElement(englishWord, arrEnglish, englishSize); // add the englishWord we got to the english words array
        addElement(turkishWord, arrTurkish, turkishSize); // add the turkishWord we got to the turkish words array

    }

    wordsSize = englishSize; // or it could be equal to turkishSize as they are have the same value.

}

enStartingMenu startingMenuChoice() {

    int choice;

    setTabs(3);
    cout << "[1] " << "Start playing." << endl;
    setTabs(3);
    cout << "[2] " << "List words." << endl;
    setTabs(3);
    cout << "[3] " << "Add new word." << endl;
    setTabs(3);
    cout << "[4] " << "Exit." << endl;
    choice = readDigit(enStartingMenu::_startPlaying, enStartingMenu::_exitMenu, "Please choose one : ");

    return (enStartingMenu)choice;

}

enStartingMenu startingScreen() {

    printHeader("STARTING MENU");

    return startingMenuChoice();

}

// a function to generate a random number in range got as parameter
int generateRandom(int from, int to) {

    return rand() % (to - from + 1) + from;

}

void addElement(string str, string arr[], int& arrSize) {

    arr[arrSize] = str;
    arrSize++;

}

// a function to generate to random indexes to use it to ask a random word in the game
void generateTwoRandomIndex(int& row, int& column, int arrRow, int arrColumn) {

    row = generateRandom(0, arrRow - 1);
    column = generateRandom(0, arrColumn - 1);

}

void selectAWord(string wordList[][::COLUMN], int& row, int& column, int arrRow, int arrColumn, string& word, string& meaning) {

    // generate two random indexes
    generateTwoRandomIndex(row, column, arrRow, arrColumn);

    // the word to ask assigned randomly
    word = wordList[row][column];


    /*if the random number in column is (0) which means we are in the first column
    So in english words the the meaning of this word will be the second column and
    the same row of the englishWord
    */
    if (column == 0)
        meaning = wordList[row][1];
    // if it's not first column the it a turkish word and does the same as before
    else
        meaning = wordList[row][0];

}

// boolean function checks if the players choice is the same as the currect answer
bool checkAnswer(string playerChoice, string currectAnswer) {

    return playerChoice == currectAnswer;

}

void printQuestion(string questionWord, string answers[], int answersCount, int questionNumber) {

    setTabs(3);
    cout << "[" << questionNumber << "] What does (" << questionWord << ") means ?" << endl;

    // loop to print the answers from the (answers) array
    for (int i = 1; i <= answersCount; i++) {
        setTabs(4);
        cout << setw(3) << "(" << i << ") " << answers[i - 1] << endl;
    }

}

// a function forces player to enter only digit [0,9] or he goes in infinite loop
int readDigit(int from, int to, string message) {

    string charNumber;
    int number;

    do {

        setTabs(3);
        cout << message << endl;
        setTabs(3);
        cin >> charNumber;

        number = charNumber[0] - '0';

    } while ((number < from || number > to) && (charNumber[0] < from + '0' || charNumber[0] > to + '0') && (charNumber.length() != 2));

    return number;

}

// a function to generate a random answers
void generateAnswers(string answers[], int answersCount, string wordList[][::COLUMN], int& row, int& column, int arrRow, int arrColumn, string& word, string& meaning) {

    // loop to fill the answers array with random answers whither tur or eng depending at the question word column
    for (int i = 0; i < answersCount; i++) {

        answers[i] = wordList[generateRandom(0, arrRow - 1)][column == 0 ? 1 : 0];

    }

    // assign the currect answer to a random index in the answers array
    answers[generateRandom(0, answersCount - 1)] = meaning;

}

// a function to check if all letter in the word are not numbers
bool isItAllLetters(string word) {
    for (int i = 0; i < word.length(); i++)
        if (isdigit(word[i]))
            return 0;

    return 1;
}

void readEngAndTur(string& englishWord, string& turkishWord) {

    // do...while loop to read the word if its empty or if it has number asks the player to enter a new word
    do {
        setTabs(3);
        cout << "Please enter the english word : ";
        cin >> englishWord;
    } while (englishWord.empty() || !isItAllLetters(englishWord));

    // do...while loop to read the word if its empty or if it has number asks the player to enter a new word
    do {
        setTabs(3);
        cout << "Please enter the turkish word : ";
        cin >> turkishWord;
    } while (turkishWord.empty() || !isItAllLetters(turkishWord));

}

void shiftElements(string wordList[][COLUMN], int arrRow, int arrColumn, int insertIndex) {

    for (int i = arrRow; i > insertIndex; i--) {
        wordList[i][0] = wordList[i - 1][0]; // shifting the english words 
        wordList[i][1] = wordList[i - 1][1]; // shifting the turkish words

    }
}

// finds the index to add the word in the alphabetically order
int findInsertIndex(string wordList[][COLUMN], int arrRow, int arrColumn, string englishWord) {

    int insertIndex = arrRow; // we assigned the biggest value could an index in this array be

    for (int i = 0; i < arrRow; i++)
        /*
        this condition here checks if the eng word is smaller or bigger (alphabetically)

        - example :

          "apple"  < "apricot" = true -> because it's equal not smaller (a = a) (p = p)(p < r)
          "apple"  < "banana"  = false -> because it's smaller (a > b)
          "banana" < "apple"   = true -> because it's bigger (b < a)

        */
        if (englishWord < wordList[i][0]) { // used 0 as (n) because the english word are all in column 1 = index(0)
            insertIndex = i;
            break;
        }

    return insertIndex;

}

void addWordToArray(string wordList[][COLUMN], int& arrRow, int arrColumn, string& englishWord, string& turkishWord, int insertIndex) {

    wordList[insertIndex][0] = englishWord;
    wordList[insertIndex][1] = turkishWord;
    arrRow++;

}

// update the text file with the new array
void updateTxtFile(string& fileName, string wordList[][COLUMN], int& arrRow, int arrColumn) {

    ofstream updateFile(fileName);

    for (int i = 0; i < arrRow; i++) {

        updateFile << wordList[i][0] << ":" << wordList[i][1] << endl;

    }

    updateFile.close();

}

void addNewWord(string wordList[][COLUMN], int& arrRow, int arrColumn, string& fileName) {

    string englishWord, turkishWord;
    int insertIndex;


    readEngAndTur(englishWord, turkishWord);

    insertIndex = findInsertIndex(wordList, arrRow, arrColumn, englishWord);


    shiftElements(wordList, arrRow, arrColumn, insertIndex);

    addWordToArray(wordList, arrRow, arrColumn, englishWord, turkishWord, insertIndex);

    updateTxtFile(fileName, wordList, arrRow, arrColumn);

}

void printRoundResult(bool isCurrect, string questionWord, string wordMeaning) {

    string result;

    if (isCurrect)
        result = "Correct";
    else
        result = "False";

    printTwoLineHeader(result, questionWord + " = " + wordMeaning);

}

void winOrLoseCounter(bool isCurrect, int& score, int& falseCount) {

    if (isCurrect) {
        score += 3;
    }
    else {
        score -= 1;
        falseCount++;
    }

}

void printRound(int roundNumber, string wordList[][::COLUMN], int arrRow, int arrColumn, int& score, int& falseCount) {

    string questionWord, wordMeaning, answers[::ANSWERS_COUNT];
    int choosenAnswer, row, column;
    bool isCurrect;

    printHeader("QUESTION");

    selectAWord(wordList, row, column, arrRow, arrColumn, questionWord, wordMeaning);

    generateAnswers(answers, ::ANSWERS_COUNT, wordList, row, column, arrRow, ::COLUMN, questionWord, wordMeaning);

    printQuestion(questionWord, answers, ANSWERS_COUNT, roundNumber);

    choosenAnswer = readDigit(1, ANSWERS_COUNT, "Please choose an answer : ") - 1;

    isCurrect = checkAnswer(answers[choosenAnswer], wordMeaning);

    printRoundResult(isCurrect, questionWord, wordMeaning);

    winOrLoseCounter(isCurrect, score, falseCount);

}

enEndGameMenu gameOverMenuChoice() {

    int choice;

    setTabs(3);
    cout << "[1] " << "Replay the game." << endl;
    setTabs(3);
    cout << "[2] " << "Previous Menu." << endl;
    setTabs(3);
    cout << "[3] " << "Exit." << endl;

    choice = readDigit(enEndGameMenu::_replayTheGame, enEndGameMenu::__exitMenu, "Please choose one : ");

    return (enEndGameMenu)choice;

}

void exitGame() {

    system("cls");

}

void gameOverScreen(string wordList[][2], int arrRow, int arrColumn) {

    printHeader("GAME OVER");

    switch (gameOverMenuChoice())
    {
    case enEndGameMenu::_replayTheGame:
        startPlaying(wordList, arrRow, arrColumn);
        break;
    case enEndGameMenu::_perviousMenu:
        gamePlay();
        break;
    case enEndGameMenu::__exitMenu:
        exitGame();
        break;

    }

}

void startPlaying(string wordList[][2], int arrRow, int arrColumn) {

    int roundNumber = 1, score, falseCount;

    score = falseCount = 0;

    cout << "\n\n";
    printHeader("START PLAYING");

    do {

        printRound(roundNumber, wordList, arrRow, arrColumn, score, falseCount);
        roundNumber++;
        cout << "\n\n";

        // stop the game after 3 uncurrect answers or if the words asked number came to 10
    } while (falseCount < 3 && roundNumber <= 10);

    printHeader("SCORE  = " + to_string(score));

}

void gamePlay() {

    string fileName = "dictionary.txt";
    string dictionaryList[::ARRSIZE], wordList[::ARRSIZE][::COLUMN], arrEng[::ARRSIZE], arrTur[::ARRSIZE];
    int dictionaryListSize, wordSize = 0;
    
    //convert the text file array taking each line as element
    txtToArray(fileName, dictionaryList, dictionaryListSize);

    dividingDictionaryIntoTwo(dictionaryList, arrEng, arrTur, dictionaryListSize, wordSize);

    convertWordTo2DimArray(wordList, arrEng, arrTur, wordSize);

    enStartingMenu userChoice;

    userChoice = startingScreen();

    // the starting menu choice then call the wanted function
    switch (userChoice)
    {
        case enStartingMenu::_startPlaying: {
            startPlaying(wordList, wordSize, ::COLUMN);
            gameOverScreen(wordList, wordSize, ::COLUMN);
        }
            break;
        case enStartingMenu::_listWord: {
            listWords(wordList, wordSize, COLUMN);
            gamePlay();
        }
            break;
        case enStartingMenu::_addNewWord: {
            addNewWord(wordList, wordSize, ::COLUMN, fileName);
            gamePlay();
        }
            break;
        case enStartingMenu::_exitMenu:
            exitGame();
            break;

        default:
            break;
    }

}

void listWords(string wordList[][COLUMN], int arrRow, int arrColumn) {

    printHeader("WORDS LIST");

    printHeader("ENGLISH & TURKISH");

    print2DimArray(wordList, arrRow, arrColumn);

}
