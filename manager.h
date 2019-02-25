#ifndef MANAGER_H
#define MANAGER_H
#include "helper.h"
#include "node.h"
#include "board.h"
#include "tetromino.h"

class Manager
{
	private:
		Node* sed;
	   sf::Color Bcolor;
	   int* rows;
	   Board* grid;	   
	   Tetromino* tetroid;
	   char shapes[7]={'T','Z','S','I','L','J','O'};
		void mkTetroid();
		static Manager* instance;
		Manager(Node* _sed, int* _rows, Board* G, sf::Color color);	
	
	public:
		~Manager();		
		void resetRow(int r);
		void shift(int mr, int t);
		Tetromino* getTetroid();
		void update(bool a);
		static void init(Node* _sed, int* _rows, Board* G, sf::Color bcolor);
		static Manager* getInstance();	

	//=========================

	class Supervisor{
		private:Manager* manager;
		public:Supervisor(Manager* _manager){
			cout<<"New manager instance!!"<<endl;
			manager=_manager;};
		~Supervisor(){if(manager){
				cout<<"Deleting Manager!!"<<endl;
				delete manager;}
		}
	};
};
//=========================

Manager::~Manager(){
	if(tetroid){
		delete tetroid;
	}
}

Manager* Manager::instance=NULL;

Manager* Manager::getInstance(){
	return instance;	
}

void Manager::init(Node* _sed, int* _rows, Board* G, sf::Color bcolor){
	instance=new Manager(_sed, _rows, G, bcolor);
	static Supervisor Sp(instance);
}





#endif