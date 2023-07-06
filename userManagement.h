//usermanagement.h
#include <iostream> //Header files
#include <fstream>
#include <cstdio>
#include <string>

#include "inboxmanagement.h"

using namespace std;

void MainMenu();
void RegisterNewUser();
void Login();
void LoggedInMenu(string userName);
void DeleteUser();
string GetUserFile(string userName);
string GetPassword(string userName);

void MainMenu() //MainMenu of the email
{
    int choice; //getting the user's intention of using the service
    cout<<"1) Login"<<'\n';
    cout<<"2) Register new user"<<'\n';
    cout<<"3) Delete user"<<'\n';
    cout<<"99) Exit"<<'\n';
    cout<<"Selection: ";
    cin>>choice;
    switch (choice) //using switch to access functions
    {
        case 1:
        Login();
        break;
        case 2:
        RegisterNewUser();
        break;
        case 3:
        DeleteUser();
        cout<<"User removed successfully!\n";
        MainMenu();
        break;
        case 99:
        cout<<"Thank you for using our mail service,Exitting!! \n";
        break;
        default:
        cout<<"Invalid choice, run the program again! \n";
        break;
    }
}


void RegisterNewUser() //Registers new users while checking if the username already exists
{
    ifstream file;
    string userName,password;
    cout<<"Enter new username: ";
    cin>>userName;
    if(userName.length()<3) //checking name length
    {
        cout<<"Username must be atleast 3 characters \n";
        MainMenu();
    }
    else
    {
        cout<<"Enter new password: ";
        cin>>password;
        if(password.length()<6) //checking pwd length
        {
            cout<<"Password must be atleast 6 characters \n";
            MainMenu();
        }
        else
        {
            file.open(userName+".txt");
            if(file) //checking if the username already exists
            {
                cout<<"User already exists!!\n";
                MainMenu();
            }
            else
            {
                ofstream info(userName+".txt"); //creating the info text with name and password
                info<<"username "+userName+'\n'+"password "+password;
                info.close();
                ofstream inbox(userName+"-inbox.txt"); //creating an inbox file for the user
                inbox<<"#email\nmailservice\n"+userName+'\n'+"Introduction\nHello, "+userName+"! Welcome to our service";
                inbox.close();
                cout<<"User created successfully!!\n";
                MainMenu();
            }
        }
    }   
}
void Login()
{
    ifstream file;
    string userName,password;
    cout<<"Enter username: ";
    cin>>userName;
    file.open(userName+".txt");
    if(file)
    {
        cout<<"Enter password: ";
        cin>>password;
        if(password==GetPassword(userName))
            LoggedInMenu(userName);
        else
        {
            cout<<"Incorrect password!! \n";
            MainMenu();
        }
    }
    else
    {
        cout<<"User does not exist!\n";
        MainMenu();
    }
}
string GetPassword(string userName)
{
    string password,word;
    ifstream file;
    file.open(userName+".txt",ios::in);
    int flag=0;
    while(1)
    {
        file>>word;
        if(flag==1)
        {
            password=word;
            break;
        }
        if(word=="password")
            flag=1;
    }
    return password;
}


void LoggedInMenu(string userName)
{
    int choice=0;
    cout<<"1) Inbox["+to_string(GetInboxCount(userName))+"]\n";
    cout<<"2) Send Email \n";
    cout<<"99) Logout\n";
    cout<<"Selection: ";
    cin>>choice;
    switch (choice)
    {
    case 1:
        cout<<endl;
        ShowInbox(userName);
        LoggedInMenu(userName);
    break;
    case 2:
        SendEmail(userName);
        cout<<"\nEmail sent!\n";
        LoggedInMenu(userName);
    break;
    case 99:
        cout<<"Logging out!! \n";
        MainMenu();
    break;
    default:
        cout<<"Invalid choice!! \n";
        LoggedInMenu(userName);
    break;
    }
}

string GetUserFile(string userName)
{
    string fileName;
    fileName=userName+".txt";
    return fileName;
}

void DeleteUser()
{
    string userName,info,inbox;
    cout<<"Enter the username of the account to delete: ";
    cin>>userName;
    info=userName+".txt";
    inbox=userName+"-inbox.txt";
    remove(info.c_str());
    remove(inbox.c_str());
}
