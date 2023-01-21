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
* <header with functions related to files>
*
*/

#pragma once
#include <iostream>
#include <limits>

#include "HelperFunctions.h"
using namespace std;

void transferDataFromFile(ifstream& file, char** fileData) {
    int index = 0;
    if (file.is_open()) {
        while (file >> fileData[index++]) {
        }
    }
}
void storeDataFromFile(char** fileData, string fileName) {
    ifstream file;
    file.open(fileName);
    if (!file.is_open()) {
        ofstream fileCreate;
        fileCreate.open(fileName);
        fileCreate.close();
        file.open(fileName);
    }
    transferDataFromFile(file, fileData);
    file.close();
}
void overwriteFile(ofstream& file, char** fileData, int endIndex) {
    int index = 0;
    while (index <= endIndex) {
        file << fileData[index++];
        if (index != endIndex) {
            file << '\n';
        }
    }
}
void executeOverwriteToFile(char** fileData, string fileName) {
    ofstream file_over;
    file_over.open(fileName);
    int endIndex = lastIndexOfData(fileData);
    overwriteFile(file_over, fileData, endIndex);
    file_over.close();
}