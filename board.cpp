/*********************************************************************
* Tetrix:board                                                             *
*                                                                    *
* Version: 1.0                                                       *
* Date:    02-25-2018                                                *
* Author:  Dan Machado                                               *                                         *
**********************************************************************/
#include<SFML/Graphics.hpp>
#include "helper.h"
#include "base.h"
#include "node.h"
#include "board.h"

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



