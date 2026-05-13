#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdio>
using namespace std;

struct Person
{
    int id, userID;
    string name, surname, telNo, email, address;
};

struct User
{
    int id;
    string login, password;
};

void getValidInt(int &number)
{
    while (!(cin >> number))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Wrong input. Try again: ";
    }
    cin.ignore(1000, '\n');
}

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void waitForEnter()
{
    cout << "\nPress Enter to continue...";
    cin.ignore(1000, '\n');
}

void saveUsersToFile(const vector<User> &users)
{
    ofstream file("users_data.txt");

    if (!file)
    {
        cout << "Cannot open file." << endl;
        return;
    }

    for (const User &user : users)
    {
        string textline = to_string(user.id) + '|' + user.login + '|' + user.password + '|';
        file << textline << endl;
    }
}

void newUser(vector<User> &users)
{
    User user;
    string input;

    user.id = (users.empty()) ? 1 : ((users.back()).id) + 1;

    cout << "Login :" << endl;
    getline(cin, input);
    for (const User &u : users)
    {
        if (u.login == input)
        {
            cout << "Login already exists. Try again." << endl;
            return;
        }
    }
    user.login = input;

    cout << "Password :" << endl;
    getline(cin, input);
    user.password = input;

    users.push_back(user);

    saveUsersToFile(users);

    return;
}

int login(const vector<User> &users)
{
    string login, password;
    cout << "Login :" << endl;
    getline(cin, login);
    cout << "Password :" << endl;
    getline(cin, password);

    bool isFound = false;
    for (const User &u : users)
    {
        if (u.login == login && u.password == password)
        {
            isFound = true;
            return u.id;
        }
    }
    if (!isFound)
    {
        cout << endl
             << "Invalid login or password" << endl
             << endl;
    }
    return 0;
}

vector<User> loadUsersFromFile()
{
    vector<User> users;
    ifstream file("users_data.txt");

    if (file.good())
    {
        users.clear();
        string textline, value;
        User user;
        while (getline(file, textline))
        {
            stringstream line(textline);
            getline(line, value, '|');
            user.id = stoi(value);
            getline(line, value, '|');
            user.login = value;
            getline(line, value, '|');
            user.password = value;
            users.push_back(user);
        }
    }
    file.close();
    return users;
}

int loginMenu()
{
    vector<User> users;
    while (true)
    {
        clearScreen();
        vector<User> users = loadUsersFromFile();

        cout << "1. Log in" << endl;
        cout << "2. Register" << endl;
        cout << "9. Exit" << endl;

        int choice;
        getValidInt(choice);

        while (!(choice == 1 || choice == 2 || choice == 9))
        {
            cout << "Choose one of the options available" << endl;
            getValidInt(choice);
        }
        switch (choice)
        {
        case 1:
        {
            int userId = login(users);
            if (userId == 0)
            {
                waitForEnter();
                break;
            }
            else
                return userId;
        }
        case 2:
            newUser(users);
            waitForEnter();
            break;
        case 9:
            return -1;
        }
    }
}

void changePassword(const int &userId)
{
    vector<User> users = loadUsersFromFile();

    for (User &user : users)
    {
        if (user.id == userId)
        {
            cout << "Write a new password: ";
            string newPassword;
            getline(cin, newPassword);
            user.password = newPassword;
            break;
        }
    }

    saveUsersToFile(users);

}

void loadDataFromFile(vector<Person> &friends, const int &userId)
{
    ifstream file("address_book_data.txt");

    if (file.good())
    {
        friends.clear();
        string textline, value;
        Person person;
        while (getline(file, textline))
        {
            stringstream line(textline);
            getline(line, value, '|');
            person.id = stoi(value);
            getline(line, value, '|');
            person.userID = stoi(value);
            getline(line, value, '|');
            person.name = value;
            getline(line, value, '|');
            person.surname = value;
            getline(line, value, '|');
            person.telNo = value;
            getline(line, value, '|');
            person.email = value;
            getline(line, value, '|');
            person.address = value;
            if (person.userID == userId)
                friends.push_back(person);
        }
    }
    file.close();
}

void sendDataToFile(const vector<Person> &friends, const int &userID)
{
    ifstream fileIn("address_book_data.txt");
    if (!fileIn)
    {
        ofstream fileOut("address_book_data.txt");

        if (!fileOut)
        {
            cout << "Cannot open file." << endl;
            return;
        }

        for (const Person &person : friends)
        {
            string textline = to_string(person.id) + '|' + to_string(person.userID) + '|' + person.name + '|' + person.surname + '|' + person.telNo + '|' + person.email + '|' + person.address + '|';
            fileOut << textline << endl;
        }
        return;
    }

    ofstream fileOut("address_book_data_temp.txt");
    if (!fileOut)
    {
        cout << "Cannot open file." << endl;
        return;
    }

    string textline, value;
    while (getline(fileIn, textline))
        {
            stringstream line(textline);
            getline(line, value, '|');
            int recordID = stoi(value);
            getline(line, value, '|');
            int recordUserID = stoi(value);
            if (recordUserID != userID)
            {
                fileOut << textline << endl;
            }
        }

    for (const Person &person : friends)
    {
        string textline = to_string(person.id) + '|' + to_string(person.userID) + '|' + person.name + '|' + person.surname + '|' + person.telNo + '|' + person.email + '|' + person.address + '|';
        fileOut << textline << endl;
    }
    fileIn.close();
    fileOut.close();

    remove("address_book_data.txt");
    rename("address_book_data_temp.txt", "address_book_data.txt");
}

void showOneEntry(const Person &person)
{
    cout << "ID:            " << person.id << endl;
    cout << "Name:          " << person.name << endl;
    cout << "Surname:       " << person.surname << endl;
    cout << "Tlf. number:   " << person.telNo << endl;
    cout << "E-mail:        " << person.email << endl;
    cout << "Address:       " << person.address << endl
         << endl;
}

void showAllEntries(const vector<Person> &friends)
{
    cout << endl;
    if (friends.empty())
        cout << "Nobody here yet! Add some friends." << endl
             << endl;
    for (const Person &person : friends)
        showOneEntry(person);
}

void addRecord(vector<Person> &friends, const int &userId)
{
    string fields[] = {"First name: ", "Last name: ", "Phone number: ", "E-mail address: ", "Address: "};
    Person person;
    string *fieldsInStruct[] = {&person.name, &person.surname, &person.telNo, &person.email, &person.address};
    string input;

    person.id = (friends.empty()) ? 1 : ((friends.back()).id) + 1;
    person.userID = userId;

    for (int i = 0; i < 5; i++)
    {
        cout << fields[i];
        getline(cin, input);
        *fieldsInStruct[i] = input;
    }
    friends.push_back(person);
    sendDataToFile(friends, userId);
}

void searchFirstName(const vector<Person> &friends)
{
    cout << "Write a first name you are looking for: ";
    string phrase;
    getline(cin, phrase);
    bool isFound = false;
    for (const Person &person : friends)
    {
        if ((person.name).find(phrase) != string::npos)
        {
            showOneEntry(person);
            isFound = true;
        }
    }
    if (!isFound)
    {
        cout << endl
             << "Nobody with that first name found" << endl
             << endl;
    }
}

void searchLastName(const vector<Person> &friends)
{
    cout << "Write a last name you are looking for: ";
    string phrase;
    getline(cin, phrase);
    bool isFound = false;
    for (const Person &person : friends)
    {
        if ((person.surname).find(phrase) != string::npos)
        {
            showOneEntry(person);
            isFound = true;
        }
    }
    if (!isFound)
    {
        cout << endl
             << "Nobody with that last name found" << endl
             << endl;
    }
}

void deletePerson(vector<Person> &friends, const int &userId)
{
    cout << "Please give an ID of a person you want to remove: ";
    int id;
    getValidInt(id);

    cout << "Are you sure you want to delete? Press (y) if yes. Any other key will take you back to main menu. ";
    string answer;
    getline(cin, answer);
    if (answer == "y")
    {
        int foundIndex = -1;
        for (size_t i = 0; i < friends.size(); i++)
        {
            if ((friends.at(i)).id == id && (friends.at(i)).userID == userId)
            {
                foundIndex = i;
                cout << "Person with ID number " << id << " is found and removed." << endl;
                friends.erase(friends.begin() + i);
                break;
            }
        }

        if (foundIndex == -1)
        {
            cout << endl
                 << "No person with that ID found." << endl;
        }
        else
        {
            sendDataToFile(friends, userId);
        }
    }
}

void modifyRecord(vector<Person> &friends, const int &userId)
{
    cout << "Please give an ID of a person you want to edit: ";
    int id;
    getValidInt(id);
    int foundIndex = -1;
    for (size_t i = 0; i < friends.size(); i++)
    {
        if ((friends.at(i)).id == id && (friends.at(i)).userID == userId)
        {
            foundIndex = i;
            cout << "Person with ID number " << id << " is found. What do you want to edit?" << endl;
            int choice;
            cout << "1. First name" << endl;
            cout << "2. Last name" << endl;
            cout << "3. Tlf. number" << endl;
            cout << "4. E-mail" << endl;
            cout << "5. Address" << endl;

            cout << "9. Nothing, after all" << endl;

            getValidInt(choice);

            while (!(choice == 1 || choice == 2 || choice == 3 || choice == 4 || choice == 5 || choice == 9))
            {
                cout << "Choose one of the options available" << endl;
                getValidInt(choice);
            }

            string input;
            switch (choice)
            {
            case 1:
                cout << "Write a new first name: ";
                getline(cin, input);
                (friends.at(i)).name = input;
                break;
            case 2:
                cout << "Write a new last name: ";
                getline(cin, input);
                (friends.at(i)).surname = input;
                break;
            case 3:
                cout << "Write a new phone number: ";
                getline(cin, input);
                (friends.at(i)).telNo = input;
                break;
            case 4:
                cout << "Write a new email: ";
                getline(cin, input);
                (friends.at(i)).email = input;
                break;
            case 5:
                cout << "Write a new address: ";
                getline(cin, input);
                (friends.at(i)).address = input;
                break;
            case 9:
                return;
            }
        }
    }
    if (foundIndex == -1)
    {
        cout << endl
             << "No person with that ID found." << endl;
    }
    else
    {
        sendDataToFile(friends, userId);
    }
}

void runAddressBook(vector<Person> &friends, const int &userId)
{
    while (true)
    {
        clearScreen();
        cout << endl
             << "Logged in with user ID: " << userId << endl;
        cout << "You have " << friends.size() << " friends in your book" << endl
             << endl;

        int choice;
        cout << "***Address Book***" << endl;
        cout << "----------------------" << endl;
        cout << "1. New entry" << endl;
        cout << "2. Search by first name" << endl;
        cout << "3. Search by last name" << endl;
        cout << "4. Show all entries" << endl;
        cout << "5. Delete a person" << endl;
        cout << "6. Edit a person" << endl;
        cout << "----------------------" << endl;
        cout << "8. Change password" << endl;
        cout << "9. Log out" << endl;

        getValidInt(choice);

        while (!(choice == 1 || choice == 2 || choice == 3 || choice == 4 || choice == 5 || choice == 6 || choice == 8 || choice == 9))
        {
            cout << "Choose one of the options available" << endl;

            getValidInt(choice);
        }

        switch (choice)
        {
        case 1:
            addRecord(friends, userId);
            waitForEnter();
            break;
        case 2:
            searchFirstName(friends);
            waitForEnter();
            break;
        case 3:
            searchLastName(friends);
            waitForEnter();
            break;
        case 4:
            showAllEntries(friends);
            waitForEnter();
            break;
        case 5:
            deletePerson(friends, userId);
            waitForEnter();
            break;
        case 6:
            modifyRecord(friends, userId);
            waitForEnter();
            break;
        case 8:
            changePassword(userId);
            waitForEnter();
            break;
        case 9:
            return;
        }
    }
}

int main()
{
    while (true)
    {
        clearScreen();
        int userId = loginMenu();
        if (userId == -1)
            return 0;

        vector<Person> friends;
        loadDataFromFile(friends, userId);

        runAddressBook(friends, userId);
    }
    return 0;
}
