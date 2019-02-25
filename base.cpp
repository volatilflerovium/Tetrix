#include <SFML/Graphics.hpp>
#include "base.h"
//#include "reference_frame.h"

ReferenceFrame* Base::RF;
sf::RenderWindow* Base::Window;
bool Base::is_window_set=false;
bool Base::is_rf_set=false;

/*
Base::Base()
				:is_window_set(false), is_rf_set(false)
{}

*/
void Base::set_window(sf::RenderWindow* W){
	if(!is_window_set){
		is_window_set=true;
		Window=W;
	}
}


void Base::set_rf(ReferenceFrame* rf){
	if(!is_rf_set){
		is_rf_set=true;
		RF=rf;
	}
}








