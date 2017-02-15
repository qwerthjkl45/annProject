#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TreeNode {
private:
	TreeNode* leftChild;
	TreeNode* rightChild;
	TreeNode* parent;
	
public:
	int key;
	TreeNode():leftChild(0),rightChild(0), parent(0), key(0){};
	TreeNode(int a):leftChild(0), rightChild(0), parent(0), key(a){};
	friend class BST;	
};

class BST {
private:
	//TreeNode* root;
public: 
	TreeNode* root;
	BST():root(0){};
	void InsertBST(int key);
	void printBST(TreeNode* node);
	void deleteBST(TreeNode* node);
};

void BST::InsertBST(int key) {
	TreeNode* x = 0;
	TreeNode* y = 0;	
	TreeNode* insertNode = new TreeNode(key);
	x = root;
	while(x!= NULL) {
		y = x;
		if(insertNode->key > x->key) 
			x = x->rightChild;
		else
			x = x->leftChild;
		
	}
	insertNode->parent = y;
	if(y == NULL)
		this->root = insertNode;
	else if(insertNode->key > y->key) 
		y->rightChild = insertNode;
	else 
		y->leftChild = insertNode;
}

void BST::printBST(TreeNode* node) {
	if(node == NULL)
		return;
	printBST(node->leftChild);
	cout<<node->key<<endl;
	printBST(node->rightChild);
	
}

void BST::deleteBST(TreeNode* node) {
	if((node->rightChild == NULL) && (node->leftChild == NULL))
		node = NULL;
	else if((node->rightChild != NULL) && (node->leftChild != NULL)) {
		cout<<"enter"<<endl;		
		TreeNode* x = new TreeNode();
		TreeNode* y = new TreeNode();
		x = root->rightChild;
		while(x != NULL) {
			y = x;
			x = x->leftChild;		
		}
		if (y->leftChild != NULL)
			x = y->leftChild;    
		else
			x = y->rightChild;
		
		if(x!= NULL)
			x->parent = y->parent;
		if(y->parent == NULL)
			this->root = x;
		else if(y == y->parent->leftChild)
			y->parent->leftChild = x;
		else 
			y->parent->rightChild = x;
		
		
		if(y!= node) {
			node->key = y->key;		
		}
		
		delete y;
		y = 0;
	}
	else { cout<<"case 3"<<endl;
		if(node->rightChild!= NULL) {
			node->rightChild->parent = node->parent;
			node->parent->rightChild = node->rightChild;
		}
		else {
			node->leftChild->parent = node->parent;
			node->parent->leftChild = node->leftChild;		
		}
	}
	//delete node;
}

int main() {
	BST T;
	T.InsertBST(5);
	T.InsertBST(2);
	T.InsertBST(7);
	T.InsertBST(4);
//	T.InsertBST(1);
	T.InsertBST(6);
	T.InsertBST(8);
	T.InsertBST(100);
	TreeNode* x = new TreeNode;
	x = T.root;
	T.printBST(x);
	cout<<"\n\n"<<endl;
	T.deleteBST(x);
	//cout<<"\n"<<x->key<<endl;
	T.printBST(x);
	
	return 0;
}



