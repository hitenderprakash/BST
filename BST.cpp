// BST: implementation of Binary Search Tree (with parent pointer)
// Hitender Prakash
//version 2 (rough draft)

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class TreeNode {
public:
	int val;
	TreeNode *parent;
	TreeNode *left;
	TreeNode *right;

	TreeNode(int arg = 0) :val(arg), parent(nullptr), left(nullptr), right(nullptr) {
	}
};

//============
TreeNode* searchNodeInBST(TreeNode* root, int value) {
	TreeNode* ret = nullptr;
	TreeNode *ptr = root;
	while (ptr) {
		if (ptr->val == value) {
			return ptr;
		}
		else if (value> ptr->val) {
			ptr = ptr->right;
		}
		else {
			ptr = ptr->left;
		}
	}
	return ret;
}

void inorder(TreeNode* root, vector<int> &retVec) {
	if (root) {
		if (root->left) {
			inorder(root->left, retVec);
		}
		retVec.push_back(root->val);
		if (root->right) {
			inorder(root->right, retVec);
		}
	}
}

void prerder(TreeNode* root, vector<int> &retVec) {
	if (root) {
		retVec.push_back(root->val);
		if (root->left) {
			prerder(root->left, retVec);
		}
		if (root->right) {
			prerder(root->right, retVec);
		}
	}
}
TreeNode* predecessor(TreeNode *ptr) {
	if (!ptr) { return nullptr; }
	if (ptr->left) {
		return ptr->left;
	}
	TreeNode * temp = ptr;
	while (temp->parent && temp == temp->parent->left) {
		temp = temp->parent;
	}
	return temp->parent;
}

TreeNode* successor(TreeNode *ptr) {
	if (!ptr) { return nullptr; }
	if (ptr->right) {
		return ptr->right;
	}
	TreeNode * temp = ptr;
	while (temp->parent && temp == temp->parent->right) {
		temp = temp->parent;
	}
	return temp->parent;
}

TreeNode* getLargestNodeInBST(TreeNode *root) {
	TreeNode *ptr = nullptr;
	if (root) {
		ptr = root;
		while (ptr->right) {
			ptr = ptr->right;
		}
	}
	return ptr;
}

TreeNode* getSmallestNodeInBST(TreeNode *root) {
	TreeNode *ptr = nullptr;
	if (root) {
		ptr = root;
		while (ptr->left) {
			ptr = ptr->left;
		}
	}
	return ptr;
}

TreeNode* addNodeInBST(TreeNode *root, TreeNode *toAdd) {
	if (!root) {
		return toAdd;
	}
	TreeNode *ptr = root;
	while (true) {
		if (toAdd->val <= ptr->val) {
			if (ptr->left) {
				ptr = ptr->left; continue;
			}
			else {
				ptr->left = toAdd;
				toAdd->parent = ptr;
				return toAdd;
			}
		}
		else {
			if (ptr->right) {
				ptr = ptr->right; continue;
			}
			else {
				ptr->right = toAdd;
				toAdd->parent = ptr;
				return toAdd;
			}
		}
	}
}

TreeNode* addNodeInBST(TreeNode *root, int v) {
	TreeNode *toAdd = new TreeNode(v);
	return addNodeInBST(root,toAdd);
}

int deleteNodeInBST(TreeNode *root, TreeNode *toDelete) {
	if (!toDelete) {
		return -1;
	}
	if (!toDelete->left && !toDelete->right) {
		delete(toDelete);
		toDelete = nullptr;
		return 0;
	}
	else if (toDelete->left) {
		TreeNode *succ = getLargestNodeInBST(toDelete->left);
		if (succ == toDelete->left) {
			succ->parent->left = succ->left;
		}
		else {
			succ->parent->right = succ->left;
		}
		if(succ->left){ succ->left->parent = succ->parent; }
		toDelete->val = succ->val;
		delete(succ);
		return 0;
	}
	else if (toDelete->right) {
		TreeNode *succ = getSmallestNodeInBST(toDelete->right);
		if (succ == toDelete->right) {
			succ->parent->right = succ->right;
		}
		else {
			succ->parent->left = succ->right;
		}
		if(succ->right){ succ->right->parent = succ->parent; }
		toDelete->val = succ->val;
		delete(succ);
		return 0;

	}
}

int deleteNodeInBST(TreeNode *root, int val) {
	TreeNode *toDelete = searchNodeInBST(root, val);
	return deleteNodeInBST(root, toDelete);
}

TreeNode* genbBST(vector<int> &inputVec, unsigned int start, unsigned int end) {
	if (inputVec.size() <= 0 || end < start || end >= inputVec.size()) {
		return nullptr;
	}
	int mid = (start + end) / 2;
	TreeNode *root = new TreeNode(inputVec[mid]);

	root->left = genbBST(inputVec, start, mid - 1);
	if (root->left) {
		root->left->parent = root;
	}

	root->right = genbBST(inputVec, mid + 1, end);
	if (root->right) {
		root->right->parent = root;
	}
	return root;
}



void displayVec(vector<int> &vecRef) {
	if (vecRef.size()>0) {
		cout << "\n";
		for (auto i : vecRef) {
			cout << i << " ";
		}
	}
}

//=====functions for unit testing purpose, to be removed 
void testSearch(TreeNode *root, int v) {
	TreeNode *pt = searchNodeInBST(root, v);
	if (pt) {
		cout << "\nSearching node with val: " << v << " returned success, node: " << pt;
		if (pt->parent) {
			cout << "\nThe parent of " << v << " is: " << pt->parent->val;
		}
		if (pt->left) {
			cout << "\nThe left child of " << v << " is: " << pt->left->val;
		}
		if (pt->right) {
			cout << "\nThe right child of " << v << " is: " << pt->right->val;
		}
	}
}
void testPred(TreeNode * root, int v) {
	TreeNode *pt = searchNodeInBST(root, v);
	if (pt) {
		TreeNode *temp = predecessor(pt);
		if (temp) {
			cout << "\nPred of " << v << " is: " << temp->val;
		}
		else {
			cout << "\nNo Pred of " << v;
		}
	}
}

void testSucc(TreeNode * root, int v) {
	TreeNode *pt = searchNodeInBST(root, v);
	if (pt) {
		TreeNode *temp = successor(pt);
		if (temp) {
			cout << "\nSucc of " << v << " is: " << temp->val;
		}
		else {
			cout << "\nNo Succ of " << v;
		}
	}
}



int main()
{
	//test driver code 
	vector<int> input = { 3, 9, 8, 2, 1, 5, 4, 7, 6 };

	sort(input.begin(), input.end());
	vector<int> inorderOut;
	vector<int> preorderOut;

	TreeNode *root = nullptr; //initialize root with nullptr
	if (!input.empty()) {
		root = genbBST(input, 0, input.size() - 1); //call genBST only if input.size()-1 is valid unsigned int
	}

	inorder(root, inorderOut);
	prerder(root, preorderOut);
	cout << "\nPreorder";
	displayVec(preorderOut);
	cout << "\ninorder";
	displayVec(inorderOut);
	vector<int> printVec;
	cout << "\nExperimenting with new capabilities";
	cout << "\n========Search:===========";
	testSearch(root, 2);
	testSearch(root, 5);
	cout << "\n==========pred==========";
	testPred(root, 6);
	testPred(root, 9);
	testPred(root, 1);

	cout << "\n==========succ==========";
	testSucc(root, 4);
	testSucc(root, 1);
	testSucc(root, 9);

	cout << "\n=====Test smallest & Largest element======";
	TreeNode *pt = nullptr;
	pt = getLargestNodeInBST(root);
	if (pt) {
		cout << "\nLargest element in BST: " << pt->val;
	}
	pt = getSmallestNodeInBST(root);
	if (pt) {
		cout << "\nSmallest  element in BST: " << pt->val;
	}

	cout << "\n=================test ADD node=========";
	addNodeInBST(root, 18);
	addNodeInBST(root, 24);
	addNodeInBST(root, 21);
	addNodeInBST(root, 22);
	//addNodeInBST(root, 15);
	//addNodeInBST(root, 16);
	deleteNodeInBST(root, 18);
	vector<int> sampleIn;
	vector<int> sampleOut;
	inorder(root,sampleIn);
	displayVec(sampleIn);
	prerder(root, sampleOut);
	displayVec(sampleOut);


	cout << "\n";
	getchar();
	return 0;
}

