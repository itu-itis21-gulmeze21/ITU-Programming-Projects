/* @Author
Student Name: Erce Gülmez
Student ID: 150210728
Date: 08/03/2022 */



#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;


class Student{
    private:
        string name;
        int grade;
    public:
        Student();
        ~Student();
        void set_grade(int);
        int get_grade();
        string get_name();
        void set_name(string);
};

Student::Student()
{
}

Student::~Student()
{
}

void Student::set_grade(int sgrade)
{
    if(sgrade<0)
        grade=0;
    else
        grade = sgrade;
}

int Student::get_grade()
{
    return grade;
}

string Student::get_name()
{
    return name;
}

void Student::set_name(string sname)
{
    name = sname;
}



bool perform_operation(char);
void print_menu();
void listStudents();
void addStudent();
void maxGradeStudent();


int capacity = 0;
Student astudents[10];

int main(){

    bool end = false;
    char choice;


    while (!end)
    {
        print_menu();
        cin >> choice;
        end = perform_operation(choice);
    }

    return EXIT_SUCCESS;
}

void print_menu()
{
    cout << "Choose an operation" << endl;
    cout << "A: Add student" << endl;
    cout << "L: List students" << endl;
    cout << "M: Name and grade of the student with the highest grade" << endl;
    cout << "E: Exit" << endl;
    cout << "Enter a choice {A,L,M,E}: ";
}

bool perform_operation(char choice)
{
    bool terminate = false;
    string strday;

    switch (choice)
    {
    case 'L':
    case 'l':
        listStudents();
        break;
    case 'A':
    case 'a':
        addStudent();
        break;
    case 'M':
    case 'm':
        maxGradeStudent();
        break;
    case 'E':
    case 'e':
        terminate = true;
        break;
    default:
        cout << "Error: You have entered an invalid choice" << endl;
        cin >> choice;
        terminate = perform_operation(choice);
        break;
    }
    return terminate;
}

void listStudents()//basically goes over the array items with the for loop and in each iteration, prints out the name and the grade of the object
{   
    for(int a=0;a<capacity;a++){
        cout<<astudents[a].get_name()<<":"<<astudents[a].get_grade()<<endl;
    }
}

void addStudent()
{
    string name;
    int grade;
    cout << "Enter the name of student: ";
    cin >> name;
    cout << "Enter the grade of student: ";
    cin >> grade;

    astudents[capacity].set_grade(grade);//seting the grade to the object's grade attribute
    astudents[capacity].set_name(name);//seting the name to the object's name attribute
    capacity++;

}

void maxGradeStudent()
{
    int tempgrade=0;//a temporary integer that holds the maximum grade
    int index=0;//a variable to keep the index of the array 
    for(int a=0;a<capacity;a++){
        if(astudents[a].get_grade()>tempgrade){
            index=a;//the index of the object that has the highest grade is assigned to 'index' variable
            tempgrade=astudents[a].get_grade();//the highest grade is assigned to 'tempgrade' variable
        }
    }
    cout<<astudents[index].get_name()<<":"<<astudents[index].get_grade()<<endl;
    
}