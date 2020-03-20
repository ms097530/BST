/*

A program whose purpose is implementing and testing a BST (binary search tree)

*/

#include <stdio.h>
#include <iostream>
#include <exception>

using namespace std;

template <typename key, typename E>
class BST;

template <typename key, typename E>
class Node
{
public:
	Node(key K, E element, Node<key, E>* left = nullptr, Node<key, E>* right = nullptr) : k(K), elem(element), Lchild(left), Rchild(right) { }
	friend class BST<key, E>;

private:
	key k;
	E elem;
	Node<key, E>* Lchild;
	Node<key, E>* Rchild;
};

template <typename key, typename E>
class BST
	//Notes for users of class:
	//1. key and E must be copyable
{
public:
	BST() : root(nullptr) { }
	BST(Node<key, E>* rt) : root(rt) { }
	~BST() { if (root != nullptr) destrhelp(root); }
	void inorderPrint()
	{
		if (root != nullptr)
			printhelp(root);
	}
	void insert(key K, E elem)
	{
		if (root == nullptr)
			root = new Node<key, E>(K, elem);
		else if (K < root->k)
			root->Lchild = inserthelp(K, elem, root->Lchild);
		else if (K >= root->k)
			root->Rchild = inserthelp(K, elem, root->Rchild);
	}

	Node<key, E>* find(const key& K)
	{
		if (root == nullptr)
			return nullptr;
		return findhelp(root, K);
	}

	void deleteNode(key K);


private:
	Node<key, E>* root;
	Node<key, E>* inserthelp(key K, E elem, Node<key, E>* node);
	Node<key, E>* deletehelp(Node<key, E>* node, key K);
	Node<key, E>* getMin(Node<key, E>* node);

	void printhelp(Node<key, E>* node)
	{
		if (node == nullptr)
			return;
		printhelp(node->Lchild);
		cout << "Key: " << node->k << "   " << "Element: " << node->elem << endl;
		printhelp(node->Rchild);
	}

	void destrhelp(Node<key, E>* node)
		//perform postorder traversal and delete nodes of tree
	{
		if (node->Lchild != nullptr)
			destrhelp(node->Lchild);
		if (node->Rchild != nullptr)
			destrhelp(node->Rchild);
		delete node;
	}

	Node<key, E>* findhelp(Node<key, E>* root, key K)
	{
		if (root->k == K)
			return root;
		else if (K < root->k)
			return findhelp(root->Lchild, K);
		else if (K >= root->k)
			return findhelp(root->Rchild, K);
		else
			return nullptr;
	}
};

template <typename key, typename E>
Node<key, E>* BST<key, E>::inserthelp(key K, E elem, Node<key, E>* node)
{

	if (node == nullptr)
		return new Node<key, E>(K, elem);

	if (K < node->k)			//take left branch and return current node
	{
		node->Lchild = inserthelp(K, elem, node->Lchild);
		return node;
	}
	else if (K >= node->k)		//take right branch and return current node
	{
		node->Rchild = inserthelp(K, elem, node->Rchild);
		return node;
	}
	
	throw std::logic_error("Unexpected logic error - insertion.");		//throw exception if none of the previous paths are taken
}

template <typename key, typename E>
void BST<key, E>::deleteNode(key K)
{
	Node<key, E>* temp = find(K);
	if (temp != nullptr)
		root = deletehelp(root, K);
}

template <typename key, typename E>
Node<key, E>* BST<key, E>::deletehelp(Node<key, E>* node, key K)
{
		
	if (K < node->k)
	{
		node->Lchild = deletehelp(node->Lchild, K);
		return node;
	}
	else if (K > node->k)
	{
		node->Rchild = deletehelp(node->Rchild, K);
		return node;
	}
	else if (K == node->k)      //found it - delete
	{
		Node<key, E>* temp;
		//check for number of children
		if (node->Lchild == nullptr && node->Rchild == nullptr)     //no children
		{
			delete node;
			return nullptr;
		}
		else if (node->Lchild != nullptr && node->Rchild == nullptr)    //only left child
		{
			temp = node->Lchild;
			delete node;
			return temp;
		}
		else if (node->Lchild == nullptr && node->Rchild != nullptr)    //only right child
		{
			temp = node->Rchild;
			delete node;
			return temp;
		}
		else if (node->Lchild != nullptr && node->Rchild != nullptr)    //two children
		{
			//get minimum element from right subtree of node to be deleted
			//this node will be a leaf, so set deleted node's children to be the children of this node
			temp = getMin(node->Rchild);
			key tempKey = temp->k;
			E tempElem = temp->elem;
			deleteNode(temp->k);
			node->k = tempKey;
			node->elem = tempElem;
			return node;
		}
	}
	throw std::logic_error("Unexpected logic error - deletion.");		//throw exception if none of the previous paths are taken
	
}

template <typename key, typename E>
Node<key, E>* BST<key, E>::getMin(Node<key, E>* node)
{
	Node<key, E>* temp = node;
	while (temp->Lchild != nullptr)
	{
		temp = temp->Lchild;
	}
	return temp;
}



int main()
{
	BST<int, int> myBST;

	myBST.insert(5, 5);
	myBST.insert(3, 3);
	myBST.insert(7, 7);
	myBST.insert(1, 1);
	myBST.insert(9, 9);
	myBST.insert(4, 4);
	myBST.insert(2, 2);
	myBST.insert(6, 6);
	myBST.insert(8, 8);
	myBST.insert(10, 10);

	myBST.inorderPrint();

	cout << endl;

	myBST.deleteNode(5);        //delete root



	myBST.inorderPrint();

	return 0;
}
