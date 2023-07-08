#include "DatabaseOperation.h"

using namespace std;
bool addBook(const  string& bookName, const  string& authorName, int quantity, int year) {
    loadDatabase();//输出前先从库初始化
    for (int i = 0; i < numBooks; i++) {
        if (books[i].bookName == bookName) {
            // 图书已存在，增加数量
            books[i].quantity += quantity;
            saveDatabase();
            return true;
            cout << "图书添加成功！";
        }
    }

    // 图书不存在，添加新条目
    int bookId = getNextBookId();

    // 扩展数组大小
    Book* newBooks = new Book[numBooks + 1];
    for (int i = 0; i < numBooks; i++) {
        newBooks[i] = books[i];
    }
    delete[] books;
    books = newBooks;

    // 添加新图书
    books[numBooks].bookName = bookName;
    books[numBooks].authorName = authorName;
    books[numBooks].quantity = quantity;
    books[numBooks].bookId = bookId;
    books[numBooks].year = year;
    numBooks++;

    saveDatabase();
}
bool addBook(const int bookID) {
    loadDatabase();//输出前先从库初始化
    for (int i = 0; i < numBooks; i++) {
        if (books[i].bookId == bookID) {
            // 图书存在，减少数量
            books[i].quantity++;
           
            saveDatabase();
            cout << "图书添加成功！\n";
            return true;
        }
    }
    return false;
}
void removeBook(const int bookID) {
    loadDatabase();//输出前先从库初始化
    for (int i = 0; i < numBooks; i++) {
        if (books[i].bookId == bookID) {
            // 图书存在，减少数量
            books[i].quantity--;
            if (books[i].quantity <= 0) {
                books[i].quantity = 0;
                // 数量减少为零时
                //改为数量0
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
    loadDatabase();//输出前先从库初始化
    cout << setw(width) << "-----------书库如下-----------" << endl;
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

bool printSimpleItem(int bookId) {//通过bookId查找信息
    for (int i = 0; i < numBooks; i++) {
        if (books[i].bookId == bookId) 
        {
   cout <<"     书籍 ID: " << setw(3) << books[i].bookId <<"\t";
   cout << "书籍名称: " << setw(10) << books[i].bookName << "\t";
        cout << "作者: " << setw(10) << books[i].authorName << "\t" << "\t";
        cout << "刊登年份: " << setw(6) << books[i].year ;
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

    // 获取文件中的图书数量
    string line;
    getline(databaseFile, line);
    stringstream ss(line);
    ss >> numBooks;

    // 分配图书数组的内存
    books = new Book[numBooks];

    // 读取每本图书的信息
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

    // 写入图书数量
    databaseFile << numBooks << endl;

    // 写入每本图书的信息
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
     ofstream file(filename,  ios::trunc);  // 打开文件并截断内容

    if (file.is_open()) {
        file.close();
    }
    else {
         cout << "无法打开文件。" <<  endl;
    }
}

