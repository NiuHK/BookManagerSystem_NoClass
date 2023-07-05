//����ת�ӣ����庯�������޲���
#include"UserOperation.h"
using namespace std;
//currentUser


// ����
void borrowBookU() {
    // ʵ�ֽ����߼�

    int bookId;

    cout << "-����-" << endl << "������Ҫ����鼮ID��";
    cin >> bookId;

    borrowBook(currentUser.username, bookId);

    cout << endl << endl;
    back();
}

// ����
void returnBookU() {
    int bookId;

    cout << "-����-"<<endl<<"������Ҫ�����鼮ID��";
    cin >> bookId;
    returnBook(currentUser.username, bookId);

    cout << endl << endl;
    back();
}

// ��ѯͼ����Ϣ
void searchBooksU() {
    // ʵ�ֲ�ѯͼ����Ϣ�߼�
    cout << endl << endl;
    string searchTerm;
    cout << "���������������ߣ�\n";
       cin >> searchTerm;
    searchBooks(searchTerm);
    cout << endl << endl;
    back();
}

// ��ѯ������Ϣ
void searchUserU() {
    cout << endl << endl;
    cout << "Your Name:\t" << currentUser.username;

    cout<<endl<<endl;

        //��ѯ�ѽ����鼮
        cout << "�ѽ����鼮���£�"<<endl;
    printBorrowedBooks(currentUser.username);
    // ʵ�ֲ�ѯ������Ϣ�߼�

    cout << endl << endl;
    back();
}

// �鿴����
void viewAnnouncementU() {
    // ʵ�ֲ鿴�����߼�
    cout << endl << endl;
    cout << "-�鿴����-\n" ;
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
    cout << "-���ͼ��-" << endl << "���������������ߣ������Լ�������ݣ��Կո�����"<<endl;
    cin >> bookName >> authorName >> quantity >> year;

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

    cout << "-ɾ��ͼ��-" << endl << "������Ҫɾ�����鼮ID�Լ�������";
    cin >> bookId>> num;
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
    cout << "-��������-" << endl << "��༭���棬��0����һ�н�����\n";
    editTxtFile(BOAED_PATH);
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
    cout << "�������������˺ţ�\n";
    string username, password;
    cin >> username;


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
 //   cout << "�������������˺ţ�\n";
    string  password;
   // cin >> username;
    
        cout << "ȷ�Ͼ����룺";
        cin >> password;
    
        ifstream userFile(USER_PATH);
        if (userFile.is_open()) {
            User user;
            while (userFile >> user.username >> user.password) {
                if (user.username == currentUser.username && user.password == password) {
                    userFile.close();
    
                    string newPassword;
                    cout << "�����������룺\n";
                    cin >> newPassword;
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
    cout << "��ѡ��\n";
    cout<<"1.����û�\n";
    cout<<"2.ɾ���û�\n";
    int choice;
    cin>>choice;
    if (choice == 1) {
		string username, password;
		cout << "�������û�����\n";
		cin >> username;
		cout << "���������룺\n";
		cin >> password;
		addUser(username, password);
	}
    else if (choice == 2) {
		string username;
		cout << "�������û�����\n";
		cin >> username;
		deleteUser(username);
	}
    else {
		cout<<"�������\n";
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


