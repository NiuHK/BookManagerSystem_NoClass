#include"Menu.h"
// ��¼
//���ܹ������ʵ�֣���������ú���ʵ�ֹ��ܣ�ȫ��ʵ���޲�������
//���ӷ����˳�

void login() {
    string username, password;
    cout << "�˺ţ�";
    cin >> username;
    cout << "���룺";
    cin >> password;

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

    cout << "�˺ź����벻��ȷ��" << endl;
}

// ��ʾ�˵�
void showMenu(const User& user) {
    if (user.username.empty()) {
        cout << "���ȵ�¼��" << endl;
        return;
    }

    cout << "��ӭ��" << currentUser.username << "����ѡ�����Ľ�ɫ��" << endl;//���ȫ��currentuser
    if (user.userCatgory == "admin") {
        cout << "1. ��ͨ�û�" << endl;
        cout << "2. ͼ�����Ա" << endl;
        cout << "3. ��������Ա" << endl;
    }
    else if (user.userCatgory == "librarian") {
        cout << "1. ��ͨ�û�" << endl;
        cout << "2. ͼ�����Ա" << endl;
    }
    else {
        userMenu(user);
    }




    int choice;
    cout << "��ѡ��";
    cin >> choice;

    switch (choice) {
    case 1:
        userMenu(user);
      //  currentUser.userCatgory = "user";
        break;
    case 2:
        librarianMenu(user);
       // currentUser.userCatgory = "librarian";
        break;
    case 3:
        adminMenu(user);
    //    currentUser.userCatgory = "admin";
        break;
    default:
        cout << "��Ч���û���" << endl;
        break;
    }
}

// ��ͨ�û��˵�
void userMenu(const User& user) {

    readerConstructed(user.username);//��ʼ���û���
    loadDatabase();//��ʼ��ͼ���


    cout << "��ͨ�û��˵���" << endl;
    cout << "1. ����" << endl;
    cout << "2. ����" << endl;
    cout << "3. ��ѯͼ����Ϣ" << endl;
    cout << "4. ��ѯ������Ϣ" << endl;
    cout << "5. �鿴����" << endl;
    cout << "6. ��������" << endl;
    cout << "��ѡ��";

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
        changePasswordU();
        break;
    default:
        cout << "��Ч��ѡ��" << endl;
        break;
    }
}

// ͼ�����Ա�˵�
void librarianMenu(const User& user) {

    readerConstructed(user.username);//��ʼ���û���
    loadDatabase();//��ʼ��ͼ���

    cout << "ͼ�����Ա�˵���" << endl;
    cout << "1. ����" << endl;
    cout << "2. ����" << endl;
    cout << "3. ��ѯͼ����Ϣ" << endl;
    cout << "4. ��ѯ������Ϣ" << endl;
    cout << "5. �鿴����" << endl;
    cout << "6. ���ͼ��" << endl;
    cout << "7. ɾ��ͼ��" << endl;
    cout << "8. ��������" << endl;
    cout << "9. �쳣�������" << endl;
    cout << "10. ��������" << endl;
    cout << "��ѡ��";

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
    default:
        cout << "��Ч��ѡ��" << endl;
        break;
    }
}

// ��������Ա�˵�
void adminMenu(const User& user) {

    readerConstructed(user.username);//��ʼ���û���
    loadDatabase();//��ʼ��ͼ���

    cout << "��������Ա�˵���" << endl;
    cout << "1. ����" << endl;
    cout << "2. ����" << endl;
    cout << "3. ��ѯͼ����Ϣ" << endl;
    cout << "4. ��ѯ������Ϣ" << endl;
    cout << "5. �鿴����" << endl;
    cout << "6. ���ͼ��" << endl;
    cout << "7. ɾ��ͼ��" << endl;
    cout << "8. ��������" << endl;
    cout << "9. �쳣�������" << endl;
    cout << "10. �޸�����" << endl;
    cout << "11. ������ͨ�û�" << endl;
    cout << "12. ����ͼ�����Ա" << endl;
    cout << "13. �鿴�鼮�б�" << endl;
    cout << "��ѡ��";

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
    default:
        cout << "��Ч��ѡ��" << endl;
        break;
    }
}

void back() {
    char judge;
    cout << endl << endl;
    cout << "�Ƿ񷵻��ϼ�: (Y/N)" << endl;
    cin >> judge;
    if (judge == 'y' || judge == 'Y') {
        cout << endl << endl;
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
    else exit(0);
}

