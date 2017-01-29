#include <iostream>
using namespace std;

class Tree
{
	struct Node
	{
		int data;
		Node* left;
		Node* right;
		
		Node(int data): data(data), left(0), right(0) {}
	};

	Node *root;
public:
	Tree()
	{
		root = 0;
	}

	void insert(int data)
	{
		Node *n = new Node(data);
		
		if (root == 0)
			root = n;
		else
		{
			if (
