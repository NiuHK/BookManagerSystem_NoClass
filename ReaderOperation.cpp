
#include"ReaderOperation.h"
//#include "DatabaseOperation.cpp"
using namespace std;


void readerConstructed(string username) {//��ʼ��һ��user�����ļ������ݣ�
ifstream readerFile(username + ".txt");
if (readerFile) {
    int bookId;
    int i=0;
    while (readerFile >> bookId) {//����
        borrowedBooks[i]=bookId;
        i++;
    }
    readerFile.close();
    bookNumber = i;//������ĵ������±�����
}
}


void borrowBook(string username, int bookId) {
    // Check if the book exists in the database
    DATA_BASE_PATH;//Library path
   
    Book* thisbooks = getBooks();
    int numBooks = getNumBooks();
    for (int i = 0; i < numBooks; i++) {
        if (books[i].bookId == bookId&& books[i].quantity>0) {
            // Book found in the database, add it to the reader's borrowed books
            borrowedBooks[bookNumber]=bookId;
            bookNumber++;
            saveData(username);//���µ�username�����ݿ���
         //   sortBookIds(username);
            removeBook(bookId);//remove from library
            cout << "Book borrowed successfully." << endl;
            return;
        }
    }

    cout << "Book not found in the database." << endl;
}

bool returnBook(string username, int bookId) {
    // Check if the book exists in the database
    Book* thisbooks = getBooks();
    int numBooks = getNumBooks();
    for (int i = 0; i < bookNumber; i++) {
        {if (borrowedBooks[i] == bookId) {

            for (int i = 0; i < numBooks; i++) {
                if (books[i].bookId == bookId) {
                    // Book found in the database, add it
                    for (i = 0; i < bookNumber; i++) {
                        if (borrowedBooks[i] == bookId) {
                            borrowedBooks[i] = 0;
                            break;
                        }
                    }
                    saveData(username);//���µ�username�����ݿ���
                    //   sortBookIds(username);
                    bool judge = addBook(bookId);//add to library
                    if (judge)
                    {
                        cout << "Book returned successfully." << endl;
                        return true;
                    }
                    cout << "Book returned failed." << endl;
                    return false;
                }
            }
        }
        }
    }

    cout << "Book not borrowed by the reader." << endl;
    return false;
}

bool printBorrowedBooks(string username) {

    readerConstructed(username);//��ʼ���û���

    // Print the borrowed books of the reader

    if (bookNumber<=0) {
        cout << "No books borrowed by the reader." << endl;
        return false;
    }
   // cout << "Borrowed Books: " << endl;
    for (int i = 0; i < bookNumber; i++) {
        cout << i+1 << "\t";//������
        printSimpleItem(borrowedBooks[i]);//��ʽ���������Ϣ
    }
    return true;

}


bool saveData(string username) {//д��txt��
    // Save reader's borrowed books to file
    sortBookIds(username);
    ofstream readerFile(username + ".txt");
    if (!readerFile) {
        cout << "Failed to save reader's data." << endl;
        return false;
    }

    for (int bookId : borrowedBooks) {
        if( bookId!=0)
        readerFile << bookId << endl;
    }

    readerFile.close();
    return true;
}
bool sortBookIds(string username) {
        // Sort the book IDs in ascending order
        sort(borrowedBooks, borrowedBooks+bookNumber);
        return true;
}
bool clearDatabase(string username) {
    for (int i = 0; i < bookNumber; i++) {
            borrowedBooks[i] = 0;
    }
    bookNumber = 0;
    saveData(username);
    return true;
}



void editTxtFile(const string& filename) {
    std::ofstream outFile(filename, std::ios::out | std::ios::trunc);

    if (!outFile) {
        cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    //Enter text for the file (Enter '0' on a new line to finish)
    string line;

    while (getline(cin, line) && line != "0") {
        outFile << line << '\n';
    }

    outFile.close();
    cout << "�ѷ�����\n";
}

void printTxtFile(const string& filename) {
    std::ifstream inFile(filename, std::ios::in);

    if (!inFile) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
  //  std::cout << "Content of the file:\n";

    while (std::getline(inFile, line)) {
        std::cout << line << '\n';
    }

    inFile.close();
}
bool searchBooks(const string& searchTerm) {
        // Search for books by title or author in the database
     //   LibrarySystem library("library_db.txt");
        Book* books = getBooks();
        int numBooks = getNumBooks();

        

        for (int i = 0; i < numBooks; i++) {
            if (books[i].bookName == searchTerm || books[i].authorName == searchTerm) {
                cout << "-------------------------" << endl;
                cout << "Book ID: " << books[i].bookId << endl;
                cout << "Book Name: " << books[i].bookName << endl;
                cout << "Author: " << books[i].authorName << endl;
                cout << "Quantity: " << books[i].quantity << endl;
                cout << "-------------------------" << endl;
                return true;
            }
            return false;
            cout << "Book not found in the database." << endl;
        }

    
}
const int MAX_USERS = 100;
bool passwdChange(string username,string newPassword) {
    ifstream userFile(USER_PATH);
    User users[MAX_USERS];
    int numUsers = 0;
    std::string line;

    // ��ȡ�ļ����ݲ������û���Ϣ
    while (getline(userFile, line)) {
        if (numUsers >= MAX_USERS) {
            std::cout << "�ﵽ����û���" << std::endl;
            break;
        }

        //¼��user��Ϣ
        size_t delimiterPos = line.find(' ');
        string temp = line.substr(delimiterPos + 1);
        size_t delimiterPos2 = temp.find(' ');
        if (delimiterPos != std::string::npos) {
            users[numUsers].username = line.substr(0, delimiterPos);
            users[numUsers].password = temp.substr(0, delimiterPos2);
            users[numUsers].userCatgory = temp.substr(delimiterPos2 + 1);
            numUsers++;
            //¼��user��Ϣ
        }
    }
    userFile.close();

    // ����ָ���û�������������
    for (int i = 0; i < numUsers; i++) {
        if (users[i].username == username) {
            users[i].password = newPassword;
            break;
        }
    }

    // ������ĺ���û���Ϣ�ص��ļ�
    std::ofstream outFile(USER_PATH);
    for (int i = 0; i < numUsers; i++) {
        outFile << users[i].username << ' ' << users[i].password <<'  '<<users[i].userCatgory<<'\n';
    }
    outFile.close();
    return true;
}
void printUsers() {
    ifstream userFile(USER_PATH);
    User users[MAX_USERS];
    int numUsers = 0;
    std::string line;

    // ��ȡ�ļ����ݲ������û���Ϣ
    while (getline(userFile, line)) {
        if (numUsers >= MAX_USERS) {
            std::cout << "�ﵽ����û���" << std::endl;
            break;
        }

        //¼��user��Ϣ
        size_t delimiterPos = line.find(' ');
        string temp = line.substr(delimiterPos + 1);
        size_t delimiterPos2 = temp.find(' ');
        if (delimiterPos != std::string::npos) {
            users[numUsers].username = line.substr(0, delimiterPos);
            users[numUsers].password = temp.substr(0, delimiterPos2);
            users[numUsers].userCatgory = temp.substr(delimiterPos2 + 1);
            numUsers++;
            //¼��user��Ϣ
        }
    }
    userFile.close();
    //�ļ����뵽users[]
    for (int i = 0; i < numUsers; i++) {
        cout << endl;
        cout << users[i].username <<'\t' << users[i].userCatgory << "\n";
        cout << "�ѽ����鼮���£�\n";
        printBorrowedBooks(users[i].username);

    }
        return;
}


void addUser(string username, string password) {
    ifstream userFile(USER_PATH);
    User users[MAX_USERS];
    int numUsers = 0;
    std::string line;
    // ��ȡ�ļ����ݲ������û���Ϣ
    while (getline(userFile, line)) {
        if (numUsers >= MAX_USERS) {
            std::cout << "�ﵽ����û���" << std::endl;
            break;
        }
        //¼��user��Ϣ
        size_t delimiterPos = line.find(' ');
        string temp = line.substr(delimiterPos + 1);
        size_t delimiterPos2 = temp.find(' ');
        if (delimiterPos != std::string::npos) {
            users[numUsers].username = line.substr(0, delimiterPos);
            users[numUsers].password = temp.substr(0, delimiterPos2);
            users[numUsers].userCatgory=temp.substr(delimiterPos2+1);
            numUsers++;
            //¼��user��Ϣ
        }
    }
    userFile.close();

    int i;
    for (i = 0; i < numUsers; i++) {
        if (users[i].username == username) {
                cout << "Wrong users.";
                return;
        }
    }

    // Add a new user to the database
	ofstream userFile1(USER_PATH, ios::app);
    if (!userFile1) {
		cout << "Failed to add user." << endl;
		return;
	}
    userFile1 << username << " " << password << " " << "user" << endl;
	userFile1.close();
	cout << "User added successfully." << endl;
	return;
	}
bool deleteUser(string username) {
	// Delete a user from the database
    ifstream userFile(USER_PATH);
    User users[MAX_USERS];
    int numUsers = 0;
    std::string line;
    // ��ȡ�ļ����ݲ������û���Ϣ
    while (getline(userFile, line)) {
        if (numUsers >= MAX_USERS) {
            std::cout << "�ﵽ����û���" << std::endl;
            break;
        }
        //¼��user��Ϣ
        size_t delimiterPos = line.find(' ');
        string temp = line.substr(delimiterPos + 1);
        size_t delimiterPos2 = temp.find(' ');
        if (delimiterPos != std::string::npos) {
            users[numUsers].username = line.substr(0, delimiterPos);
            users[numUsers].password = temp.substr(0, delimiterPos2);
            users[numUsers].userCatgory = temp.substr(delimiterPos2 + 1);
            numUsers++;
            //¼��user��Ϣ
        }
    }
    userFile.close();
	// ����ָ���û�����ɾ��
    int i;
    for (i = 0; i < numUsers; i++) {
        if (users[i].username == username) {
			users[i].username = "";
			users[i].password = "";
            users[i].userCatgory="";
			break;
		}
	}
    if (i >= numUsers)cout << "No matched users.";
	// ������ĺ���û���Ϣ�ص��ļ�
	ofstream outFile(USER_PATH);
    for ( i = 0; i < numUsers; i++) {
		outFile << users[i].username << ' ' << users[i].password << users[i].userCatgory<< '\n';
	}
	outFile.close();
	return true;
}


void addSU() {
    ifstream userFile(USER_PATH);
    User users[MAX_USERS];
    int numUsers = 0;
    std::string line;
    // ��ȡ�ļ����ݲ������û���Ϣ
    while (getline(userFile, line)) {
        if (numUsers >= MAX_USERS) {
            std::cout << "�ﵽ����û���" << std::endl;
            break;
        }
        //¼��user��Ϣ
        size_t delimiterPos = line.find(' ');
        string temp = line.substr(delimiterPos + 1);
        size_t delimiterPos2 = temp.find(' ');
        if (delimiterPos != std::string::npos) {
            users[numUsers].username = line.substr(0, delimiterPos);
            users[numUsers].password = temp.substr(0, delimiterPos2);
            users[numUsers].userCatgory = temp.substr(delimiterPos2 + 1);
            numUsers++;
            //¼��user��Ϣ
        }
    }
    userFile.close();

    for (int i = 0; i < numUsers; i++) {
        cout << endl;
        cout << users[i].username << '\t' << "catgory:"<<users[i].userCatgory << "\n";

    }

    string username,newCatdory;
    cout << "��ѡ��Ҫ���ĵ��û�:  ";
    cin >> username;
    cout << "��ѡ��Ҫ���ĵ���ݣ�  ";
    int choice;
    cout << "1.ͼ�����Ա  2.��ͨ�û�  3.�����û�" << endl;
    cin >> choice;
    switch (choice) {
        case 1:
		newCatdory = "librarian";
		break;
        case 2:
            newCatdory = "user";
            break;
            case 3:
            newCatdory = "admin";
            break;
            default:
			cout << "�������" << endl;
    }

    int i;
    for (i = 0; i < numUsers; i++) {
        if (users[i].username == username) {
            users[i].userCatgory =newCatdory;
            break;
        }
    }
    if (i >= numUsers)cout << "No matched users.";
    // ������ĺ���û���Ϣ�ص��ļ�
    ofstream outFile(USER_PATH);
    for (i = 0; i < numUsers; i++) {
        outFile << users[i].username << ' ' << users[i].password <<' '<< users[i].userCatgory << '\n';
    }
    outFile.close();
    return;
}
