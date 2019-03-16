#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <Windows.h>


using namespace sf;
using namespace std;


int H = 720, W = 720, moving = 1;
sf::RenderWindow window(sf::VideoMode(W, H), "X&O Remastered");

sf::CircleShape circle (100);

sf::RectangleShape line2(sf::Vector2f(250, 5));
sf::RectangleShape line1(sf::Vector2f(250, 5));


char brd[3][3] = { {'.','.','.'},{'.','.','.'},{'.','.','.'} };
float x[3] = {  (H / 3) - 225,(H / 3) + 20, (H - 215) };
float y[3] = { 10, 260 ,510 };


void print_circle(float x, float y)
{
	circle.setPosition(x, y);
	window.draw(circle);
}

void print_lines(float x, float y)
{
	line1.setPosition(x+12, y);
	line2.setPosition(x+12, y+176);
	window.draw(line1);
	window.draw(line2);
}

void print_board()
{
	window.clear(Color::Black);
	

	RectangleShape square(Vector2f(3, H));
	square.setFillColor(Color::Yellow);
	square.setPosition(W / 3, 0);
	window.draw(square);

	square.setPosition((W / 3) * 2, 0);
	window.draw(square);

	square.setSize(Vector2f(W, 3));
	square.setPosition(0, H / 3);
	window.draw(square);


	square.setPosition(0, (H / 3) * 2);
	window.draw(square);

	for (int i = 0; i < 3;i++)
		for (int j = 0; j < 3; j++)
		{
			if  (brd[i][j] == 'X') print_circle( x[i], y[j] );
			if  (brd[i][j] == 'O') print_lines( x[i], y[j] );
		}
			

}

void Move(int mov)
{
	int x,y;
	Event event1;
	while (window.pollEvent(event1))
	{

		if (event1.type == Event::MouseButtonPressed)
			if (event1.key.code == Mouse::Left)
			{
				x = (Mouse::getPosition(window).x) / 240;
				y = (Mouse::getPosition(window).y) / 240;
				if (mov % 2 == 0) brd[x][y] = 'O';
				else brd[x][y] = 'X';
				cout << x << y << endl;
				moving++;
			}
		if (event1.type == Event::Closed)
			window.close();
	}

}

char check()
{
	for (int i = 0; i < 3; i++)
	{
		if (brd[0][i] == brd[1][i] && brd[1][i] == brd[2][i] && (brd[0][i] == 'X' || brd[0][i] == 'O')) { return brd[1][i]; }
		if (brd[i][0] == brd[i][1] && brd[i][1] == brd[i][2] && (brd[i][0] == 'X' || brd[i][0] == 'O')) { return brd[i][1]; }
		if (brd[0][0] == brd[1][1] && brd[1][1] == brd[2][2] && (brd[1][1] == 'X' || brd[1][1] == 'O') || (brd[0][2] == brd[1][1] && brd[1][1] == brd[2][0] && (brd[1][1] == 'X' || brd[1][1] == 'O'))){ return brd[1][1]; }
	}
}

void result(char win)
{
	Event event;
	Font font;
	font.loadFromFile("12905.otf");
	Text text("",font,50);
	if (win == 'X')
	{
		while (window.isOpen())
		{
			
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
					window.close();
			}
			window.clear(sf::Color::Black);
			text.setString("O win");
			text.setPosition((H / 2) - 25, (W / 2) - 25);
			window.draw(text);
			window.display();
		}
	}
	if (win == 'O')
	{
		while (window.isOpen())
		{
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
					window.close();
			}
			window.clear(Color::Black);
			text.setString("X win");
			text.setPosition((H / 2) - 25, (W / 2) - 25);
			window.draw(text);
			window.display();
		}
	}
	if (win == '.')
	{
		while (window.isOpen())
		{
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
					window.close();
			}
			window.clear(Color::Black);
			text.setString("Draw");
			text.setPosition((H / 2) - 50, (W / 2) - 50);
			window.draw(text);
			window.display();
		}
	}
	
}


int main()
{
	char temp;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			brd[i][j] = 0;

	window.setVerticalSyncEnabled(true);
	
	circle.setOutlineThickness(-10);
	circle.setOutlineColor(Color::Yellow);
	circle.setFillColor(Color::Black);

	line1.rotate(45);
	line2.rotate(-45);

	

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		print_board();
		Move(moving);
		window.display();
		if (moving >= 5)
		{
			result(check());
		}
		if (moving == 10)
		{
			result('.');
		}

	}
	return 0;
}

