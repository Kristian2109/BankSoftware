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
* <cpp file for execution of the code>
*
*/

#include <iostream>
#include <fstream>
#include <string>

#include "Transactions.h"
#include "Register.h"
#include "FileFunctions.h"
#include "LogIn.h"
#include "HelperFunctions.h"
#include "CancelAccount.h"
const string FILE_NAME = "user_data.txt";

int main()
{
    char action = 0;
    char name[MAX_NAME] = "";
    char pass[MAX_PASS] = "";
    char amount[MAX_SUM_LEN] = "0";
    char** fileData = new char* [100];
    createMemory(fileData);
    storeDataFromFile(fileData, FILE_NAME);

    while (action != 'Q') {
        system("CLS");
        logInMenu(action);
        if (action == 'L' || action == 'l') {
            int indexUser = -1; // For security we assume that the user doesn't have account
            bool isLoggedIn = false;
            loginUser(fileData, name, pass, indexUser, isLoggedIn);
            if (!isLoggedIn) {
                continue;
            }
            do {
                showUserOptions(fileData, indexUser, name);
                cin >> action;
                switch (action) {
                case 'C':
                case 'c':
                    executeCancelAccount(fileData, name, indexUser);
                    break;
                case 'D':
                case 'd':
                    executeDeposit(fileData, amount, indexUser);
                    break;
                case 'L':
                case 'l':
                    system("CLS");
                    cin.ignore(1);
                    break;
                case 'T':
                case 't':
                    executeTransferSum(fileData, amount, indexUser);
                    break;
                case 'W':
                case 'w':
                    executeWithdraw(fileData, amount, indexUser);
                    break;
                default:
                    cout << endl; centerText("Incorect input!\n\n", 7);
                    Pause(6);
                }
            } while (action != 'L' && action != 'l');
        }
        else if (action == 'R' || action == 'r') {
            char** newFileData = new char* [100];
            bool isValidRegistration = true;
            executeRegister(fileData, newFileData, name, pass, FILE_NAME, isValidRegistration);
            if (!isValidRegistration) {
                continue;
            }
            fileData = newFileData;
        }
        else if (action == 'Q' || action == 'q') {
            executeOverwriteToFile(fileData, FILE_NAME);
        }
        else {
            centerText("Incorrect input.\n\n", 7);
            Pause(6);
        }
    }

    system("CLS");
    cout << "\n\n";
    centerText("You've successfully exited the program and overwritten the data.", 3);
    deleteMemory(fileData);
    return 0;
}