#include <iostream>
#include <windows.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

struct User
{
    int idUser;
    string login, password;
};

struct Person
{
    int id = 0, idUser = 0;
    string name = "", surname = "", numberPhone = "", mail = "", adress = "";
};

string addLine()
{
    string input = "";
    getline(cin, input);
    return input;
}

char addChar()
{
    string input = "";
    char choise  = {0};

    while(true)
    {
        input = addLine();
        if (input.length() == 1)
        {
            choise = input[0];
            break;
        }
        cout << "To nie jest pojedynczy znak. Wpisz ponownie." << endl;
    }
    return choise;
}

int addInteger()
{
    string input = "";
    int number = 0;
    while(true)
    {
        input = addLine();
        stringstream myStream(input);
        if (myStream >> number)
            break;
        cout << "To nie jest liczba. Wpisz ponownie. " << endl;
    }
    return number;
}

string konwertIntToString(int number)
{
    ostringstream ss;
    ss << number;
    string str = ss.str();
    return str;
}

User inputNewUserToStuktur(string newString)
{
    User user;
    int numberOfSingleDataFromUser = 1;
    string singleDataFromUser = "";

    for (size_t numberOfLine = 0; numberOfLine < newString.length(); numberOfLine++)
    {
        if (newString[numberOfLine] != '|')
        {
            singleDataFromUser += newString[numberOfLine];
        }
        else
        {
            switch(numberOfSingleDataFromUser)
            {
            case 1:
                user.idUser = atoi(singleDataFromUser.c_str());
                break;
            case 2:
                user.login = singleDataFromUser;
                break;
            case 3:
                user.password = singleDataFromUser;
                break;
            }
            singleDataFromUser = "";
            numberOfSingleDataFromUser++;
        }
    }
    return user;
}

void loadUsersFromFile(vector<User> &users)
{
    User user;
    string line = "";

    ifstream book;
    book.open("Uzytkownicy.txt", ios :: in);

    if (book.good())
    {
        while(getline(book, line))
        {
            user = inputNewUserToStuktur(line);
            users.push_back(user);
        }
    }
    book.close();
}

void writeUserToBook(const User &user)
{
    ofstream book;
    book.open("Uzytkownicy.txt", ios :: out | ios :: app);
    if (book.good())
    {
        book << user.idUser << '|' << user.login << '|' << user.password << '|' << endl;
        book.close();
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
        system("pause");
    }
}

void addNewBookUser(vector<User> &users)
{
    fstream book;
    string line = "";

    book.open("Uzytkownicy.txt", ios :: out);
    if (book.good())
    {
        for (vector<User>::iterator itr = users.begin(); itr != users.end(); itr++)
        {
            line += konwertIntToString(itr->idUser) + '|';
            line += itr->login + '|';
            line += itr->password + '|';
            book << line << endl;
            line = "";
        }
        book.close();
    }
    else
    {
        cout << "Nie mozna otworzyc pliku." << endl;
    }
}

void createAccount(vector<User> &users)
{
    User user;
    string login = "";
    system("cls");
    cout << ">>> Rejestracja Uzytkownika <<<" << endl << endl;

    if (users.size() == 0)
    {
        user.idUser = 1;
    }
    else
    {
        user.idUser = users.back().idUser + 1;
    }
    cout << "Podaj nazwe Uzytkownika: ";
    user.login = addLine();

    for(vector<User>::iterator itr = users.begin(); itr != users.end(); itr++)
    {
        while(itr->login == user.login)
        {
            cout << "Taki Uzytkownik istnieje. Wpisz inna nazwe Uzytkownika: ";
            user.login = addLine();
        }
    }
    cout << "Podaj haslo: ";
    user.password = addLine();
    users.push_back(user);
    writeUserToBook(user);
    cout << "Konto zalozone!";
    Sleep(1000);
}

int singIn(vector<User> &users)
{
    bool foundFriend = false;
    string searchLogin = "";
    system("cls");
    cout << ">>> Logowanie Uzytkownika <<<" << endl << endl;
    cout << "Podaj login Uzytkownika: ";
    searchLogin = addLine();

    if (!users.empty())
    {
        for(vector<User>::iterator itr = users.begin(); itr != users.end(); itr++)
        {
            if (itr->login == searchLogin)
            {
                for (int attempt = 0; attempt < 3; attempt++)
                {
                    cout << "Podaj haslo. Pozostalo prob " << 3 - attempt << ": ";

                    if (itr->password == addLine())
                    {
                        cout << "Zalogowales sie pomyslnie!";
                        Sleep(1000);
                        return itr->idUser;
                    }
                }
                cout << "Podales 3 razy bledne haslo. Poczekaj 3 sekundy przed kolejna proba" << endl;
                Sleep(3000);
                return 0;
            }
        }
        if (!foundFriend)
        {
            cout << "Nie ma Uzytkownika z takim loginem." << endl;
        }
    }
    else
    {
        cout << "Ksiazka adresowa jest pusta." << endl;
    }
    Sleep(1000);
    return 0;
}

void editPassword(vector<User> &users, const int idLogUsers)
{
   User user;
   string newPassword = "";
   system("cls");
   cout << "Podaj nowe haslo: ";
   newPassword = addLine();

   for(vector<User>::iterator itr = users.begin(); itr != users.end(); itr++)
   {
       if (itr->idUser == idLogUsers)
       {
           itr->password = newPassword;
           cout << "Haslo zostalo zmienione!" << endl;
           addNewBookUser(users);
           Sleep(1500);
       }
   }
}

Person inputNewPersonToStuktur(string newString)
{
    Person person;
    int numberOfSingleDataFromPerson = 1;
    string singleDataFromPerson = "";

    for (size_t numberOfLine = 0; numberOfLine < newString.length(); numberOfLine++)
    {
        if (newString[numberOfLine] != '|')
        {
            singleDataFromPerson += newString[numberOfLine];
        }
        else
        {
            switch(numberOfSingleDataFromPerson)
            {
            case 1:
                person.id = atoi(singleDataFromPerson.c_str());
                break;
            case 2:
                person.idUser = atoi(singleDataFromPerson.c_str());
                break;
            case 3:
                person.name = singleDataFromPerson;
                break;
            case 4:
                person.surname = singleDataFromPerson;
                break;
            case 5:
                person.numberPhone = singleDataFromPerson;
                break;
            case 6:
                person.mail = singleDataFromPerson;
                break;
            case 7:
                person.adress = singleDataFromPerson;
                break;
            }
            singleDataFromPerson = "";
            numberOfSingleDataFromPerson++;
        }
    }
    return person;
}

void loadPeopleFromFile(vector<Person> &people, const int idLogUsers)
{
    Person person;
    string line = "";
    ifstream book("KsiazkaAdresowa.txt", ios :: app);
    book.close();
    book.open("KsiazkaAdresowa.txt", ios :: in);

    if (!book.is_open())
    {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych.";
    }

    while(getline(book, line))
    {
        person = inputNewPersonToStuktur(line);
        if (person.idUser == idLogUsers)
        {
            people.push_back(person);
        }
    }
    book.close();
}

void allPeople(vector<Person> &people)
{
    system("cls");
    if (!people.empty())
    {
        cout << ">>> KSIAZKA ADRESOWA <<<" << endl << endl;
        for (vector<Person>::iterator itr = people.begin(); itr != people.end(); itr++)
        {
                cout << "1. Id: " << "\t" << "\t" << itr->id << endl;
                cout << "2. Imie: " << "\t" << itr->name << endl;
                cout << "3. Nazwisko: " << "\t" << itr->surname << endl;
                cout << "4. Telefon: " << "\t" << itr->numberPhone << endl;
                cout << "5. Adres mail: " << "\t" << itr->mail << endl;
                cout << "6. Adres: " << "\t" << itr->adress << endl << endl;
        }
    }
    else
    {
        cout << "Ksiazka adresowa jest pusta." << endl << endl;
    }
    system("pause");
}

void writePersonToBook(const Person &person)
{
    fstream book;
    book.open("KsiazkaAdresowa.txt", ios :: out | ios :: app);
    if (book.good())
    {
        book << person.id << '|' << person.idUser << '|' << person.name << '|';
        book << person.surname << '|' << person.numberPhone << '|';
        book << person.mail << '|' << person.adress << '|' << endl;
        book.close();
        cout << "Dane Przyjaciela zapisane!" << endl;
        Sleep(2000);
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
        Sleep(2000);
    }
}

void addNewBook(vector<Person> &people, const int searchId)
{
    Person person;
    ifstream book;
    string line = "";

    book.open("KsiazkaAdresowa.txt",  ios :: in);
    if (book.good())
    {
        while(getline(book, line))
        {
            person = inputNewPersonToStuktur(line);
            fstream temporaryBook;
            temporaryBook.open("KsiazkaAdresowaTymczasowa.txt", ios :: out | ios :: app);
            if (person.id != searchId)
            {
                temporaryBook << line << endl;
            }
            else
            {
                for (vector<Person>::iterator itr = people.begin(); itr != people.end(); itr++)
                {
                    if (itr->id == searchId)
                    {
                        temporaryBook << konwertIntToString(itr->id) + '|';
                        temporaryBook << konwertIntToString(person.idUser) + '|';
                        temporaryBook << itr->name + '|';
                        temporaryBook << itr->surname + '|';
                        temporaryBook << itr->numberPhone + '|';
                        temporaryBook << itr->mail + '|';
                        temporaryBook << itr->adress + '|' << endl;
                    }
                }
            }
            temporaryBook.close();
        }
        book.close();
    }
    else
    {
        cout << "Nie mozna otworzyc pliku." << endl;
    }
    remove("KsiazkaAdresowa.txt");
    rename("KsiazkaAdresowaTymczasowa.txt", "KsiazkaAdresowa.txt");
}

void searchName(vector<Person> &people)
{
    bool foundFriend = false;
    string searchOfName = "";
    system("cls");

    if (!people.empty())
    {
        cout << "Podaj imie Przyjaciela jakie chcesz odszukac: ";
        searchOfName = addLine();

        for (vector<Person>::iterator  itr = people.begin(); itr != people.end(); itr++)
        {
            if (itr->name == searchOfName)
            {
                foundFriend = true;
                cout << "1. Id: " << "\t" << "\t" << itr->id << endl;
                cout << "2. Imie: " << "\t" << itr->name << endl;
                cout << "3. Nazwisko: " << "\t" << itr->surname << endl;
                cout << "4. Telefon: " << "\t" << itr->numberPhone << endl;
                cout << "5. Adres mail: " << "\t" << itr->mail << endl;
                cout << "6. Adres: " << "\t" << itr->adress << endl << endl;
            }
        }
        if ( !foundFriend)
        {
            cout << "W ksiazce nie ma Przyjaciela o takim imieniu!" << endl;
        }
    }
    else
    {
        cout << "Ksiazka adresowa jest pusta" << endl << endl;
    }
    Sleep(2000);
}

void searchSurname(vector<Person> &people)
{
    bool foundFriend = false;
    string searchOfSurname = "";
    system("cls");

    if (!people.empty())
    {
        cout << "Podaj nazwisko Przyjaciela jakie chcesz odszukac: ";
        searchOfSurname = addLine();

        for (vector<Person>::iterator  itr = people.begin(); itr != people.end(); itr++)
        {
            if (itr->surname == searchOfSurname)
            {
                foundFriend = true;
                cout << "1. Id: " << "\t" << "\t" << itr->id << endl;
                cout << "2. Imie: " << "\t" << itr->name << endl;
                cout << "3. Nazwisko: " << "\t" << itr->surname << endl;
                cout << "4. Telefon: " << "\t" << itr->numberPhone << endl;
                cout << "5. Adres mail: " << "\t" << itr->mail << endl;
                cout << "6. Adres: " << "\t" << itr->adress << endl << endl;
            }
        }
        if ( !foundFriend)
        {
            cout << "W ksiazce nie ma Przyjaciela o takim nazwisku!" << endl;
        }
    }
    else
    {
        cout << "Ksiazka adresowa jest pusta" << endl << endl;
    }
    Sleep(2000);
}

int checkIdLastPerson()
{
    Person person;
    string line = "";
    int idLastPerson = 0;
    fstream book;
    book.open("KsiazkaAdresowa.txt", ios :: in);

    if (book.good())
    {
        while(getline(book, line))
        {
            person = inputNewPersonToStuktur(line);
            idLastPerson = person.id;
        }
        book.close();
    }
    return idLastPerson;
}

void addPerson(vector<Person> &people, const int idLogUsers)
{
    Person person;
    system("cls");
    cout << ">>> DODAWANIE NOWEGO PRZYJACIELA <<<" << endl << endl;
    person.id = checkIdLastPerson() + 1;
    person.idUser = idLogUsers;
    cout << "Podaj imie Przyjaciela: ";
    person.name = addLine();
    cout << "Podaj nazwisko Przyjaciela: ";
    person.surname = addLine();
    cout << "Podaj telefon Przyjaciela: ";
    person.numberPhone = addLine();
    cout << "Podaj mail Przyjaciela: ";
    person.mail = addLine();
    cout << "Podaj adres Przyjaciela: ";
    person.adress = addLine();

    people.push_back(person);
    writePersonToBook(person);
}

void deletePerson(vector<Person> &people)
{
    int searchId = 0;
    char letterT;
    bool foundFriend = false;
    system("cls");

    if (!people.empty())
    {
        cout << ">>> Usuwanie Przyjaciela <<<" << endl << endl;
        cout << "Podaj ID Przyjaciela, ktorego chcesz usunac: ";
        searchId = addInteger();

        for (vector<Person>::iterator itr = people.begin(); itr != people.end(); itr++)
        {
            if (itr->id == searchId)
            {
                foundFriend = true;
                cout << "Potwierdz naciskajac klawisz 't': ";
                letterT = addChar();
                if (letterT == 't')
                {
                    people.erase(itr);
                    cout << "Przyjaciel zostal usuniety z kasiazki!" << endl;
                    addNewBook(people, searchId);
                    break;
                }
                else
                {
                    cout << "Wybrany Przyjaciel nie zostal usuniety" << endl << endl;
                    break;
                }
            }
        }
        if ( !foundFriend)
        {
            cout << "W ksiazce nie ma Przyjaciela o takim ID!" << endl;
        }
    }
    else
    {
        cout << "Ksiazka adresowa jest pusta" << endl << endl;
    }
    Sleep(2000);
}

void editPerson(vector<Person> &people)
{
    int searchId = 0;
    bool foundFriend = false;
    char choise;
    system("cls");

    if (!people.empty())
    {
        cout << ">>> Edycja Przyjaciela <<<" << endl << endl;
        cout << "Podaj ID Przyjaciela, ktorego chcesz edytowac: ";
        searchId = addInteger();

        for (vector<Person>::iterator itr = people.begin(); itr != people.end(); itr++)
        {
            if (itr->id == searchId)
            {
                foundFriend = true;
                system("cls");
                cout << "===========================" << endl;
                cout << "     Edycja Przyjaciela   " << endl;
                cout << "===========================" << endl;
                cout << "1. Zmien imie" << endl;
                cout << "2. Zmien nazwisko" << endl;
                cout << "3. Zmien numer telefonu" << endl;
                cout << "4. Zmien adres mail" << endl;
                cout << "5. Zmien adres" << endl;
                cout << "6. Powrot do menu glownego" << endl;
                cout << "Wybieram: ";
                choise = addChar();

                switch(choise)
                {
                case '1':
                    cout << "Wpisz nowe imie: ";
                    itr->name = addLine();
                    cout << "Dane Przyjaciela zostaly zmienione" << endl;
                    addNewBook(people, searchId);
                    break;

                case '2':
                    cout << "Wpisz nowe nazwisko: ";
                    itr->surname = addLine();
                    cout << "Dane Przyjaciela zostaly zmienione" << endl;
                    addNewBook(people, searchId);
                    break;

                case '3':
                    cout << "Wpisz nowy numer telefonu: ";
                    itr->numberPhone = addLine();
                    cout << "Dane Przyjaciela zostaly zmienione" << endl;
                    addNewBook(people, searchId);
                    break;

                case '4':
                    cout << "Wpisz nowy adres mail: ";
                    itr->mail = addLine();
                    cout << "Dane Przyjaciela zostaly zmienione" << endl;
                    addNewBook(people, searchId);
                    break;

                case '5':
                    cout << "Wpisz nowy adres: ";
                    itr->adress = addLine();
                    cout << "Dane Przyjaciela zostaly zmienione" << endl;
                    addNewBook(people, searchId);
                    break;

                case '6':
                    cout << endl << "Powrot do menu glownego" << endl;
                    break;
                }
            }
        }
        if (!foundFriend)
        {
            cout << "W ksiazce nie ma Przyjaciela o takim ID!" << endl;
        }
    }
    else
    {
        cout << "Ksiazka Adresowa jest pusta." << endl;
    }
    Sleep(2000);
}

void newMenu(vector<User> &users, int idLogUsers)
{
    vector<Person> people;
    char choise;
    loadPeopleFromFile(people, idLogUsers);

    while (idLogUsers != 0 )
    {
        system("cls");
        cout<<"==========================="<<endl;
        cout<<"     KSIAZKA ADRESOWA    "<<endl;
        cout<<"==========================="<<endl;
        cout << "1. Dodaj przyjaciela" << endl;
        cout << "2. Wyszukaj przyjaciela po imieniu" << endl;
        cout << "3. Wyszukaj przyjaciela po nazwisku" << endl;
        cout << "4. Wyswietl wszystkich przyjaciol" << endl;
        cout << "5. Usun przyjaciela" << endl;
        cout << "6. Edytuj przyjaciela" << endl;
        cout<<"==========================="<<endl;
        cout << "7. Zmien haslo" << endl;
        cout << "9. Wyloguj sie" << endl;
        cout<<"==========================="<<endl;
        cout<<"Wybieram: ";
        choise = addChar();

        switch(choise)
        {
        case '1':
            addPerson(people, idLogUsers);
            break;
        case '2':
            searchName(people);
            break;
        case '3':
            searchSurname(people);
            break;
        case '4':
            allPeople(people);
            break;
        case '5':
            deletePerson(people);
            break;
        case '6':
            editPerson(people);
            break;
        case '7':
            editPassword(users, idLogUsers);
            break;
        case '9':
            cout << endl << "Wylogowales sie!" << endl;
            idLogUsers = 0;
            Sleep(1500);
            break;
        }
    }
}

int main()
{
    vector <User> users;
    char choise;
    int idLogUsers = 0;
    loadUsersFromFile(users);

    while (1)
    {
        system("cls");
        cout<<"==========================="<<endl;
        cout<<"     KSIAZKA ADRESOWA    "<<endl;
        cout<<"==========================="<<endl;
        cout << "1. Rejestracja" << endl;
        cout << "2. Logowanie" << endl;
        cout << "3. Zakoncz program" << endl;
        cout<<"==========================="<<endl;
        cout<<"Wybieram: ";
        choise = addChar();

        switch(choise)
        {
        case '1':
            createAccount(users);
            break;
        case '2':
            idLogUsers = singIn(users);
            if (idLogUsers != 0)
            {
                newMenu(users, idLogUsers);
            }
            break;
        case '3':
            cout << endl << "Koniec programu!" << endl;
            exit(0);
            break;
        default:
            cout << "Wybrano niepoprawna opcje. Sproboj ponownie!" << endl;
            Sleep(1500);
            break;
        }
    }
    return 0;
}
