//����ת�ӣ����庯�������޲���
#include"UserOperation.h"
using namespace std;
//currentUser


// ����
void borrowBookU() {
    // ʵ�ֽ����߼�
    int bookId;
    printDatabase();
    cout << endl << endl;
    cout << "\t\t-����" << endl << "--������Ҫ����鼮ID��(����0������һ��)";
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

// ����
void returnBookU() {
    int bookId;
    cout << "\t\t\t�ѽ����鼮���£�" << endl;
    printBorrowedBooks(currentUser.username);

    cout << endl << endl;
    cout << "\t\t-����-"<<endl<<"������Ҫ�����鼮ID:  (����0������һ��)";
    cin >> bookId;

    if (bookId == 0) {
        back(false);
        return;
    }

    returnBook(currentUser.username, bookId);

    cout << endl << endl;
    back(true);
}

// ��ѯͼ����Ϣ
void searchBooksU() {
    // ʵ�ֲ�ѯͼ����Ϣ�߼�
    cout << endl << endl;
    printDatabase();
    cout << endl << endl;
    string searchTerm;
    cout << "���������������߻��鼮id����0�����ϼ���\n";
       cin >> searchTerm;
       if (searchTerm == "0") {
           back(false);
           return;
       }
    searchBooks(searchTerm);
    cout << endl << endl;
    back(true);
}

// ��ѯ������Ϣ
void searchUserU() {
    cout << endl << endl;
    cout << "\tYour Name:\t" << currentUser.username;

    cout<<endl<<endl;

        //��ѯ�ѽ����鼮
        cout << "\t\t\t�ѽ����鼮���£�"<<endl;
    printBorrowedBooks(currentUser.username);
    // ʵ�ֲ�ѯ������Ϣ�߼�

    cout << endl << endl;
    back();
}

// �鿴����
void viewAnnouncementU() {
    // ʵ�ֲ鿴�����߼�
    cout << endl << endl;
    cout << "\t\t\t-�鿴����-\n" ;
    printTxtFile(BOAED_PATH);
    cout << endl << endl;
    back();
}

// ���ͼ��
void addBookU() {
    
    string bookName ;
    string authorName;
    int quantity=0;
    int year=0;
    cout << endl << endl;
    cout << "\t\t\t-���ͼ��-" << endl << "���������������ߣ������Լ�������ݣ��Կո�����(����0�����ϼ�)"<<endl;
    cin >> bookName;
    if(bookName.length() == 1)
    if (stoi(bookName) == 0) {
        back(false);
        return;
    }
    cin>> authorName >> quantity >> year;

    addBook( bookName, authorName, quantity, year);
    // ʵ�����ͼ���߼�

    cout << endl << endl;
    back();
}

// ɾ��ͼ��
void deleteBookU() {
    int bookId=0;
    int num= 0;
    cout << endl << endl;
    printDatabase();
    cout << endl << endl;

    cout << "\t\t\t-ɾ��ͼ��-" << endl << "������Ҫɾ�����鼮ID�Լ�������(����0�����ϼ�)";
    cin >> bookId;
    if (bookId == 0) {
        back(false);
        return;
    }
    cin>> num;
    for(int i=0;i<num;i++)
    removeBook(bookId);
    // ʵ��ɾ��ͼ���߼�

    cout << endl << endl;
    back();
}

// ��������
void publishAnnouncementU() {
    // ʵ�ַ��������߼�
    cout << endl << endl;
    cout << "-��������" << endl;
    cout << "--1. ׷�ӹ���" << endl << "--2. ���Ƿ���" << endl << "--0. �����ϼ�" << endl;
    int choice;
    cin >> choice;
    switch (choice) {
    case 1:
        cout << "----׷�ӹ���" << endl << "��༭���棬��0����һ�н�����\n";
        addTxtFile(BOAED_PATH);
        break;
    case 2:
        cout << "----��������" << endl << "��༭���棬��0����һ�н�����\n";
        editTxtFile(BOAED_PATH);
        break;
    case 0:
        back(false);
        return;
        break;
    aefault:
        cout << "��Ч��ѡ��" << endl;
        back(true);
        return;
    }
    cout << endl << endl;
    back();
}

// �쳣�������
void manageExceptionalReturnsU() {
    // ʵ���쳣��������߼�
    cout << endl << endl;

    cout << endl << endl;
    back();
}

// ����Ա�޸�����
void changePasswordSU() {
    // ʵ���޸������߼�
    cout << endl << endl;
    cout << "�������������˺ţ�(����0�����ϼ�)\n";
    string username, password;
    cin >> username;
    if (username.length() == 1)
    if (stoi(username) == 0) {
        back(false);        return;
    }

    string newPassword;
    cout << "�����������룺\n";
    cin >> newPassword;
    passwdChange(username, newPassword);
    back();
    return;
}

// �޸�����
void changePasswordU() {
    // ʵ���޸������߼�
    cout << endl << endl;
    string  password;
        cout << "ȷ�Ͼ����룺(����0�����ϼ�)";
        cin >> password;
        if (password.length() == 1)
        if (stoi(password) == 0) {
            back(false);        return;
        }
        ifstream userFile(USER_PATH);
        if (userFile.is_open()) {
            User user;
            while (userFile >> user.username >> user.password) {
                if (user.username == currentUser.username && user.password == password) {
                    userFile.close();
    
                    string newPassword;
                    cout << "�����������룺\n";
                    cin >> newPassword;
                    if (newPassword.length() == 1)
                    if (stoi(newPassword) == 0) {
                        cout << "���벻��Ϊ0";
                        back(false);        return;
                    }
                    passwdChange(currentUser.username, newPassword);
                    back();
                    return;
                }
            }
            userFile.close();
        }
    
        cout << "�˺Ż����벻��ȷ��" << endl;
    
        cout << endl << endl;
        back();
}

// ������ͨ�û�
void manageUsersU() {
    // ʵ�ֹ�����ͨ�û��߼�
    cout << endl << endl;
    printUsers();
    cout << "-��ѡ��\n";
    cout<<"--1.����û�\n";
    cout<<"--2.ɾ���û�\n";
    cout << "--0.�����ϼ�\n";
    int choice;
    cin>>choice;
    if (choice == 1) {
		string username, password;
		cout << "---�������û�����\n";
		cin >> username;
		cout << "---���������룺\n";
		cin >> password;
		addUser(username, password);
	}
    else if (choice == 2) {
		string username;
		cout << "�������û�����\n";
		cin >> username;
		deleteUser(username);
	}
    else if (choice == 0) {
        back(false);
        return;
    }else
    {
		cout<<"----�������\n";
	}
    cout << endl << endl;
    back();
}

// ����ͼ�����Ա
void manageLibrariansU() {
    // ʵ�ֹ���ͼ�����Ա�߼�
    cout << endl << endl;
    addSU();
    cout << endl << endl;
    back();
}


void listLibrariansU() {
    // �г������鵥
    cout << endl << endl;
    printDatabase();
    cout << endl << endl;
    back();
}


