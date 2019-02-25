/*********************************************************************
* Tetrix: manager                                                           *
*                                                                    *
* Version: 1.0                                                       *
* Date:    02-25-2018                                                *
* Author:  Dan Machado                                               *                                         *
**********************************************************************/
#include<map>
#include<iostream>
#include<SFML/Graphics.hpp>

#include "helper.h"
#include "node.h"
#include "board.h"
#include "tetromino.h"
#include "manager.h"

std::map<char, MkTetroid> Manager::pieces;
std::vector<char> Manager::shapes;

void Manager::registerShape(char c, MkTetroid mk){
	std::map<char, MkTetroid>::iterator pos=pieces.find(c);
	if(pos==pieces.end()){
		shapes.push_back(c);
		pieces[c]=mk;
	}
}

Tetromino* Manager::mkTetromino(char c){
	std::map<char, MkTetroid>::iterator pos=pieces.find(c);
	if(pos!=pieces.end()){
		return pieces[c]();
	}
}


Manager::~Manager(){
	if(tetroid){
		delete tetroid;
	}
}

Manager* Manager::instance=NULL;

Manager* Manager::getInstance(){
	return instance;	
}

void Manager::init(int* _rows, Board* G, sf::Color bcolor){
	instance=new Manager(_rows, G, bcolor);
	static Supervisor Sp(instance);
}

Manager::Manager(int* _rows, Board* G, sf::Color color)
	:rows(_rows), board(G), Bcolor(color){}

Tetromino* Manager::getTetroid(){
	if(!tetroid){
		mkTetroid();
	}
	return tetroid;
}


void Manager::mkTetroid(){
	if(tetroid){
		delete tetroid;
		tetroid=NULL;
	}
	
	if(!tetroid){
		tetroid=mkTetromino(shapes[rand()%shapes.size()]);
	}
}

void Manager::update(bool a){
	if(a){
		int t=0;
		int mr=0;
		Point position;
		for(int i=0; i<4; i++){
			position=tetroid->getPosition(i);
			if(rows[position.y]==board->getWidth()){
				rows[position.y]=0;
				resetRow(position.y);
				t++;
				if(position.y>mr){
					mr=position.y;
				}
			}
		}

		if(t){
			mr++;
			shift(mr, t);	
		}
		
		mkTetroid();
	}
}

void Manager::resetRow(int r){
	sf::Color bcolor(Bcolor);
	Node* tmp=board->getNode(0, r);
	while(tmp){
		tmp->processData([&bcolor](sf::RectangleShape& rect, bool& active)->void{
			active=false;
			rect.setFillColor(bcolor);	
		});
		tmp=tmp->getAddress('r');
	}	
}

void Manager::shift(int mr, int t){
	sf::Color bcolor=Bcolor;
	sf::Color tcolor=tetroid->getColor();
	for(int c=0; c<board->getWidth(); c++){
		Node* tmp=board->getNode(c, mr);
		Node* tmp2=board->getNode(c, mr-t);
		while(tmp){
			if(tmp->isActive()){
				tmp->processData([&bcolor, &tcolor](sf::RectangleShape& rect, bool& active)->void{
					active=false;
					tcolor=rect.getFillColor();	
					rect.setFillColor(bcolor);	
				});
				tmp2->processData([&tcolor](sf::RectangleShape& rect, bool& active)->void{
					active=true;
					rect.setFillColor(tcolor);	
				});
			}
			tmp=tmp->getAddress('t');
			tmp2=tmp2->getAddress('t');
		}
	}
	for(int i=mr-t; i<board->getHeight()-t; i++){
		rows[i]=rows[i+t];
	}
	for(int i=board->getHeight()-t; i<board->getHeight(); i++){
		rows[i]=0;
	}
}
