#pragma once

#include <iostream>
#include <limits>
using namespace std;

const int MAX_NAME = 40;
const int MAX_PASS = 20;
const int MAX_SUM_LEN = 10;

const int MAX_LINE_LEN = MAX_NAME + MAX_PASS + MAX_SUM_LEN;
const char approvedSymbols[9] = "!@#$%^&*";

void coutTabs(int number) {
    for (int i = 0; i < number; i++) {
        cout << '\t';
    }
}
void centerText(string text, int tabs) {
    coutTabs(tabs);
    cout << text;
}
bool isDigit(char number) {
    return number >= 48 && number <= 57;
}
void continueAfterAction(int numTabs) {
    centerText("Press any symbol + enter to continue.\n\n", numTabs);
    char letter = '0';
    coutTabs(7); cin >> letter;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
void createMemory(char** fileData) {
    for (int i = 0; i < 100; i++) {
        fileData[i] = new char[MAX_PASS + MAX_NAME + MAX_SUM_LEN];
    }
}
void deleteMemory(char** fileData) {
    for (int i = 0; i < 20; i++) {
        delete[] fileData[i];
    }
    delete[] fileData;
}
bool isSmallLetter(char symbol) {
    return (symbol >= 97 && symbol <= 122);
}
bool isBigLetter(char symbol) {
    return (symbol >= 65 && symbol <= 90);
}
bool isApprovedSymbol(char symbol) {
    int index = 0;
    while (approvedSymbols[index] != '\0') {
        if (approvedSymbols[index] == symbol) {
            return true;
        }
        index++;
    }
    return false;
}
int fromCharToInt(char symbol) {
    return symbol - 48;
}
int findBeginIndexData(char* userData, int codeData) {
    int currentIndexData = 0;
    int indexChars = 0;
    while (currentIndexData != codeData) {
        if (userData[indexChars++] == ':') {
            currentIndexData++;
        }
    }

    return indexChars;
}
int lastIndexOfData(char** fileData) {
    int index = 0;
    while (fileData[index][0] != '\0') {
        index++;
    }

    return index;
}
bool saveProgram() {
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return true;
    }
    return false;
}
void storeUserInput(char* inputArr, int size) {
    cin.getline(inputArr, (size - 1));
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}
bool willGoBack(char* data) {
    char messageToGoBack[3] = "-1";
    int index = 0;
    while (index < 2) {
        if (data[index] != messageToGoBack[index]) {
            return false;
        }
        index++;
    }

    return (data[index] == '\0'); // The string should be exactly equal, so the data should end here.
}