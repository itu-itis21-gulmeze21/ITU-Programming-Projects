/* @Author
Student Name: Erce Gülmez
Student ID: 150210728
Date: 06/04/2022 */

#include <iostream>
#include <queue>
#include <QStack.h>


using namespace std;

void QStack::push(int x)
{
    int s= main.size();//get the size
    main.push(x);//enqueue the element
    for(int i=0;i<s;i++){
        main.push(main.front());//enqueue the front element
        main.pop();//dequeue
    }

}

void QStack::pop()
{
    if(main.empty()){//empty stack 
        cout<<"Stack is empty"<<endl;
    }
    else{
        int x=main.front();//get the front element for printing its value
        main.pop();//dequeue
        cout<<x<<" is popped"<<endl;
    }
}

void QStack::printStack()
{
    if (main.empty())
        return;

    int x;
    for(unsigned long int i=0;i<main.size();i++)
    {
        x = main.front();
        main.pop();
        cout << x << ' ';
        main.push(x);
    }
}