/* @Author
Student Name: Erce Gülmez
Student ID: 150210728
Date: 22/04/2022 */
#ifndef BST_NODE
#define BST_NODE

class Node{
    private:
        int data;
        Node* left;
        Node* right;
    public:
        Node(int);
        void set_data(int);
        int get_data();
        void set_left(Node*);
        Node* get_left();
        void set_right(Node*);
        Node* get_right();
};

#endif 