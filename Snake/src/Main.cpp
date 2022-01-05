#include <SFML/Graphics.hpp>
#include <cmath>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>

//consts
int size = 800;
int boxSize = 10;
float deltaTime = 0.0;
float oldTime = 0.0;

//classes

class point
{
public:
	float x = 0;
	float y = 0;
	void set(float a, float b)
	{
		x = a;
		y = b;
	}
	point add(point p)
	{
		float finalX = x + p.x;
		float finalY = y + p.y;

		point final;
		final.set(finalX, finalY);

		return final;
	}
};

class food
{
public:
	point pos;
	sf::RectangleShape rectangle;
	food(int x, int y)
	{
		repos(x, y);
		rectangle.setSize(sf::Vector2f(boxSize, boxSize));
		rectangle.setFillColor(sf::Color::Red);
		updatePos();
	}
	void repos(int a, int b)
	{
		pos.set(a, b);
	}
	void updatePos()
	{
		rectangle.setPosition(pos.x, pos.y);
	}
};

class Snake
{
public:
	sf::RectangleShape rectangle;
	point pos;
	point vel;
	float slowness = 0.4;
	bool disp = true;
	bool inFood = false;

	Snake(int startX, int startY)
	{
		pos.set(startX, startY);
		vel.set(boxSize, 0);
		rectangle.setSize(sf::Vector2f(boxSize, boxSize));
		rectangle.setFillColor(sf::Color::Green);
	}
	void updatePos()
	{
		rectangle.setPosition(pos.x, pos.y);
	}
	void move()
	{
		pos = pos.add(vel);
	}
	void check()
	{
		if (pos.x > size - (boxSize))
		{
			pos.x = boxSize;
		}
		if (pos.x < (boxSize))
		{
			pos.x = size - (boxSize);
		}
		if (pos.y > size - (boxSize))
		{
			pos.y = boxSize;
		}
		if (pos.y < (boxSize))
		{
			pos.y = size - boxSize;
		}
	}

	void checkFood(food a)
	{
		if (a.pos.x == pos.x && a.pos.y == pos.y)
		{
			inFood = true;
		}
		else
		{
			if (inFood == true)
			{
				std::cout << "NICEEE" << std::endl;
			}
			inFood = false;
		}
	}
};

//objects
int frames = 0;

sf::RenderWindow window(sf::VideoMode(size, size + 50), "Snake Game");

//main
int main()
{

	Snake bob = Snake(size / 2, size / 2);
	int randX = round(rand() % size / boxSize) * boxSize;
	int randY = round(rand() % size / boxSize) * boxSize;
	food NomNom = food(randX, randY);

	while (window.isOpen())
	{
		sf::Event event;
		frames += 1;

		deltaTime = clock() - oldTime;
		double fps = (1 / deltaTime) * 1000;
		oldTime = clock();

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				// window closed
				case sf::Event::Closed:
					window.close();
					break;

				// key pressed
				case sf::Event::KeyPressed:
					switch (event.key.code)
					{
						case sf::Keyboard::W:
							bob.vel.set(0, -boxSize);
							break;

						case sf::Keyboard::S:
							bob.vel.set(0, boxSize);
							break;

						case sf::Keyboard::A:
							bob.vel.set(-boxSize, 0);
							break;

						case sf::Keyboard::D:
							bob.vel.set(boxSize, 0);
							break;

						case sf::Keyboard::Space:
							window.close();
							break;

						default:
							break;
					}
					break;

				// we don't process other types of events
				default:
					break;
			}
		}

		window.clear();

		if (frames >= (fps * bob.slowness))
		{
			frames = 0;
			bob.move();
		}
		bob.check();
		bob.checkFood(NomNom);
		bob.updatePos();
		window.draw(bob.rectangle);
		window.draw(NomNom.rectangle);

		sf::RectangleShape divider;
		sf::Vector2<float> line;
		line.x = size;
		line.y = 1;
		divider.setSize(line);
		divider.setPosition(0, size);

		window.draw(divider);

		window.display();
	}

	return 0;
}
