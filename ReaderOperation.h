#pragma once
#include"DatabaseOperation.h"
#include <fstream>
#include <iostream>
#include <algorithm>


void readerConstructed(string username);


    void borrowBook(string username,int bookId);
    bool returnBook(string username,int bookId);
    bool printBorrowedBooks(string username);//Change the structure
    bool searchBooks(const std::string& searchTerm);
    bool saveData(string username);
    bool sortBookIds(string username);
    bool clearDatabase(string username);
    void editTxtFile(const string& filename);
    void printTxtFile(const string& filename);


