/*********************************************************************
* Tetrix : tetromino                                                            *
*                                                                    *
* Version: 1.0                                                       *
* Date:    02-25-2018                                                *
* Author:  Dan Machado                                               *                                         *
**********************************************************************/
#ifndef TETROMINO_H
#define TETROMINO_H

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



inline Point Tetromino::getPosition(int i) const {
	return positions[i];
}

inline sf::Color Tetromino::getColor() const{
	return Tcolor;
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

inline TetroT::TetroT()
	:Tetromino({Point(6, board->getHeight()-1), Point(7,board->getHeight()-1), Point(8,board->getHeight()-1), Point(7,board->getHeight()-2)}, sf::Color(0, 255, 0)), 
	Tcolor(sf::Color(0, 255, 0)){}


inline Tetromino* TetroT::mk_instance(){
	return new TetroT();
}

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

inline TetroZ::TetroZ()
	:Tetromino({Point(6, board->getHeight()-1), Point(7,board->getHeight()-1), Point(7,board->getHeight()-2), Point(8,board->getHeight()-2)}, sf::Color(255, 165, 0)),
	Tcolor(sf::Color(255, 165, 0))
	{}

inline Tetromino* TetroZ::mk_instance(){
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

inline TetroS::TetroS()
	:Tetromino({Point(6, board->getHeight()-1), Point(7,board->getHeight()-1), Point(5,board->getHeight()-2), Point(6,board->getHeight()-2)}, sf::Color(0, 255, 255)),
	Tcolor(sf::Color(0, 255, 255))
	{}


inline Tetromino* TetroS::mk_instance(){
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

inline TetroO::TetroO()
	:Tetromino({Point(6, board->getHeight()-1), Point(7,board->getHeight()-1), Point(6,board->getHeight()-2), Point(7,board->getHeight()-2)}, sf::Color(0, 0, 255)),
	Tcolor(sf::Color(0, 0, 255))
	{}

inline void TetroO::rotation(){}
inline Tetromino* TetroO::mk_instance(){
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

inline TetroL::TetroL()
	:Tetromino({Point(6, board->getHeight()-1), Point(7,board->getHeight()-1), Point(8,board->getHeight()-1), Point(6,board->getHeight()-2)}, sf::Color(255, 0, 255)),
	Tcolor(sf::Color(255, 0, 255))
	{}

inline Tetromino* TetroL::mk_instance(){
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

inline Tetromino* TetroJ::mk_instance(){
	return new TetroJ();
}

inline TetroJ::TetroJ()
	:Tetromino({Point(6, board->getHeight()-1), Point(7,board->getHeight()-1), Point(8,board->getHeight()-1), Point(8,board->getHeight()-2)}, sf::Color(255, 255,0)),
	Tcolor(sf::Color(255,255,0))
{}

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


inline TetroI::TetroI()
	:Tetromino({Point(6, board->getHeight()-1), Point(7,board->getHeight()-1), Point(8,board->getHeight()-1), Point(9,board->getHeight()-1)}, sf::Color(255, 0,0)),
	Tcolor(sf::Color(255,0,0))
{}

inline Tetromino* TetroI::mk_instance(){
	return new TetroI();
}

//====================================================================
//====================================================================







#endif