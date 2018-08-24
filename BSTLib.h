// BSTLib: implementation of Simple Binary Search Tree (with parent pointer)
// Hitender Prakash

#ifndef _BST_H
#define _BST_H

#include <vector>
#include <algorithm>
#include <iostream>
#include <algorithm>
#include <string>
#include <iomanip>
#include <unordered_map>
#include <utility>
#include <cmath>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#include <gdiplus.h>
using namespace Gdiplus;
#endif


#define PI 3.14

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
			cout << i << " ";
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

	template <typename nodeObject>
	int getMaxDepthOfBST(TreeNode<nodeObject> *pRoot) {
		if (!pRoot) {
			return 0;
		}
		return max(getMaxDepthOfBST(pRoot->Left), getMaxDepthOfBST(pRoot->Right)) + 1;
	}


	class TwoDCoord {
	public:
		int X;
		int Y;
		TwoDCoord(int x, int y):X(x),Y(y){}
	};

	//conditionally compiled=====================
#ifdef _WIN32
	int drawCircleGDI(TwoDCoord cord, int radius, HWND myconsole, HDC mydc, COLORREF COLOR) {
		int cx = cord.X;
		int cy = cord.Y;
		for (int x = 0; x <= radius; x++) {
			int y = (int)sqrt(radius*radius - x * x);
			SetPixel(mydc, cx + x, cy + y, COLOR);
			SetPixel(mydc, cx - x, cy + y, COLOR);
			SetPixel(mydc, cx + x, cy - y, COLOR);
			SetPixel(mydc, cx - x, cy - y, COLOR);
	}
		return SUCCESS;
	}
	int drawLineGDI(TwoDCoord cordA, TwoDCoord cordB, HWND myconsole, HDC mydc, COLORREF COLOR) {
		double x1 = cordA.X, x2 = cordB.X, y1 = cordA.Y, y2 = cordB.Y;
		double dx = x2 - x1;
		double dy = y2 - y1;

		int x, y;
		if (dx != 0) {
			for (x = (int)min(x1, x2); x <= max(x1, x2); x++) {
				y = (int)(y1 + (dy / dx)*(x - x1));
				SetPixel(mydc, x, y, COLOR);
			}
		}
		else {
			int x = (int)x1;
			for (int y = (int)min(y1, y2); y <= max(y1, y2); y++) {
				SetPixel(mydc, x, y, COLOR);
			}
		}
		return SUCCESS;
	}

	template <typename nodeObject>
	void printBSTOnConsole(TreeNode<nodeObject> *pRoot) {
		int scaleX = 20;
		int scaleY = 30;
		int radius = 10;
		unordered_map<TreeNode<nodeObject>*, pair<TreeNode<nodeObject>*, TwoDCoord>> mp;
		recordPrintableCoordinatesOfBST(pRoot, 0, 0, mp);
		CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
		HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);

		typename unordered_map<TreeNode<nodeObject>*, pair<TreeNode<nodeObject>*, TwoDCoord>>::iterator it;
		for (it = mp.begin(); it != mp.end(); it++) {

			it->second.second.Y = it->second.second.Y * scaleY + csbiInfo.dwCursorPosition.Y + radius;
			it->second.second.X = it->second.second.X * scaleX + csbiInfo.dwCursorPosition.X + radius;
		}
		HWND myconsole = GetConsoleWindow();
		HDC mydc = GetDC(myconsole);
		//COLORREF COLOR = RGB(50, 150, 245);
		cout << "\nPress Enter to see the tree:\n";
		cin.ignore();
		system("cls");

		for (it = mp.begin(); it != mp.end(); it++) {
			drawCircleGDI(it->second.second, radius, myconsole, mydc, RGB(20, 100, 250));
			auto itt = mp.find(it->second.first);
			if (itt != mp.end()) {
				drawLineGDI(it->second.second, itt->second.second, myconsole, mydc, RGB(100, 150, 200));
			}
		}
		cin.ignore();
		ReleaseDC(myconsole, mydc);
	}

#elif __linux__
	template <typename nodeObject>
	void printBSTOnConsole(TreeNode<nodeObject> *pRoot) {
		int scaleX = 2;
		int scaleY = 3;
		int radius = 1;
		unordered_map<TreeNode<nodeObject>*, pair<TreeNode<nodeObject>*, TwoDCoord>> mp;
		recordPrintableCoordinatesOfBST(pRoot, 0, 0, mp);
		int cols = mp.size();
		int rows = getMaxDepthOfBST(pRoot);
		if (rows <= 0) { return; }
		rows = rows * scaleY;//better print
		string filler(scaleX, '.');
		vector<vector<string>> Table(rows, vector<string>(cols, filler));

		typename unordered_map<TreeNode<nodeObject>*, pair<TreeNode<nodeObject>*, TwoDCoord>>::iterator it;
		for (it = mp.begin(); it != mp.end(); it++) {
			string valstring = to_string(it->first->val.value);
			Table[it->second.second.Y*scaleY][it->second.second.X] = valstring;
		}

		for (unsigned int i = 0; i < Table.size(); i++) {
			cout << "\n";
			for (unsigned int j = 0; j < Table[0].size(); j++) {
				cout << Table[i][j] << std::setw(3) << std::setfill(' ') << std::right;
			}
		}
	}

#endif
	//////////////////////////////////////

	template <typename nodeObject>
	int recordPrintableCoordinatesOfBST(TreeNode<nodeObject> *pRoot, int x, int y, unordered_map<TreeNode<nodeObject>*, pair<TreeNode<nodeObject>*, TwoDCoord>> &mp) {
		if (!pRoot) {
			return ERROR; //this is just to handle very first call if root is null, we dont call function on null node in recursin
		}
		int curX = x;
		if (pRoot->Left) {
			curX = recordPrintableCoordinatesOfBST(pRoot->Left, x, y + 1, mp) + 1;
		}

		mp.insert(std::make_pair(pRoot, std::make_pair(pRoot->Parent, TwoDCoord(curX, y))));
		if (pRoot->Right) {
			curX = recordPrintableCoordinatesOfBST(pRoot->Right, curX + 1, y + 1, mp);
		}
		return curX;
		/*
		int curX=x;
		if(!pRoot){
		return curX-1;
		}
		curX = recordPrintableCoordinatesOfBST(pRoot->Left, x, y + 1, vec) + 1;
		mp.insert(std::make_pair(pRoot, std::make_pair(pRoot->Parent, TwoDCoord(curX, y))));
		return recordPrintableCoordinatesOfBST(pRoot->Right, curX + 1, y + 1, vec) ;
		*/
	}

}
#endif 

