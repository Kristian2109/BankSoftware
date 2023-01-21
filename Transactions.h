#pragma once

#include <iostream>

#include "HelperFunctions.h"
#include "ExtractData.h"
using namespace std;

void cleanChar(char* arr) {
    int index = 0;
    while (arr[index] != '\0') {
        arr[index++] = '\0';
    }
}
void turnDoubleIntoReversedChar(double amount, char* amountChar, int& index) {
    cleanChar(amountChar);
    if (amount == 0) {
        amountChar[0] = '0';
        return;
    }
    bool isNegative = amount < 0;
    int intAmount = ((isNegative) ? -(amount * 100) : (amount * 100));

    while (intAmount != 0) {
        if (index == 2) {
            amountChar[index++] = '.';
            continue;
        }
        amountChar[index++] = (intAmount % 10) + 48;
        intAmount /= 10;
    }

    ((isNegative) ? amountChar[index++] = '-' : NULL);
}
void reverseArray(char* arr, int len) {
    for (int i = 0; i < len / 2; i++) {
        char temp = arr[i];
        arr[i] = arr[len - i - 1];
        arr[len - i - 1] = temp;
    }
}
void turnDoubleIntoChar(double amount, char* amountChar) {
    int index = 0;
    turnDoubleIntoReversedChar(amount, amountChar, index);
    reverseArray(amountChar, index);
}
void overwriteRow(char* userData, char* amountChar, int& indexChars) {
    int amountIndex = 0;
    while (amountChar[amountIndex] != '\0') {
        userData[indexChars++] = amountChar[amountIndex++];
    }
    userData[indexChars] = '\0';
}
void depositSum(char** fileData, char* amountChar, double sum, int indexUser) {
    int beginIndexBallance = findBeginIndexData(fileData[indexUser], 2);
    double endAmount = getAmountOfMoneyFromUserLine(fileData[indexUser], beginIndexBallance) + sum;

    turnDoubleIntoChar(endAmount, amountChar);
    overwriteRow(fileData[indexUser], amountChar, beginIndexBallance);

    cout << endl << "\t\t\t\t\tYou've successfully deposited " << sum << " BGN.\n\n";
}
void executeDeposit(char** fileData, char* amountChar, int indexUser) {
    system("CLS"); cout << "\n\n";
    centerText("Enter a positive sum to deposit.", 5);
    cout << "\n\n\t\t\t\t\t\t\t";

    int counter = 0;
    double depositAmount = 0;

    cin >> depositAmount;

    if (saveProgram()) {
        cout << endl;
        centerText("You've entered unapproved symbol.\n\n", 6);
        Pause(6);
        return;
    }

    if (depositAmount == -1) {
        return;
    }

    while (counter < 2) {
        if (depositAmount > 0 && depositAmount <= 100000) {
            depositAmount = round(depositAmount * 100) / 100;
            depositSum(fileData, amountChar, depositAmount, indexUser);
            Pause(5);
            return;
        }

        centerText("Incorrect input. Please enter a positive sum up to 100k. ", 5); cout << "\n\n";
        coutTabs(7);
        cin >> depositAmount;
        counter++;
    }

    centerText("You've entered incorrect sum 3 times. Choose another action.\n\n", 4);
    Pause(5);
}
void withdrawSum(char** fileData, char* amountChar, double amount, int indexUser) {
    int indexChars = findBeginIndexData(fileData[indexUser], 2);
    double endAmount = getAmountOfMoneyFromUserLine(fileData[indexUser], indexChars) - amount;
    turnDoubleIntoChar(endAmount, amountChar);
    overwriteRow(fileData[indexUser], amountChar, indexChars);
}
bool isWithdrawInLimits(char* userLine, double amountToWithdraw) {
    int beginIndexBallance = findBeginIndexData(userLine, 2);
    double currentBallance = getAmountOfMoneyFromUserLine(userLine, beginIndexBallance);
    return (currentBallance - amountToWithdraw >= -10000);

}
void executeWithdraw(char** fileData, char* amountChar, int indexUser) {
    int counter = 0;

    cin.ignore(1);
    system("CLS"); cout << "\n\n";
    printLineStars();
    centerText("Enter a positive:  ", 5);

    while (counter < 3) {
        double amountToWithdraw = 0;
        cin >> amountToWithdraw;
        if (saveProgram()) {
            cout << endl; centerText("You've entered unapproved symbol.\n\n", 6);
            Pause(6);
            return;
        }
        if (amountToWithdraw == -1) {
            return;
        }
        if (isWithdrawInLimits(fileData[indexUser], amountToWithdraw)) {
            amountToWithdraw = round(amountToWithdraw * 100) / 100;
            withdrawSum(fileData, amountChar, amountToWithdraw, indexUser);
            printLineStars();
            cout << "\n\n\t\t\t\tYou've successfully withdrawed " << amountToWithdraw << " BGN from you bank account.\n\n";
            Pause(5);
            return;
        }
        else {
            cout << "\n\n\t\t\t\tYou've exceeded your max overdraft of 10000 BGN. Try again\n\n";
        }
        counter++;
    }
    centerText("You haven't given a correct sum 3 times. Try again later.\n\n", 5);
    Pause(5);
}
bool transferSum(char** fileData, char* amountChar, int indexUserToFund, double amount, int currentUserIndex) {

    if (isWithdrawInLimits(fileData[currentUserIndex], amount)) {
        withdrawSum(fileData, amountChar, amount, currentUserIndex);
        depositSum(fileData, amountChar, amount, indexUserToFund);
        system("CLS");
        return true;
    }

    return false;
}
void executeTransferSum(char** fileData, char* amountChar, int currentUserIndex) {
    cin.ignore(1);

    int counter = 0;
    double amount = 0;

    while (counter < 3) {
        system("CLS");
        printLineStars();
        centerText("Enter the username of the user you want to fund.\n\n\t\t\t\t\t\t", 5);
        char userToFund[MAX_NAME];
        storeUserInput(userToFund, MAX_NAME); cout << "\n\n";
        if (willGoBack(userToFund)) {
            return;
        }

        int indexUser = findUserIndexByName(fileData, userToFund);
        if (indexUser == -1) {
            centerText("Not such a user. Try again with other username.\n", 5);
            Pause(5);
            continue;
        }

        if (indexUser == currentUserIndex) {
            centerText("Don't try to fund yourself :).\n", 5);
            Pause(5);
            continue;
        }

        printLineStars();
        centerText("Enter the amount of the sum you want to transfer.\n\n\t\t\t\t\t\t\t\t", 5);
        cin >> amount;
        if (amount == -1) {
            return;
        }
        if (saveProgram()) {
            cout << endl; centerText("You've entered unapproved symbol.\n\n", 6);
            Pause(6);
            return;
        }
        if (transferSum(fileData, amountChar, indexUser, amount, currentUserIndex)) {
            amount = round(amount * 100) / 100;
            printLineStars();
            cout << "\n\n\t\t\t\t\tYour transfer of " << amount << " BGN to "
                << userToFund << " is successful. \n\n";
            Pause(6);
            return;
        }
        counter++;
    }
}
