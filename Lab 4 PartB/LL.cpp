/*
 * Joe Brueno
 * Mar 12, 2019
 * Daniel Gaston
 *
 */

#include "LL.hpp"

LL::LL() { // default constructor
	first = NULL;
	last = NULL;
	size = 0;
	score = 0;
}

LL::~LL() {

}

void LL::printList() { // prints out the nodes of the linked list in order of first to last
	NodeL *temp = first;
	while (temp != NULL) {
		cout << temp->word << endl;
		temp = temp->next;
	} // while
	cout << endl;
}

void LL::push(string w) { // adds a node to the end of the linked list
	if (first == NULL) {
		first = new NodeL(w);
		last = first;
	}

	NodeL *temp = new NodeL(w);
	last->next = temp;
	last = temp;
	size++;
}

void LL::addFirst(string w) { // add the first node of a list, setting it to be the first and last node
	size++;
	first = new NodeL(w);
	last = first;
}

void LL::getScore() { // sets the linked list score to the value of all the word scores added together
	NodeL *temp = first;
	while (temp != NULL) {
		score += temp->wscore;
		temp = temp->next;
	}
}

