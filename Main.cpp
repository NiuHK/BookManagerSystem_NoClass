#include"Menu.h"
int main() {

    login();
    return 0;
    //双初始化在Menu登录实现


    readerConstructed("user1");
    loadDatabase();
  //  clearDatabase();
    //addBook("Book1", "Author1", 0, 1020);
    //addBook("Book2", "Author2", 1, 1001);
    //addBook("Book3", "Author3", 2, 1002);
   borrowBook("user1", 1); 
    printDatabase();
    cout << endl;
    //readerConstructed("user1");
    //borrowBook("user1", 1);
    //borrowBook("user1", 2);
    //borrowBook("user1", 3);
    //borrowBook("user1", 2);
    //borrowBook("user1", 3);
    //printDatabase();
 
    printBorrowedBooks("user1");
   cout << endl;
    return 0;


    login();
    return 0;

}