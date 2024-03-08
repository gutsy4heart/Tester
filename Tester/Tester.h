#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include <sstream>
#include<conio.h>
using namespace std;

string root = "../files/";
class Person {
protected:
	string fullName;
	string homeAdress;
	string phoneNumber;
public:
	Person() : fullName(""), homeAdress(""), phoneNumber("")
	{}
	virtual void registration() = 0;
	virtual void regisLogin() = 0;
	virtual bool isLoginUnique(const string& newLogin) = 0;
	virtual bool isPasswordCorrect( const string& login, const string& enteredPass) = 0;
	virtual void authorization() = 0;
	virtual void encrypt(string& log, string pass) = 0;
	virtual void decrypt(string& log, string& pass) = 0;
	virtual string getName() {
		return fullName;
	}
	virtual string getAdress() {
		return homeAdress;
	}
	virtual string getPhonenumber() {
		return phoneNumber;
	}
	virtual ~Person() = 0 {};
};

void mainMenu() {
	cout << "Welcome!" << endl;
	cout << "1. Registration." << endl;
	cout << "2. Autorization." << endl;
	cout << "0. Exit." << endl;
	cout << "Select a category: ";
}

class User : public Person
{
protected:
	string login;
	string password;
public:
	User() : login(""), password("")
	{}
	virtual string getLogin() {
		return login;
	}
	bool isLoginUnique(const string& newLogin) override {
		ifstream file(root + "userData.txt", ios::in);
		if (file.is_open()) {
			string log,pass;
			while (file >> log >> pass) {
				if (log == newLogin) {
					file.close();
					return false;
				}
			}

			file.close();
		}
		return true;  
	}
	
	void registration() override {
		cout << "Enter your fullname: ";
		getline(cin >> ws, fullName);
		cout << "Enter your home adress: ";
		getline(cin >> ws, homeAdress);
		cout << "Enter your phone number: ";
		cin >> phoneNumber;
		cout << "Registration was successful!!" << endl;
	}
	void regisLogin() override {
		cout << "Registration your login and password ^^" << endl;
		cout << "Login: ";	
		cin >> login;
		if (!isLoginUnique(login)) {
			cout << "This login already exists!" << endl;
			return;
		}
		else {
			cout << "Password: ";
			cin >> password;
			cout << "Welcome! " << login << endl;
		}

		writeRegistrationFile();
	}
	
	void authorization() override {
		cout << "Sign in" << endl;
		cout << "Login: ";
		cin >> login;
		cout << "Password: ";
		cin >> password;

		if (isPasswordCorrect(login, password)) {
			cout << "Welcome " << login << endl;
			encrypt(login, password);
		}
		else {
			cout << "Incorrect login or password!" << endl;
			system("pause");
			system("cls");
			return authorization(); 
		}
	}
	bool isPasswordCorrect(const string& enteredLogin, const string& enteredPass) override {
		ifstream file(root + "userData.txt", ios::in);
		if (file.is_open()) {
			string encryptedLogin, encryptedPassword;
			while (file >> encryptedLogin >> encryptedPassword) {
				string decryptedLogin = encryptedLogin;
				string decryptedPassword = encryptedPassword;
				for (char& ch : decryptedLogin) {
					ch = static_cast<char>(ch - 1);
				}
				for (char& ch : decryptedPassword) {
					ch = static_cast<char>(ch - 1);
				}
				if (decryptedLogin == enteredLogin && decryptedPassword == enteredPass) {
					file.close();
					return true;
				}
			}
			file.close();
		}
		return false;
	}

	void encrypt(string& log, string pass) override {
		for (char& ch : login) {
			ch = static_cast<char>(ch + 1);
		}
		for (char& ch : pass) {
			ch = static_cast<char>(ch + 1);
			ch = '*';
		}
		cout << "Encrypt login: " << log << endl;
		cout << "Encrypt password: " << pass << endl;
	}
	void decrypt(string& log, string& pass) override {
		for (char& ch : log) {
			ch = static_cast<char>(ch - 1);
		}
		for (char& ch : pass) {
			if (ch == '*') {
				ch = static_cast<char>(ch - 1);
			}
		}

	}
	void writeRegistrationFile() {
		ofstream file(root + "userData.txt", ios::out | ios::app);
		if (file.is_open()) {
			for (char& ch : login) {
				ch = static_cast<char>(ch + 1);
			}
			for (char& ch : password) {
				ch = static_cast<char>(ch + 1);
				
			}
			file << login << endl;
			file << password << endl;
			file << fullName << endl;
			file << homeAdress << endl;
			file << phoneNumber << endl;
			file << "\n";
		}
		file.close();
	}
	~User() override {};
};

class Questions
{
protected:
	string question, answer;
	string chapter;
	int trueCount, falseCount;
public:
	Questions() 
	{
		question = "";
		answer = "";
		chapter = "";
		trueCount = 0;
		falseCount = 0;
	}
	virtual void displayTest() = 0;
	virtual void answersCheck() = 0;
	virtual ~Questions() = 0 {};
	
};
class OpenType : public Questions, public User {
private:
	int savedTrueCount;
	bool interruptTest;
	string root = "../files/";
	string selectChapter;
public:
	OpenType() : savedTrueCount(0), interruptTest(false) {}
	void answersCheck() override {
		const int totalQuestions = 12;
		double percentage = static_cast<double>(trueCount) / totalQuestions * 100;
		cout << "Percentage of Correct Answers: " << percentage << "%" << endl;
	}
	bool askToInterruptTest() {
		char interruptChoice;
		cout << "Do you want to interrupt the test? (y/n): ";
		cin >> interruptChoice;
		if (interruptChoice == 'y' || interruptChoice == 'Y') {
			interruptTest = true;
			writeInterruptTest();
			hasSavedProgress();
			return true;
			system("cls");
		}
		else {
			interruptTest = false;
			return false;
		}
	}
	bool hasSavedProgress() {
		ifstream progressFile(root + "interrupt.dat", ios::in);
		return progressFile.good();
	}
	void skipLines(ifstream& file, int count) {
		for (int i = 0; i < count; ++i) {
			string dummyString;
			getline(file, dummyString);
		}
	}
	
	void displayTest() override {
		int choice{}, choice2{}, menu{};
		authorization();
		system("pause");
		system("cls");
		cout << "-----------------------------" << endl;
		cout << "1. Take the test." << endl;
		cout << "2. View previous test results." << endl;
		cout << "0. Exit your account." << endl;
		cout << "-----------------------------" << endl;
		cout << "Select choice: ";
		cin >> menu;
		system("cls");
		if (menu == 1) {
			readChapterFile();
			cin >> choice;
			cin.ignore();
		}
		else if (menu == 2) {
			readResultTestFile();
		}
		else if (menu == 0) {
			return mainMenu();
		}

		switch (choice) {
		case 1:
			selectChapter = "Logic";
			readQuestionsFile("logicQuestions.txt", "logicAnswers.txt", selectChapter);
			system("pause");
			break;
		case 2:
			cout << "1. City names." << endl;
			cout << "2. Car brand names." << endl;
			cout << "Select category :)";
			cin >> choice2;
			cin.ignore();
			if (choice2 == 1) {
				selectChapter = "Quiz: City names.";
				readQuestionsFile("citiesQuizQues.txt", "citiesQuizAnsw.txt", selectChapter);
			}
			else if (choice2 == 2) {
				selectChapter = "Quiz: Cars brand names.";
				readQuestionsFile("carsQuizQues.txt", "carsQuizAnsw.txt", selectChapter);
				break;
			}
			system("pause");
			break;
		case 3:
			selectChapter = "Discrete math";
			readQuestionsFile("q_discrete mathematics.txt", "a_discrete mathematics.txt", selectChapter);
			system("pause");
			break;
		default:
			cout << "Incorrect selection :)" << endl;
			break;
		}
	}
	void readQuestionsFile(string fileQuestions, string fileAnswers, string& selectChapter) {
		ifstream FileQues(root + fileQuestions, ios::in);
		ifstream FileAnsw(root + fileAnswers, ios::in);
		bool inter{};
		if (savedTrueCount > 0) {
			skipLines(FileQues, savedTrueCount);
			skipLines(FileAnsw, savedTrueCount);
		}

		if (FileQues.is_open() && FileAnsw.is_open()) {
			//string question, answer;
			int falseCount{};
			for (; getline(FileQues, question) && getline(FileAnsw, answer);) {
				cout << question << endl;
				string userAnswer;
				cout << "Your Answer: ";
				getline(cin >> ws, userAnswer);
				if (_strcmpi(userAnswer.c_str(), answer.c_str()) == 0) {
					cout << "Correct Answer!" << endl;
					savedTrueCount++;
					trueCount++;
				}
				else {
					cout << "Incorrect Answer. Correct Answer: " << answer << endl;
					falseCount++;
				}
				cout << "-----------------------------" << endl;
				inter = askToInterruptTest();
				if (inter) break;
			}
			if (inter) {
				writeResultTestFile(chapter);
				FileQues.close();
				FileAnsw.close();
				system("pause");
				system("cls");
				return;
			}
			cout << "-----------------------------" << endl;
			cout << "Total Answers :) " << endl;
			cout << "Correct answers: " << trueCount << endl;
			cout << "Incorrect answers: " << falseCount << endl;
			cout << "Mark: " << trueCount << endl;
			cout << "-----------------------------" << endl;
			answersCheck();
			writeResultTestFile(chapter);
			FileQues.close();
			FileAnsw.close();
		}
		else {
			cout << "Unable to open the files." << endl;
		}
		system("pause");
		system("cls");
	}
	void readChapterFile() {
		ifstream fileChapter(root + "chapters.txt", ios::in);
		if (fileChapter.is_open()) {
			cout << "Select a section:" << endl;
			while (getline(fileChapter, chapter)) {
				cout << chapter << endl;
			}
			fileChapter.close();
		}
		else {
			cout << "Unable to open the file." << endl;
		}
	}
	void writeResultTestFile(string selectChapters) {
		ofstream fileResult(root + "resultStudents.txt", ios::out | ios::app);
		if (fileResult.is_open()) {
			fileResult << "Results:" << endl;
			fileResult << "Login: " << login << endl;
			fileResult << "Chapter: " << selectChapter << endl;
			fileResult << "Mark: " << trueCount << endl;
			fileResult << "-----------------------------" << endl;

			fileResult.close();
		}
		else {
			cout << "Error: Unable to open the file for writing." << endl;
		}
	}
	void readResultTestFile() {
		ifstream fileResult(root + "resultStudents.txt", ios::in);
		if (fileResult.is_open()) {
			string line;
			while (getline(fileResult, line)) {
				if (line.find("Login: " + login) != string::npos) {
					cout << line << endl;
					while (getline(fileResult, line) && line != "") {
						cout << line << endl;
					}
					break;
				}
			}
			fileResult.close();
		}
		else {
			cout << "Error: Unable to open the file." << endl;
			return;
		}
		system("pause");
		system("cls");
	}
	
	bool writeInterruptTest() {
		ofstream file(root + "interrupt.dat", ios::out | ios::trunc);
		if (file.is_open()) {
			file << "CurrentQuestion: " << trueCount << endl; // !!!!!
			file << "SavedTrueCount: " << savedTrueCount << endl;
			file.close();
			cout << "Test progress saved successfully." << endl;
		}
		else {
			cout << "Error: Unable to open the file for writing." << endl;
		}
		return true;
	}
	bool readInterruptTest() {
		ifstream file(root + "interrupt.dat", ios::in);
		if (file.is_open()) {
			file >> trueCount;
			file >> savedTrueCount;
			file.close();
			cout << "Test progress loaded successfully." << endl;
			return true;
			system("pause");
			system("cls");
		}
		else {
			cout << "Error: Unable to open the file for reading." << endl;
			return false;
		}
	}
	void testMenu() {
		cout << "---------------------------" << endl;
		cout << "1. Take the test." << endl;
		cout << "2. View previous test results." << endl;
		cout << "0. Exit your account." << endl;
		if (!interruptTest && hasSavedProgress()) {
			readInterruptTest();
		}
		displayTest();
	}
	~OpenType() override {};
};

void MenuMain(OpenType& t) {
	while (true) {
		mainMenu();
		int choice;
		cin >> choice;
		system("cls");
		switch (choice) {
		case 1:
			t.registration();
			system("pause");
			system("cls");
			t.regisLogin();
			system("pause");
			system("cls");
			break;
		case 2:
			t.displayTest();
			system("pause");
			break;
		case 0:
			cout << "Goodbye!" << endl;
			exit(1);
		default:
			cout << "Invalid choice. Please enter a valid option." << endl;
			break;
		}
	}
}