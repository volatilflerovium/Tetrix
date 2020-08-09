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
#include "manager.h"

using namespace std;

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
	FrameRate Framerate(30);
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


