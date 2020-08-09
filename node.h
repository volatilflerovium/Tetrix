/*********************************************************************
* Tetrix: node                                                             *
*                                                                    *
* Version: 1.0                                                       *
* Date:    02-25-2018                                                *
* Author:  Dan Machado                                               *                                         *
**********************************************************************/
#ifndef NODE_H
#define NODE_H
#include<SFML/Graphics.hpp>

#include "helper.h"

class Node
{
	protected:
		Node* top=NULL;
		Node* right=NULL;
		Node* bottom=NULL;
		Node* left=NULL;
		sf::RectangleShape Rect;
		bool active;
		int row;

	public:
		Node(float sd, sf::Color color);
		void setAddress(Node* c, char p);
		Node* getAddress(char c)const;
		bool isActive() const;
		void setColor(const sf::Color& color);
		template<typename Function>
		void processData(Function func);		
};

inline Node::Node(float sd, sf::Color color)
		:Rect(sf::Vector2f(sd-0.5, sd-0.5)), active(false){
	Rect.setFillColor(color);
	Rect.setPosition(sf::Vector2f(sd-0.5, sd-0.5));
}

inline bool Node::isActive()const {
	return active;
}

inline void Node::setColor(const sf::Color& color){
	Rect.setFillColor(color);
}


template<typename Function>
void Node::processData(Function func){
	func(Rect, active);
}


#endif