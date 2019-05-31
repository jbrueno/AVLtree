/*
 * Joe Brueno
 * April 12, 2019
 * Daniel Gaston
 *
 */

#include "BSTY.hpp"
#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

BSTY::BSTY() {
	root = NULL;
}

// insert a new node with data x (a string) into the
// binary search tree
bool BSTY::insertit(string x) {
	cout << "inserting " << x << endl;

	if (root == NULL) { // if the root is null, insert the new node as the root
		root = new NodeT(x);
		return true;
	}

	NodeT *current = NULL;
	NodeT *next = root;

	while (next != NULL) { // finds the node that will be the parent of the inserted node
		current = next;
		if (x < current->data) {
			next = current->left;
		} else
			next = current->right;
	} // while

	if (x < current->data) { // if the new node is less than the parent set it as the left child
		NodeT *newNode = new NodeT(x);
		current->left = newNode;
		newNode->parent = current;
		adjustHeights(newNode);

		NodeT *tmp = newNode;

		while (tmp != NULL) {
			if(findBalance(tmp) > 1 || findBalance(tmp) < -1)
			rotateTree(tmp);
			tmp = tmp->parent;
		}

		return true;
	} else if (x > current->data) { // if the new node is greater than the parent set it as the right child
		NodeT *newNode = new NodeT(x);
		current->right = newNode;
		newNode->parent = current;
		adjustHeights(newNode);

		NodeT *tmp = newNode;

		while (tmp != NULL) {
			if(findBalance(tmp) > 1 || findBalance(tmp) < -1)
			rotateTree(tmp);
			tmp = tmp->parent;
		}
		return true;
	} // else if

	return false; // if the node is already in the tree, return false
}

// the adjustHeights method updates the heights of every ancestor of the node n.
void BSTY::adjustHeights(NodeT *n) {

	if (n == NULL)                                   // if n is null, do nothing
		return;
	if (n->left != NULL && n->right == NULL) { // if n has a left child and no right child, its height is its left childs height + 1
		n->height = n->left->height + 1;
	} else if (n->right != NULL && n->left == NULL) { // if n has a right child and no left child, its height is its right childs height + 1
		n->height = n->right->height + 1;
	} else if (n->left == NULL && n->right == NULL) { // n has no children(leaf), its height is 1
		n->height = 1;
	} else if (n->left != NULL && n->right != NULL) { // n has two children, set its height the the height of the child with the greatest height + 1
		if (n->right->height > n->left->height) { // right child height is greater than left
			n->height = n->right->height + 1;
		} else {                  // left child height is greater than right
			n->height = n->left->height + 1;
		} // else
	} // else if
	adjustHeights(n->parent);
} // adjustHeights

void BSTY::printTreeIO() {
	if (root == NULL) {
		cout << "Empty Tree" << endl;
	} else {
		printTreeIO(root);
	}
}

// Print the tree in order (left child, then parent, then right child).
void BSTY::printTreeIO(NodeT *n) {
	if (n == NULL) { // is n is null, do nothing
		return;
	} else {
		printTreeIO(n->left); // print left-most nodes
		n->printNode(); // print root node
		printTreeIO(n->right); // print right-most nodes
	}
}

void BSTY::printTreePre() {
	if (root == NULL) {
		cout << "Empty Tree" << endl;
	} else {
		printTreePre(root);
	}
}

// Prints the tree using pre-order traversal (parent, then left child, then right
void BSTY::printTreePre(NodeT *n) {
	if (n == NULL) {
		return;
	} else {
		n->printNode(); // print root node
		printTreePre(n->left); // print left-most nodes
		printTreePre(n->right); // print right-most nodes
	}
}

void BSTY::printTreePost() {
	if (root == NULL) {
		cout << "Empty Tree" << endl;
	} else {
		printTreePost(root);
		cout << endl;
	}
}

// Prints the tree using pre-order traversal (left child, then right, then parent)
void BSTY::printTreePost(NodeT *n) {
	if (n == NULL) {
		return;
	} else {
		printTreePost(n->left); // print left-most nodes
		printTreePost(n->right); // print right-most nodes
		n->printNode(); // print root node
	}
}
void BSTY::myPrint() {
	if (root == NULL) {
		cout << "Empty Tree" << endl;
	} else {
		myPrint(root);
		cout << endl;
	}
}
void BSTY::myPrint(NodeT *n) {
	if (n == NULL) {
		return;
	} else {
		myPrint(n->left);
		cout << n->data.length() - 1;
		if (mine) {
			cout << ".";
			mine = false;
		}
		myPrint(n->right);
	}
}

// the find method takes as input a string, and finds whether that string is already
// in the tree or not
NodeT *BSTY::find(string x) {
	if (root == NULL || root->data == x) { // the root is null or the root is what you are trying to find
		root->printNode();
		return root;
	}
	NodeT *current = root;
	NodeT *next = root;
	int track = 0; // keeps track of the amount of comparisons it takes to find the node

	while (next != NULL) { // finds the value of x in the tree and sets that node to current
		current = next;
		if (x < current->data) { // if x is less than current, next is currents left
			next = current->left;
			track++;
		} else if (x > current->data) { // if x > current, next is currents right
			next = current->right;
			track++;
		} else { // else exit loop
			break;
		} // else
	} // while
	if (x == current->data) { // if current is equal to x, print and return current
		current->printNode();
		return current;
	} else { // current isnt equal to x, so the node is not in the tree
		cout << x << " can't be found" << endl;
		return NULL;
	} // else
} // find

void BSTY::rotateTree(NodeT *n) {

	int nBalance = findBalance(n);
	int xBalance = findBalance(n->left);
	int yBalance = findBalance(n->right);

	if (nBalance > 1 && xBalance >= 0) {
		cout << n->data << " must rotate right (" << nBalance << ")" << endl;
		root = rotateRight(n);
	} else if (nBalance > 1 && xBalance < 0) {
		cout << n->data << " must rotate right (" << nBalance << ")" << endl;
		cout << n->left->data << " must rotate left (child)" << endl;
		root = rotateLeft(n->left);
		root = rotateRight(n);
	}
	if (nBalance < -1 && yBalance < 0) {
		cout << n->data << " must rotate left (" << nBalance << ")" << endl;
		root = rotateLeft(n);
	} else if (nBalance < -1 && yBalance >= 0) {
		cout << n->data << " must rotate left (" << nBalance << ")" << endl;
		cout << n->right->data << " must rotate right (child)" << endl;
		root = rotateRight(n->right);
		root = rotateLeft(n);
	}
}

NodeT * BSTY::rotateRight(NodeT * n) {

	NodeT *x = n->left;
	NodeT *y = x->right;
	if (n == root) {
		if (y == NULL) {
			x->right = n;
			x->parent = n->parent;
			n->parent = x;
			n->left = NULL;
			fixRotatedHeights(n, x);
			return x;
		} else {
			x->right = n;
			n->left = y;
			x->parent = n->parent;
			y->parent = n;
			n->parent = x;
			fixRotatedHeights(n, x);
			return x;
		}
	}

	if (n == n->parent->right && y == NULL) {
		x->right = n;
		x->parent = n->parent;
		n->parent->right = x;
		n->left = NULL;
		n->parent = x;
		fixRotatedHeights(n, x);
		fixRotatedParents(x->parent);
		return root;
	} else if (n == n->parent->right && y != NULL) {
		x->right = n;
		n->left = y;
		x->parent = n->parent;
		n->parent->right = x;
		y->parent = n;
		n->parent = x;
		fixRotatedHeights(n, x);
		fixRotatedParents(x->parent);
		return root;
	} else if (n == n->parent->left && y == NULL) {
		x->right = n;
		x->parent = n->parent;
		n->parent->left = x;
		n->left = NULL;
		n->parent = x;
		fixRotatedHeights(n, x);
		fixRotatedParents(x->parent);
		return root;
	} else if (n == n->parent->left && y != NULL) {
		x->right = n;
		n->left = y;
		x->parent = n->parent;
		n->parent->left = x;
		y->parent = n;
		n->parent = x;
		fixRotatedHeights(n, x);
		fixRotatedParents(x->parent);
		return root;
	} else {
		return root;
	}
}

NodeT * BSTY::rotateLeft(NodeT * n) {

	NodeT *x = n->right;
	NodeT *y = x->left;

	if (n == root) {
		if (y == NULL) {
			x->left = n;
			x->parent = n->parent;
			n->parent = x;
			n->right = NULL;
			fixRotatedHeights(n, x);
			return x;
		} else {
			x->left = n;
			n->right = y;
			x->parent = n->parent;
			y->parent = n;
			n->parent = x;
			fixRotatedHeights(n, x);
			return x;
		}
	}

	if (n == n->parent->right && y == NULL) {
		x->left = n;
		x->parent = n->parent;
		n->parent->right = x;
		n->right = NULL;
		n->parent = x;
		fixRotatedHeights(n, x);
		fixRotatedParents(x->parent);
		return root;
	} else if (n == n->parent->right && y != NULL) {
		x->left = n;
		n->right = y;
		x->parent = n->parent;
		n->parent->right = x;
		y->parent = n;
		n->parent = x;
		fixRotatedHeights(n, x);
		fixRotatedParents(x->parent);
		return root;
	} else if (n == n->parent->left && y == NULL) {
		x->parent = n->parent;
		x->left = n;
		n->right = NULL;
		n->parent->left = x;
		n->parent = x;
		fixRotatedHeights(n, x);
		fixRotatedParents(x->parent);
		return root;
	} else if (n == n->parent->left && y != NULL) {
		x->left = n;
		n->right = y;
		x->parent = n->parent;
		n->parent->left = x;
		y->parent = n;
		n->parent = x;
		fixRotatedHeights(n, x);
		fixRotatedParents(x->parent);
		return root;
	} else {
		return root;
	}
}

int BSTY::findBalance(NodeT *n) {

	if (n == NULL) {
		return 0;
	} else if (n->left == NULL && n->right != NULL) {
		return 0 - n->right->height;
	} else if (n->right == NULL && n->left != NULL) {
		return n->left->height - 0;
	} else if (n->left == NULL && n->right == NULL) {
		return 0;
	} else {
		return n->left->height - n->right->height;
	}
}

void BSTY::fixRotatedHeights(NodeT *n, NodeT *x) {
	if(n->left == NULL && n->right == NULL){
		n->height = 1;
	} else if(n->left != NULL && n->right == NULL){
		n->height = n->left->height + 1;
	} else if(n->right != NULL && n->left == NULL){
		n->height = n->right->height + 1;
	} else {
		if(n->right->height > n->left->height){
			n->height = n->right->height + 1;
		} else {
			n->height = n->left->height + 1;
		}
	}
	if(x->left == NULL && x->right == NULL){
			x->height = 1;
		} else if(x->left != NULL && x->right == NULL){
			x->height = x->left->height + 1;
		} else if(x->right != NULL && x->left == NULL){
			x->height = x->right->height + 1;
		} else {
			if(x->right->height > x->left->height){
				x->height = x->right->height + 1;
			} else {
				x->height = x->left->height + 1;
			}
		}
}

void BSTY::fixRotatedParents(NodeT *n) {
	if (n == NULL) {
		return;
	}

	if(n->left == NULL && n->right == NULL){
		n->height = 1;
	} else if(n->left != NULL && n->right == NULL){
		n->height = n->left->height + 1;
	} else if(n->right != NULL && n->left == NULL){
		n->height = n->right->height + 1;
	} else {
		if(n->right->height > n->left->height){
			n->height = n->right->height + 1;
		} else {
			n->height = n->left->height + 1;
		}
	}
	fixRotatedParents(n->parent);
}

/* remove(): takes as input a string, uses the find method to find the node in the tree that
 /* holds that string, and then calls replace1, replace2, or replace3 depending on what type
 /* of replacing should be done.  It adjusts the heights, deletes the node, and returns
 /* true if the removal was successful.
 */
bool BSTY::remove(string s) {
	NodeT *tmp = find(s);
	if (tmp == NULL) { // if the node is not in the tree, return false
		return false;
	} else if (tmp->left == NULL && tmp->right == NULL) { // if tmp has no children, execute remove1
		remove1(tmp);
		return true;
	} else if ((tmp->left != NULL && tmp->right == NULL)
			|| (tmp->right != NULL && tmp->left == NULL)) { // if tmp has once child, execute remove 2
		remove2(tmp);
		return true;
	} else { // if tmp has two children, execute remove3
		remove3(tmp);
		return true;
	} // else

} // remove

// remove1(): called when the node to be removed has no children. Takes as input the
// node to be removed
void BSTY::remove1(NodeT *n) {
	NodeT *fixHeight = n->parent;
	if (n == root) { // if n is the root, delete the root
		delete root;
	} else if (n->parent->left == n) { // if n is its parents left node
		n->parent->left = NULL;
		delete n;
		adjustHeights(fixHeight);
	} else { // n is its parents right node
		n->parent->right = NULL;
		delete n;
		adjustHeights(fixHeight);
	} // else
} // remove1

/* remove2(): called when the node to be removed has 1 child only.  Takes as input
 * the node to be removed and bypasses it by making the parent point to the node's
 * one child, and makes the node's one child point to the node's parent.
 */
void BSTY::remove2(NodeT *n) {
	if (n == root && n->left != NULL) { // n is the root and it has a left child
		root->data = n->left->data;
		n->left = NULL;
		delete n->left;
	} // if
	if (n == root && n->right != NULL) { // n is the root and has a right child
		root->data = n->right->data;
		n->right = NULL;
		delete n->right;
	} // if
	if (n->parent->left == n) { // n is its parents left node
		if (n->left != NULL) { // n has a left child
			n->parent->left = n->left;
			n->left->parent = n->parent;
			adjustHeights(n->left);
			delete n;
		} else { // n has a right child
			n->parent->left = n->right;
			n->right->parent = n->parent;
			adjustHeights(n->right);
			delete n;
		} // else
	} // if
	if (n->parent->right == n) { // n is its parents right node
		if (n->left != NULL) { // n has a left child
			n->parent->right = n->left;
			n->left->parent = n->parent;
			adjustHeights(n->left);
			delete n;
		} else { // n has a right child
			n->parent->right = n->right;
			n->right->parent = n->parent;
			adjustHeights(n->right);
			delete n;
		} // else
	} // if
} // remove2

//remove3(): called when the node to be removed has 2 children.  Takes as input the
// node to be removed.
void BSTY::remove3(NodeT *n) {

	NodeT *min = findMin(n); // min is the n's subtree's left-most node
	NodeT *fixParent = min->parent;
	NodeT *fixChild = min->right;

	if (root == n) {  // n is the root
		if (min->parent == n) { // mins parent is n
			n->data = min->data; // copy mins data to n
			n = min; // n's address is min's address
			min->parent->right = NULL; // mins parents right is null
			delete n;
			adjustHeights(min);
		} else if (min->right == NULL) { // mins right is null
			n->data = min->data; // copy data
			n = min; // n address = min address
			min->parent->left = NULL; // mins parents left is null
			delete n;
			adjustHeights(fixParent);
		} else if (min->right != NULL) { // min has a right child
			min->parent->left = min->right; // mins parents left is mins right
			min->right->parent = min->parent; // min rights parent is mins parent
			n->data = min->data; // copy data
			n = min; // n address = min address
			delete n;
			adjustHeights(fixChild);
		} // else if
	} // if

	if (n == n->parent->right && min->parent == n) { // n is n's parents right & min is n's child
		min->left = n->left;
		min->left->parent = min;
		min->parent = n->parent;
		min->parent->right = min;
		delete n;
		adjustHeights(min);
	} else if (n == n->parent->left && min->parent == n) { // n is n's parents left & min is n's child
		min->left = n->left;
		min->left->parent = min;
		min->parent = n->parent;
		min->parent->left = min;
		delete n;
		adjustHeights(min);
	} // else if

	if (n == n->parent->left && min->right == NULL) { // n is n's parents left and min has no children
		min->parent->left = min->left;
		min->left = n->left;
		min->left->parent = min;
		min->right = n->right;
		min->right->parent = min;
		min->parent = n->parent;
		min->parent->left = min;
		delete n;
		adjustHeights(fixParent);
	} else if (n == n->parent->left && min->right != NULL) { // n is n's parents left and min has a child
		min->right->parent = min->parent;
		min->parent->left = min->right;
		min->left = n->left;
		min->left->parent = min;
		min->right = n->right;
		min->right->parent = min;
		min->parent = n->parent;
		min->parent->left = min;
		delete n;
		adjustHeights(fixChild);
	} else if (n == n->parent->right && min->right == NULL) { // n is n's parents right and min has no children
		min->parent->left = min->left;
		min->left = n->left;
		min->left->parent = min;
		min->right = n->right;
		min->right->parent = min;
		min->parent = n->parent;
		min->parent->right = min;
		delete n;
		adjustHeights(fixParent);
	} else if (n == n->parent->right && min->right != NULL) { // n is n's parents right and min has a child
		min->right->parent = min->parent;
		min->parent->left = min->right;
		min->left = n->left;
		min->left->parent = min;
		min->right = n->right;
		min->right->parent = min;
		min->parent = n->parent;
		min->parent->right = min;
		delete n;
		adjustHeights(fixChild);
	} // else if
}

/* findMin(): takes as input a node, and finds the left-most descendant of its
 /* right child.  The left-most descendent is returned.
 */
NodeT * BSTY::findMin(NodeT * n) {
	NodeT *replace;
	NodeT *temp = n->right; // temp is the 'root' of n's right subtree
	while (temp != NULL) { // while temp still has a left, replace is = temp's left
		replace = temp;
		temp = temp->left;
	}
	return replace; // return leftmost node of n's right subtree
}

void BSTY::myPrintEC() {
	if (root == NULL) {
		cout << "Empty Tree" << endl;
	} else {
		myPrintEC(root);
		cout << endl;
	}
}
void BSTY::myPrintEC(NodeT *n) {
	if (n == NULL) {
		return;
	} else {
		myPrintEC(n->left);
		cout << alpha[n->data.length() - 2];
		myPrintEC(n->right);
	}
}
