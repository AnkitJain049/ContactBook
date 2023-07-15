#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

struct Contact {
    string name;
    string gender;
    int age;
    string phoneNumber;
    string address;
};


void showMenu() {
    cout << "" << endl;
    cout << "" << endl;
    cout << "********************************" << endl;
    cout << "********* CONTACT BOOK *********" << endl;
    cout << "********************************" << endl;
    cout << "*****    1. Add contacts   *****" << endl;
    cout << "*****    2. Show contacts  *****" << endl;
    cout << "*****    3. Delete contact *****" << endl;
    cout << "*****    4. Find a contact *****" << endl;
    cout << "*****    5. Edit contact   *****" << endl;
    cout << "*****    6. Clear contacts *****" << endl;
    cout << "*****    0. Exit           *****" << endl;
    cout << "********************************" << endl;
    cout << "********* Version 1.0 **********" << endl;
    cout << "********************************" << endl;
    cout << "" << endl;
    cout << "" << endl;
}

void addContact(const string& filename) {
    ofstream outputFile(filename, ios::app);

    if (outputFile.is_open()) {
        Contact newContact;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, newContact.name);

        cout << "Enter Gender (Male/Female): ";
        getline(cin, newContact.gender);

        cout << "Enter Age: ";
        cin >> newContact.age;

        cout << "Enter Phone Number: ";
        cin.ignore();
        getline(cin, newContact.phoneNumber);

        cout << "Enter Address: ";
        getline(cin, newContact.address);

        outputFile << newContact.name << endl;
        outputFile << newContact.gender << endl;
        outputFile << newContact.age << endl;
        outputFile << newContact.phoneNumber << endl;
        outputFile << newContact.address << endl;
        outputFile << endl; // Add an empty line between contacts

        outputFile.close();
        cout << "Contact added successfully!" << endl;
    }
    else {
        cout << "Unable to open file: " << filename << endl;
    }
}

void showContacts(const string& filename) {
    ifstream inputFile(filename);
    if (inputFile.is_open()) {
        string line;
        while (getline(inputFile, line)) {
            cout << "Name: " << line << endl;
            getline(inputFile, line);
            cout << "Gender: " << line << endl;
            getline(inputFile, line);
            cout << "Age: " << line << endl;
            getline(inputFile, line);
            cout << "Phone Number: " << line << endl;
            getline(inputFile, line);
            cout << "Address: " << line << endl;
            getline(inputFile, line); // Read the empty line between contacts
            cout << endl;
        }

        inputFile.close();
    }
    else {
        cout << "Unable to open file: " << filename << endl;
    }
}

void deleteContact(const string& filename, const string& contactName) {
    ifstream inputFile(filename);
    if (inputFile.is_open()) {
        ofstream tempFile("temp.txt");
        string line;
        bool contactFound = false;

        while (getline(inputFile, line)) {
            if (line == contactName) {
                // Skip the lines of the contact to be deleted
                for (int i = 0; i < 4; i++) {
                    getline(inputFile, line);
                }
                contactFound = true;
            }
            else {
                // Write the lines of other contacts to the temp file
                tempFile << line << endl;
            }
        }

        inputFile.close();
        tempFile.close();

        // Replace the original file with the temp file
        if (contactFound) {
            if (remove(filename.c_str()) != 0) {
                cout << "Unable to delete contact." << endl;
            }
            else if (rename("temp.txt", filename.c_str()) != 0) {
                cout << "Unable to update contact file." << endl;
            }
            else {
                cout << "Contact deleted successfully!" << endl;
            }
        }
        else {
            cout << "Contact not found." << endl;
            remove("temp.txt");
        }
    }
    else {
        cout << "Unable to open file: " << filename << endl;
    }
}

void findContact(const string& filename, const string& contactName) {
    ifstream inputFile(filename);
    if (inputFile.is_open()) {
        string line;
        bool contactFound = false;

        while (getline(inputFile, line)) {
            if (line == contactName) {
                cout << "Contact found:" << endl;
                cout << "Name: " << line << endl;
                getline(inputFile, line);
                cout << "Gender: " << line << endl;
                getline(inputFile, line);
                cout << "Age: " << line << endl;
                getline(inputFile, line);
                cout << "Phone Number: " << line << endl;
                getline(inputFile, line);
                cout << "Address: " << line << endl;
                getline(inputFile, line); // Read the empty line between contacts
                cout << endl;
                contactFound = true;
                break;
            }
            else {
                // Skip the lines of the contact
                for (int i = 0; i < 4; i++) {
                    getline(inputFile, line);
                }
            }
        }

        inputFile.close();

        if (!contactFound) {
            cout << "Contact not found." << endl;
        }
    }
    else {
        cout << "Unable to open file: " << filename << endl;
    }
}

void editContact(const string& filename, const string& contactName) {
    ifstream inputFile(filename);
    if (inputFile.is_open()) {
        ofstream tempFile("temp.txt");
        string line;
        bool contactFound = false;

        while (getline(inputFile, line)) {
            if (line == contactName) {
                cout << "Enter new Name: ";
                getline(cin, line);
                tempFile << line << endl;

                cout << "Enter new Gender (Male/Female): ";
                getline(cin, line);
                tempFile << line << endl;

                cout << "Enter new Age: ";
                getline(cin, line);
                tempFile << line << endl;

                cout << "Enter new Phone Number: ";
                getline(cin, line);
                tempFile << line << endl;

                cout << "Enter new Address: ";
                getline(cin, line);
                tempFile << line << endl;

                getline(inputFile, line); // Read the empty line between contacts
                contactFound = true;
            }
            else {
                // Write the lines of other contacts to the temp file
                tempFile << line << endl;
            }
        }

        inputFile.close();
        tempFile.close();

        // Replace the original file with the temp file
        if (contactFound) {
            if (remove(filename.c_str()) != 0) {
                cout << "Unable to update contact." << endl;
            }
            else if (rename("temp.txt", filename.c_str()) != 0) {
                cout << "Unable to update contact file." << endl;
            }
            else {
                cout << "Contact updated successfully!" << endl;
            }
        }
        else {
            cout << "Contact not found." << endl;
            remove("temp.txt");
        }
    }
    else {
        cout << "Unable to open file: " << filename << endl;
    }
}

void clearContacts(const string& filename) {
    ofstream outputFile(filename, ofstream::trunc);
    if (outputFile.is_open()) {
        outputFile.close();
        cout << "All contacts cleared successfully!" << endl;
    }
    else {
        cout << "Unable to open file: " << filename << endl;
    }
}

int main() {
    int choice;
    do {
        showMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        cout << "" << endl;

        switch (choice) {
        case 1:
            addContact("contacts.txt");
            break;
            cout << "" << endl;
            cout << "" << endl;
        case 2:
            showContacts("contacts.txt");
            break;
            cout << "" << endl;
            cout << "" << endl;
        case 3: {
            cin.ignore();
            cout << "Enter the name of the contact to delete: ";
            string contactName;
            getline(cin, contactName);
            deleteContact("contacts.txt", contactName);
            break;
            cout << "" << endl;
            cout << "" << endl;
        }
        case 4: {
            cin.ignore();
            cout << "Enter the name of the contact to find: ";
            string contactName;
            getline(cin, contactName);
            findContact("contacts.txt", contactName);
            break;
            cout << "" << endl;
            cout << "" << endl;
        }
        case 5: {
            cin.ignore();
            cout << "Enter the name of the contact to edit: ";
            string contactName;
            getline(cin, contactName);
            editContact("contacts.txt", contactName);
            break;
            cout << "" << endl;
            cout << "" << endl;
        }
        case 6:
            clearContacts("contacts.txt");
            break;
            cout << "" << endl;
            cout << "" << endl;
        case 0:
            cout << "Saving contacts and exiting the program. Goodbye!" << endl;
            break;
            cout << "" << endl;
            cout << "" << endl;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
            cout << "" << endl;
            cout << "" << endl;
        }
    } while (choice != 0);

    return 0;
}
