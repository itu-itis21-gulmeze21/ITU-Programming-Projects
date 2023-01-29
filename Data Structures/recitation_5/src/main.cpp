/* @Author
Student Name: Erce Gülmez
Student ID : 150210728
Date: 10/05/2022 */
#include <iostream>
#include <vector>
#include "BinSTree.h"

using namespace std;

void print_menu();
bool perform_operation(char);
void convert(Node*);
void print_preorder_heap(Node*);
void print_less_than(int n, Node*);
void BST_to_MinHeap(Node*, vector<int> , int*);
void inorder_traversal(Node*, vector<int>&);

BinSTree* bst = new BinSTree();

int main()
{

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
    cout << "A: Add node to Binary Search Tree" << endl;
    cout << "C: Convert Binary Search Tree to Min Heap"<< endl;
    cout << "L: List Heap node less than the entered value"<< endl;
    cout << "P: Print Min Heap"<< endl;
    cout << "E: Exit" << endl;
    cout << "Enter a choice {A,C,L,P,E}:";
}

bool perform_operation(char choice)
{
    bool terminate = false;
    int e,l;

    switch (choice)
    {
        case 'A':
        case 'a':
            cout << "Enter node data:";
            cin >> e;
            bst->add(e);
            break;
        case 'C':
        case 'c':
            bst->root = bst->buildTree();
            convert(bst->root);
            break;
        case 'L':
        case 'l':
            cout << "Enter value:";
            cin >> l;
            print_less_than(l, bst->root);
            cout << endl;
            break;
        case 'P':
        case 'p':
            print_preorder_heap(bst->root);
            cout << endl;
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

void convert(Node* root)
{
    vector<int> arr;
    int i = -1;
    inorder_traversal(root, arr);
    BST_to_MinHeap(root, arr, &i);
}
void print_preorder_heap(Node* root)
{
    if(root)
    {
        cout << root->get_data() << " ";
        print_preorder_heap(root->get_left());
        print_preorder_heap(root->get_right());
    }
}
void print_less_than(int n, Node* root)
{
    if(root!=NULL){
        if(root->get_data()<n){//checks if this node's data is less than n, prints it if this is true
            cout<<root->get_data()<<" ";
        }
        print_less_than(n,root->get_left());
        print_less_than(n,root->get_right());
    }

}

void BST_to_MinHeap(Node* root, vector<int> arr, int* i)
{
    if(root!=NULL){
        root->set_data(arr[++(*i)]);//since *i=-1 in the beginning, set the (*i + 1)th element of the vector. increments *i at each set operation 
        BST_to_MinHeap(root->get_left(),arr, i);
        BST_to_MinHeap(root->get_right(),arr, i);
    }
}

void inorder_traversal(Node* root, vector<int>& arr)
{
    if(root!=NULL){
        inorder_traversal(root->get_left(),arr);
        arr.push_back(root->get_data());//pushes it to the vector inorder
        inorder_traversal(root->get_right(),arr);
    }
}