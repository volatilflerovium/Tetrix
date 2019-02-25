#include<iostream>
#include<cmath>
#include<string>
#include<cstdlib>
#include<ctime>

#include<SFML/Graphics.hpp>

#include "helper.h"
#include "framerate.h"
#include "reference_frame.h"
#include "base.h"
#include "node.h"
#include "board.h"
#include "tetromino.h"
//#include "manager.h"

using namespace std;

//####################################################################
//####################################################################
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
	  // char shapes[7]={'T','Z','S','I','L','J','O'};
		
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

std::map<char, MkTetroid> Manager::pieces;
std::vector<char> Manager::shapes;

//###############
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

void Manager::update(bool a){
	if(a){
		int t=0;
		int mr=0;
		Point position;
		for(int i=0; i<4; i++){
			position=tetroid->getPosition(i);
			// cout<<rows<<"  "<<position.y<<" ++++ "<<rows[position.y]<<" Reset row?? "<<endl;
			if(rows[position.y]==board->getWidth()){
				//cout<<position.y<<" ++++ "<<rows[position.y]<<" Reset row "<<endl;
				rows[position.y]=0;
				resetRow(position.y);
				t++;
				if(position.y>mr){
					mr=position.y;
				}
			}
			else if(rows[position.y]>board->getWidth()){
				cout<<"BUG!!!"<<endl;
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

void Manager::mkTetroid(){
	if(tetroid){
		delete tetroid;
		tetroid=NULL;
	}
	
	if(!tetroid){
		tetroid=mkTetromino(shapes[rand()%shapes.size()]);
	}
}	


//####################################################################
//####################################################################
//####################################################################
//####################################################################


int main(){
	srand(time(0));
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	cout<<"Display settings: "<< sf::VideoMode::getDesktopMode().width << ", " << sf::VideoMode::getDesktopMode().height<<endl;

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "My window",sf::Style::Default, settings);

   ReferenceFrame RF(10, WINDOW_HEIGHT-100, 1);

	Manager::registerShape('T', TetroT::mk_instance);
	Manager::registerShape('S', TetroS::mk_instance);
	Manager::registerShape('Z', TetroZ::mk_instance);
	Manager::registerShape('L', TetroL::mk_instance);
	Manager::registerShape('J', TetroJ::mk_instance);
	Manager::registerShape('O', TetroO::mk_instance);
	Manager::registerShape('I', TetroI::mk_instance);

	Board::set_rf(&RF);
	Board Grid(15, 15);

	Grid.accessPoint(Manager::init);
	Grid.accessPoint(Tetromino::init);

	Manager* tetrix=Manager::getInstance();	
	Tetromino* TT=tetrix->getTetroid();

	int p=0;
	char dir='b';
	bool a=true;
	FrameRate Framerate(8);
	double t;
	while(window.isOpen()){
		sf::Event event;
		while(window.pollEvent(event)){
			if(event.type==sf::Event::Closed){
				window.close();
			}
			else if(a && event.type == sf::Event::KeyPressed){
				if(event.key.code == sf::Keyboard::Up){
					TT->rotation();
					dir='b';
					a=false;
				}
				else if(event.key.code == sf::Keyboard::Left){
					dir='l';
					a=false;
				}
				else if(event.key.code == sf::Keyboard::Right){
					dir='r';
					a=false;
				}
				else{
					dir='b';
					a=false;
				}				
			}
		}

		if(Framerate()>=0){
			Framerate.reset();

			window.clear(sf::Color::Black);
		  
			//################################################################
			//draw things here ###############################################
			
			if(p%15==14){
				tetrix->update(TT->move(dir));
				dir='b';
				p=0;
				a=true;
			}
			p++;

			Grid.looping([&window](int w, int h, Node* node)->void{
				node->processData([&window](sf::RectangleShape rect, bool active)->void{
					window.draw(rect);
				});
			});

			// END of drawing ###############################################
			//###############################################################

			t=0;
			Framerate.reset();
		}
		window.display();
	}
	
	//delete TT; this deletion is handle by the destructor of manager

	return 0;
}


