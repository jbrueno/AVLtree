/*
 * NodeL.cpp
 *
 *  Created on: Apr 20, 2019
 *      Author: joebrueno
 */

#include "NodeL.hpp"

NodeL::NodeL(){
	word = "";
	next = NULL;
	wscore = 0;
}

NodeL::NodeL(string x){
	word = x;
	wscore = 0;
	next = NULL;
}

NodeL::~NodeL(){

}
