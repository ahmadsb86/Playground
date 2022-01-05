#include <SFML/Graphics.hpp>
#include <stdio.h>

int main()
{
	int size = 400;

	std::cout << "Hello, World";

	sf::RenderWindow window(sf::VideoMode(size, size), "lol");

	// Load a sprite to display
	sf::Texture texture;
	if (!texture.loadFromFile("content/dababy.jpg"))
		return EXIT_FAILURE;
	sf::Sprite sprite(texture);
	sprite.setScale(0.25, 0.25);

	// Load a music to play
	sf::Music music;
	if (!music.openFromFile("content/lesgo.ogg"))
		return EXIT_FAILURE;

	music.setLoop(true);

	int ss = 0;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode == 32)
				{
					if (ss == 0)
					{
						ss = 1;
						music.play();
					}
					else if (ss == 1)
					{
						ss = 0;
						music.stop();
					}
				}
			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					std::cout << "the right button was pressed" << std::endl;
					std::cout << "mouse x: " << event.mouseButton.x << std::endl;
					std::cout << "mouse y: " << event.mouseButton.y << std::endl;
				}
			}
		}

		window.clear();
		window.draw(sprite);
		window.display();
	}

	return 0;
}