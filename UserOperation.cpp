//这是转接，定义函数尽量无参数
#include"UserOperation.h"
using namespace std;
//currentUser


// 借书
void borrowBookU() {
    // 实现借书逻辑
    int bookId;
    printDatabase();
    cout << endl << endl;
    cout << "\t\t-借书" << endl << "--请输入要借的书籍ID：(输入0返回上一级)";
    cin >> bookId;
    if (bookId == 0) {
        //cout << currentUser.userCatgory ;
        back(false);
        return;
    }
    borrowBook(currentUser.username, bookId);

    cout << endl << endl;
    back(true);
}

// 还书
void returnBookU() {
    int bookId;
    cout << "\t\t\t已借阅书籍如下：" << endl;
    printBorrowedBooks(currentUser.username);

    cout << endl << endl;
    cout << "\t\t-还书-"<<endl<<"请输入要还的书籍条目:  (输入0返回上一级)";
    cin >> bookId;

    if (bookId == 0) {
        back(false);
        return;
    }
    readerConstructed(currentUser.username);//初始化用每个户库
    returnBook(currentUser.username, bookId);
    back(true);
}

// 查询图书信息
void searchBooksU() {
    // 实现查询图书信息逻辑
    cout << endl << endl;
    printDatabase();
    cout << endl << endl;
    string searchTerm;
    cout << "请输入书名或作者或书籍id：（0返回上级）\n";
       cin >> searchTerm;
       if (searchTerm == "0") {
           back(false);
           return;
       }
    searchBooks(searchTerm);
    cout << endl << endl;
    back(true);
}

// 查询个人信息
void searchUserU() {
    cout << endl << endl;
    cout << "\tYour Name:\t" << currentUser.username;

    cout<<endl<<endl;

        //查询已借阅书籍
        cout << "\t\t\t已借阅书籍如下："<<endl;
    printBorrowedBooks(currentUser.username);
    // 实现查询个人信息逻辑

    cout << endl << endl;
    back();
}

// 查看公告
void viewAnnouncementU() {
    // 实现查看公告逻辑
    cout << endl << endl;
    cout << "\t\t\t-查看公告-\n" ;
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
    cout << "\t\t\t-添加图书-" << endl << "请输入书名，作者，数量以及出版年份，以空格间隔：(输入0返回上级)"<<endl;
    cin >> bookName;
    if(bookName.length() == 1)
    if (stoi(bookName) == 0) {
        back(false);
        return;
    }
    cin>> authorName >> quantity >> year;

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

    cout << "\t\t\t-删除图书-" << endl << "请输入要删除的书籍ID以及数量：(输入0返回上级)";
    cin >> bookId;
    if (bookId == 0) {
        back(false);
        return;
    }
    cin>> num;
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
    cout << "-发布公告" << endl;
    cout << "--1. 追加公告" << endl << "--2. 覆盖发布" << endl << "--0. 返回上级" << endl;
    int choice;
    cin >> choice;
    switch (choice) {
    case 1:
        cout << "----追加公告" << endl << "请编辑公告，以0另起一行结束：\n";
        addTxtFile(BOAED_PATH);
        break;
    case 2:
        cout << "----发布公告" << endl << "请编辑公告，以0另起一行结束：\n";
        editTxtFile(BOAED_PATH);
        break;
    case 0:
        back(false);
        return;
        break;
    aefault:
        cout << "无效的选择！" << endl;
        back(true);
        return;
    }
    cout << endl << endl;
    back();
}

// 异常还书管理
void manageExceptionalReturnsU() {
    // 实现异常还书管理逻辑
    cout << endl << endl;
    constructedAll();
    printWrongCommit();
    cout << endl << endl;
    back();
}

// 管理员修改密码
void changePasswordSU() {
    // 实现修改密码逻辑
    cout << endl << endl;
    cout << "输入更改密码的账号：(输入0返回上级)\n";
    string username, password;
    cin >> username;
    if (username.length() == 1)
    if (stoi(username) == 0) {
        back(false);        return;
    }

    string newPassword;
    cout << "请输入新密码：\n";
    cin >> newPassword;
    passwdChange(username, newPassword);
    back();
    return;
}

// 修改密码
void changePasswordU() {
    // 实现修改密码逻辑
    cout << endl << endl;
    string  password;
        cout << "确认旧密码：(输入0返回上级)";
        cin >> password;
        if (password.length() == 1)
        if (stoi(password) == 0) {
            back(false);        return;
        }
        ifstream userFile(USER_PATH);
        if (userFile.is_open()) {
            User user;
            while (userFile >> user.username >> user.password>>user.userCatgory) {
                if (user.username == currentUser.username && user.password == password) {
                    userFile.close();
    
                    string newPassword;
                    cout << "请输入新密码：\n";
                    cin >> newPassword;
                    if (newPassword.length() == 1)
                    if (stoi(newPassword) == 0) {
                        cout << "密码不可为0";
                        back(false);        return;
                    }
                    passwdChange(currentUser.username, newPassword);
                    back();
                    return;
                }
            }

            userFile.close();
        }
    
        cout << "账号或密码不正确！" << endl;
    
        cout << endl << endl;
        back();
}

// 管理普通用户
void manageUsersU() {
    // 实现管理普通用户逻辑
    cout << endl << endl;
    printUsers();
    cout << "-请选择：\n";
    cout<<"--1.添加用户\n";
    cout<<"--2.删除用户\n";
    cout << "--0.返回上级\n";
    int choice;
    cin>>choice;
    if (choice == 1) {
		string username, password;
		cout << "---请输入用户名：\n";
		cin >> username;
		cout << "---请输入密码：\n";
		cin >> password;
		addUser(username, password);
	}
    else if (choice == 2) {
		string username;
		cout << "请输入用户名：\n";
		cin >> username;
		deleteUser(username);
	}
    else if (choice == 0) {
        back(false);
        return;
    }else
    {
		cout<<"----输入错误！\n";
	}
    cout << endl << endl;
    back();
}

// 管理图书管理员
void manageLibrariansU() {
    // 实现管理图书管理员逻辑
    cout << endl << endl;
    addSU();
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


