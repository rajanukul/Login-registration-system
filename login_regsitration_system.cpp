#include <iostream>
#include <fstream>
#include <string.h>
#include <iomanip>
using namespace std;
class Database
{
    char name[20];
    char username[15];
    char password[10];

public:
    void getdata();
    void showdata();
    char *getname() { return name; }
    char *getuser() { return username; }
    char *getpass() { return password; }
    void update(char *nm, char *un, char *pass)
    {
        strcpy(name, nm);
        strcpy(username, un);
        strcpy(password, pass);
    }
    void newrecord();
    void display();
    void forgotpass();
    void searchuser();
    void updateuser();
    void deleteuser();
    int login();
};
void Database::getdata()
{
    cout << "\nEnter name : ";
    cin >> name;
    cout << "\nEnter username : ";
    cin >> username;
    cout << "\nEnter password : ";
    cin >> password;
}
void Database::showdata()
{
    cout << endl;
    cout << "Name : " << name << endl;
    cout << "Username : " << username << endl;
}

void Database ::newrecord()
{
    int found = 0;
    char rrep[11];
    char nmopi[20];
    char word[15];
    getdata();
    strcpy(nmopi, name);
    strcpy(rrep, username);
    strcpy(word, password);
    fstream file;
    file.open("database.txt", ios::in | ios::app | ios::binary);
    while (file.read((char *)this, sizeof(*this)))
    {
        if (strcmp(rrep, getuser()) == 0)
        {
            found = 1;
            break;
        }
    }
    file.clear();
    file.close();
    if (found == 1)
        cout << "\n\n** Data already exist ** \n\n";

    else
    {
        file.open("database.txt", ios::app | ios::binary);
        update(nmopi, rrep, word);
        file.write((char *)this, sizeof(*this));
        cout << "\n\n** Record Added Succesfully ** \n\n";
        file.close();
    }
}
void Database ::display()
{
    //Display All Records
    fstream file;
    file.open("database.txt", ios::ate | ios::in | ios::out | ios::binary);
    file.seekg(0, ios::beg);
    cout << "\n\n** Records in DATABASE ** \n\n";
    while (file)
    {
        file.read((char *)this, sizeof(*this));
        if (!file.eof())
            showdata();
    }
    file.clear();
    file.close();
}
void Database ::searchuser()
{
    //Search name on basis of username
    char c, ch, nm[20], user[11];
    int cnt, found = 0;
    cout << "\nEnter Username : ";
    cin >> user;
    fstream file;
    file.open("database.txt", ios::ate | ios::in | ios::out | ios::binary);
    file.seekg(0, ios::beg);
    while (file.read((char *)this, sizeof(*this)))
    {
        if (strcmp(user, getuser()) == 0)
        {
            found = 1;
            showdata();
        }
    }
    file.clear();
    if (found == 0)
        cout << "\n\n** Record Not found ** \n\n";
    file.close();
}
void Database ::updateuser()
{
    int cnt = 0, found = 0;
    char ch[20], newn[20], newu[20], newpass[15];
    fstream file;
    file.open("database.txt", ios::ate | ios::in | ios::out | ios::binary);
    cout << "\n\nEnter username to update : ";
    cin >> ch;
    file.seekg(0, ios::beg);
    while (file.read((char *)this, sizeof(*this)))
    {
        cnt++;
        if (strcmp(ch, getuser()) == 0)
        {
            found = 1;
            break;
        }
    }
    file.clear();
    if (found == 0)
        cout << "\n\n** Record Not found ** \n\n";
    else
    {
        strcpy(newn, name);
        int location = (cnt - 1) * sizeof(*this);
        cout << "\nEnter new Username : ";
        cin >> newu;
        cout << "\nEnter new Password : ";
        cin >> newpass;
        file.seekp(location);
        update(newn, newu, newpass);
        file.write((char *)this, sizeof(*this));
    }
    file.close();
}
void Database::deleteuser()
{
    char uname[20];
    int pos, flag = 0;
    cout << "\nEnter username to delete : ";
    cin >> uname;
    ifstream file;
    file.open("database.txt", ios::in | ios::binary);
    ofstream temp;
    temp.open("temp.txt", ios::out | ios::binary);
    file.seekg(0, ios::beg);
    while (file.read((char *)this, sizeof(*this)))
    {
        if (strcmp(uname, getuser()) == 0)
        {
            flag = 1;
            cout << "\n\n** Deleted Record is **\n";
            showdata();
        }
        else
            temp.write((char *)this, sizeof(*this));
    }
    file.close();
    temp.close();
    remove("database.txt");
    rename("temp.txt", "database.txt");
    if (flag == 1)
        cout << "\n\n** Record successfully Deleted ** \n\n";
    else
        cout << "\n\n** Record not found **\n\n";
}
int Database::login()
{

    char c, ch, nm[20], user[11], poss[15];
    int cnt, found = 0;
    cout << "\n\nEnter Username : ";
    cin >> user;
    cout << "\nEnter Password : ";
    cin >> poss;
    ifstream file;
    file.open("database.txt", ios::in | ios::binary);
    file.seekg(0, ios::beg);
    while (file.read((char *)this, sizeof(*this)))
    {
        if ((strcmp(user, getuser()) == 0) && (strcmp(poss, getpass()) == 0))
        {
            found = 1;
            cout << "\n\n** Login successful ** \n\n";
        }
    }
    file.clear();
    if (found == 0)
        cout << "\n\n** Wrong Credentials ** \n\n";
    file.close();
    return found;
}
void Database::forgotpass()
{
    char c, ch, nm[20], user[11], name[15];
    int cnt, found = 0;
    cout << "\n\nEnter Name : ";
    cin >> name;
    cout << "\nEnter Username : ";
    cin >> user;
    fstream file;
    file.open("database.txt", ios::ate | ios::in | ios::out | ios::binary);
    file.seekg(0, ios::beg);
    while (file.read((char *)this, sizeof(*this)))
    {
        if ((strcmp(user, getuser()) == 0) && (strcmp(name, getname()) == 0))
        {
            found = 1;
            cout << "\nYour Password : " << getpass();
        }
    }
    file.clear();
    if (found == 0)
        cout << "\n\n*Record Not found / Wrong Credential*\n";
    file.close();
}
int main()
{
    system("Color 7C");
    cout << "\n\n** LOGIN AND REGISTRATION SYSTEM **\n\n";
    Database rec;
    char ch;
    int n, auth, choice;
repeat:
    cout << "1) Register\n2) Login\n3) Forgot Password\nYour Choice ";
    cin >> n;
    if (n == 1)
    {
        rec.newrecord();
        cout<<"\n";
        cout << "\nDo you wish to re enter choice?  (y/n)\n";
            cin >> ch;
            if (ch == 'y' || ch == 'Y')
            {
                cout << "-------------------\n";
                goto repeat;
            }
            else
                cout << "\n----GoodBye-----\n";
    }
    else if (n == 2)
    {
        auth = rec.login();
        if (auth == 1)
        {

            while (1)
            {
                cout << "\n\n1) Display All Records\n";
                cout << "2) Search User\n";
                cout << "3) Update\n";
                cout << "4) delete rec\n";
                cout << "5) Exit\n";
                cout << "Choose your choice : ";
                cin >> choice;

                switch (choice)
                {
                case 1:
                    rec.display();
                    break;

                case 2:
                    rec.searchuser();
                    break;
                case 3:
                    rec.updateuser();
                    break;
                case 4:
                    rec.deleteuser();
                    break;
                case 5:
                    exit(1);

                default:
                    cout << "Invalid Option!!" << endl;
                }
            }
        }

        else
        {
            cout << "\nDo you wish to re enter choice?  (y/n)\n";
            cin >> ch;
            if (ch == 'y' || ch == 'Y')
            {
                cout << "-------------------\n";
                goto repeat;
            }
            else
                cout << "\n----GoodBye-----\n";
        }
    }
    else if (n == 3)
    {
        rec.forgotpass();
        cout<<"\n";
        cout << "\nDo you wish to re enter choice?  (y/n)\n";
            cin >> ch;
            if (ch == 'y' || ch == 'Y')
            {
                cout << "-------------------\n";
                goto repeat;
            }
            else
                cout << "\n----GoodBye-----\n";
    }

    return 0;
}
