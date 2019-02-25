/*********************************************************************
* Tetrix: node                                                             *
*                                                                    *
* Version: 1.0                                                       *
* Date:    02-25-2018                                                *
* Author:  Dan Machado                                               *                                         *
**********************************************************************/
#include "node.h"



void Node::setAddress(Node* c, char p){
	if(p=='t'){
		top=c;	
	}
	else if(p=='r'){
		right=c;
	}
	else if(p=='b'){
		bottom=c;
	}
	else if(p=='l'){
		left=c;
	}
}


Node* Node::getAddress(char c) const{
	if(c=='t'){
		return top;	
	}
	else if(c=='r'){
		return right;
	}
	else if(c=='b'){
		return bottom;
	}
	else{// if(c=='l'){
		return left;
	}
}
