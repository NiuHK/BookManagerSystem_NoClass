#include"Menu.h"
// 登录
//功能管理界面实现，仅负责调用函数实现功能，全部实现无参数调用
//增加返回退出

void reload() {
  rename(DATA_BASE_PATH_SAVE.c_str(), DATA_BASE_PATH.c_str());
  rename(BOAED_PATH_SAVE.c_str(), BOAED_PATH.c_str());
  rename(USER_PATH_SAVE.c_str(), USER_PATH.c_str());
  rename(WRONG_COMMIT_SAVE.c_str(), WRONG_COMMIT.c_str());

}
void save() {
    rename(DATA_BASE_PATH.c_str(), DATA_BASE_PATH_SAVE.c_str());
    rename(BOAED_PATH.c_str(), BOAED_PATH_SAVE.c_str());
    rename(USER_PATH.c_str(), USER_PATH_SAVE.c_str());
    rename(WRONG_COMMIT.c_str(), WRONG_COMMIT_SAVE.c_str());
}
void login() {
    string username, password;
    cout << "\n\n\n\n";
    cout <<"\t    "<< "  图书管理系统：\n";
    cout  << "---------------------------------------\n";
    cout << "\t\t-请先登录！\t\t\n";
    cout << "\t\t--账号：";
    cin >> username;
    cout << "\t\t" << "--密码：";
    password=getPasswd();

    ifstream userFile(USER_PATH);
    if (userFile.is_open()) {
        User user;
        while (userFile >> user.username >> user.password>>user.userCatgory) {
            if (user.username == username && user.password == password) {
                currentUser = user;
                userFile.close();
                showMenu(currentUser);
                return;
            }
        }
        userFile.close();
    }

    cout << "账号和密码不正确！" << endl;
}

// 显示菜单
void showMenu(const User& user) {
  system("cls");
    if (user.username.empty()) {
        cout << "请先登录！" << endl;
        return;
    }

   // cout << "欢迎，" << currentUser.username << "！请选择您的角色：" << endl;//输出全局currentuser
    if (user.userCatgory == "admin") {
    /*    cout << "1. 普通用户" << endl;
        cout << "2. 图书管理员" << endl;
        cout << "3. 超级管理员" << endl;*/
        adminMenu(user);
    }
    else if (user.userCatgory == "librarian") {
    /*    cout << "1. 普通用户" << endl;
        cout << "2. 图书管理员" << endl;*/
        librarianMenu(user);
    }
    else {
        userMenu(user);
    }
}

// 普通用户菜单
void userMenu(const User& user) {
    int width = 20;
    system("cls");
    readerConstructed(user.username);//初始化用户库
    loadDatabase();//初始化图书库

    cout << "欢迎， " << currentUser.username << "  ！" << endl;//输出全局currentuser
    cout << setw(width) << left << "普通用户菜单：" << endl;
    cout << "-------------------------------------------" << '\n';
    cout << setw(width) << left << "1. 借书";
    cout << setw(width) << left << "2. 还书" << endl;
    cout << setw(width) << left << "3. 查询图书信息";
    cout << setw(width) << left << "4. 查询个人信息" << endl;
    cout << setw(width) << left << "5. 查看公告";
    cout << setw(width) << left << "6. 更改密码" << endl;
    cout << setw(width) << left << "0. 退出系统" << endl;
    cout << setw(width) << left << "-1. 注销" << endl;
    cout << "-------------------------------------------" << '\n';
    cout << "请选择：";

    int choice;
    cin >> choice;
    system("cls");
    switch (choice) {
    case 1:
        borrowBookU();
        break;
    case 2:
        returnBookU();
        break;
    case 3:
        searchBooksU();
        break;
    case 4:
        searchUserU();
        break;
    case 5:
        viewAnnouncementU();
        break;
    case 6:
        changePasswordU();
        break;
    case 0:
        cout << endl << "System close." << endl;
        exit(0);
        break;
    case -1:
        login();
        break;
    default:
        cout << "无效的选择！" << endl;
        break;
    }
}

// 图书管理员菜单
void librarianMenu(const User& user) {
    int width = 20;
    system("cls");
    readerConstructed(user.username);//初始化用户de库
    loadDatabase();//初始化图书库
    cout << "欢迎， " << currentUser.username << "  ！" << endl;//输出全局currentuser
    cout << setw(width) << left << "图书管理员菜单：" << endl;
    cout << "-------------------------------------------" << '\n';
    cout << setw(width) << left << "1. 借书" ;
    cout << setw(width) << left << "2. 还书" << endl;
    cout << setw(width) << left << "3. 查询图书信息";
    cout << setw(width) << left << "4. 查询个人信息" << endl;
    cout << setw(width) << left << "5. 查看公告" ;
    cout << setw(width) << left << "6. 添加图书" << endl;
    cout << setw(width) << left << "7. 删除图书";
    cout << setw(width) << left << "8. 发布公告" << endl;
    cout << setw(width) << left << "9. 异常还书管理" ;
    cout << setw(width) << left << "10. 更改密码" << endl;
    cout << setw(width) << left << "0. 退出系统" << endl;
    cout << setw(width) << left << "-1. 注销" << endl;
    cout << "-------------------------------------------" << '\n';
    cout << setw(width) << left << "请选择：";

    int choice;
    cin >> choice;
    system("cls");
    switch (choice) {
    case -1:
        login();
        break;
    case 1:
        borrowBookU();
        break;
    case 2:
        returnBookU();
        break;
    case 3:
        searchBooksU();
        break;
    case 4:
        searchUserU();
        break;
    case 5:
        viewAnnouncementU();
        break;
    case 6:
        addBookU();
        break;
    case 7:
        deleteBookU();
        break;
    case 8:
        publishAnnouncementU();
        break;
    case 9:
        manageExceptionalReturnsU();
        break;
    case 10:
        changePasswordU();
        break;
    case 0:
        cout << endl << "System close." << endl;
        exit(0);
        break;
    default:
        cout << "无效的选择！" << endl;
        break;
    }
}

// 超级管理员菜单
void adminMenu(const User& user) {
    int width = 20;
    system("cls");
    readerConstructed(user.username);//初始化用户库
    loadDatabase();//初始化图书库
    cout<<"\n\n\n";
    cout << "\t    欢迎， " << currentUser.username << "  ！" << endl;//输出全局currentuser
    cout <<"\n\t    超级管理员菜单：" << '\n';
    cout << "-------------------------------------------" << '\n';
    cout << setw(width) <<left<< "1. 借书" ;//
    cout << setw(width) << left << "2. 还书" << '\n';//
    cout << setw(width) << left <<"3. 查询图书信息" ;//
    cout << setw(width) << left << "4. 查询个人信息" << endl;//
    cout << setw(width) << left << "5. 查看公告" ;//
    cout << setw(width) << left << "6. 添加图书" << endl;//
    cout << setw(width) << left << "7. 删除图书" ;//
    cout << setw(width) << left << "8. 发布公告" << endl;
    cout << setw(width) << left << "9. 异常还书管理" ;
    cout << setw(width) << left << "10. 修改密码" << endl;
    cout << setw(width) << left << "11. 管理所有用户" ;
    cout << setw(width) << left << "12. 管理图书管理员" << endl;
    cout << setw(width) << left << "13. 查看书籍列表" ;
    cout << setw(width) << left << "0. 退出系统" << endl;
    cout << setw(width) << left << "-1. 注销" << endl;
    cout << "-------------------------------------------" << '\n';
    cout << setw(width) << right << "请选择：";

    int choice;
    cin >> choice;
    system("cls");
    switch (choice) {
    case -1:
        login();
        break;
    case 1:
        borrowBookU();
        break;
    case 2:
        returnBookU();
        break;
    case 3:
        searchBooksU();
        break;
    case 4:
        searchUserU();
        break;
    case 5:
        viewAnnouncementU();
        break;
    case 6:
        addBookU();
        break;
    case 7:
        deleteBookU();//
        break;
    case 8:
        publishAnnouncementU();
        break;
    case 9:
        manageExceptionalReturnsU();
        break;
    case 10:
        changePasswordSU();
        break;
    case 11:
        manageUsersU();
        break;
    case 12:
       manageLibrariansU();
        break;
    case 13:
       listLibrariansU();
        break;
    case 0:
        cout << endl << "System close." << endl;
        exit(0);
        break;
    default:
        cout << "无效的选择！" << endl;
        break;
    }
}

void back(bool isBack ) {
    if (isBack) {//true 启用提示 false 直接返回
        char judge;
        cout << endl << endl;
        cout << "是否返回上级: (Y/N)" << endl;
        cin >> judge;
        if (judge == 'n' || judge == 'N') {
            exit(0);
            return;
        }
    }

        if (currentUser.userCatgory == "librarian") {
            librarianMenu(currentUser);
        }
        else if (currentUser.userCatgory == "admin") {
            adminMenu(currentUser);
        }
        else {
            userMenu(currentUser);
        }
    }

