#pragma once
//实现txt数据库， LibrarySystem library1("libary_db3.txt")中libary_db3.txt为数据库路径，实现一个类多个数据库。

#include"globals.h"
using namespace std;



    bool addBook(const std::string& bookName, const std::string& authorName, int quantity, int year); //Change the structure
    bool addBook(const int bookID);
    void removeBook(const int bookID);
    //  void removeBook(const string& bookName);
    //  void returnBook(const string& bookName);
   // void returnBook(const int bookID);
    void searchBook(const std::string& bookName);
    void printDatabase(); //Change the structure
    void clearDatabase();
    Book* findBookById(int bookId);
    Book* getBooks();
    int getNumBooks();
   bool printSimpleItem(int bookId); //Change the structure//通过bookId查找信息
    int getNextBookId();
    void loadDatabase();//Change the structure
    void saveDatabase();// //Change the structure