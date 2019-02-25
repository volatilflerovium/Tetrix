/*********************************************************************
* Tetrix:board                                                             *
*                                                                    *
* Version: 1.0                                                       *
* Date:    02-25-2018                                                *
* Author:  Dan Machado                                               *                                         *
**********************************************************************/
#ifndef BOARD_H
#define BOARD_H

#include<SFML/Graphics.hpp>
#include "helper.h"
#include "base.h"
#include "node.h"

class Board : public Base
{
	private:
		int counter=0;
		Node* head=NULL;
		void insertNode(Node* node);

		int width;
		int height;		
		Node* tail=NULL;
		sf::Color bColor;
		int* rows=NULL;

	public:
		~Board();
		Board(int M, int N);

		template<typename Function>
		void looping(Function func);

		template<typename Function>
		void accessPoint(Function func);

		int getWidth() const;
		int getHeight() const;
		Node* getNode(int m, int n) const;
};


template<typename Function>
void Board::looping(Function func){
	Node* tmp1=tail;
	Node* tmp2=tail->getAddress('t');
	int i=0, j=0;
	while(tmp1!=NULL){
		func(i, j, tmp1);
		tmp1=tmp1->getAddress('r');
		i++;
		if(!tmp1){
			if(!tmp2){
				break;		
			}
			i=0;
			j++;
			tmp1=tmp2;
			tmp2=tmp2->getAddress('t');
		}
	}
}

template<typename Function>
void Board::accessPoint(Function func){
	func(rows, this, bColor);
}

inline int Board::getWidth() const {
	return width;
}

inline int Board::getHeight() const {
	return height;
}


#endif