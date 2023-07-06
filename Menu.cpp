#include"Menu.h"
// ��¼
//���ܹ������ʵ�֣���������ú���ʵ�ֹ��ܣ�ȫ��ʵ���޲�������
//���ӷ����˳�

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
    cout <<"\t    "<< "  ͼ�����ϵͳ��\n";
    cout  << "---------------------------------------\n";
    cout << "\t\t-���ȵ�¼��\t\t\n";
    cout << "\t\t--�˺ţ�";
    cin >> username;
    cout << "\t\t" << "--���룺";
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

    cout << "�˺ź����벻��ȷ��" << endl;
}

// ��ʾ�˵�
void showMenu(const User& user) {
  system("cls");
    if (user.username.empty()) {
        cout << "���ȵ�¼��" << endl;
        return;
    }

   // cout << "��ӭ��" << currentUser.username << "����ѡ�����Ľ�ɫ��" << endl;//���ȫ��currentuser
    if (user.userCatgory == "admin") {
    /*    cout << "1. ��ͨ�û�" << endl;
        cout << "2. ͼ�����Ա" << endl;
        cout << "3. ��������Ա" << endl;*/
        adminMenu(user);
    }
    else if (user.userCatgory == "librarian") {
    /*    cout << "1. ��ͨ�û�" << endl;
        cout << "2. ͼ�����Ա" << endl;*/
        librarianMenu(user);
    }
    else {
        userMenu(user);
    }
}

// ��ͨ�û��˵�
void userMenu(const User& user) {
    int width = 20;
    system("cls");
    readerConstructed(user.username);//��ʼ���û���
    loadDatabase();//��ʼ��ͼ���

    cout << "��ӭ�� " << currentUser.username << "  ��" << endl;//���ȫ��currentuser
    cout << setw(width) << left << "��ͨ�û��˵���" << endl;
    cout << "-------------------------------------------" << '\n';
    cout << setw(width) << left << "1. ����";
    cout << setw(width) << left << "2. ����" << endl;
    cout << setw(width) << left << "3. ��ѯͼ����Ϣ";
    cout << setw(width) << left << "4. ��ѯ������Ϣ" << endl;
    cout << setw(width) << left << "5. �鿴����";
    cout << setw(width) << left << "6. ��������" << endl;
    cout << setw(width) << left << "0. �˳�ϵͳ" << endl;
    cout << setw(width) << left << "-1. ע��" << endl;
    cout << "-------------------------------------------" << '\n';
    cout << "��ѡ��";

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
        cout << "��Ч��ѡ��" << endl;
        break;
    }
}

// ͼ�����Ա�˵�
void librarianMenu(const User& user) {
    int width = 20;
    system("cls");
    readerConstructed(user.username);//��ʼ���û�de��
    loadDatabase();//��ʼ��ͼ���
    cout << "��ӭ�� " << currentUser.username << "  ��" << endl;//���ȫ��currentuser
    cout << setw(width) << left << "ͼ�����Ա�˵���" << endl;
    cout << "-------------------------------------------" << '\n';
    cout << setw(width) << left << "1. ����" ;
    cout << setw(width) << left << "2. ����" << endl;
    cout << setw(width) << left << "3. ��ѯͼ����Ϣ";
    cout << setw(width) << left << "4. ��ѯ������Ϣ" << endl;
    cout << setw(width) << left << "5. �鿴����" ;
    cout << setw(width) << left << "6. ���ͼ��" << endl;
    cout << setw(width) << left << "7. ɾ��ͼ��";
    cout << setw(width) << left << "8. ��������" << endl;
    cout << setw(width) << left << "9. �쳣�������" ;
    cout << setw(width) << left << "10. ��������" << endl;
    cout << setw(width) << left << "0. �˳�ϵͳ" << endl;
    cout << setw(width) << left << "-1. ע��" << endl;
    cout << "-------------------------------------------" << '\n';
    cout << setw(width) << left << "��ѡ��";

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
        cout << "��Ч��ѡ��" << endl;
        break;
    }
}

// ��������Ա�˵�
void adminMenu(const User& user) {
    int width = 20;
    system("cls");
    readerConstructed(user.username);//��ʼ���û���
    loadDatabase();//��ʼ��ͼ���
    cout<<"\n\n\n";
    cout << "\t    ��ӭ�� " << currentUser.username << "  ��" << endl;//���ȫ��currentuser
    cout <<"\n\t    ��������Ա�˵���" << '\n';
    cout << "-------------------------------------------" << '\n';
    cout << setw(width) <<left<< "1. ����" ;//
    cout << setw(width) << left << "2. ����" << '\n';//
    cout << setw(width) << left <<"3. ��ѯͼ����Ϣ" ;//
    cout << setw(width) << left << "4. ��ѯ������Ϣ" << endl;//
    cout << setw(width) << left << "5. �鿴����" ;//
    cout << setw(width) << left << "6. ���ͼ��" << endl;//
    cout << setw(width) << left << "7. ɾ��ͼ��" ;//
    cout << setw(width) << left << "8. ��������" << endl;
    cout << setw(width) << left << "9. �쳣�������" ;
    cout << setw(width) << left << "10. �޸�����" << endl;
    cout << setw(width) << left << "11. ���������û�" ;
    cout << setw(width) << left << "12. ����ͼ�����Ա" << endl;
    cout << setw(width) << left << "13. �鿴�鼮�б�" ;
    cout << setw(width) << left << "0. �˳�ϵͳ" << endl;
    cout << setw(width) << left << "-1. ע��" << endl;
    cout << "-------------------------------------------" << '\n';
    cout << setw(width) << right << "��ѡ��";

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
        cout << "��Ч��ѡ��" << endl;
        break;
    }
}

void back(bool isBack ) {
    if (isBack) {//true ������ʾ false ֱ�ӷ���
        char judge;
        cout << endl << endl;
        cout << "�Ƿ񷵻��ϼ�: (Y/N)" << endl;
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

