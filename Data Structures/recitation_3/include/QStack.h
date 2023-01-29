/* @Author
Student Name: Erce Gülmez
Student ID: 150210728
Date: 06/04/2022 */

#include <queue>

using namespace std;

class QStack
{
    private:
        queue<int> main;

    public:
        void push(int);
        void pop();
        void printStack();
};