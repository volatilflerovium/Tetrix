/*********************************************************************
* Tetrix: manager                                                            *
*                                                                    *
* Version: 1.0                                                       *
* Date:    02-25-2018                                                *
* Author:  Dan Machado                                               *                                         *
**********************************************************************/
#ifndef MANAGER_H
#define MANAGER_H

#include<map>
#include<iostream>
#include<SFML/Graphics.hpp>

#include "base.h"
#include "node.h"
#include "board.h"
#include "tetromino.h"

class Tetromino;
typedef Tetromino* (*MkTetroid)();

class Manager
{
	private:
		static std::map<char, MkTetroid> pieces; //array of pointers to different pieces
		static std::vector<char> shapes;

	private:
	   sf::Color Bcolor;
	   int* rows;
	   Board* board;	   
	   Tetromino* tetroid=NULL;
		
		void mkTetroid();
		static Manager* instance;
		Manager(int* _rows, Board* G, sf::Color color);	
		Tetromino* mkTetromino(char c);

	public:
		~Manager();		
		void resetRow(int r);
		void shift(int mr, int t);
		Tetromino* getTetroid();
		void update(bool a);
		static void init(int* _rows, Board* G, sf::Color bcolor);
		static Manager* getInstance();	

		static void registerShape(char c, MkTetroid);

		//=========================
		// We use a class to handle the deletion of the singleton
		class Supervisor{
			private:
				Manager* manager;
			public:
				Supervisor(Manager* _manager){
					//cout<<"New manager instance!!"<<endl;
					manager=_manager;
				};
				~Supervisor(){
					if(manager){
						//cout<<"Deleting Manager!!"<<endl;
						delete manager;
					}
				}
		};
};



#endif