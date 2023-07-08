#include "DatabaseOperation.h"

using namespace std;
bool addBook(const  string& bookName, const  string& authorName, int quantity, int year) {
    loadDatabase();//���ǰ�ȴӿ��ʼ��
    for (int i = 0; i < numBooks; i++) {
        if (books[i].bookName == bookName) {
            // ͼ���Ѵ��ڣ���������
            books[i].quantity += quantity;
            saveDatabase();
            return true;
            cout << "ͼ����ӳɹ���";
        }
    }

    // ͼ�鲻���ڣ��������Ŀ
    int bookId = getNextBookId();

    // ��չ�����С
    Book* newBooks = new Book[numBooks + 1];
    for (int i = 0; i < numBooks; i++) {
        newBooks[i] = books[i];
    }
    delete[] books;
    books = newBooks;

    // �����ͼ��
    books[numBooks].bookName = bookName;
    books[numBooks].authorName = authorName;
    books[numBooks].quantity = quantity;
    books[numBooks].bookId = bookId;
    books[numBooks].year = year;
    numBooks++;

    saveDatabase();
}
bool addBook(const int bookID) {
    loadDatabase();//���ǰ�ȴӿ��ʼ��
    for (int i = 0; i < numBooks; i++) {
        if (books[i].bookId == bookID) {
            // ͼ����ڣ���������
            books[i].quantity++;
           
            saveDatabase();
            cout << "ͼ����ӳɹ���\n";
            return true;
        }
    }
    return false;
}
void removeBook(const int bookID) {
    loadDatabase();//���ǰ�ȴӿ��ʼ��
    for (int i = 0; i < numBooks; i++) {
        if (books[i].bookId == bookID) {
            // ͼ����ڣ���������
            books[i].quantity--;
            if (books[i].quantity <= 0) {
                books[i].quantity = 0;
                // ��������Ϊ��ʱ
                //��Ϊ����0
            }
            saveDatabase();
            cout << "Book removed (lib) successfully." << endl;
            return;
        }
    }
    cout << "Book not found in the database." << endl;
}


void printDatabase() {
    int width = 20;
    loadDatabase();//���ǰ�ȴӿ��ʼ��
    cout << setw(width) << "-----------�������-----------" << endl;
    for (int i = 0; i < numBooks; i++) {
        if (books[i].quantity!=0) {
 cout << setw(width) << "Book ID: " << books[i].bookId << endl;
        cout << setw(width) << "Book Name: " << books[i].bookName << endl;
        cout << setw(width) << "Author: " << books[i].authorName << endl;
        cout << setw(width) << "Quantity: " << books[i].quantity << endl;
        cout << setw(width) << "Publish Year: " << books[i].year << endl;
        cout << setw(width) << "-----------------------------" << endl;
        }
       
    }
    cout << setw(width) << "----- End of Database -----" << endl;
}

bool printSimpleItem(int bookId) {//ͨ��bookId������Ϣ
    for (int i = 0; i < numBooks; i++) {
        if (books[i].bookId == bookId) 
        {
   cout <<"     �鼮 ID: " << setw(3) << books[i].bookId <<"\t";
   cout << "�鼮����: " << setw(10) << books[i].bookName << "\t";
        cout << "����: " << setw(10) << books[i].authorName << "\t" << "\t";
        cout << "�������: " << setw(6) << books[i].year ;
        return true;
        }
    }
    return false;
    cout << "No matched item.";
}


void clearDatabase() {
    delete[] books;
    books = nullptr;
    numBooks = 0;
    saveDatabase();
}

int getNextBookId() {
    int maxId = 0;
    for (int i = 0; i < numBooks; i++) {
        if (books[i].bookId > maxId) {
            maxId = books[i].bookId;
        }
    }
    return maxId + 1;
}

void loadDatabase() {
    ifstream databaseFile(DATA_BASE_PATH);
    if (!databaseFile) {
        cout << "Database file not found. Creating a new database." << endl;
        books = nullptr;
        numBooks = 0;
        return;
    }

    // ��ȡ�ļ��е�ͼ������
    string line;
    getline(databaseFile, line);
    stringstream ss(line);
    ss >> numBooks;

    // ����ͼ��������ڴ�
    books = new Book[numBooks];

    // ��ȡÿ��ͼ�����Ϣ
    for (int i = 0; i < numBooks; i++) {
        getline(databaseFile, line);
        stringstream ss(line);
        ss >> books[i].bookId >> books[i].bookName >> books[i].authorName >> books[i].quantity >> books[i].year;
    }

    databaseFile.close();
}

void saveDatabase() {
    ofstream databaseFile(DATA_BASE_PATH);
    if (!databaseFile) {
        cout << "Failed to save database." << endl;
        return;
    }

    // д��ͼ������
    databaseFile << numBooks << endl;

    // д��ÿ��ͼ�����Ϣ
    for (int i = 0; i < numBooks; i++) {
        databaseFile << books[i].bookId << " " << books[i].bookName << " " << books[i].authorName << " " << books[i].quantity << " " << books[i].year << endl;
    }

    databaseFile.close();
}


void searchBook(const  string& searchQuery) {
    bool found = false;
    for (int i = 0; i < numBooks; i++) {
        if (books[i].bookName == searchQuery || books[i].authorName == searchQuery) {
             cout << "Book ID: " << books[i].bookId <<  endl;
             cout << "Book Name: " << books[i].bookName <<  endl;
             cout << "Author: " << books[i].authorName <<  endl;
             cout << "Quantity: " << books[i].quantity <<  endl;
             cout << "-------------------------" <<  endl;
            found = true;
        }
    }
    if (!found) {
         cout << "Book not found in the database." <<  endl;
    }
}

Book* findBookById(int bookId) {
    for (int i = 0; i < numBooks; i++) {
        if (books[i].bookId == bookId) {
            return &books[i];
        }
    }
    return nullptr;
}
Book* getBooks() {
    return books;
}

int getNumBooks() {
    return numBooks;
}



void clearTxt(string filename) {
     ofstream file(filename,  ios::trunc);  // ���ļ����ض�����

    if (file.is_open()) {
        file.close();
    }
    else {
         cout << "�޷����ļ���" <<  endl;
    }
}

