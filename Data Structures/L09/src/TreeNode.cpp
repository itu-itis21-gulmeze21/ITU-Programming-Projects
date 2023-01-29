#include "TreeNode.h"
#include <stdlib.h>

TreeNode::TreeNode(char data)
{
    this->data=data;
    this->left=NULL;
    this->right=NULL;
}
void TreeNode::set_data(char d){
    this->data=d;
}
char TreeNode::get_data(){
    return this->data;
}
void TreeNode::set_left(TreeNode* l){
    this->left=l;
}
TreeNode* TreeNode::get_left(){
    return this->left;
}
void TreeNode::set_right(TreeNode* r){
    this->right=r;
}
TreeNode* TreeNode::get_right(){
    return this->right;
}