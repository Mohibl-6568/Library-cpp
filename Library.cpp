#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>

using namespace std;

// Book structure
struct Book {
    int id;
    string title;
    string author;
    bool issued;
    int issuedTo; // Student ID who issued the book
};

// Student structure
struct Student {
    int id;
    string name;
};

// Library Management System Class
class Library {
private:
    vector<Book> books;
    vector<Student> students;
    int bookCounter;
    int studentCounter;

    const string BOOKS_FILE = "books.txt";
    const string STUDENTS_FILE = "students.txt";

public:
    Library() : bookCounter(1), studentCounter(1) {
        loadBooks();
        loadStudents();
    }

    ~Library() {
        saveBooks();
        saveStudents();
    }

    // Add a new book
    void addBook(const string& title, const string& author) {
        books.push_back({bookCounter++, title, author, false, -1});
        cout << "Book added successfully!\n";
    }

    // View all books
    void viewBooks() const {
        if (books.empty()) {
            cout << "No books available.\n";
            return;
        }
        for (const auto& book : books) {
            cout << "ID: " << book.id << ", Title: " << book.title << ", Author: " << book.author;
            if (book.issued) {
                cout << " (Issued to Student ID: " << book.issuedTo << ")";
            }
            cout << "\n";
        }
    }

    // Register a new student
    void registerStudent(const string& name) {
        students.push_back({studentCounter++, name});
        cout << "Student registered successfully!\n";
    }

    // View all students
    void viewStudents() const {
        if (students.empty()) {
            cout << "No students registered.\n";
            return;
        }
        for (const auto& student : students) {
            cout << "ID: " << student.id << ", Name: " << student.name << "\n";
        }
    }

    // Delete a book by ID
    void deleteBook(int id) {
        auto it = books.begin();
        while (it != books.end()) {
            if (it->id == id) {
                books.erase(it);
                cout << "Book deleted successfully!\n";
                return;
            }
            ++it;
        }
        cout << "Book not found.\n";
    }

    // Delete a student by ID
    void deleteStudent(int id) {
        auto it = students.begin();
        while (it != students.end()) {
            if (it->id == id) {
                students.erase(it);
                cout << "Student deleted successfully!\n";
                return;
            }
            ++it;
        }
        cout << "Student not found.\n";
    }

    // Issue a book to a student
    void issueBook(int bookId, int studentId) {
        for (auto& book : books) {
            if (book.id == bookId) {
                if (book.issued) {
                    cout << "Book is already issued.\n";
                    return;
                }
                book.issued = true;
                book.issuedTo = studentId;
                cout << "Book issued successfully!\n";
                return;
            }
        }
        cout << "Book not found.\n";
    }

    // View issued books and their details
    void viewIssuedBooks() const {
        bool issuedBooksExist = false;
        for (const auto& book : books) {
            if (book.issued) {
                issuedBooksExist = true;
                cout << "Book ID: " << book.id << ", Title: " << book.title << ", Author: " << book.author;
                cout << " (Issued to Student ID: " << book.issuedTo << ")\n";
            }
        }
        if (!issuedBooksExist) {
            cout << "No books are currently issued.\n";
        }
    }

    // Check if a student exists
    bool studentExists(int id) const {
        for (const auto& student : students) {
            if (student.id == id) {
                return true;
            }
        }
        return false;
    }

    // Check if a book exists
    bool bookExists(int id) const {
        for (const auto& book : books) {
            if (book.id == id) {
                return true;
            }
        }
        return false;
    }

    // Load books from file
    void loadBooks() {
        ifstream file(BOOKS_FILE);
        if (!file.is_open()) {
            cout << "No existing books file found. Starting with an empty library.\n";
            return;
        }

        Book book;
        while (file >> book.id >> ws && getline(file, book.title) && getline(file, book.author) >> book.issued >> book.issuedTo) {
            books.push_back(book);
            if (book.id >= bookCounter) {
                bookCounter = book.id + 1;
            }
        }
        file.close();
    }

    // Save books to file
    void saveBooks() const {
        ofstream file(BOOKS_FILE);
        if (!file.is_open()) {
            cerr << "Error saving books to file.\n";
            return;
        }

        for (const auto& book : books) {
            file << book.id << "\n"
                 << book.title << "\n"
                 << book.author << "\n"
                 << book.issued << " " << book.issuedTo << "\n";
        }
        file.close();
    }

    // Load students from file
    void loadStudents() {
        ifstream file(STUDENTS_FILE);
        if (!file.is_open()) {
            cout << "No existing students file found. Starting with an empty student list.\n";
            return;
        }

        Student student;
        while (file >> student.id >> ws && getline(file, student.name)) {
            students.push_back(student);
            if (student.id >= studentCounter) {
                studentCounter = student.id + 1;
            }
        }
        file.close();
    }

    // Save students to file
    void saveStudents() const {
        ofstream file(STUDENTS_FILE);
        if (!file.is_open()) {
            cerr << "Error saving students to file.\n";
            return;
        }

        for (const auto& student : students) {
            file << student.id << "\n"
                 << student.name << "\n";
        }
        file.close();
    }
};

// Main function
int main() {
    Library library;
    int choice;
    while (true) {
        cout << "\nLibrary Management System\n";
        cout << "1. Librarian Login\n";
        cout << "2. Student Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            // Librarian Menu
            while (true) {
                cout << "\nLibrarian Menu\n";
                cout << "1. Add Book\n";
                cout << "2. View Books\n";
                cout << "3. Register Student\n";
                cout << "4. View Students\n";
                cout << "5. Delete Book\n";
                cout << "6. Delete Student\n";
                cout << "7. View Issued Books\n";
                cout << "8. Back to Main Menu\n";
                cout << "Enter your choice: ";
                cin >> choice;

                if (choice == 1) {
                    string title, author;
                    cout << "Enter book title: ";
                    cin.ignore();
                    getline(cin, title);
                    cout << "Enter book author: ";
                    getline(cin, author);
                    library.addBook(title, author);
                } else if (choice == 2) {
                    library.viewBooks();
                } else if (choice == 3) {
                    string name;
                    cout << "Enter student name: ";
                    cin.ignore();
                    getline(cin, name);
                    library.registerStudent(name);
                } else if (choice == 4) {
                    library.viewStudents();
                } else if (choice == 5) {
                    int id;
                    cout << "Enter book ID to delete: ";
                    cin >> id;
                    library.deleteBook(id);
                } else if (choice == 6) {
                    int id;
                    cout << "Enter student ID to delete: ";
                    cin >> id;
                    library.deleteStudent(id);
                } else if (choice == 7) {
                    library.viewIssuedBooks();
                } else if (choice == 8) {
                    break;
                } else {
                    cout << "Invalid choice. Try again.\n";
                }
            }
        } else if (choice == 2) {
            // Student Menu
            int studentId;
            cout << "Enter your student ID: ";
            cin >> studentId;

            if (!library.studentExists(studentId)) {
                cout << "Student not found.\n";
                continue;
            }

            while (true) {
                cout << "\nStudent Menu\n";
                cout << "1. View Books\n";
                cout << "2. Issue Book\n";
                cout << "3. Back to Main Menu\n";
                cout << "Enter your choice: ";
                cin >> choice;

                if (choice == 1) {
                    library.viewBooks();
                } else if (choice == 2) {
                    int bookId;
                    cout << "Enter book ID to issue: ";
                    cin >> bookId;
                    if (library.bookExists(bookId)) {
                        library.issueBook(bookId, studentId);
                    } else {
                        cout << "Book not found.\n";
                    }
                } else if (choice == 3) {
                    break;
                } else {
                    cout << "Invalid choice. Try again.\n";
                }
            }
        } else if (choice == 3) {
            cout << "Exiting...\n";
            break;
        } else {
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
