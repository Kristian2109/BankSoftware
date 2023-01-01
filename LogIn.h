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
int isUserAuthenticated(char** data, char* username, char* pass) {
    hash <string> hashing;
    unsigned long hashedPass = hashing(pass);
    int index = 0;

    while (data[index][0] != '\0') {
        int endIndexName = checkNameEndIndex(data[index], username);

        if (endIndexName != 0) {
            if (getPassHash(data[index], endIndexName + 1) == hashedPass) {
                return index;
            }
            else {
                return -2;
            }
        }
        index++;
    }
    return -1;
}
void enterUserDetails(char* data, int isName) {
    cout << endl; coutTabs(6);
    (isName == 1) ? cout << "Enter your username: \n\n" : cout << "Enter your password: \n\n";
    coutTabs(5);
    storeUserInput(data, (isName == 1) ? MAX_NAME : MAX_PASS);
    //cin.getline(data, (isName == 1) ? MAX_NAME : MAX_PASS);
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
        lineIndexInFile = isUserAuthenticated(fileData, name, pass);
        if (lineIndexInFile >= 0) {
            isLoggedIn = true;
            return;
        }
        else if (lineIndexInFile == -1) {
            cout << endl; centerText("Not such a username. Try again.", 5);
            enterUserDetails(name, 1);
            enterUserDetails(pass, 0);
        }
        else {
            cout << endl; centerText("  False password. Try again.", 5);
            enterUserDetails(pass, 0);
        }
    }
    cout << endl;
    centerText("You've made three wrong tries. Wait 5 minutes. ", 4);
    isLoggedIn = false;
    continueAfterAction(5);

}
void getAction(char& action) {
    char actionArr[10];
    storeUserInput(actionArr, 9);
    if (actionArr[1] != '\0') {
        action = 'K';
        return;
    }
    //cout << "Heeeeey  " << actionArr[0] << endl;
    //continueAfterAction;
    action = actionArr[0];
    cin.ignore(1);
}
void logInMenu(char& action) {
    centerText("Type 'L' to Login.\n\n", 6);
    centerText("Type 'R' to Register.\n\n", 6);
    centerText("Type 'Q' to Quit.\n\n", 6);
    coutTabs(7);
    char actionArr[10];
    storeUserInput(actionArr, 9);
    action = actionArr[0];
    if (actionArr[1] != '\0') {
        action = 'K';
        return;
    }
}
void showUserOptions(char** fileData, int authCode) {
    system("CLS");
    char ballance[MAX_SUM_LEN] = "0";
    getBallanceChar(fileData, ballance, authCode);
    cout << "\n\n\t\t\t\t\tYou have " << ballance << " BGN.Choose one of the following options: \n\n";
    centerText("C - cancel account\n", 7);
    centerText("D - deposit\n", 7);
    centerText("L - logout\n", 7);
    centerText("T - transfer\n", 7);
    centerText("W - withdraw\n\n", 7);
}