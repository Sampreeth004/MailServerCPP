//inboxmanagement.h
#include <iostream> //Header files
#include <fstream>
#include <cstdio>
#include <string>

using namespace std;

void ShowInbox(std::string userName);
string GetInboxFile(std::string userName);
int GetInboxCount(std::string userName);
string FormatEmailString(std::string from, std::string to, std::string subject, std::string msg);
void SendEmail(string userName);
bool DoesUserExist(string userName);

int GetInboxCount(string userName)
{
    ifstream file;
    string word;
    file.open(userName+"-inbox.txt",ios::in);
    int count=0;
    while(1)
    {
        file>>word;
        if(word=="#email")
            count++;
        if(file.eof())
            break;
    }
    return count;
}


string GetInboxFile(string userName)
{
    return userName+"-inbox.txt";
}

string FormatEmailString(string from, string to, string subject, string msg)
{
    string email="#email\n"+from+'\n'+to+'\n'+subject+'\n'+msg;
    return email;
}
void SendEmail(string userName)
{
    string receiver,subject,message,mail;
    fstream file;
    cout<<"Send email to: ";
    getline(cin >> ws, receiver);
    if(DoesUserExist(receiver))
    {
        cout<<"Subject: ";
        getline(cin >> ws, subject);
        cout<<"Message: ";
        getline(cin >> ws, message);
        mail=FormatEmailString(userName,receiver,subject,message);
        cout<<"Sending:\n"+mail;
        file.open(receiver+"-inbox.txt",ios::app);
        file<<"\n"+mail;
        file.close();
    }
    else
    {
        cout<<"Receiver not found, try again!\n";
        return;
    }
}
void ShowInbox(string userName)
{
    ifstream file(userName+"-inbox.txt");
    string line;
    int c=0;
    while(getline(file,line))
    {
        if(line=="#email")
            c=0;
        if(c==1)
            cout<<"From: "+line+'\n';
        if(c==2)
            cout<<"To: "+line+'\n';
        if(c==3)
            cout<<"Subject: "+line+'\n';
        if(c==4)
        {
            cout<<"Message: "+line+'\n';
            cout<<endl;
        }
        c++;
    }
    file.close();
}

bool DoesUserExist(string userName)
{
    ifstream file;
    file.open(userName+".txt");
    if(file)
        return true;
    else
        return false;
}
