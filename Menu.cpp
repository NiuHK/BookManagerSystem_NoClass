#include"Menu.h"
// 登录
//功能管理界面实现，仅负责调用函数实现功能，全部实现无参数调用
//增加返回退出

void login() {
    string username, password;
    cout << "账号：";
    cin >> username;
    cout << "密码：";
    cin >> password;

    ifstream userFile("users.txt");
    if (userFile.is_open()) {
        User user;
        while (userFile >> user.username >> user.password) {
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
    if (user.username.empty()) {
        cout << "请先登录！" << endl;
        return;
    }

    cout << "欢迎，" << currentUser.username << "！请选择您的角色：" << endl;//输出全局currentuser
    if (user.username == "admin") {
        cout << "1. 普通用户" << endl;
        cout << "2. 图书管理员" << endl;
        cout << "3. 超级管理员" << endl;
    }
    else if (user.username == "librarian") {
        cout << "1. 普通用户" << endl;
        cout << "2. 图书管理员" << endl;
    }
    else {
        userMenu(user);
    }




    int choice;
    cout << "请选择：";
    cin >> choice;

    switch (choice) {
    case 1:
        userMenu(user);
        currentUser.userCatgory = "user";
        break;
    case 2:
        librarianMenu(user);
        currentUser.userCatgory = "librarian";
        break;
    case 3:
        adminMenu(user);
        currentUser.userCatgory = "admin";
        break;
    default:
        cout << "无效的用户！" << endl;
        break;
    }
}

// 普通用户菜单
void userMenu(const User& user) {

    readerConstructed(user.username);//初始化用户库
    loadDatabase();//初始化图书库


    cout << "普通用户菜单：" << endl;
    cout << "1. 借书" << endl;
    cout << "2. 还书" << endl;
    cout << "3. 查询图书信息" << endl;
    cout << "4. 查询个人信息" << endl;
    cout << "5. 查看公告" << endl;
    cout << "请选择：";

    int choice;
    cin >> choice;

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
    default:
        cout << "无效的选择！" << endl;
        break;
    }
}

// 图书管理员菜单
void librarianMenu(const User& user) {

    readerConstructed(user.username);//初始化用户库
    loadDatabase();//初始化图书库

    cout << "图书管理员菜单：" << endl;
    cout << "1. 借书" << endl;
    cout << "2. 还书" << endl;
    cout << "3. 查询图书信息" << endl;
    cout << "4. 查询个人信息" << endl;
    cout << "5. 查看公告" << endl;
    cout << "6. 添加图书" << endl;
    cout << "7. 删除图书" << endl;
    cout << "8. 发布公告" << endl;
    cout << "9. 异常还书管理" << endl;
    cout << "请选择：";

    int choice;
    cin >> choice;

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
    default:
        cout << "无效的选择！" << endl;
        break;
    }
}

// 超级管理员菜单
void adminMenu(const User& user) {

    readerConstructed(user.username);//初始化用户库
    loadDatabase();//初始化图书库

    cout << "超级管理员菜单：" << endl;
    cout << "1. 借书" << endl;
    cout << "2. 还书" << endl;
    cout << "3. 查询图书信息" << endl;
    cout << "4. 查询个人信息" << endl;
    cout << "5. 查看公告" << endl;
    cout << "6. 添加图书" << endl;
    cout << "7. 删除图书" << endl;
    cout << "8. 发布公告" << endl;
    cout << "9. 异常还书管理" << endl;
    cout << "10. 修改密码" << endl;
    cout << "11. 管理普通用户" << endl;
    cout << "12. 管理图书管理员" << endl;
    cout << "13. 查看书籍列表" << endl;
    cout << "请选择：";

    int choice;
    cin >> choice;

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
    case 11:
        manageUsersU();
        break;
    case 12:
        manageLibrariansU();
        break;
    case 13:
       listLibrariansU();
        break;
    default:
        cout << "无效的选择！" << endl;
        break;
    }
}

void back() {
    char judge;
    cout << endl << endl;
    cout << "是否返回上级: (Y/N)" << endl;
    cin >> judge;
    if (judge == 'y' || judge == 'Y') {
        cout << endl << endl;
        if (currentUser.username == "librarian") {
            librarianMenu(currentUser);
        }
        else if (currentUser.username == "admin") {
            adminMenu(currentUser);
        }
        else {
            userMenu(currentUser);
        }
    }
}

