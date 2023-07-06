
#include"ReaderOperation.h"
//#include "DatabaseOperation.cpp"

string getPasswd() {
    string passwd;
#ifdef _WIN32
    char ch;
    while ((ch = _getch()) != '\r') {  // 读取键盘输入直到按下回车键
        if (ch == '\b') {  // 处理退格键
            if (!passwd.empty()) {
                passwd.pop_back();
                std::cout << "\b \b";
            }
        }
        else {
            passwd.push_back(ch);
            std::cout << '*';
        }
    }
#endif
    return passwd;
}

void readerConstructed(string username) {//初始化一个user，从文件读数据；
ifstream readerFile(USER_DATA_PATH+username + ".txt");
if (readerFile) {
    int bookId;
    long long borrowedTime;
    int i=0;
    while (readerFile >> bookId>> borrowedTime) {//读入,判断异常还书
        borrowedBooks[i].bookId=bookId;
        borrowedBooks[i].borrowedTime = borrowedTime;
        if (!isRightCommit(borrowedTime)) {
            recordWrongCommit(username,borrowedBooks[i]);
        }
        i++;
    }
    readerFile.close();
    bookNumber = i;//读入借阅单，记下本数；
}
}

void constructedAll() {
    clearTxt(WRONG_COMMIT);
    User users[100];
    ifstream userFile(USER_PATH);
    int numUsers = 0;
    std::string line;
    
    // 读取文件内容并解析用户信息
    while (getline(userFile, line)) {

        //录入user信息
        size_t delimiterPos = line.find(' ');
        string temp = line.substr(delimiterPos + 1);
        size_t delimiterPos2 = temp.find(' ');
        if (delimiterPos != std::string::npos) {
            users[numUsers].username = line.substr(0, delimiterPos);
            readerConstructed(users[numUsers].username);//初始化用每个户库
            numUsers++;
            //录入user信息
        }
    }
    userFile.close();
    ////文件读入到users[]
    //for (int i = 0; i < numUsers; i++) {

    //}
}



void borrowBook(string username, int bookId) {
    // Check if the book exists in the database
    DATA_BASE_PATH;//Library path
   
    Book* thisbooks = getBooks();
    int numBooks = getNumBooks();
    for (int i = 0; i < numBooks; i++) {
        if (books[i].bookId == bookId&& books[i].quantity>0) {
            // Book found in the database, add it to the reader's borrowed books
            borrowedBooks[bookNumber].bookId=bookId;
            borrowedBooks[bookNumber].borrowedTime = time(0);
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
        {if (borrowedBooks[i].bookId == bookId) {

            for (int i = 0; i < numBooks; i++) {
                if (books[i].bookId == bookId) {
                    // Book found in the database, add it
                    for (i = 0; i < bookNumber; i++) {
                        if (borrowedBooks[i].bookId == bookId) {
                            borrowedBooks[i].bookId = 0;
                            borrowedBooks[i].borrowedTime = 0;
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

    readerConstructed(username);//初始化用每个户库
   // USER_DATA_PATH + username + ".txt"
    // Print the borrowed books of the reader

    if (bookNumber<=0) {
        cout << "-------------------------------------------------------------------------------------------\n";
        cout << "No books borrowed by the reader." << endl;
        cout << "-------------------------------------------------------------------------------------------\n";
        return false;
    }
   // cout << "Borrowed Books: " << endl;
    cout << "-------------------------------------------------------------------------------------------\n";
    for (int i = 0; i < bookNumber; i++) {
        cout << i+1 << "\t";//输出序号
        printSimpleItem(borrowedBooks[i].bookId);//格式输出借阅信息
        cout <<showTime(borrowedBooks[i].borrowedTime) << endl;
    }
    cout << "-------------------------------------------------------------------------------------------\n";    return true;
   // clearDatabase(username);
}


bool saveData(string username) {//写到txt中
    // Save reader's borrowed books to file
    sortBookIds(username);
    ofstream readerFile(USER_DATA_PATH+username + ".txt");
    if (!readerFile) {
        cout << "Failed to save reader's data." << endl;
        return false;
    }

    for (BorrowedBooks toGetBookId : borrowedBooks) {
        int bookId = toGetBookId.bookId;
        if( bookId!=0)
        readerFile << bookId <<" "<< toGetBookId.borrowedTime<< endl;
    }

    readerFile.close();
    return true;
}
bool cmp(BorrowedBooks a, BorrowedBooks b) {
    return a.bookId < b.bookId;
}
bool sortBookIds(string username) {
        // Sort the book IDs in ascending order
        sort(borrowedBooks, borrowedBooks+bookNumber,cmp);
        return true;
}
bool clearDatabase(string username) {
    for (int i = 0; i < bookNumber; i++) {
            borrowedBooks[i].bookId = 0;
            borrowedBooks[i].borrowedTime = 0;
    }
    bookNumber = 0;
    saveData(username);
    return true;
}



void addTxtFile(const string& filename) {
    time_t ts = time(NULL);
    std::ofstream outFile(filename, ios::app);//| std::ios::trunc

    if (!outFile) {
        cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    //Enter text for the file (Enter '0' on a new line to finish)
    string line;

        outFile << "-----"<<ctime(&ts);
    while (getline(cin, line) && line != "0") {
        outFile << line << '\n';
    }
    outFile << '\n';
    outFile.close();
    cout << "已添加！\n";
}

void editTxtFile(const string& filename) {
    time_t ts = time(NULL);
    std::ofstream outFile(filename, ios::out | std::ios::trunc);

    if (!outFile) {
        cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    //Enter text for the file (Enter '0' on a new line to finish)
    string line;
    outFile << "-----" << ctime(&ts);
    while (getline(cin, line) && line != "0") {
        outFile << line << '\n';
    }
    outFile << '\n';
    outFile.close();
    cout << "已发布！\n";
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
        Book* books = getBooks();
        int numBooks = getNumBooks();

        

        for (int i = 0; i < numBooks; i++) {
            if (AllisNum(searchTerm)) {
            if (books[i].bookName == searchTerm || books[i].authorName == searchTerm || books[i].bookId == stoi(searchTerm)) {
                cout << "-------------------------" << endl;
                cout << "Book ID: " << books[i].bookId << endl;
                cout << "Book Name: " << books[i].bookName << endl;
                cout << "Author: " << books[i].authorName << endl;
                cout << "Quantity: " << books[i].quantity << endl;
                cout << "-------------------------" << endl;
                return true;
            }
            }
            else {
                if (books[i].bookName == searchTerm || books[i].authorName == searchTerm ) {
                    cout << "-------------------------" << endl;
                    cout << "Book ID: " << books[i].bookId << endl;
                    cout << "Book Name: " << books[i].bookName << endl;
                    cout << "Author: " << books[i].authorName << endl;
                    cout << "Quantity: " << books[i].quantity << endl;
                    cout << "-------------------------" << endl;
                    return true;
                }
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

    // 读取文件内容并解析用户信息
    while (getline(userFile, line)) {
        if (numUsers >= MAX_USERS) {
            std::cout << "达到最大用户数" << std::endl;
            break;
        }

        //录入user信息
        size_t delimiterPos = line.find(' ');
        string temp = line.substr(delimiterPos + 1);
        size_t delimiterPos2 = temp.find(' ');
        if (delimiterPos != std::string::npos) {
            users[numUsers].username = line.substr(0, delimiterPos);
            users[numUsers].password = temp.substr(0, delimiterPos2);
            users[numUsers].userCatgory = temp.substr(delimiterPos2 + 1);
            numUsers++;
            //录入user信息
        }
    }
    userFile.close();

    // 查找指定用户名并更改密码
    for (int i = 0; i < numUsers; i++) {
        if (users[i].username == username) {
            users[i].password = newPassword;
            break;
        }
    }

    // 保存更改后的用户信息回到文件
    std::ofstream outFile(USER_PATH);
    for (int i = 0; i < numUsers; i++) {
        outFile << users[i].username <<" " << users[i].password <<" " << users[i].userCatgory << '\n';
    }
    outFile.close();
    return true;
}
void printUsers() {
    ifstream userFile(USER_PATH);
    User users[MAX_USERS];
    int numUsers = 0;
    std::string line;

    // 读取文件内容并解析用户信息
    while (getline(userFile, line)) {
        if (numUsers >= MAX_USERS) {
            std::cout << "达到最大用户数" << std::endl;
            break;
        }

        //录入user信息
        size_t delimiterPos = line.find(' ');
        string temp = line.substr(delimiterPos + 1);
        size_t delimiterPos2 = temp.find(' ');
        if (delimiterPos != std::string::npos) {
            users[numUsers].username = line.substr(0, delimiterPos);
            users[numUsers].password = temp.substr(0, delimiterPos2);
            users[numUsers].userCatgory = temp.substr(delimiterPos2 + 1);
            numUsers++;
            //录入user信息
        }
    }
    userFile.close();
    //文件读入到users[]
    for (int i = 0; i < numUsers; i++) {
        cout << endl;
        cout << setw(10) << users[i].username <<"  (  " << users[i].userCatgory << "  )";
        cout <<setw(10) << "已借阅书籍如下：\n";
        readerConstructed(users[i].username);//初始化用每个户库
        printBorrowedBooks(users[i].username);
        cout << endl << endl;
        readerConstructed(currentUser.username);//初始化用每个户库
    }
        return;
}


void addUser(string username, string password) {
    ifstream userFile(USER_PATH);
    User users[MAX_USERS];
    int numUsers = 0;
    std::string line;
    // 读取文件内容并解析用户信息
    while (getline(userFile, line)) {
        if (numUsers >= MAX_USERS) {
            std::cout << "达到最大用户数" << std::endl;
            break;
        }
        //录入user信息
        size_t delimiterPos = line.find(' ');
        string temp = line.substr(delimiterPos + 1);
        size_t delimiterPos2 = temp.find(' ');
        if (delimiterPos != std::string::npos) {
            users[numUsers].username = line.substr(0, delimiterPos);
            users[numUsers].password = temp.substr(0, delimiterPos2);
            users[numUsers].userCatgory=temp.substr(delimiterPos2+1);
            numUsers++;
            //录入user信息
        }
    }
    userFile.close();

    int i;
    for (i = 0; i < numUsers; i++) {
        if (users[i].username == username) {
                cout << "Have same users.";
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
    ofstream file(USER_DATA_PATH+username+".txt");//初始化文件
    file.close();
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
    // 读取文件内容并解析用户信息
    while (getline(userFile, line)) {
        if (numUsers >= MAX_USERS) {
            std::cout << "达到最大用户数" << std::endl;
            break;
        }
        //录入user信息
        size_t delimiterPos = line.find(' ');
        string temp = line.substr(delimiterPos + 1);
        size_t delimiterPos2 = temp.find(' ');
        if (delimiterPos != std::string::npos) {
            users[numUsers].username = line.substr(0, delimiterPos);
            users[numUsers].password = temp.substr(0, delimiterPos2);
            users[numUsers].userCatgory = temp.substr(delimiterPos2 + 1);
            numUsers++;
            //录入user信息
        }
    }
    userFile.close();
	// 查找指定用户名并删除
    int i,num;
    for (i = 0; i < numUsers; i++) {
        if (users[i].username == username) {
			users[i].username = "";
			users[i].password = "";
            users[i].userCatgory="";
            string path = USER_DATA_PATH + username + ".txt";
            const char* cstr = path.c_str();
            remove(cstr);//删除用户文件
            num = i;
			break;
		}
	}
    if (i >= numUsers)cout << "No matched users.";
	// 保存更改后的用户信息回到文件
	ofstream outFile(USER_PATH);
    for ( i = 0; i < numUsers; i++) {
        if(num!=i)
		outFile << users[i].username << ' ' << users[i].password <<' '<< users[i].userCatgory << '\n';
	}
	outFile.close();
    

	return true;
}


void addSU() {
    ifstream userFile(USER_PATH);
    User users[MAX_USERS];
    int numUsers = 0;
    std::string line;
    // 读取文件内容并解析用户信息
    while (getline(userFile, line)) {
        if (numUsers >= MAX_USERS) {
            std::cout << "达到最大用户数" << std::endl;
            break;
        }
        //录入user信息
        size_t delimiterPos = line.find(' ');
        string temp = line.substr(delimiterPos + 1);
        size_t delimiterPos2 = temp.find(' ');
        if (delimiterPos != std::string::npos) {
            users[numUsers].username = line.substr(0, delimiterPos);
            users[numUsers].password = temp.substr(0, delimiterPos2);
            users[numUsers].userCatgory = temp.substr(delimiterPos2 + 1);
            numUsers++;
            //录入user信息
        }
    }
    userFile.close();

    for (int i = 0; i < numUsers; i++) {
        cout << endl;
        cout << "\t"<<users[i].username << "  (  " << users[i].userCatgory << "  )\n";

    }

    string username,newCatdory;
    cout << "-请选择要更改的用户: (输入0返回上级) ";
    cin >> username;
    if (username.length() == 1)
    if (stoi(username) == 0) {
        back(false);
        return;
    }
    cout << "--请选择要更改的身份：  ";
    int choice;
    cout << "\n---1.图书管理员  \n---2.普通用户  \n---3.超级用户" << endl;
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
			cout << "----输入错误" << endl;
    }

    int i;
    for (i = 0; i < numUsers; i++) {
        if (users[i].username == username) {
            users[i].userCatgory =newCatdory;
            break;
        }
    }
    if (i >= numUsers)cout << "No matched users.";
    // 保存更改后的用户信息回到文件
    ofstream outFile(USER_PATH);
    for (i = 0; i < numUsers; i++) {
        outFile << users[i].username << ' ' << users[i].password <<' '<< users[i].userCatgory << '\n';
    }
    outFile.close();
    return;
}


bool isRightCommit(time_t lastExecutionTime) {
    time_t days = (time(0) - lastExecutionTime) / (60);//(60 * 60 * 24)天数，用int取整
    if (days > 5)return false;
    return true;
}


string showTime(long long time1) {
    time_t time = static_cast<time_t>(time1);//格式转化
    tm* timeinfo = localtime(&time);
    char buffer[11];
    std::strftime(buffer, sizeof(buffer), "%Y/%m/%d", timeinfo);
    return buffer;
}

void recordWrongCommit(string username,BorrowedBooks borrowedBook) {
    // string WRONG_COMMIT;//异常还书记录
    std::ofstream outputFile(WRONG_COMMIT,ios::app);//增加式写入
    if (outputFile.is_open()) {
        outputFile << username<<" "<< borrowedBook.bookId<<" "<< showTime(borrowedBook.borrowedTime)<<endl;
        outputFile.close();
    }
}
void printWrongCommit() {
    std::ifstream inFile(WRONG_COMMIT, std::ios::in);

    if (!inFile) {
        std::cerr << "Error opening file: " << WRONG_COMMIT << std::endl;
        return;
    }

    std::string line;
    //  std::cout << "Content of the file:\n";

    while (std::getline(inFile, line)) {
        std::cout << line << '\n';
    }

    inFile.close();
}