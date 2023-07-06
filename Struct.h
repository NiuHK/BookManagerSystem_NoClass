#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#ifndef STRUCT_H
#define STRUCT_H
using namespace std;

// �ṹ�嶨��
struct User {
    string username;
    string password;
    int* borrowedBooks ;//id����ͷָ��
    int numBorrowedBooks;
    string userCatgory;
};

struct Book {
    int bookId;
    std::string bookName;
    std::string authorName;
    int quantity;
    int year;
};


#endif //STRUCT_H

