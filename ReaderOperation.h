#pragma once
#include"DatabaseOperation.h"
#include"Menu.h"


void readerConstructed(string username);//判断异常
void constructedAll();//更新异常借阅ONLY

string getPasswd();

    void borrowBook(string username,int bookId);
    bool returnBook(string username,int bookId);
    bool printBorrowedBooks(string username);//Change the structure
    bool searchBooks(const string& searchTerm);
    bool saveData(string username);
    bool sortBookIds(string username);
    bool clearDatabase(string username);
    void addTxtFile(const string& filename);
    void editTxtFile(const string& filename);
    void printTxtFile(const string& filename);
    bool passwdChange(string username, string newPassword);
    void printUsers();
    void addUser(string username, string password);
    bool deleteUser(string username);
    void addSU();
    bool cmp(BorrowedBooks a, BorrowedBooks b); 
    bool isRightCommit(time_t lastExecutionTime);
    void recordWrongCommit(string username,BorrowedBooks borrowedBook);
    string showTime(long long time1);
    void printWrongCommit();
    bool returnBook(string username, int bookId);