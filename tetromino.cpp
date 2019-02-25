#include<iostream>

#include<SFML/Graphics.hpp>

#include "helper.h"
#include "node.h"
#include "board.h"
#include "tetromino.h"

using namespace std;

void Tetromino::init(int* _rows, Board* G, sf::Color bcolor){
	if(!isSet){
		board=G;
		rows=_rows;
		Bcolor=bcolor;
		Dir['r']=Point(1,0);
		Dir['b']=Point(0,-1);
		Dir['l']=Point(-1,0);
		Dir['t']=Point(0,1);		
		isSet=true;
	}
}

Tetromino::Tetromino(std::initializer_list<Point> l, sf::Color color)
	:Tcolor(color){
	int i=0;
	for(Point P : l){
		positions[i]=P;
		tetroid[i]=board->getNode(P.x, P.y);
		tetroid[i]->processData([&color](sf::RectangleShape& rect, bool& active)->void{
			rect.setFillColor(color);
		});
		i++;
	}
}

bool Tetromino::canMove(char d){
	bool a=true;
	Node* tmp=NULL;
	for(int i=0; i<4; i++){
		tmp=tetroid[i]->getAddress(d);
		if(tmp){
			a=a && !tmp->isActive();
		}
		else{
			a=false;
			break;
		}
	}
	return a;
}

bool Tetromino::move(char d){
	if(canMove(d)){
		sf::Color tcolor=Tcolor;
		sf::Color bcolor=Bcolor;
		for(int i=0; i<4; i++){
			tetroid[i]->processData([&bcolor](sf::RectangleShape& rect, bool& active)->void{
				rect.setFillColor(bcolor);
			});
			positions[i]+=Dir[d];
			tetroid[i]=tetroid[i]->getAddress(d);
		}
		for(int i=0; i<4; i++){
			tetroid[i]->processData([&tcolor](sf::RectangleShape& rect, bool& active)->void{
				rect.setFillColor(tcolor);
			});
		}
		return false;
	}
	else if(d=='b'){		
		for(int i=0; i<4; i++){
			tetroid[i]->processData([](sf::RectangleShape& rect, bool& active)->void{
				active=true;
			});
			rows[positions[i].y]++;
			cout<<rows<<" index: "<<i<<" "<<positions[i].y<<" = = "<<rows[positions[i].y]<<endl;
		}
		return true;
	}
	return false;
}

void Tetromino::swap(int target, int ref, char dir, Point P){
	tetroid[target]->setColor(Bcolor);
	tetroid[target]=tetroid[ref]->getAddress(dir);
	tetroid[target]->setColor(Tcolor);
	positions[target]+=P;
}

//====================================================================
//====================================================================

TetroT::TetroT()
	:Tetromino({Point(10, board->getHeight()-1), Point(11,board->getHeight()-1), Point(12,board->getHeight()-1), Point(11,board->getHeight()-2)}, sf::Color(0, 255, 0)), 
	Tcolor(sf::Color(0, 255, 0)){}

void TetroT::rotation(){
	static int p[3]={2,3,0};
	Node* tmp=NULL;

	if(rotationa==0){
		//cout<<"0 "<<p[index]<<" 000 ++++++++++++++++++++++++++++++++++++"<<endl;
		if(tetroid[1]->getAddress('t')){
			swap(p[index], 1, 't', Point(0,1));
			rotationa=1;
			index++;
		}
	}
	else if(rotationa==1){
		//cout<<"1 "<<p[index]<<" 111 ++++++++++++++++++++++++++++++++++++"<<endl;
		tmp=tetroid[1]->getAddress('r');
		if(!tmp){
			move('l');
		}
		tmp=tetroid[1]->getAddress('r');
		if(tmp && !tmp->isActive()){
			swap(p[index], 1, 'r', Point(0,1));
			rotationa=2;
			index++;
		}
	}
	else if(rotationa==2){
		//cout<<"2 "<<p[index]<<" 222++++++++++++++++++++++++++++++++++++"<<endl;
		tmp=tetroid[1]->getAddress('b');
		if(tmp && !tmp->isActive()){
			swap(p[index], 1, 'b', Point(0,-1));
			rotationa=3;
			index++;
		}
	}
	else if(rotationa==3){
		//cout<<"3 "<<p[index]<<" 33++++++++++++++++++++++++++++++++++++"<<endl;
		tmp=tetroid[1]->getAddress('l');
		if(!tmp ){
			move('r');
		}
		tmp=tetroid[1]->getAddress('l');
		if(tmp && !tmp->isActive()){
			//cout<<"3 "<<p[index]<<" 33++++++++++++++++++++++++++++++++++++"<<endl;
			swap(p[index], 1, 'l', Point(0,-1));
			rotationa=0;
			index++;
		}
	}
	index=index%3;
	//sort();
}

//====================================================================
//====================================================================


TetroZ::TetroZ()
	:Tetromino({Point(6, board->getHeight()-1), Point(7,board->getHeight()-1), Point(7,board->getHeight()-2), Point(8,board->getHeight()-2)}, sf::Color(255, 165, 0)),
	Tcolor(sf::Color(255, 165, 0))
	{}


void TetroZ::rotation(){

	if(rotationa==0){
		swap(0, 2, 'l', Point(0,-1));
		swap(3, 0, 'b', Point(-2,-1));
		rotationa=1;
	}
	else{
		swap(0, 1, 'l', Point(0,1));
		swap(3, 2, 'r', Point(2,1));
		rotationa=0;
	}
}

//====================================================================
//====================================================================

TetroS::TetroS()
	:Tetromino({Point(6, board->getHeight()-1), Point(7,board->getHeight()-1), Point(5,board->getHeight()-2), Point(6,board->getHeight()-2)}, sf::Color(0, 255, 255)),
	Tcolor(sf::Color(0, 255, 255))
	{}

void TetroS::rotation(){
	if(rotationa==0){
		swap(0, 2, 't', Point(-1,0));
		swap(1, 3, 'b', Point(-1,-2));
		rotationa=1;
	}
	else{
		swap(0, 3, 't', Point(1,0));
		swap(1, 0, 'r', Point(1,2));
		rotationa=0;
	}
}


//====================================================================
//====================================================================


TetroO::TetroO()
	:Tetromino({Point(6, board->getHeight()-1), Point(7,board->getHeight()-1), Point(6,board->getHeight()-2), Point(7,board->getHeight()-2)}, sf::Color(0, 0, 255)),
	Tcolor(sf::Color(0, 0, 255))
	{}

//====================================================================
//====================================================================

TetroL::TetroL()
	:Tetromino({Point(6, board->getHeight()-1), Point(7,board->getHeight()-1), Point(8,board->getHeight()-1), Point(6,board->getHeight()-2)}, sf::Color(255, 0, 255)),
	Tcolor(sf::Color(255, 0, 255))
	{}


void TetroL::rotation(){
	if(rotationa==0){
		swap(2, 1, 't', Point(-1,1));
		swap(0, 1, 'b', Point(1,-1));
		swap(3, 0, 'r', Point(2,0));
		rotationa=1;
	}
	else if(rotationa==1){
		cout<<"rotation: 1"<<endl;
		swap(2, 1, 'l', Point(-1,-1));
		swap(0, 1, 'r', Point(1,1));
		swap(3, 0, 't', Point(0,2));
		rotationa=2;
	}
	else if(rotationa==2){
		cout<<"rotation: 2"<<endl;
		swap(2, 1, 'b', Point(1,-1));
		swap(0, 1, 't', Point(-1,1));
		swap(3, 0, 'l', Point(-2,0));
		rotationa=3;
	}
	else if(rotationa==3){
		cout<<"rotation: 3"<<endl;
		swap(2, 1, 'r', Point(1,1));
		swap(0, 1, 'l', Point(-1,-1));
		swap(3, 0, 'b', Point(0,-2));
		rotationa=0;
	}

}


//====================================================================
//====================================================================

TetroJ::TetroJ()
	:Tetromino({Point(6, board->getHeight()-1), Point(7,board->getHeight()-1), Point(8,board->getHeight()-1), Point(8,board->getHeight()-2)}, sf::Color(255, 255,0)),
	Tcolor(sf::Color(255,255,0))
{}


//swap(int target, int ref, char dir, Point P);
void TetroJ::rotation(){
	if(rotationa==0){
		swap(0, 1, 't', Point(1,1));
		swap(2, 1, 'b', Point(-1,-1));
		swap(3, 2, 'l', Point(-2,0));
		rotationa=1;
	}
	else if(rotationa==1){
		cout<<"rotation: 1"<<endl;
		swap(0, 1, 'r', Point(1,-1));
		swap(2, 1, 'l', Point(-1,1));
		swap(3, 2, 't', Point(0,2));
		rotationa=2;
	}
	else if(rotationa==2){
		cout<<"rotation: 2"<<endl;
		swap(0, 1, 'b', Point(-1,-1));
		swap(2, 1, 't', Point(1,1));
		swap(3, 2, 'r', Point(2,0));
		rotationa=3;
	}
	else if(rotationa==3){
		cout<<"rotation: 3"<<endl;
		swap(0, 1, 'l', Point(-1,1));
		swap(2, 1, 'r', Point(1,-1));
		swap(3, 2, 'b', Point(0,-2));
		rotationa=0;
	}

}


//====================================================================
//====================================================================


TetroI::TetroI()
	:Tetromino({Point(6, board->getHeight()-1), Point(7,board->getHeight()-1), Point(8,board->getHeight()-1), Point(9,board->getHeight()-1)}, sf::Color(255, 0,0)),
	Tcolor(sf::Color(255,0,0))
{}

void TetroI::rotation(){
	if(rotationa==0){
		swap(0, 1, 'b', Point(1,-1));
		swap(2, 1, 't', Point(-1,1));
		swap(3, 2, 't', Point(-2,2));
		rotationa=1;
	}
	else if(rotationa==1){
		cout<<"rotation: 1"<<endl;
		swap(0, 1, 'l', Point(-1,1));
		swap(2, 1, 'r', Point(1,-1));
		swap(3, 2, 'r', Point(2,-2));
		rotationa=0;
	}

}

//====================================================================
//====================================================================

/**/

