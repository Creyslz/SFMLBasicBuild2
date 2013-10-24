// SFMLBasicBuild2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML\Graphics.hpp>
#include <iostream>


int _tmain(int argc, _TCHAR* argv[])
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	sf::RectangleShape rect(sf::Vector2f(10, 10));

	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;

	int tX=-1;
	int tY=-1;

	sf::Clock myClock = sf::Clock::Clock();
	sf::Time start = myClock.getElapsedTime();
	sf::Time end = myClock.getElapsedTime();

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			end = myClock.getElapsedTime();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				left = true;
			} else {
				left = false;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				up = true;
			} else {
				up = false;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				down = true;
				std::cout<<"x:" <<rect.getPosition().x << ", y:" << rect.getPosition().y <<"\n";
			} else {
				down= false;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				right = true;
			} else {
				right = false;
			}


			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				std::cout<<"click\n";
				sf::Vector2i localPosition = sf::Mouse::getPosition(window);
				std::cout<<"x:" <<localPosition.x << ", y:" << localPosition.y<<"\n";
				sf::Vector2f pos = rect.getPosition();
				rect.setPosition(localPosition.x-5, localPosition.y-5);
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				std::cout<<"Lclick\n";
				sf::Vector2i localPosition = sf::Mouse::getPosition(window);
				std::cout<<"x:" <<localPosition.x << ", y:" << localPosition.y<<"\n";
				sf::Vector2f pos = rect.getPosition();
				tX = localPosition.x + 5;
				tY = localPosition.y + 5;
			}
		}
		int change = end.asMilliseconds()-start.asMilliseconds();
		float offx = 0, offy = 0;
		if(change > 10)
		{
			start = myClock.getElapsedTime();
			end = myClock.getElapsedTime();
			
			if(right)
				offx += 2;
			if(left)
				offx -= 2;
			if(up)
				offy -= 2;
			if(down) 
				offy += 2;
		}

		if(tX != -1 && tY != -1)
		{
			int xdir, ydir;
			if(tX > rect.getPosition().x+10)
			{
				xdir = 1;
			} else {
				xdir = -1;
			}

			if(tY > rect.getPosition().y+10)
			{
				ydir = 1;
			} else {
				ydir = -1;
			}
			offx = xdir*(.1f/(1+exp(-5.0f*(tX-rect.getPosition().x-10)*xdir)));
			offy = ydir*(.1f/(1+exp(-5.0f*(tY-rect.getPosition().y-10)*ydir)));
		}
			rect.move(offx, offy);


		window.clear();
		window.draw(shape);
		window.draw(rect);

		window.display();
	}
	return 0;
}