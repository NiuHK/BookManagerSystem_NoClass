//这是转接，定义函数尽量无参数
#include"UserOperation.h"
using namespace std;
//currentUser


// 借书
void borrowBookU() {
    // 实现借书逻辑

    int bookId;

    cout << "-借书-" << endl << "请输入要借的书籍ID：";
    cin >> bookId;

    borrowBook(currentUser.username, bookId);

    cout << endl << endl;
    back();
}

// 还书
void returnBookU() {
    int bookId;

    cout << "-还书-"<<endl<<"请输入要还的书籍ID：";
    cin >> bookId;
    returnBook(currentUser.username, bookId);

    cout << endl << endl;
    back();
}

// 查询图书信息
void searchBooksU() {
    // 实现查询图书信息逻辑
    cout << endl << endl;
    string searchTerm;
    cout << "请输入书名或作者：\n";
       cin >> searchTerm;
    searchBooks(searchTerm);
    cout << endl << endl;
    back();
}

// 查询个人信息
void searchUserU() {
    cout << endl << endl;
    cout << "Your Name:\t" << currentUser.username;

    cout<<endl<<endl;

        //查询已借阅书籍
        cout << "已借阅书籍如下："<<endl;
    printBorrowedBooks(currentUser.username);
    // 实现查询个人信息逻辑

    cout << endl << endl;
    back();
}

// 查看公告
void viewAnnouncementU() {
    // 实现查看公告逻辑
    cout << endl << endl;
    cout << "-查看公告-\n" ;
    printTxtFile(BOAED_PATH);
    cout << endl << endl;
    back();
}

// 添加图书
void addBookU() {
    
    string bookName ;
    string authorName;
    int quantity=0;
    int year=0;
    cout << endl << endl;
    cout << "-添加图书-" << endl << "请输入书名，作者，数量以及出版年份，以空格间隔："<<endl;
    cin >> bookName >> authorName >> quantity >> year;

    addBook( bookName, authorName, quantity, year);
    // 实现添加图书逻辑

    cout << endl << endl;
    back();
}

// 删除图书
void deleteBookU() {
    int bookId=0;
    int num= 0;
    cout << endl << endl;
    printDatabase();
    cout << endl << endl;

    cout << "-删除图书-" << endl << "请输入要删除的书籍ID以及数量：";
    cin >> bookId>> num;
    for(int i=0;i<num;i++)
    removeBook(bookId);
    // 实现删除图书逻辑

    cout << endl << endl;
    back();
}

// 发布公告
void publishAnnouncementU() {
    // 实现发布公告逻辑
    cout << endl << endl;
    cout << "-发布公告-" << endl << "请编辑公告，以0另起一行结束：\n";
    editTxtFile(BOAED_PATH);
    cout << endl << endl;
    back();
}

// 异常还书管理
void manageExceptionalReturnsU() {
    // 实现异常还书管理逻辑
    cout << endl << endl;

    cout << endl << endl;
    back();
}

// 修改密码
void changePasswordU() {
    // 实现修改密码逻辑
    cout << endl << endl;

    cout << endl << endl;
    back();
}

// 管理普通用户
void manageUsersU() {
    // 实现管理普通用户逻辑
    cout << endl << endl;

    cout << endl << endl;
    back();
}

// 管理图书管理员
void manageLibrariansU() {
    // 实现管理图书管理员逻辑
    cout << endl << endl;
   
    cout << endl << endl;
    back();
}


void listLibrariansU() {
    // 列出所有书单
    cout << endl << endl;
    printDatabase();
    cout << endl << endl;
    back();
}


