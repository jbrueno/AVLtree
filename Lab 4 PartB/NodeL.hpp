/*
 * NodeL.hpp
 *
 *  Created on: Apr 20, 2019
 *      Author: joebrueno
 */

#ifndef NODEL_HPP_
#define NODEL_HPP_
#include <iostream>
using namespace std;

class NodeL {

	friend class LL;
	//friend class Game;

public:
	string word;
	int wscore;
	NodeL *next;
	NodeL();
	NodeL(string word);
	~NodeL();
};

#endif /* NODEL_HPP_ */
