/**
*
* Solution to course project # 9
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2022/2023
*
* @author Kristian Petrov
* @idnumber 8MI0600201
* @compiler MSVC
*
* <header with functions for regisration page>
*
*/

#pragma once
#include <iostream>
#include <limits> 
#include "HelperFunctions.h"
#include "ExtractData.h"
#include "FileFunctions.h"

using namespace std;

bool isNameValid(char* name) {
    int index = 0;
    while (name[index] != '\0') {
        if (name[index] < 32 || name[index] > 126 || name[index] == ':') {
            return false;
        }
        index++;
    }
    return true;
}
bool isPassValid(char* pass) {
    int index = 0;
    int numLowLet = 0;
    int numHighLet = 0;
    int numSymbols = 0;
    int numDigits = 0;
    while (pass[index] != '\0') {
        if (isBigLetter(pass[index])) {
            numHighLet++;
        }
        else if (isSmallLetter(pass[index])) {
            numLowLet++;
        }
        else if (isApprovedSymbol(pass[index])) {
            numSymbols++;
        }
        else if (isDigit(pass[index])) {
            numDigits++;
        }
        else {
            return false;
        }
        index++;
    }

    return index > 4 && numLowLet > 0 && numSymbols > 0 && numHighLet > 0 && numDigits > 0;
}
void registerName(char** fileData, char* name, bool& isNameRegistered) {
    int counter = 0;
    while (counter < 3) {
        printLineStars();
        cout << endl; coutTabs(5);
        cout << "Give username with only lattin letters and symbols: \n\n";
        coutTabs(5);
        storeUserInput(name, MAX_NAME);
        if (willGoBack(name)) {
            isNameRegistered = false;
            return;
        }
        if (isNameValid(name) && findUserIndexByName(fileData, name) < 0) {
            isNameRegistered = true;
            return;
        }
        cout << "\n\n";
        if (isNameValid(name) == false) {
            centerText("Unapproved symbols. Only lattin letters and symbols without colon.\n\n", 4);
        }
        else {
            centerText("This username is taken. Enter another username.\n\n", 5);
        }
        coutTabs(5);
        cin.getline(name, MAX_NAME);
        counter++;
    }
    centerText("You didn't register your name. Try again later.\n\n", 5);
    Pause(5);
    isNameRegistered = false;
}
void registerPass(char* pass, bool& isPassRegistered) {
    printLineStars();
    cout << endl; coutTabs(5);
    cout << "Enter a password with only lattin letters, digits and symbol," << endl;
    coutTabs(5);
    cout << "at least one symbol, low and high letter: " << endl;
    cout << endl; coutTabs(5);

    int counter = 0;
    while (counter < 3) {
        storeUserInput(pass, MAX_PASS);
        if (isPassValid(pass)) {
            isPassRegistered = true;
            return;
        }
        cout << endl; coutTabs(5);
        cout << "False password, try again: \n\n"; coutTabs(5);
        counter++;
    }

    cout << endl; centerText("You didn't register your password. Try again later.\n\n", 5);
    Pause(5);
    isPassRegistered = false;
}
void registerUser(char** fileData, char* name, char* pass, bool& isValidRegistration) {
    system("CLS");
    bool isNameRegistered = false;
    registerName(fileData, name, isNameRegistered);
    if (!isNameRegistered) {
        isValidRegistration = false;
        return;
    }
    bool isPassRegistered = false;
    registerPass(pass, isPassRegistered);
    if (!isPassRegistered) {
        isValidRegistration = false;
        return;
    }
    hash <string> hash;
    unsigned long hashedPass = hash(pass);
    ofstream file;
    file.open("user_data.txt", ios::app);
    file << name << ':' << hashedPass << ':' << '0' << '\n';
    file.close();
    printLineStars();
    centerText("You've successfully registered your profile\n", 5);
    Pause(5);
}
void executeRegister(char** oldfileData, char** newFileData, char* name, char* pass, const string file_name, bool& isValidRegistration) {
    registerUser(oldfileData, name, pass, isValidRegistration);
    if (!isValidRegistration) {
        return;
    }
    deleteMemory(oldfileData);
    createMemory(newFileData);
    storeDataFromFile(newFileData, file_name);
}