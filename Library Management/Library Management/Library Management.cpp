#include <iostream>
#include <string>
#include <stdio.h>
#include<stdlib.h>
#include <fstream>
#include <conio.h>


using namespace std;
class book
{
private:
	string id, bookName;


public:

	void addBook(fstream& f) {
		fstream file;
		file.open("books.txt", ios::app | ios::in);

		string  idInput, idd;
		bool flag = true;

		cout << "\nEnter Id : "; cin >> idInput;

		if (file.is_open()) {
			while (getline(file, idd, '|')) {
				if (idInput.compare(idd) == 0) {
					cout << "id is used";
					flag = false;
					break;
				}
			}
		}
		if (flag == true) {
			cout << "Enter Book Name : "; cin >> bookName;
			f << idInput << "|";
			f << bookName << "|";
			f << "\n";
		}
		f.close();
		file.close();

	}

	void listOfABooks(fstream& f) {

		while (getline(f, id, '|'))
		{
			getline(f, bookName, '|');

			cout << "\n ID:" << id << "\t Book Name : " << bookName << endl;

		}

	}
	void listOfBBooks(fstream& f) {

		while (getline(f, id, '|'))
		{
			getline(f, bookName, '|');
			cout << "\n ID:" << id << "\t Book Name : " << bookName << endl;

		}

	}
	void bookSearch(fstream& f, string Pid)
	{
		bool flage = false;
		while (getline(f, id, '|'))
		{
			getline(f, bookName, '|');

			if (atoi(Pid.c_str()) == atoi(id.c_str()))
			{
				cout << "\nID:" << id;
				cout << "\tBook Name:" << bookName << endl;

				flage = true;
				break;
			}
		}
		if (flage == false)
			cout << "\n Book not found !";
	}

	void delete_book(const string& idNr) {
		ifstream file;
		ofstream outFile("newList.txt");
		string readFile, id;

		file.open("books.txt", ios::app);

		if (file.is_open()) {
			while (getline(file, readFile)) {
				int pos = readFile.find('|');
				id = readFile.substr(0, pos);
				if (idNr != id) {
					outFile << readFile << endl;
				}
			}
		}
		file.close();
		outFile.close();

		remove("books.txt");
		rename("newList.txt", "books.txt");
	}

	void borrowBook(const string& idNr) {
		ifstream file;
		ofstream tempFile("newList.txt"), borrowFile;
		string readFile, id;

		file.open("books.txt", ios::app);
		borrowFile.open("borrowedBook.txt", ios::app);

		if (file.is_open()) {

			while (getline(file, readFile)) {

				int pos = readFile.find('|');
				id = readFile.substr(0, pos);

				if (idNr != id) {                      //copying books to temp file without the borrowed one
					tempFile << readFile << endl;
				}

				else if (idNr == id) {
					borrowFile << readFile << endl;
				}
			}

		}

		file.close();
		tempFile.close();

		remove("books.txt");
		rename("newList.txt", "books.txt");
	}


	void returnBook(const string& idNr) {
		ifstream file;
		ofstream tempFile("newList.txt"), returFile;
		string readFile, id;

		file.open("borrowedBook.txt", ios::app);
		returFile.open("Books.txt", ios::app);

		if (file.is_open()) {

			while (getline(file, readFile)) {

				int pos = readFile.find('|');
				id = readFile.substr(0, pos);

				if (idNr != id) {                      //copying books to temp file without the borrowed one
					tempFile << readFile << endl;
				}

				else if (idNr == id) {
					returFile << readFile << endl;
				}
			}

		}

		file.close();
		tempFile.close();

		remove("borrowedBook.txt");
		rename("newList.txt", "borrowedBook.txt");
	}

};




int main() {
	fstream File, bFile;
	book b;
	string id;



	int outerChoice = 0;
	while (outerChoice != 9) {
		system("cls");
		cout << "\n Wellcome to Hashem's library  \n\n";

		cout << "\n1. Amin";
		cout << "\n2. User";
		cout << "\n9. Exit";
		cout << "\n\nEnter your choice : ";
		cin >> outerChoice;

		if (outerChoice == 1)
		{
			system("cls");

			int innerChoice = 0;
			while (innerChoice != 9) {
				cout << "\n\n Admin Login is Successful !! Press any key to continue..";
				cout << "\n1. Add Book";
				cout << "\n2. Search";
				cout << "\n3. Delete Book";
				cout << "\n4. List Available Books";
				cout << "\n5. List Borrowed books Books";
				cout << "\n9. Exit";
				cout << "\n\n Enter your choice : ";

				cin >> innerChoice;
				switch (innerChoice) {
				case 1: File.open("books.txt", ios::app);  b.addBook(File); File.close();  break;

				case 2: {
					cout << "enter book id you want to search for "; cin >> id;
					File.open("books.txt", ios::in); b.bookSearch(File, id); File.close(); break;
				}

				case 3: cout << "\n Enter book ID : "; cin >> id;  b.delete_book(id); break;

				case 4: File.open("books.txt", ios::in);  b.listOfABooks(File); File.close();  break;

				case 5: bFile.open("borrowedbook.txt", ios::in);  b.listOfBBooks(bFile); bFile.close();  break;

				case 9: break;

				default: cout << "\n\n Invalid Choice. Press any key to continue..";

				}
				cout << "\n"; system("pause"); system("cls");
			}
		}


		else if (outerChoice == 2) {
			int innerrChoice = 0;
			while (innerrChoice != 9) {

				system("cls");
				cout << "\n1. Borrow a Book";
				cout << "\n2. Return a Book";
				cout << "\n3. List Available Books";
				cout << "\n9. Exit";
				cout << "\n\n Enter your choice : ";
				cin >> innerrChoice;

				switch (innerrChoice) {

				case 1: cout << "\n Enter book ID : "; cin >> id;  b.borrowBook(id); cout << "The book has been borrowed"; break;

				case 2:cout << "\n Enter book ID : "; cin >> id;  b.returnBook(id); cout << "The book has been return"; break;

				case 3: { File.open("books.txt", ios::in);  b.listOfABooks(File); File.close();  break; }

				case 9: break;

				default: cout << "\n\n Error: Invalid Choice. Press any key to continue..";

				}
				cout << "\n"; system("pause"); system("cls");
			}
		}
	}
	return 0;
}
