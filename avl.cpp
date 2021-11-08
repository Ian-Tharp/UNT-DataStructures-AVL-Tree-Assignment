/*
    Ian Tharp - ict0011 - IanTharp2@my.unt.edu
    11/2/21
    Dr. Heng Fan
    Assignment #3 - AVL Tree Implementation
*/

#include <stdio.h>
#include <iostream>
#include "avl.hpp"
using namespace std;

#define IS_ROOT 0
#define IS_LEFT 1
#define IS_RIGHT 2

/*
 * You will probably need auxiliary methods to 
 *  - find the minimum of tree
 *  - rotate (single and double, in both directions
 *  - balance an AVL  tree
 */

int getHeight(AvlNode* root) {
    int leftHeight, rightHeight;
    if (root == NULL) {
        return 0;
    }
    if (root->left == NULL) {
        leftHeight = 0;
    }
    else {
        leftHeight = 1 + root->left->height;
    }

    if (root->right == NULL) {
        rightHeight = 0;
    }
    else {
        rightHeight = 1 + root->right->height;
    }
    if (leftHeight > rightHeight) {
        return leftHeight;
    }
    return rightHeight;
}

AvlNode* rRotate(AvlNode*& root) {
    AvlNode* node;
    node = root->left;
    root->left = node->right;
    node->right = root;
    root->height = getHeight(root);
    node->height = getHeight(node);
    return node;
}

AvlNode* lRotate(AvlNode*& root) {
    AvlNode* node;
    node = root->right;
    root->right = node->left;
    node->left = root;
    root->height = getHeight(root);
    node->height = getHeight(node);
    return node;
}

AvlNode* rrRotate(AvlNode*& root) {
    root = lRotate(root);
    return root;
}

AvlNode* llRotate(AvlNode*& root) {
    root = rRotate(root);
    return root;
}

AvlNode* lrRotate(AvlNode*& root) {
    root->left = lRotate(root->left);
    root = rRotate(root);
    return root;
}

AvlNode* rlRotate(AvlNode*& root) {
    root->right = rRotate(root->right);
    root = lRotate(root);
    return root;
}

AvlNode* getMin(AvlNode*& root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}
AvlNode* getMax(AvlNode*& root) {
    while (root->right != NULL) {
        root = root->right;
    }
    return root;
}

int balanceFactor(AvlNode*& root) {
    int lh, rh;
    if (root == NULL) {
        return 0;
    }
    if (root->left == NULL) {
        lh = 0;
    }
    else {
        lh = 1 + root->left->height;
    }

    if (root->right == NULL) {
        rh = 0;
    }
    else {
        rh = 1 + root->right->height;
    }
    return (lh - rh);
}


/**
 * Internal method to insert into a subtree.
 * x is the item to insert.
 * t is the node that roots the subtree.
 * Set the new root of the subtree.
 */
void insert(const int& info, AvlNode*& root)
{

    if (root == NULL) {
        root = new AvlNode(info, NULL, NULL);
        //cout << "New Node created: " << info << endl;
    }
    else {
        if (info > root->element) {
            insert(info, root->right);
            if (balanceFactor(root) == -2)
                if (info > root->right->element)
                    root = rrRotate(root);
                else
                    root = rlRotate(root);
        }
        else {
            if (info < root->element)
            {
                insert(info, root->left);
                if (balanceFactor(root) == 2)
                    if (info < root->left->element)
                        root = llRotate(root);
                    else
                        root = lrRotate(root);
                
            }
        }
        root->height = getHeight(root);
        return;
    }
}

/**
 * Internal method to remove from a subtree.
 * info is the item to remove.
 * root is the node that roots the subtree.
 * Set the new root of the subtree.
 */
void remove(const int& info, AvlNode*& root) {
    //cout << "Code for deleting " << info << " goes here" << endl;
    AvlNode* node;
    AvlNode* node2;

    if (root->left == NULL && root->right == NULL) {
        root = NULL;
        delete root;
        return;
    }
    else if (root->element > info) {
        remove(info, root->left);
    }
    else {
        if (root->left != NULL) {
            node2 = getMin(root->left);
            root->element = node2->element;
            remove(node2->element, root->left);
        }
        else {
            node2 = getMax(root->right);
            root->element = node2->element;
            remove(node2->element, root->right);
        }
    }
    if (balanceFactor(root) == 2 && balanceFactor(root->left) == 1) {
        root = llRotate(root);
    }
    else if (balanceFactor(root) == 2 && balanceFactor(root->left) == -1) {
        root = lRotate(root);
    }
    else if (balanceFactor(root) == 2 && balanceFactor(root->left) == 0) {
        root = llRotate(root);
    }
    else if (balanceFactor(root) == -2 && balanceFactor(root->right) == -1) {
        root = rrRotate(root);
    }
    else if (balanceFactor(root) == -2 && balanceFactor(root->right) == 1) {
        root = rlRotate(root);
    }
    else if (balanceFactor(root) == -2 && balanceFactor(root->right) == 0) {
        root = llRotate(root);
    }
    return;
}

/*
 * Print methods, do not change
 */
void print(AvlNode *root, int level, int type) {
  if (root == NULL) {
    return;
  }
  if (type == IS_ROOT) {
    std::cout << root -> element << "\n";
  } else {
    for (int i = 1; i < level; i++) {
      std::cout << "| ";
    }
    if (type == IS_LEFT) {
      std::cout << "|l_" << root -> element << "\n";
    } else {
      std::cout << "|r_" << root -> element << "\n";
    }
  }
  if (root -> left != NULL) {
    print(root -> left, level + 1, IS_LEFT);
  }
  if (root -> right != NULL) {
    print(root -> right, level + 1, IS_RIGHT);
  }
}
void print(AvlNode *root) {
  print(root, 0, IS_ROOT);
}
/*
 * END Print methods, do not change
 */


/* 
 * Main method, do not change
 */
int main(int argc, const char * argv[]) {
  AvlNode *root = NULL;
  std::string filename = argv[1];
  freopen(filename.c_str(), "r", stdin);
  std::string input;
  int data;
  while(std::cin >> input){
    if (input == "insert"){
      std::cin>>data;
      insert(data, root);
    } else if(input == "delete"){
      std::cin>>data;
      remove(data, root);
    } else if(input == "print"){
      print(root);
      std::cout << "\n";
    } else{
      std::cout<<"Data not consistent in file";
      break;
    }
  }
  return 0;
}
/*
 * END main method
 */
