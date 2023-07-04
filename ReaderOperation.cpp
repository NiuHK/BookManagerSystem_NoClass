
#include"ReaderOperation.h"
//#include "DatabaseOperation.cpp"
using namespace std;


void readerConstructed(string username) {//初始化一个user，从文件读数据；
ifstream readerFile(username + ".txt");
if (readerFile) {
    int bookId;
    int i=0;
    while (readerFile >> bookId) {//读入
        borrowedBooks[i]=bookId;
        i++;
    }
    readerFile.close();
    bookNumber = i;//读入借阅单，记下本数；
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
            saveData(username);//更新到username的数据库内
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
                    saveData(username);//更新到username的数据库内
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
    // Print the borrowed books of the reader

    if (bookNumber<=0) {
        cout << "No books borrowed by the reader." << endl;
        return false;
    }
   // cout << "Borrowed Books: " << endl;
    for (int i = 0; i < bookNumber; i++) {
        cout << i+1 << "\t";//输出序号
        printSimpleItem(borrowedBooks[i]);//格式输出借阅信息
    }
    return true;

}


bool saveData(string username) {//写到txt中
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
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    //Enter text for the file (Enter '0' on a new line to finish)
    string line;

    while (std::getline(std::cin, line) && line != "0") {
        outFile << line << '\n';
    }

    outFile.close();
    std::cout << "已发布！\n";
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