// BST.cpp : Defines the entry point for the console application.
//
//Hitender Prakash (hitenderprakash@gmail.com)
//Driver Code : Only For the puspose of Testing functions in BSLib
//May not have proper error handling
//

//#include "stdafx.h"
#include <vector>
#include <iostream>
#include "BSTLib.h"
using namespace std;
using namespace BSTLIB;

class Item {
public:
	int value;

	Item(int arg) :value(arg) {}
	friend bool operator == (const Item& a, const Item& b) {
		return (a.value == b.value);
	}
	friend bool operator < (const Item& a, const Item& b) {
		return (a.value < b.value);
	}
	friend bool operator > (const Item& a, const Item& b) {
		return (a.value > b.value);
	}

	friend bool operator <= (const Item& a, const Item& b) {
		return (a<b || a==b);
	}

	friend bool operator >= (const Item& a, const Item& b) {
		return (a>b || a == b);
	}

	friend ostream& operator << (ostream& os, const Item& it) {
		os << it.value;
		return os;
	}
};


int main()
{
	std::vector<Item> input;
	for (int i = 0; i < 10; i++) {
		input.push_back(Item(i+1));
	}

	TreeNode<Item> *root = generateBSTFromSortedNodesList(input, 0, input.size() - 1);
	cout << "\nGenerated Tree with val: 1,2,3......10";
	
	TreeNode<Item> *pTestPtr = nullptr;

	pTestPtr = searchNodeByValueInBST(root, Item(2));
	cout << "\n Searching for node with val=2...";
	if (pTestPtr) {cout << "\nYes, Found: " << pTestPtr->val;}
	else { cout << "\nNot found any node with val: 2"; }

	cout << "\nAdding node with val: 15";
	Item it(15);
	pTestPtr = new TreeNode<Item>(it);
	pTestPtr = addExistingIsolatedTreeNodeToBST(root, pTestPtr);

	pTestPtr = searchNodeByValueInBST(root, Item(15));
	cout << "\n Searching for node with val=15...";
	if (pTestPtr) { cout << "\nYes, Found: " << pTestPtr->val; }
	else { cout << "\nNot found any node with val: 15"; }

	cout << "\nAdding new node by value with val: 11 ";
	pTestPtr = addNewNodeByValueInBST(root, Item(11));

	pTestPtr = searchNodeByValueInBST(root, Item(11));
	cout << "\n Searching for node with val=11...";
	if (pTestPtr) { cout << "\nYes, Found: " << pTestPtr->val; }
	else { cout << "\nNot found any node with val: 11"; }

	if (ERROR == deleteNodeByValueInBST(root, Item(13))) {
		cout << "\nDelete Invalid node tes case passed";
	}

	pTestPtr = addNewNodeByValueInBST(root, Item(12));
	deleteNodeByValueInBST(root, Item(15));

	vector<TreeNode<Item>*> PreOrderPtList;
	getBSTPreOrderTraversalTreeNodePtrList(root, PreOrderPtList);
	cout << "\nPreOrderPtList: ";
	for (TreeNode<Item>* i : PreOrderPtList) { cout << i->val<<" "; }

	vector<Item> PreOrderList = getBSTPreOrderTraversalNodeList(root);
	cout << "\nPreOrderList: ";
	displayList(PreOrderList);


	vector<TreeNode<Item>*> InOrderPtList;
	getBSTInOrderTraversalTreeNodePtrList(root, InOrderPtList);
	cout << "\nIordePtrList: ";
	for (TreeNode<Item>* i : InOrderPtList) { cout << i->val<<" "; }

	vector<Item> InOrderList = getBSTInOrderTraversalNodeList(root);
	cout << "\nInOrderList: ";
	displayList(InOrderList);

	vector<TreeNode<Item>*> PostOrderPtList;
	getBSTPostOrderTraversalTreeNodePtrList(root, PostOrderPtList);
	cout << "\nPostOrderPtList: ";
	for (TreeNode<Item>* i : PostOrderPtList) { cout << i->val<<" "; }

	vector<Item> PostOrderList = getBSTPostOrderTraversalNodeList(root);
	cout << "\nPostOrderList: ";
	displayList(PostOrderList);

	
	TreeNode<Item> *pt = getPtrToPrevNodeInSortedOrderInBST(searchNodeByValueInBST(root, Item(6)));
	if (pt) { cout << "\nPrev of 6 is: " << pt->val; }

	pt = getPtrToNextNodeInSortedOrderInBST(searchNodeByValueInBST(root, Item(4)));
	if (pt) { cout << "\nNext of 4 is: " << pt->val; }

	cout << "\nThe biggest node in tree: ";
	pt = getPtrToLargestNodeInBST(root);
	if (pt) { cout << pt->val; }

	cout << "\nThe Smallest node in tree: ";
	pt = getPtrToSmallestNodeInBST(root);
	if (pt) { cout << pt->val; }
	
	TreeNode<Item> *root_2 = nullptr;
	TreeNode<Item> *p = addNewNodeByValueInBST(root_2, Item(100));
	if (root_2 && (root_2 == p)) {
		cout << "\nCreate new Tree 2 from scratch with adding node successfull, new Tree's root is: " << root_2->val;
	}

	/*vector<TreeNodeAt2DimPlane<Item>> vec;
	int ret = recordPrintableCoordinatesOfBST(root, 0, 0, vec);
	for (TreeNodeAt2DimPlane<Item> i : vec) {
		cout << i;
	}*/

	cout << "\nMax depth: " << getMaxDepthOfBST(root);
	cout << "\nTree lools like:";
	cout << "\n===========================================";
	printBSTOnConsole(root,3,2);

	cin.ignore();
    return 0;
}

