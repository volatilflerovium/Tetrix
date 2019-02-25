#ifndef TETROMINO_H
#define TETROMINO_H

//#include<functional>
#include<map>
#include<iostream>
#include<SFML/Graphics.hpp>

#include "helper.h"
#include "node.h"
#include "board.h"

using namespace std;


class Tetromino
{
	protected:		
		Node* tetroid[4];
		Point positions[4];
		sf::Color Tcolor;
		bool canMove(char d);		
		void swap(int target, int ref, char dir, Point P);

	   static std::map<char,Point>Dir;
	   static sf::Color Bcolor;
	   static bool isSet;
	   static int* rows;
	   static Board* board;
	   

	public:
		Tetromino(std::initializer_list<Point> l, sf::Color color);
		bool move(char d);
		virtual void rotation()=0;
		
		sf::Color getColor() const;
		static void init(int* _rows, Board* G, sf::Color bcolor);
		Point getPosition(int i) const;
		bool checkPath(Node* start, std::initializer_list<char> dir)const;// Point& P);
		static Tetromino* mk_instance();
};


Board* Tetromino::board=NULL;
sf::Color Tetromino::Bcolor(0,0,0);
bool Tetromino::isSet=false;
int* Tetromino::rows=NULL;
std::map<char,Point> Tetromino::Dir;

inline Point Tetromino::getPosition(int i) const {
	return positions[i];
}

inline sf::Color Tetromino::getColor() const{
	return Tcolor;
}

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
		}
		if(positions[0].y<board->getHeight()-2){
			return true;
		}
		else{
			return false;		
		}
	}
	return false;
}

void Tetromino::swap(int target, int ref, char dir, Point P){
	tetroid[target]->setColor(Bcolor);
	tetroid[target]=tetroid[ref]->getAddress(dir);
	tetroid[target]->setColor(Tcolor);
	positions[target]+=P;
}

bool Tetromino::checkPath(Node* start, std::initializer_list<char> dir)const{
	bool a=true;
	Node* tmp=start;
	for(char d : dir){
		tmp=tmp->getAddress(d);
		if(!tmp || tmp->isActive()){
			return false;
		}
	}
	return true;
}

//####################################################################
//####################################################################
//####################################################################


class TetroT : public Tetromino
{
	private:
		sf::Color Tcolor;
		int indexing=0;
		int rotationa=0;

	public:
		TetroT();
		void rotation();
		static Tetromino* mk_instance();
};

TetroT::TetroT()
	:Tetromino({Point(6, board->getHeight()-1), Point(7,board->getHeight()-1), Point(8,board->getHeight()-1), Point(7,board->getHeight()-2)}, sf::Color(0, 255, 0)), 
	Tcolor(sf::Color(0, 255, 0)){}

Tetromino* TetroT::mk_instance(){
	return new TetroT();
}


void TetroT::rotation(){
	static int p[3]={2,3,0};
	Node* tmp=NULL;
	//*
	if(rotationa==0){
		if(checkPath(tetroid[1], {'t'})){
			swap(p[indexing], 1, 't', Point(0,1));
			rotationa=1;
			indexing++;
		}
	}
	else if(rotationa==1){
		tmp=tetroid[1]->getAddress('r');
		if(!tmp){
			move('l');
		}
		tmp=tetroid[1]->getAddress('r');
		if(tmp && !tmp->isActive()){
			swap(p[indexing], 1, 'r', Point(0,1));
			rotationa=2;
			indexing++;
		}
	}
	else if(rotationa==2){
		tmp=tetroid[1]->getAddress('b');
		if(tmp && !tmp->isActive()){
			swap(p[indexing], 1, 'b', Point(0,-1));
			rotationa=3;
			indexing++;
		}
	}
	else if(rotationa==3){
		tmp=tetroid[1]->getAddress('l');
		if(!tmp ){
			move('r');
		}
		tmp=tetroid[1]->getAddress('l');
		if(tmp && !tmp->isActive()){
			swap(p[indexing], 1, 'l', Point(0,-1));
			rotationa=0;
			indexing++;
		}
	}
	indexing=indexing%3;
	/**/
}

//####################################################################
//####################################################################
//####################################################################

class TetroZ : public Tetromino
{
	private:
		sf::Color Tcolor;
		int rotationa=0;

	public:
		TetroZ();
		void rotation();
		static Tetromino* mk_instance();
};

Tetromino* TetroZ::mk_instance(){
	return new TetroZ();
}
//####################################################################
//####################################################################

class TetroS : public Tetromino
{
	private:
		sf::Color Tcolor;
		int rotationa=0;

	public:
		TetroS();
		void rotation();
		static Tetromino* mk_instance();
};
Tetromino* TetroS::mk_instance(){
	return new TetroS();
}
//####################################################################
//####################################################################


class TetroO : public Tetromino
{
	private:
		sf::Color Tcolor;

	public:
		TetroO();
		void rotation();
		static Tetromino* mk_instance();
};


inline void TetroO::rotation(){}
Tetromino* TetroO::mk_instance(){
	return new TetroO();
}
//####################################################################
//####################################################################

class TetroL : public Tetromino
{
	private:
		sf::Color Tcolor;
		int rotationa=0;

	public:
		TetroL();
		void rotation();
		static Tetromino* mk_instance();
};

Tetromino* TetroL::mk_instance(){
	return new TetroL();
}

//####################################################################
//####################################################################

class TetroJ : public Tetromino
{
	private:
		sf::Color Tcolor;
		int rotationa=0;

	public:
		TetroJ();
		void rotation();
		static Tetromino* mk_instance();
};

Tetromino* TetroJ::mk_instance(){
	return new TetroJ();
}

//####################################################################
//####################################################################

class TetroI : public Tetromino
{
	private:
		sf::Color Tcolor;
		int rotationa=0;

	public:
		TetroI();
		void rotation();
		static Tetromino* mk_instance();
};

Tetromino* TetroI::mk_instance(){
	return new TetroI();
}

//====================================================================
//====================================================================


TetroZ::TetroZ()
	:Tetromino({Point(6, board->getHeight()-1), Point(7,board->getHeight()-1), Point(7,board->getHeight()-2), Point(8,board->getHeight()-2)}, sf::Color(255, 165, 0)),
	Tcolor(sf::Color(255, 165, 0))
	{}


void TetroZ::rotation(){

	if(rotationa==0 && checkPath(tetroid[2], {'l','b'})){
		swap(0, 2, 'l', Point(0,-1));
		swap(3, 0, 'b', Point(-2,-1));
		rotationa=1;
	}
	else if(rotationa==1 && checkPath(tetroid[1], {'l'}) && checkPath(tetroid[2], {'r'})){
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
	if(rotationa==0 && checkPath(tetroid[2], {'t'}) && checkPath(tetroid[3], {'b'})){
		swap(0, 2, 't', Point(-1,0));
		swap(1, 3, 'b', Point(-1,-2));
		rotationa=1;
	}
	else if(rotationa==1 && checkPath(tetroid[3], {'t','r'})){
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
	if(rotationa==0 && checkPath(tetroid[1], {'t'}) && checkPath(tetroid[1], {'b', 'r'})){
		swap(2, 1, 't', Point(-1,1));
		swap(0, 1, 'b', Point(1,-1));
		swap(3, 0, 'r', Point(2,0));
		rotationa=1;
	}
	else if(rotationa==1 && checkPath(tetroid[1], {'l'}) && checkPath(tetroid[1], {'r', 't'})){
		swap(2, 1, 'l', Point(-1,-1));
		swap(0, 1, 'r', Point(1,1));
		swap(3, 0, 't', Point(0,2));
		rotationa=2;
	}
	else if(rotationa==2 && checkPath(tetroid[1], {'b'}) && checkPath(tetroid[1], {'t', 'l'})){
		swap(2, 1, 'b', Point(1,-1));
		swap(0, 1, 't', Point(-1,1));
		swap(3, 0, 'l', Point(-2,0));
		rotationa=3;
	}
	else if(rotationa==3 && checkPath(tetroid[1], {'r'}) && checkPath(tetroid[1], {'l', 'b'})){
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
	if(rotationa==0 && checkPath(tetroid[1], {'t'}) && checkPath(tetroid[1], {'b', 'l'})){
		swap(0, 1, 't', Point(1,1));
		swap(2, 1, 'b', Point(-1,-1));
		swap(3, 2, 'l', Point(-2,0));
		rotationa=1;
	}
	else if(rotationa==1 && checkPath(tetroid[1], {'r'}) && checkPath(tetroid[1], {'l', 'r'})){
		swap(0, 1, 'r', Point(1,-1));
		swap(2, 1, 'l', Point(-1,1));
		swap(3, 2, 't', Point(0,2));
		rotationa=2;
	}
	else if(rotationa==2 && checkPath(tetroid[1], {'b'}) && checkPath(tetroid[1], {'t', 'r'})){
		swap(0, 1, 'b', Point(-1,-1));
		swap(2, 1, 't', Point(1,1));
		swap(3, 2, 'r', Point(2,0));
		rotationa=3;
	}
	else if(rotationa==3 && checkPath(tetroid[1], {'l'}) && checkPath(tetroid[1], {'r', 'b'})){
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
	if(rotationa==0 && checkPath(tetroid[1], {'b'}) && checkPath(tetroid[1], {'t', 't'})){
		swap(0, 1, 'b', Point(1,-1));
		swap(2, 1, 't', Point(-1,1));
		swap(3, 2, 't', Point(-2,2));
		rotationa=1;
	}
	else if(rotationa==1 && checkPath(tetroid[1], {'l'}) && checkPath(tetroid[1], {'r', 'r'})){
		swap(0, 1, 'l', Point(-1,1));
		swap(2, 1, 'r', Point(1,-1));
		swap(3, 2, 'r', Point(2,-2));
		rotationa=0;
	}

}




#endif