#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

struct Person
{
    int id;
    string name, surname, telNo, email, address;
};

void loadDataFromFile(vector <Person>& persons)
{
    ifstream file("datafile_new_format");

    if(file.good())
    {
        persons.clear();
        string textline, value;
        Person person;
        while(getline(file, textline))
        {
            stringstream line(textline);
            getline(line, value, '|');
            person.id=stoi(value);
            getline(line, value, '|');
            person.name=value;
            getline(line, value, '|');
            person.surname=value;
            getline(line, value, '|');
            person.telNo=value;
            getline(line, value, '|');
            person.email=value;
            getline(line, value, '|');
            person.address=value;
            persons.push_back(person);
        }

    }
    file.close();
}

void sendDataToFile (const vector <Person>& friends)
{
    ofstream file("datafile_new_format");
    for (Person person : friends)
    {
        string textline = to_string(person.id)+'|'+person.name+'|'+person.surname+'|'+person.telNo+'|'+person.email+'|'+person.address+'|';
        file<<textline<<endl;
    }
}
void showOneEntry (const Person& person)
{
    cout<<"ID:            "<<person.id<<endl;
    cout<<"Name:          "<<person.name<<endl;
    cout<<"Surname:       "<<person.surname<<endl;
    cout<<"Tlf. number:   "<<person.telNo<<endl;
    cout<<"E-mail:        "<<person.email<<endl;
    cout<<"Address:       "<<person.address<<endl<<endl;
}

void showAllEntries (const vector <Person>& friends)
{
    cout<<endl;
    if (friends.empty())
        cout << "Nobody here yet! Add some friends." << endl<<endl;
    for (Person person : friends)
        showOneEntry(person);
}

void addRecord (vector <Person>& friends)
{
    string fields[]= {"First name: ", "Last name: ", "Phone number: ", "E-mail address: ", "Address: "};
    Person person;
    string* fieldsInStruct[]= {&person.name, &person.surname, &person.telNo, &person.email, &person.address };
    string input;

    person.id = (friends.empty()) ? 1 : ((friends.back()).id)+1;

    for (int i=0; i<5; i++)
    {
        cout << fields[i];
        getline(cin, input);
        *fieldsInStruct[i]=input;
    }
    friends.push_back(person);
    sendDataToFile(friends);
}

void searchFirstName(const vector <Person>& friends)
{
    cout<<"Write a first name you are looking for: ";
    string phrase;
    getline(cin, phrase);
    bool isFound = false;
    for (const Person& person : friends)
    {
        if((person.name).find(phrase)!=string::npos)
        {
            showOneEntry(person);
            isFound = true;
        }
    }
    if(!isFound)
    {
        cout << endl << "Nobody with that first name found" << endl<<endl;
    }
}

void searchLastName(const vector <Person>& friends)
{
    cout<<"Write a last name you are looking for: ";
    string phrase;
    getline(cin, phrase);
    bool isFound = false;
    for (const Person& person : friends)
    {
        if((person.surname).find(phrase)!=string::npos)
        {
            showOneEntry(person);
            isFound = true;
        }
    }
    if(!isFound)
    {
        cout << endl << "Nobody with that last name found" << endl<<endl;
    }
}

void deletePerson (vector <Person>& friends)
{
    cout<<"Please give an ID of a person you want to remove: ";
    int id;
    cin >> id;
    cin.ignore();
    cout<<"Are you sure you want to delete? Press (y) if yes. Any other key will take you back to main menu. ";
    string answer;
    getline(cin, answer);
    if (answer == "y")
    {
        int foundIndex=-1;
        for (size_t i=0; i<friends.size(); i++)
        {
            if((friends.at(i)).id==id)
            {
                foundIndex=i;
                cout<<"Person with ID number "<< id <<" is found and removed."<< endl;
                friends.erase(friends.begin()+i);
                break;
            }
        }

        if (foundIndex==-1)
        {
            cout << endl << "No person with that ID found." << endl;
        }
        else
        {
            sendDataToFile(friends);
        }
    }

}

void modifyRecord(vector <Person>& friends)
{
    cout<<"Please give an ID of a person you want to edit: ";
    int id;
    cin >> id;
    cin.ignore();
    int foundIndex=-1;
    for (size_t i=0; i<friends.size(); i++)
    {
        if((friends.at(i)).id==id)
        {
            foundIndex=i;
            cout<<"Person with ID number "<< id <<" is found. What do you want to edit?"<< endl;
            int choice;
            cout << "1. First name" << endl;
            cout << "2. Last name" << endl;
            cout << "3. Tlf. number" << endl;
            cout << "4. E-mail" << endl;
            cout << "5. Address" << endl;

            cout << "9. Nothing, after all" << endl;

            cin >> choice;
            cin.ignore();
            while (!(choice==1 || choice==2 || choice==3 || choice==4 || choice==5 || choice==9 ))
            {
                cout << "Choose one of the options available"<<endl;
                cin.clear();
                cin.ignore(1000, '\n');
                cin >> choice;
            }

            string input;
            switch (choice)
            {
            case 1:
                cout << "Write a new first name: ";
                getline(cin, input);
                (friends.at(i)).name=input;
                break;
            case 2:
                cout << "Write a new last name: ";
                getline(cin, input);
                (friends.at(i)).surname=input;
                break;
            case 3:
                cout << "Write a new phone number: ";
                getline(cin, input);
                (friends.at(i)).telNo=input;
                break;
            case 4:
                cout << "Write a new email: ";
                getline(cin, input);
                (friends.at(i)).email=input;
                break;
            case 5:
                cout << "Write a new address: ";
                getline(cin, input);
                (friends.at(i)).address=input;
                break;
            case 9:
                return;
            }

        }

    }
    if (foundIndex==-1)
    {
        cout << endl << "No person with that ID found." << endl;
    }
    else
    {
        sendDataToFile(friends);
    }
}

int main()
{
    vector <Person> friends;
    loadDataFromFile(friends);
    int numberOfRecords= friends.size();
    while (1)
    {
        cout << endl << "You have " << numberOfRecords << " friends in your book" << endl;

        int choice;
        cout << "***Address Book***" <<endl;
        cout << "1. New entry" << endl;
        cout << "2. Search by first name" << endl;
        cout << "3. Search by last name" << endl;
        cout << "4. Show all entries" << endl;
        cout << "5. Delete a person" << endl;
        cout << "6. Edit a person" << endl;

        cout << "9. Exit" << endl;

        cin >> choice;
        cin.ignore();
        while (!(choice==1 || choice==2 || choice==3 || choice==4 || choice==5 || choice==6 || choice==9 ))
        {
            cout << "Choose one of the options available"<<endl;
            cin.clear();
            cin.ignore(1000, '\n');
            cin >> choice;
        }

        switch (choice)
        {
        case 1:
            addRecord(friends);
            numberOfRecords=friends.size();
            break;
        case 2:
            searchFirstName(friends);
            break;
        case 3:
            searchLastName(friends);
            break;
        case 4:
            showAllEntries(friends);
            break;
        case 5:
            deletePerson(friends);
            numberOfRecords=friends.size();
            break;
        case 6:
            modifyRecord(friends);
            break;
        case 9:
            return 0;
        }
    }
    return 0;
}
