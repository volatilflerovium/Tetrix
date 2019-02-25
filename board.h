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


Board::~Board(){
	Node* tmp1;
	Node* tmp2=tail->getAddress('t');
	while(tail!=NULL){
		tmp1=tail->getAddress('r');
		delete tail;
		tail=tmp1;
		if(!tail){
			tail=tmp2;
			if(tmp2){
				tmp2=tail->getAddress('t');
			}
		}
	}
}

Board::Board(int M, int N)
		:width(M), height(N), bColor(55,55,55){//140, 8, 90){

	rows=new int[N];
	for(int i=0; i<N; i++){
		rows[i]=0;
	}

	/*{**********************************************/
	for(int k=0; k<M*N; k++){
		insertNode(new Node(SD-0.5, bColor));	
	}
	ReferenceFrame RFD=*RF;
	looping([&RFD](int w, int h, Node* node)->void{
		float x=RFD.trans_x(w*SD);
		float y=RFD.trans_y(h*SD);
		
		node->processData([&x, &y](sf::RectangleShape& rect, bool& active)->void{
			rect.setPosition(x, y);
		});
	});
	/*}**********************************************/
}

void Board::insertNode(Node* node){
	if(counter>width*height){
		return;
	}

	if(head==NULL){
		tail=node;
	}
	else{
		int j=counter/width;
		int i=counter-j*width;
		Node* tmp;

		if(0<i){
			head->setAddress(node, 'r');
			node->setAddress(head, 'l');
			if(j>0){
				tmp=head->getAddress('b');
				tmp=tmp->getAddress('r');
				node->setAddress(tmp, 'b');
				tmp->setAddress(node, 't');
			}
		}
		else{
			tmp=tail;
			while(tmp->getAddress('t')!=NULL){
				tmp=tmp->getAddress('t');
			}
			
			tmp->setAddress(node, 't');
			node->setAddress(tmp, 'b');
		}
	}
	counter++;
	head=node;	
}

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



Node* Board::getNode(int m, int n) const{
	char d='t';
	Node* tmp=tail;
	for(int j=0; j<n; j++){
		if(!tmp->getAddress(d)){
			break;
		}
		tmp=tmp->getAddress(d);
	}
	d='r';
	if(m<0){
		m*=-1;
		d='l';
	}

	for(int i=0; i<m; i++){
		if(!tmp->getAddress(d)){
			break;
		}
		tmp=tmp->getAddress(d);
	}

	return tmp;
}



#endif