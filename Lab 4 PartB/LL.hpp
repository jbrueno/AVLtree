/*
 * LL.hpp
 *
 *  Created on: Apr 20, 2019
 *      Author: joebrueno
 */

#ifndef LL_HPP_
#define LL_HPP_

#include <stdlib.h>
#include <iostream>
#include "NodeL.hpp"
using namespace std;

class LL {
	friend class Game;

	NodeL *first;
	NodeL *last;
	int size;
	int score;
public:
	LL();
	~LL();
	void printList();
	void push(string w);
	void addFirst(string w);
	void getScore();

};

#endif /* LL_HPP_ */
