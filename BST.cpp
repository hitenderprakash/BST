// BST: implementation of Binary Search Tree (with parent pointer)
// Hitender Prakash
//version 1 (rough draft)

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


int main()
{
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
	
	cout << "\n";
	getchar();
	return 0;
}


