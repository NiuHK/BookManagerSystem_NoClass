#include"globals.h"
extern  string DATA_BASE_PATH = "./data/Library.txt";
extern  string DATA_BASE_PATH_SAVE = "./data/Library.data";
extern string BOAED_PATH = "./data/Announcement.txt";
extern string BOAED_PATH_SAVE = "./data/Announcement.data";
extern string WRONG_COMMIT ="./data/WrongCommit.txt";
extern string WRONG_COMMIT_SAVE = "./data/WrongCommit.data";
extern string USER_DATA_PATH = "./data/users/";
extern string USER_PATH="./data/users.txt";
extern string USER_PATH_SAVE = "./data/users.data";
extern int numBooks=0;
extern Book* books = NULL;
extern  BorrowedBooks  borrowedBooks[100] = {0};
extern int bookNumber=0;
 User currentUser;



 bool AllisNum(string str)
 {
     for (int i = 0; i < str.size(); i++)
     {
         int tmp = (int)str[i];
         if (tmp >= 48 && tmp <= 57)
         {
             continue;
         }
         else
         {
             return false;
         }
     }
     return true;
 }

