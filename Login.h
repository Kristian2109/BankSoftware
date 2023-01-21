#pragma once

#include <iostream>
#include <limits>
#include "HelperFunctions.h"
#include "ExtractData.h"
using namespace std;

unsigned long getPassHash(char* line, int index) {
    unsigned long result = 0;
    while (line[index] != ':') {
        result *= 10;
        result += fromCharToInt(line[index++]);
    }
    return result;
}
int getUserIndex(char** data, char* username, char* pass) {
    hash <string> hashing;
    unsigned long hashedPass = hashing(pass);
    int index = 0;

    while (data[index][0] != '\0') {
        int endIndexName = checkNameEndIndex(data[index], username);

        if (endIndexName != 0) {
            if (getPassHash(data[index], endIndexName + 1) == hashedPass) {
                return index;
            }
            else return -2;
        }
        index++;
    }
    return -1;
}
void enterUserDetails(char* data, int isName) {
    printLineStars();
    cout << endl; coutTabs(5);
    (isName == 1) ? cout << "Enter your username:  " : cout << "Enter your password:  ";
    storeUserInput(data, (isName == 1) ? MAX_NAME : MAX_PASS);
}
void loginUser(char** fileData, char* name, char* pass, int& lineIndexInFile, bool& isLoggedIn) {
    int counter = 0;
    system("CLS");
    enterUserDetails(name, 1);
    enterUserDetails(pass, 0);
    while (counter++ != 3) {
        if (willGoBack(name)) {
            isLoggedIn = false;
            return;
        }
        system("CLS");
        lineIndexInFile = getUserIndex(fileData, name, pass);
        if (lineIndexInFile >= 0) {
            isLoggedIn = true;
            return;
        }
        else if (lineIndexInFile == -1) {
            cout << endl; centerText("Not such a username. Try again.\n", 5);
            printLineStars();
            enterUserDetails(name, 1);
            enterUserDetails(pass, 0);
        }
        else {
            cout << endl; centerText("  False password. Try again.", 5);
            enterUserDetails(pass, 0);
            printLineStars();
        }
    }
    cout << endl;
    centerText("You've made three wrong tries. Wait 5 minutes. ", 4);
    isLoggedIn = false;
    Pause(5);

}
void getAction(char& action) {
    char actionArr[10];
    storeUserInput(actionArr, 9);
    if (actionArr[1] != '\0') {
        action = 'K';
        return;
    }
    action = actionArr[0];
    cin.ignore(1);
}
void logInMenu(char& action) {
    cout << "\t\t\t\t\t\tWELCOME TO KRIS BANK\n\n";
    printLineStars();
    centerText("Choose what you want to do.\n", 6);
    centerText("If you type a wrong option. Type -1 and you will go back.\n\n", 6);
    centerText("'L' - Login.\n\n", 6);
    centerText("'R' - Register.\n\n", 6);
    centerText("'Q' - Quit.\n\n", 6);
    printLineStars();
    coutTabs(6); cout << "Action:  ";
    char actionArr[10];
    storeUserInput(actionArr, 9);
    action = actionArr[0];
    if (actionArr[1] != '\0') {
        action = 'K';
        return;
    }
}
void showUserOptions(char** fileData, int authCode, char* name) {
    system("CLS");
    char ballance[MAX_SUM_LEN] = "0";
    getBallanceChar(fileData, ballance, authCode);
    printLineStars();
    cout << "\t\t\t\t\tHello " << name << "! What do you want to do?\n\n";
    cout << "\t\t\t\t\tYou have " << ballance << " BGN.Choose one of the following options: \n\n";
    centerText("C - cancel account\n", 6);
    centerText("D - deposit\n", 6);
    centerText("L - logout\n", 6);
    centerText("T - transfer\n", 6);
    centerText("W - withdraw\n\n", 6);
    printLineStars();
    centerText("Action:  ", 6);
}