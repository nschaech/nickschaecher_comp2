#ifndef NODE	
#define NODE
#include <iostream>
using namespace std;
//binary node template class to create binaryNodes
template<class T>
class binaryNode {
public:
	T data;
	binaryNode<T >*left;
	binaryNode<T> *right;

	binaryNode(T d)
		:data(d),left(nullptr),right(nullptr){}

};

//binarySearhtree class to initialize binaryNodes and add the needed functions
template<class T>
class binarySearchTree {
private:
	binaryNode<T>* root;
	int numberOfNodes;

	//insert function
	void insert(T item, binaryNode<T>*& t)
	{
		//Insert nodes at the edge of the list
		if (t == nullptr)
		{
			t = new binaryNode<T>(item);
			numberOfNodes++;
		}
		//traverse list by comparing the new item with a given item
		//if the new item is less the given item traverse left
		else if (item < t->data)
		{
			insert(item, t->left);
		}
		//if the new item is greater than the given item traverse right
		else if (item > t->data)
		{
			insert(item, t->right);
		}
	}
	//find functions
	binaryNode<T>* find(T item, binaryNode<T>* t, long long int& compare)
	{
		//If the item is not found return nullptr
		if (t == nullptr)
		{
			return nullptr;
		}
		//traverse list by recursively calling find function like in insert to determine where the item is
		else if (item < t->data)
		{
			compare++;
			return find(item, t->left,compare);
		}
		else if (item > t->data)
		{
			compare++;
			return find(item, t->right,compare);
		}
		//if item when compared is not greater or less than the checked data the item must be equal to the data being checked.
		else
		{
			compare++;
			return t;
		}
	}

	//function to traverse a list and delete along the way
	void elements(T &data)
	{
		//if the list is empty return
		if (root->left == nullptr)
		{
			return;
		}
		else
		{
			//top node is what is returned
			data = root->left->data;
			//remove top node to get anothe node in the list to return
			remove(root->left->data,root->left);
			return;
		}
	}
public:
	//constructor to set initial value to root
	binarySearchTree() : root(nullptr), numberOfNodes(0) {}
	//destructor needed to deallocate allocated memory
	~binarySearchTree() {
		clear(root->left);
	}

	//Find min function traverses the binary tree to the far left to find the least valuable element
	binaryNode<T>* findMin(binaryNode<T>* t)
	{
		if (t == nullptr)
		{
			return nullptr;
		}
		else if (t->left == nullptr)
		{
			return t;
		}
		return findMin(t->left);
	}
	
	//remove function deallocates a given node
	void remove(T item, binaryNode<T> *&t)
	{
		//traverse binary tree
		if (t == nullptr)
		{
			return;
		}
		if (item < t->data)
		{
			remove(item, t->left);
		}
		else if (item > t->data)
		{
			remove(item, t->right);
		}
		else
		{
			binaryNode<T>* oldNode;
			//if the node to the left of the node to be removed is a nullptr set node that will replace the deleted node to the right node
			if (t->left == nullptr)
			{
				oldNode = t;
				t = t->right;
				delete oldNode;
				numberOfNodes--;
				return;
			}
			//If right node to the node to be deleted is nullptr set the node to replace the deleted node to the left node of the deleted node
			else if (t->right == nullptr)
			{
				oldNode = t;
				t = t->left;
				delete oldNode;
				numberOfNodes--;
				return;
			}
			//Set the node to replace the deleted node to the minimum node if none of the above conditions is true
			oldNode = findMin(t->right);
			t->data = oldNode->data;
			//recursively call this function to meet a condition that will delete the node that is desired to be deleted
			remove(t->data, t->right);
		}
	}
	//public insert to call private insert since only the element of type T is being passed in cpp
	void insert(T item)
	{
		insert(item, root);
	}
	//public find for compars that are passed and given item called in cpp
	binaryNode<T>* find(T item,long long int& compare)
	{
		return find(item, root,compare);
	}
	//clear function to deallocate memory upon when the desctructor is called
	void clear(binaryNode<T>* t)
	{
		if (t == nullptr)
		{
			return;
		}
		else {
			clear(t->left);
			clear(t->right);
			delete(t);
			numberOfNodes--;
		}
	}

	//T elements returns data at the given top node of the binary tree
	T elements()
	{
		T data;
		elements(data);
		return data;
	}
	//int get size returns teh number of nodes in the tree which was iterated in insert function above.
	int getNumberOfNodes() { return numberOfNodes; }


};

#endif
