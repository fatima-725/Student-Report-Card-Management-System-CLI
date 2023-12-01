#include<iostream>
#include<conio.h> //getch()
#include<windows.h>//system("cls")
#include<fstream> //filing
#include<iomanip>//opening modes
#include<stdio.h>
using namespace std;
// Function Declaration
void intro();
void login();
void exit();

class student
{
protected:
    int rollno,n;
    char f_name[10], l_name[10];
    float s1,s2,s3,s4,s5,s6,total;
    double per;
    char grade;
public:
    void getdata();
    void showdata();
    int rolln();
    void displayall_tabular();
    void Total();
    void Total(float s);
    void grades();
};

class admin : public student
{
public:
    void enter_record();
    void display_all();
    void search_display();
    void delet();
};

void student :: displayall_tabular()
{
    cout<<rollno<<setw(13)<<f_name<<setw(12)<<l_name<<setw(6)<<s1<<setw(6)<<s2<<setw(6)<<s3<<setw(6)<<s4<<setw(6)<<s5<<setw(6)<<s6<<setw(8)<<per<<setw(8)<<grade<<endl;
}


void student :: grades()
{
    if (per>=80)
        grade='A';
    else if (per>=70 && per<80)
        grade='B';
    else if (per>=60 && per<50)
        grade='C';
    else if (per>=50 && per<40)
        grade='D';
    else
        grade='F';
}
void student:: Total()
{
    s6=0;
    total=s1+s2+s3+s4+s5;
    per=total/5.0;
    grades();

}
void student :: Total(float s)
{
    cout<<"Enter The Marks in Subject 6 out of 100 : ";
    cin>>s6;
    total=s1+s2+s3+s4+s5+s6;
    per=total/6.0;
    grades();
}

void student::getdata()
{

    cout<<"Enter Roll No : ";
    cin>>rollno;
    try
    {
        if (rollno<=0)
        {
            throw (rollno);
        }
    }
    catch(int a)
    {
        cout<<"Roll no must be greater than 0"<<endl;
    }
    cout<<"Enter First Name : ";
    cin>>f_name;
    cout<<"Enter Last Name : ";
    cin>>l_name;
    cout<<"Number of courses : ";
    cin>>n;
    cout<<"Enter The Marks in Subject 1 out of 100 : ";
    cin>>s1;
    cout<<"Enter The Marks in Subject 2 out of 100 : ";
    cin>>s2;
    cout<<"Enter The Marks in Subject 3 out of 100 : ";
    cin>>s3;
    cout<<"Enter The Marks in Subject 4 out of 100 : ";
    cin>>s4;
    cout<<"Enter The Marks in Subject 5 out of 100 : ";
    cin>>s5;
    if(n==5)
    {
        Total();
    }
    else if(n==6)
    {

        Total(n);
    }

}

void student::showdata()
{
    cout<<"\nRoll Number of Student :"<<rollno<<endl;
    cout<<"Name of Student : "<<f_name<<" "<<l_name<<endl;
    if(n==5)
    {
        cout<<"Marks in Subject 1 : "<<s1<<endl;
        cout<<"Marks in Subject 2 : "<<s2<<endl;
        cout<<"Marks in Subject 3 : "<<s3<<endl;
        cout<<"Marks in Subject 4 : "<<s4<<endl;
        cout<<"Marks in Subject 5 : "<<s5<<endl;
        cout<<"Percentage of Student : "<<per<<endl;
        cout<<"Grade of Student : "<<grade<<endl;
    }
    if(n==6)
    {
        cout<<"Marks in Subject 1 : "<<s1<<endl;
        cout<<"Marks in Subject 2 : "<<s2<<endl;
        cout<<"Marks in Subject 3 : "<<s3<<endl;
        cout<<"Marks in Subject 4 : "<<s4<<endl;
        cout<<"Marks in Subject 5 : "<<s5<<endl;
        cout<<"Marks in Subject 6 : "<<s6<<endl;
        cout<<"Percentage of Student : "<<per<<endl;
        cout<<"Grade of Student : "<<grade<<endl;
    }

}

int student::rolln()
{
    return rollno;
}

void admin :: enter_record()
{
    student st;
    ofstream o_file;
    o_file.open("Student.dat",ios::binary|ios::app);
    st.getdata();
    o_file.write((char *)&st,sizeof(st));
    o_file.close();
    system("cls");
}

void admin :: display_all()
{
    system("cls");
    cout<<"\n\n\n\n";
    student st;
    cout<<"======================================================================================"<<endl;
    cout<<"Roll no First Name Last Name Sub 1 Sub 2 Sub 3 Sub 4 Sub 5 Sub 6 Percentage Grade"<<endl;
    cout<<"======================================================================================"<<endl;
    ifstream i_file;
    i_file.open("Student.dat",ios::binary);
    if(!i_file)
        cout<<"Cannot be open";
    while(i_file.read((char *)&st,sizeof(st)))
    {
        st.displayall_tabular();
    }
    cin.ignore();
    cin.get();
    i_file.close();
    system("cls");
}

void admin :: search_display()
{
    int n;
    cout<<"Enter the roll no to search : ";
    cin>>n;
    ifstream i_file;
    i_file.open("Student.dat",ios::binary);
    student st;
    bool x=0;
    if(!i_file)
        cout<<"Cannot be open";
    else
    {
        while(i_file.read((char *)&st,sizeof(st)))
        {

            if(st.rolln()==n)
            {
                st.showdata();
                x=1;
            }
        }
        if(x==0)
        {
            cout<<"Record Not Found"<<endl;
        }
        i_file.close();
        cin.ignore();
        cin.get();
        system("cls");
    }
}

void admin :: delet()
{
    system("cls");
    student st;
    ifstream i_file;
    ofstream o_file;
    i_file.open("Student.dat",ios::binary|ios::in);
    o_file.open("Temp.dat",ios::binary | ios::out);
    i_file.seekg(0);
    if( !i_file || !o_file)
    {
        cout<<"Error in opening file"<<endl;
    }
    else
    {
        int n;
        cout<<"Enter the roll no to Delete: ";
        cin>>n;
        while(i_file.read((char *)&st,sizeof(student)))
        {
            if(st.rolln()!=n)
            {
                o_file.write((char*)&st, sizeof(st));
            }
        }
        i_file.close();
        o_file.close();
        remove("Student.dat");
        rename("Temp.dat","Student.dat");
        cout<<"Record Deleted"<<endl;
        cin.ignore();
        cin.get();
        system("cls");
    }
}

void exit()
{
    system("cls");
    cout<<"\n\t\tThank YOu"<<endl;
}

void intro()
{
    cout<<"\n\n\n\t\t\t\t\t------Welcome------ \n\n\n\t\t\t\t------Student report card generator------"<<endl;
    cout<<"\n\n\n\tDesigned by"<<endl;
    cout<<"\n\n\tFatima Tuz Zahra\n\tAliza Alwani\n\tSavera Tehseen\n\tDileep Kumar"<<endl;
    cout<<"\n\n\nPress any key to continue"<<endl;
    getch();
    system("cls");
}

void login()
{
    cout<<"\n\n\n\n\tEnter the following information correctly to go to the main menu"<<endl;
    string username,password;
check_in:
    cout<<"\nUsername : ";
    cin>>username;
    cout<<"Password : ";
    cin>>password;
    if(username=="Admin" && password=="1234")
        return;
    else
    {
        cout<<"Invalid username and/or password"<<endl;
        goto check_in;
    }

}

int main()
{
    admin ad;
    intro();
    //login();
    int i;
    do
    {
        cout<<"\n\t\t Main Menu"<<endl;
        cout<<"\t\t 01. Enter Student Record "<<endl;
        cout<<"\t\t 02. Display All Students Record "<<endl;
        cout<<"\t\t 03. Search and Display Specific Student Record "<<endl;
        cout<<"\t\t 04. Delete Student Record "<<endl;
        cout<<"\t\t 05. Exit"<<endl;
        cout<<"\n Select Your Option (1-6): ";
        cin>>i;
        switch(i)
        {
        case 1:
            ad.enter_record();
            break;
        case 2:
            ad.display_all();
            break;
        case 3:
            ad.search_display();
            break;
        case 4:
            ad.delet();
            break;
        case 5:
            exit();
            break;
        }
    }
    while(i!=5);
}
