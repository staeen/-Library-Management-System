/*
This is a simple library management system implementing files
you can call it version 1.0
Author:Stanzen Dorjay
*/
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class Book {
    int bookId;
    char title[50];
    char author[50];
    float price;
public:
    void addBook();
    void displayBook();
    void modifyBook();
    int getBookId();
};

void Book::addBook() {
    cout << "\nEnter book details:\n";
    cout << "Book Id: ";
    cin >> bookId;
    cout << "Title: ";
    cin.ignore();
    cin.getline(title, 50);
    cout << "Author: ";
    cin.getline(author, 50);
    cout << "Price: ";
    cin >> price;
}

void Book::displayBook() {
    cout << "\nBook Details:\n";
    cout << "Book Id: " << bookId << "\n";
    cout << "Title: " << title << "\n";
    cout << "Author: " << author << "\n";
    cout << "Price: " << price << "\n";
}

void Book::modifyBook() {
    cout << "\nEnter new book details:\n";
    cout << "Title: ";
    cin.ignore();
    cin.getline(title, 50);
    cout << "Author: ";
    cin.getline(author, 50);
    cout << "Price: ";
    cin >> price;
}

int Book::getBookId() {
    return bookId;
}

void addBookToFile() {
    Book book;
    ofstream fout("library.dat", ios::binary | ios::app);
    book.addBook();
    fout.write(reinterpret_cast<char *>(&book), sizeof(Book));
    fout.close();
    cout << "\nBook added successfully!\n";
}

void displayBookDetails(int bookId) {
    Book book;
    ifstream fin("library.dat", ios::binary);
    bool found = false;
    while (fin.read(reinterpret_cast<char *>(&book), sizeof(Book))) {
        if (book.getBookId() == bookId) {
            book.displayBook();
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "\nBook not found!\n";
    }
    fin.close();
}

void displayAllBooks() {
    Book book;
    ifstream fin("library.dat", ios::binary);
    while (fin.read(reinterpret_cast<char *>(&book), sizeof(Book))) {
        book.displayBook();
        cout << "\n";
    }
    fin.close();
}

void modifyBookDetails(int bookId) {
    Book book;
    fstream file("library.dat", ios::binary | ios::in | ios::out);
    bool found = false;
    while (file.read(reinterpret_cast<char *>(&book), sizeof(Book))) {
        if (book.getBookId() == bookId) {
            book.modifyBook();
            int pos = -1 * static_cast<int>(sizeof(Book));
            file.seekp(pos, ios::cur);
            file.write(reinterpret_cast<char *>(&book), sizeof(Book));
            found = true;
            break;
        }
    }
    file.close();
    if (!found) {
        cout << "\nBook not found!\n";
    }
    else {
        cout << "\nBook modified successfully!\n";
    }
}

void deleteBook(int bookId) {
    Book book;
    ifstream fin("library.dat", ios::binary);
    ofstream fout("temp.dat", ios::binary);
    bool found = false;
    while (fin.read(reinterpret_cast<char *>(&book), sizeof(Book))) {
        if (book.getBookId() != bookId) {
            fout.write(reinterpret_cast<char *>(&book), sizeof(Book));
}
else {
found = true;
}
}
fin.close();
fout.close();
remove("library.dat");
rename("temp.dat", "library.dat");
if (found) {
cout << "\nBook deleted successfully!\n";
}
else {
cout << "\nBook not found!\n";
}
}
int main() {
int choice, bookId;
cout << "*** Library Management System ***\n";
do {
cout << "\nChoose an option:\n";
cout << "1. Add Book\n";
cout << "2. Display Book Details\n";
cout << "3. Display All Books\n";
cout << "4. Modify Book Details\n";
cout << "5. Delete Book\n";
cout << "6. Exit\n";
cout << "Enter choice: ";
cin >> choice;
switch (choice) {
case 1:
addBookToFile();
break;
case 2:
cout << "\nEnter book id: ";
cin >> bookId;
displayBookDetails(bookId);
break;
case 3:
displayAllBooks();
break;
case 4:
cout << "\nEnter book id: ";
cin >> bookId;
modifyBookDetails(bookId);
break;
case 5:
cout << "\nEnter book id: ";
cin >> bookId;
deleteBook(bookId);
break;
case 6:
cout << "\nExiting...\n";
break;
default:
cout << "\nInvalid choice!\n";
}
} while (choice != 6);
return 0;
}