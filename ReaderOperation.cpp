
#include"ReaderOperation.h"

string getPasswd() {
    string passwd;
#ifdef _WIN32
    char ch;
    while ((ch = _getch()) != '\r') {  // ��ȡ��������ֱ�����»س���
        if (ch == '\b') {  // �����˸��
            if (!passwd.empty()) {
                passwd.pop_back();
                
                cout << "\b \b";
            }
        }
        else {
            passwd.push_back(ch);
             cout << '*';
        }
    }
#endif
    return passwd;
}

void readerConstructed(string username) {//��ʼ��һ��user�����ļ������ݣ�
ifstream readerFile(USER_DATA_PATH+username + ".txt");
if (readerFile) {
    int bookId;
    long long borrowedTime;
    int i=0;
    while (readerFile >> bookId>> borrowedTime) {//����,�ж��쳣����
        borrowedBooks[i].bookId=bookId;
        borrowedBooks[i].borrowedTime = borrowedTime;
        if (!isRightCommit(borrowedTime)) {
            recordWrongCommit(username,borrowedBooks[i]);
        }
        i++;
    }
    readerFile.close();
    bookNumber = i;//������ĵ������±�����
}
}

void constructedAll() {
    clearTxt(WRONG_COMMIT);
    User users[100];
    ifstream userFile(USER_PATH);
    int numUsers = 0;
     string line;
    
    // ��ȡ�ļ����ݲ������û���Ϣ
    while (getline(userFile, line)) {

        //¼��user��Ϣ
        size_t delimiterPos = line.find(' ');
        string temp = line.substr(delimiterPos + 1);
        size_t delimiterPos2 = temp.find(' ');
        if (delimiterPos !=  string::npos) {
            users[numUsers].username = line.substr(0, delimiterPos);
            readerConstructed(users[numUsers].username);//��ʼ����ÿ������
            numUsers++;
            //¼��user��Ϣ
        }
    }
    userFile.close();
    ////�ļ����뵽users[]
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
    bookId--;
    // Check if the book exists in the database
    Book* thisbooks = getBooks();
    int bookIdTemp;
            for (int j = 0; j < numBooks; j++) {
                if (books[j].bookId == borrowedBooks[bookId].bookId) {
                    // Book found in the database, add it
                    borrowedBooks[bookId].bookId = 0;
                    borrowedBooks[bookId].borrowedTime = 0;
                    bookIdTemp = books[j].bookId;
                    numBooks--;
                    bookNumber--;
                    break;
                }
            }
            saveData(username);//���µ�username�����ݿ���
            bool judge = addBook(bookIdTemp);//add to library
            if (judge)
                cout << "Book returned successfully." << numBooks << " " << bookNumber << endl;
                return true;
            
            cout << "Book returned failed." << endl;
            return false;
        
    
    cout << "Book not borrowed by the reader." << endl;
    return false;
}


//bool returnBook(string username, int bookId) {
//    // Check if the book exists in the database
//    Book* thisbooks = getBooks();
//    for (int i = 0; i < bookNumber; i++) {
//        if (borrowedBooks[i].bookId == bookId) { 
//            for (int j = 0; j < numBooks; j++) {
//                if (books[j].bookId == bookId) {
//                    // Book found in the database, add it
//                    borrowedBooks[i].bookId = 0;
//                    borrowedBooks[i].borrowedTime = 0;
//                    numBooks--;
//                    bookNumber--;
//                    break;
//                }
//            }
//                    saveData(username);//���µ�username�����ݿ���
//                    bool judge = addBook(bookId);//add to library
//                    if (judge)
//                    {
//                        cout << "Book returned successfully."<< numBooks<<" "<< bookNumber << endl;
//                        return true;
//                    }
//                    cout << "Book returned failed." << endl;
//                    return false;
//                
//            
//        }
//        
//    }
//
//    cout << "Book not borrowed by the reader." << endl;
//    return false;
//}

bool printBorrowedBooks(string username) {

    readerConstructed(username);//��ʼ����ÿ������
   // USER_DATA_PATH + username + ".txt"
    // Print the borrowed books of the reader

    if (bookNumber<=0) {
        cout << "-------------------------------------------------------------------------------------------\n";
        cout << "No books borrowed by the reader." << endl;
        cout << "-------------------------------------------------------------------------------------------\n";
        return false;
    }
   // cout << "Borrowed Books: " << endl;
    cout << "-------------------------------------------------------------------------------------------------------------------------------------\n";
    for (int i = 0; i < bookNumber; i++) {
        cout << "��Ŀ��ţ� " << i + 1;//������
        printSimpleItem(borrowedBooks[i].bookId);//��ʽ���������Ϣ
        cout << "����ʱ�䣺 " <<setw(10)<<showTime(borrowedBooks[i].borrowedTime) << endl<<endl;
    }
    cout << "-------------------------------------------------------------------------------------------------------------------------------------\n";    return true;
   // clearDatabase(username);
}


bool saveData(string username) {//д��txt��
    // Save reader's borrowed books to file
    sortBookIds(username);
    ofstream readerFile(USER_DATA_PATH+username + ".txt");
    if (!readerFile) {
        cout << "Failed to save reader's data."<< endl;
        return false;
    }
    for (BorrowedBooks toGetBookId : borrowedBooks) {
        if(toGetBookId.bookId !=0)
        readerFile << toGetBookId.bookId <<" "<< toGetBookId.borrowedTime<< endl;
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
     ofstream outFile(filename, ios::app);//|  ios::trunc

    if (!outFile) {
        cerr << "Error opening file: " << filename <<  endl;
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
    cout << "����ӣ�\n";
}

void editTxtFile(const string& filename) {
    time_t ts = time(NULL);
     ofstream outFile(filename, ios::out |  ios::trunc);

    if (!outFile) {
        cerr << "Error opening file: " << filename <<  endl;
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
    cout << "�ѷ�����\n";
}

void printTxtFile(const string& filename) {
     ifstream inFile(filename,  ios::in);

    if (!inFile) {
         cerr << "Error opening file: " << filename <<  endl;
        return;
    }

     string line;
  //   cout << "Content of the file:\n";

    while ( getline(inFile, line)) {
         cout << line << '\n';
    }

    inFile.close();
}
bool searchBooks(const string& searchTerm) {
    // Search for books by title or author in the database
    int numBooks = getNumBooks();
    loadDatabase();
    int i = 0;
    for (i = 0; i < numBooks; i++) {


        if (AllisNum(searchTerm)) {
            if (books[i].bookName == searchTerm || books[i].authorName == searchTerm || books[i].bookId == stoi(searchTerm)) {
                cout << "-------------------------" << endl;
                cout << "Book ID: " << books[i].bookId << endl;
                cout << "Book Name: " << books[i].bookName << endl;
                cout << "Author: " << books[i].authorName << endl;
                cout << "Quantity: " << books[i].quantity << endl;
                cout << "-------------------------" << endl;
            }
        }
        else {
            if (books[i].bookName == searchTerm || books[i].authorName == searchTerm) {
                cout << "-------------------------" << endl;
                cout << "Book ID: " << books[i].bookId << endl;
                cout << "Book Name: " << books[i].bookName << endl;
                cout << "Author: " << books[i].authorName << endl;
                cout << "Quantity: " << books[i].quantity << endl;
                cout << "-------------------------" << endl;
            }
        }
    }
}
    
const int MAX_USERS = 100;
bool passwdChange(string username,string newPassword) {
    ifstream userFile(USER_PATH);
    User users[MAX_USERS];
    int numUsers = 0;
     string line;

    // ��ȡ�ļ����ݲ������û���Ϣ
    while (getline(userFile, line)) {
        if (numUsers >= MAX_USERS) {
             cout << "�ﵽ����û���" <<  endl;
            break;
        }

        //¼��user��Ϣ
        size_t delimiterPos = line.find(' ');
        string temp = line.substr(delimiterPos + 1);
        size_t delimiterPos2 = temp.find(' ');
        if (delimiterPos !=  string::npos) {
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
     ofstream outFile(USER_PATH);
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
     string line;

    // ��ȡ�ļ����ݲ������û���Ϣ
    while (getline(userFile, line)) {
        if (numUsers >= MAX_USERS) {
             cout << "�ﵽ����û���" <<  endl;
            break;
        }

        //¼��user��Ϣ
        size_t delimiterPos = line.find(' ');
        string temp = line.substr(delimiterPos + 1);
        size_t delimiterPos2 = temp.find(' ');
        if (delimiterPos !=  string::npos) {
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
        cout << setw(10) << users[i].username <<"  (  " << users[i].userCatgory << "  )";
        cout <<setw(10) << "�ѽ����鼮���£�\n";
        readerConstructed(users[i].username);//��ʼ����ÿ������
        printBorrowedBooks(users[i].username);
        cout << endl << endl;
        readerConstructed(currentUser.username);//��ʼ����ÿ������
    }
        return;
}


void addUser(string username, string password) {
    ifstream userFile(USER_PATH);
    User users[MAX_USERS];
    int numUsers = 0;
     string line;
    // ��ȡ�ļ����ݲ������û���Ϣ
    while (getline(userFile, line)) {
        if (numUsers >= MAX_USERS) {
             cout << "�ﵽ����û���" <<  endl;
            break;
        }
        //¼��user��Ϣ
        size_t delimiterPos = line.find(' ');
        string temp = line.substr(delimiterPos + 1);
        size_t delimiterPos2 = temp.find(' ');
        if (delimiterPos !=  string::npos) {
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
    ofstream file(USER_DATA_PATH+username+".txt");//��ʼ���ļ�
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
     string line;
    // ��ȡ�ļ����ݲ������û���Ϣ
    while (getline(userFile, line)) {
        if (numUsers >= MAX_USERS) {
             cout << "�ﵽ����û���" <<  endl;
            break;
        }
        //¼��user��Ϣ
        size_t delimiterPos = line.find(' ');
        string temp = line.substr(delimiterPos + 1);
        size_t delimiterPos2 = temp.find(' ');
        if (delimiterPos !=  string::npos) {
            users[numUsers].username = line.substr(0, delimiterPos);
            users[numUsers].password = temp.substr(0, delimiterPos2);
            users[numUsers].userCatgory = temp.substr(delimiterPos2 + 1);
            numUsers++;
            //¼��user��Ϣ
        }
    }
    userFile.close();
	// ����ָ���û�����ɾ��
    int i,num;
    for (i = 0; i < numUsers; i++) {
        if (users[i].username == username) {
			users[i].username = "";
			users[i].password = "";
            users[i].userCatgory="";
            string path = USER_DATA_PATH + username + ".txt";
            const char* cstr = path.c_str();
            remove(cstr);//ɾ���û��ļ�
            num = i;
			break;
		}
	}
    if (i >= numUsers)cout << "No matched users.";
	// ������ĺ���û���Ϣ�ص��ļ�
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
     string line;
    // ��ȡ�ļ����ݲ������û���Ϣ
    while (getline(userFile, line)) {
        if (numUsers >= MAX_USERS) {
             cout << "�ﵽ����û���" <<  endl;
            break;
        }
        //¼��user��Ϣ
        size_t delimiterPos = line.find(' ');
        string temp = line.substr(delimiterPos + 1);
        size_t delimiterPos2 = temp.find(' ');
        if (delimiterPos !=  string::npos) {
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
        cout << "\t"<<users[i].username << "  (  " << users[i].userCatgory << "  )\n";

    }

    string username,newCatdory;
    cout << "-��ѡ��Ҫ���ĵ��û�: (����0�����ϼ�) ";
    cin >> username;
    if (username.length() == 1)
    if (stoi(username) == 0) {
        back(false);
        return;
    }
    cout << "--��ѡ��Ҫ���ĵ���ݣ�  ";
    int choice;
    cout << "\n---1.ͼ�����Ա  \n---2.��ͨ�û�  \n---3.�����û�" << endl;
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
			cout << "----�������" << endl;
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


bool isRightCommit(time_t lastExecutionTime) {
    time_t days = (time(0) - lastExecutionTime) / (60);//(60 * 60 * 24)��������intȡ��
    if (days > 5)return false;
    return true;
}


string showTime(long long time1) {
    time_t time = static_cast<time_t>(time1);//��ʽת��
    tm* timeinfo = localtime(&time);
    char buffer[11];
     strftime(buffer, sizeof(buffer), "%Y/%m/%d", timeinfo);
    return buffer;
}

void recordWrongCommit(string username,BorrowedBooks borrowedBook) {
    // string WRONG_COMMIT;//�쳣�����¼
     ofstream outputFile(WRONG_COMMIT,ios::app);//����ʽд��
    if (outputFile.is_open()) {
        outputFile << username<<" "<< borrowedBook.bookId<<" "<< showTime(borrowedBook.borrowedTime)<<endl;
        outputFile.close();
    }
}
void printWrongCommit() {
     ifstream inFile(WRONG_COMMIT,  ios::in);

    if (!inFile) {
         cerr << "Error opening file: " << WRONG_COMMIT <<  endl;
        return;
    }

     string line;
     string userename;
     int bookid;
     string borredtime;
    while (inFile>>userename) {
        inFile >> bookid >> borredtime;

        cout <<setw(10)<< userename <<"    ��������"<< setw(12) << borredtime;
        printSimpleItem(bookid);
        cout<< endl<<endl;
    }

    inFile.close();
}