/*
 * Joe Brueno
 * April 12, 2019
 * Daniel Gaston
 *
 */

#ifndef NODET_HPP_
#define NODET_HPP_

#include <string>
using namespace std;

class NodeT {
	friend class BSTY;

public:
	string data;
	int height;
	NodeT *left;
	NodeT *right;
	NodeT *parent;

	NodeT(string x);
	~NodeT();
	void printNode();
};



#endif /* NODET_HPP_ */
