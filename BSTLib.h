// BSTLib: implementation of Simple Binary Search Tree (with parent pointer)
// Hitender Prakash

#ifndef _BST_H
#define _BST_H

#include <vector>
#include <algorithm>
#include <iostream>
#include <algorithm>

#define SUCCESS 1
#define ERROR 0

using namespace std;

namespace BSTLIB {
	template<typename nodeObject>
	class TreeNode {
	public:

		nodeObject val;
		/* nodeObject should have =,< and > overloaded */

		TreeNode *Left;
		TreeNode *Right;
		TreeNode *Parent;

		TreeNode(nodeObject inArg) :val(inArg), Left(nullptr), Right(nullptr), Parent(nullptr) {}

		friend ostream& operator<<(ostream& os, const TreeNode<nodeObject>& it) {
			os << it.val;
			return os;
		}
	};

	template<typename nodeObject>
	void displayList(vector<nodeObject>&vec) {
		//cout << "\n";
		for (nodeObject i : vec) {
			cout << i<<" ";
		}
	}

	//if given node *ptr is in a given subtree
	template<typename nodeObject>

	bool isNodeInBST(TreeNode<nodeObject> *pRoot, TreeNode<nodeObject> *pNodeToBeChecked) {
		//assert(NodeToBeChecked!=nullptr);
		//we want program to continue if by mistake NodeToBeChecked is  null 
		if (!pRoot || !pNodeToBeChecked) { return nullptr; }
		else {
			return (isNodeInBST(pRoot->Left, pNodeToBeChecked) || isNodeInBST(pRoot->Right, pNodeToBeChecked));
		}
	}

	template<typename nodeObject>
	TreeNode<nodeObject>* searchNodeByValueInBST(TreeNode<nodeObject> *pRoot, nodeObject node_value) {
		TreeNode<nodeObject>* pRet = nullptr;
		TreeNode<nodeObject> *ptr = pRoot;
		while (ptr) {
			if (ptr->val == node_value) {
				pRet = ptr;
				break;
			}
			else if (node_value> ptr->val) {
				ptr = ptr->Right;
			}
			else {
				ptr = ptr->Left;
			}
		}
		return pRet;
	}
	template<typename nodeObject>
	TreeNode<nodeObject>* generateBSTFromSortedNodesList(vector<nodeObject> &NodesList, unsigned int startIndex, unsigned int endIndex) {
		if (NodesList.size() <= 0 || endIndex < startIndex || endIndex >= NodesList.size()) {
			return nullptr;
		}
		int mid = (startIndex + endIndex) / 2;
		TreeNode<nodeObject> *pRoot = new TreeNode<nodeObject>(NodesList[mid]);

		pRoot->Left = generateBSTFromSortedNodesList(NodesList, startIndex, mid - 1);
		if (pRoot->Left) {
			pRoot->Left->Parent = pRoot;
		}

		pRoot->Right = generateBSTFromSortedNodesList(NodesList, mid + 1, endIndex);
		if (pRoot->Right) {
			pRoot->Right->Parent = pRoot;
		}
		return pRoot;
	}

	template<typename nodeObject>
	void getBSTInOrderTraversalTreeNodePtrList(TreeNode<nodeObject>* pRoot, vector<TreeNode<nodeObject>*> &retVec) {
		if (pRoot) {
			if (pRoot->Left) {
				getBSTInOrderTraversalTreeNodePtrList(pRoot->Left, retVec);
			}
			retVec.push_back(pRoot);
			if (pRoot->Right) {
				getBSTInOrderTraversalTreeNodePtrList(pRoot->Right, retVec);
			}
		}
	}

	template<typename nodeObject>
	vector<nodeObject> getBSTInOrderTraversalNodeList(TreeNode<nodeObject>* pRoot) {
		vector<nodeObject> retVect;
		vector<TreeNode<nodeObject>*> NodePtrList;
		getBSTInOrderTraversalTreeNodePtrList(pRoot, NodePtrList);
		for (TreeNode<nodeObject>* p : NodePtrList) {
			retVect.push_back(p->val);
		}
		return retVect;
	}


	template<typename nodeObject>
	void getBSTPreOrderTraversalTreeNodePtrList(TreeNode<nodeObject>* pRoot, vector<TreeNode<nodeObject>*> &retVec) {
		if (pRoot) {
			retVec.push_back(pRoot);
			if (pRoot->Left) {
				getBSTPreOrderTraversalTreeNodePtrList(pRoot->Left, retVec);
			}
			if (pRoot->Right) {
				getBSTPreOrderTraversalTreeNodePtrList(pRoot->Right, retVec);
			}
		}
	}

	template<typename nodeObject>
	vector<nodeObject> getBSTPreOrderTraversalNodeList(TreeNode<nodeObject>* pRoot) {
		vector<nodeObject> retVect;
		vector<TreeNode<nodeObject>*> NodePtrList;
		getBSTPreOrderTraversalTreeNodePtrList(pRoot, NodePtrList);
		for (TreeNode<nodeObject>* p : NodePtrList) {
			retVect.push_back(p->val);
		}
		return retVect;
	}

	template<typename nodeObject>
	void getBSTPostOrderTraversalTreeNodePtrList(TreeNode<nodeObject>* pRoot, vector<TreeNode<nodeObject>*> &retVec) {
		if (pRoot) {
			if (pRoot->Left) {
				getBSTPostOrderTraversalTreeNodePtrList(pRoot->Left, retVec);
			}
			if (pRoot->Right) {
				getBSTPostOrderTraversalTreeNodePtrList(pRoot->Right, retVec);
			}
			retVec.push_back(pRoot);
		}
	}

	template<typename nodeObject>
	vector<nodeObject> getBSTPostOrderTraversalNodeList(TreeNode<nodeObject>* pRoot) {
		vector<nodeObject> retVect;
		vector<TreeNode<nodeObject>*> NodePtrList;
		getBSTPostOrderTraversalTreeNodePtrList(pRoot, NodePtrList);
		for (TreeNode<nodeObject>* p : NodePtrList) {
			retVect.push_back(p->val);
		}
		return retVect;
	}

	template<typename nodeObject>
	TreeNode<nodeObject>* getPtrToPrevNodeInSortedOrderInBST(TreeNode<nodeObject> *pNodePtr) {
		if (!pNodePtr) { return nullptr; }
		if (pNodePtr->Left) {
			return pNodePtr->Left;
		}
		TreeNode<nodeObject> *pTempPtr = pNodePtr;
		while (pTempPtr->Parent && pTempPtr == pTempPtr->Parent->Left) {
			pTempPtr = pTempPtr->Parent;
		}
		return pTempPtr->Parent;
	}

	template<typename nodeObject>
	TreeNode<nodeObject>* getPtrToNextNodeInSortedOrderInBST(TreeNode<nodeObject> *pNodePtr) {
		if (!pNodePtr) { return nullptr; }
		if (pNodePtr->Right) {
			return pNodePtr->Right;
		}
		TreeNode<nodeObject> *pTempPtr = pNodePtr;
		while (pTempPtr->Parent && pTempPtr == pTempPtr->Parent->Right) {
			pTempPtr = pTempPtr->Parent;
		}
		return pTempPtr->Parent;
	}

	template <typename nodeObject>
	TreeNode<nodeObject>* getPtrToLargestNodeInBST(TreeNode<nodeObject> *pRoot) {
		TreeNode<nodeObject> *pTempPtr = nullptr;
		if (pRoot) {
			pTempPtr = pRoot;
			while (pTempPtr->Right) {
				pTempPtr = pTempPtr->Right;
			}
		}
		return pTempPtr;
	}

	template <typename nodeObject>
	TreeNode<nodeObject>* getPtrToSmallestNodeInBST(TreeNode<nodeObject> *pRoot) {
		TreeNode<nodeObject> *pTempPtr = nullptr;
		if (pRoot) {
			pTempPtr = pRoot;
			while (pTempPtr->Left) {
				pTempPtr = pTempPtr->Left;
			}
		}
		return pTempPtr;
	}

	template <typename nodeObject>
	TreeNode<nodeObject>* addExistingIsolatedTreeNodeToBST(TreeNode<nodeObject> *&pRoot, TreeNode<nodeObject> *pNodeToAdd) {
		if (!pNodeToAdd) { return nullptr; }
		if (!pRoot) {
			pRoot = pNodeToAdd; // it creates new tree and assign the pRoot to itself (thas why we send root ptr by reference
			return pNodeToAdd;
		}
		TreeNode<nodeObject> *pTempPtr = pRoot;
		while (true) {
			if (pNodeToAdd->val < pTempPtr->val || pNodeToAdd->val == pTempPtr->val) {
				if (pTempPtr->Left) {
					pTempPtr = pTempPtr->Left; continue;
				}
				else {
					pTempPtr->Left = pNodeToAdd;
					pNodeToAdd->Parent = pTempPtr;
					return pNodeToAdd;
				}
			}
			else {
				if (pTempPtr->Right) {
					pTempPtr = pTempPtr->Right; continue;
				}
				else {
					pTempPtr->Right = pNodeToAdd;
					pNodeToAdd->Parent = pTempPtr;
					return pNodeToAdd;
				}
			}
		}
	}

	template <typename nodeObject>
	TreeNode<nodeObject>* addNewNodeByValueInBST(TreeNode<nodeObject> *&pRoot, nodeObject node_value) {
		TreeNode<nodeObject> *pNodetoAdd = new TreeNode<nodeObject>(node_value);
		return addExistingIsolatedTreeNodeToBST(pRoot, pNodetoAdd);
	}

	template <typename nodeObject>
	int deleteNodeByAddressInBST(TreeNode<nodeObject> *pRoot, TreeNode<nodeObject> *pNodeToBeDeleted) {
		if (!pNodeToBeDeleted) {
			return ERROR;
		}
		if (!pNodeToBeDeleted->Left && !pNodeToBeDeleted->Right) {
			delete(pNodeToBeDeleted);
			pNodeToBeDeleted = nullptr;
			return SUCCESS;
		}
		else if (pNodeToBeDeleted->Left) {
			TreeNode<nodeObject> *pSuccessorNode = getPtrToLargestNodeInBST(pNodeToBeDeleted->Left);
			if (pSuccessorNode == pNodeToBeDeleted->Left) {
				pSuccessorNode->Parent->Left = pSuccessorNode->Left;
			}
			else {
				pSuccessorNode->Parent->Right = pSuccessorNode->Left;
			}
			if (pSuccessorNode->Left) { pSuccessorNode->Left->Parent = pSuccessorNode->Parent; }
			pNodeToBeDeleted->val = pSuccessorNode->val;
			delete(pSuccessorNode);
			return SUCCESS;
		}
		else /*if (pNodeToBeDeleted->Right)*/ {
			TreeNode<nodeObject> *pSuccessorNode = getPtrToSmallestNodeInBST(pNodeToBeDeleted->Right);
			if (pSuccessorNode == pNodeToBeDeleted->Right) {
				pSuccessorNode->Parent->Right = pSuccessorNode->Right;
			}
			else {
				pSuccessorNode->Parent->Left = pSuccessorNode->Right;
			}
			if (pSuccessorNode->Right) { pSuccessorNode->Right->Parent = pSuccessorNode->Parent; }
			pNodeToBeDeleted->val = pSuccessorNode->val;
			delete(pSuccessorNode);
			return SUCCESS;
		}
	}

	template <typename nodeObject>
	int deleteNodeByValueInBST(TreeNode<nodeObject> *pRoot, nodeObject node_value) {
		TreeNode<nodeObject> *pNodeToBeDeleted = searchNodeByValueInBST(pRoot, node_value);
		return deleteNodeByAddressInBST(pRoot, pNodeToBeDeleted);
	}
}
#endif 

