/* @Author
Student Name: Erce Gülmez
Student ID : 150210728
Date: 10/05/2022 */
class Node{
    private:
        int data;
        Node* left;
        Node* right;
    
    public:
        Node(int);
        void set_left(Node*);
        void set_right(Node*);
        void set_data(int);

        Node* get_left();
        Node* get_right();
        Node** get_left_addr();
        Node** get_right_addr();
        int get_data();
};
