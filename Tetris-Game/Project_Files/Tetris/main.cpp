#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <string>
#include <sstream>

#include "Tetris.hpp"


int main()
{
	Tetris tetris;

	bool rotate = 0; // for figure rotating
	int x_position = 0; // to control the arrows
	int score = 0; // actually score
	int best_score = 0; // the best score
	float timer = 0; // for time counting
	double delay = 0.3; // speed of falling
	int full_row; // which row is full

	sf::RenderWindow window(sf::VideoMode(460, 396), "Tetris game");

	sf::Texture tex1, tex2;
	tex1.loadFromFile("images/colors.png");
	tex2.loadFromFile("images/tetrisbackground.png");

	sf::Sprite spr1, spr2;
	spr1.setTexture(tex1);
	spr2.setTexture(tex2);

	sf::Event eve;

	sf::Clock clock;

	sf::Font font;
	font.loadFromFile("fonts/FT_BetonBold.otf");

	sf::Text text;
	text.setFont(font);


	/********************************************************************** MAIN LOOP **********************************************************************/
	while (window.isOpen())
	{
		srand((unsigned int)time(NULL));
		float time = clock.getElapsedTime().asSeconds(); // returns the time in seconds since the last time it was used clock.restart()
		clock.restart();
		timer += time;


		/**********  EVENT DETECTION  **********/
		while (window.pollEvent(eve))
		{
			if (eve.type == sf::Event::Closed)
				window.close();
			if (eve.type == sf::Event::KeyPressed)
			{
				if (eve.key.code == sf::Keyboard::Up) rotate = true;
				else if (eve.key.code == sf::Keyboard::Right) x_position = 1;
				else if (eve.key.code == sf::Keyboard::Left) x_position = -1;
				else if (eve.key.code == sf::Keyboard::Escape) window.close();
			}

		}


		/**********  <- MOVING ->  **********/
		tetris.move_position(x_position);


		/**********  ^ ROTATION ^  **********/
		if (rotate)
			tetris.rotate_figure();


		/**********  v FASTER FALLING v  **********/
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) delay = 0.05;
		if (timer > delay)
		{
			tetris.fast_falling();
			timer = 0; // reset the timer
		}


		/**********  DELETE ROW WHEN IS FULL  **********/
		if (full_row = tetris.which_row_is_full())
		{
			score++; // aktualny wynik	
			tetris.clear_row(full_row); // delete the filled row and move the game area one position relative to the deleted row
		}


		/**********   CREATE RANDOM FIGURE  **********/
		// Create next figures and control if the figure is in free game area
		if (tetris.point_in_free_area())
			tetris.create_figures();


		/**********   END OF GAME MOMENT   **********/
		if (tetris.end_game_check())
		{
			text.setCharacterSize(30);
			text.setFillColor(sf::Color::Red);
			text.setPosition(280, 300);
			text.setString("GAME OVER !");
			window.draw(text);
			text.setCharacterSize(20);
			text.setPosition(300, 330);
			text.setString("press space");
			window.draw(text);
			window.display();
			while (1)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) // when we click escape we close the window
					window.close();
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) // when whe click space start new game
				{
					tetris.clear_game_area(); // clean game area
					if (score > best_score) // check if it is the best score
						best_score = score;
					score = 0;
					break;
				}
			}
		}


		/********************************************************************** DISPLAYS **********************************************************************/
		window.clear(sf::Color::Black);
		window.draw(spr2); // background

		int** game_area = tetris.get_game_area(); // get values of game area
		Point* Point_position = tetris.get_Point_position(); // get values of actually point position
		Point* Point_next_figure = tetris.get_Point_next_figure(); // get values of next figure

		/**********   DRAW ACTUALLY FIGURE   **********/
		for (int i = 0; i < 4; i++)
		{
			spr1.setTextureRect(sf::IntRect(tetris.get_color() * 18, 0, 18, 18));
			spr1.setPosition(float(Point_position[i].x * 18), float(Point_position[i].y * 18));
			spr1.move(18, 18); // move the object relative to its current position x // to match the background
			window.draw(spr1);
		}


		/**********   DRAW ALL FIGURE   **********/
		for (int i = 0; i < X; i++)
		{
			for (int j = 0; j < Y; j++)
			{
				if (game_area[i][j] == 0) continue; // when we have not filled the field no one figure, omit
				spr1.setTextureRect(sf::IntRect(game_area[i][j] * 18, 0, 18, 18)); // cuts a chunk out of the whole texture
				spr1.setPosition(float(j * 18), float(i * 18)); // the sprite will be placed at the x, y position
				spr1.move(18, 18);
				window.draw(spr1);
			}
		}


		/**********   DRAW NEXT FIGURE   **********/
		for (int i = 0; i < 4; i++)
		{
			spr1.setTextureRect(sf::IntRect(tetris.get_next_color() * 18, 0, 18, 18));
			spr1.setPosition(float(Point_next_figure[i].x * 18), float(Point_next_figure[i].y * 18));
			spr1.move(328, 58);
			window.draw(spr1);
		}


		/**********   DRAW SCORE AND SOME FUNCTIONALLITY  **********/
		std::stringstream ss1, ss2;
		ss1 << score;
		ss2 << best_score;
		std::string str1 = ss1.str();
		std::string str2 = ss2.str();

		text.setCharacterSize(30);
		text.setFillColor(sf::Color::White);
		text.setPosition(280, 180);
		text.setString("YOUR SCORE:");
		window.draw(text);
		text.setPosition(340, 210);
		text.setString(str1);
		window.draw(text);
		text.setPosition(280, 240);
		text.setString("BEST SCORE:");
		window.draw(text);
		text.setPosition(340, 270);
		text.setString(str2);
		window.draw(text);
		text.setCharacterSize(15);
		text.setPosition(295, 360);
		text.setString("press ESC to exit");
		window.draw(text);


		/**********   DISPLAY ALL AND RESET VARIABLES   **********/
		window.display();
		x_position = 0;  
		delay = 0.3; 
		rotate = 0; 


		/**********   CLEAN MEMORY   **********/
		for (int i = 0; i < X; i++)
		{
			delete[] game_area[i];
		}
		delete[] game_area;
		game_area = 0;

		delete[] Point_position;
		Point_position = 0;
		delete[] Point_next_figure;
		Point_next_figure = 0;

	}
	return 0;
}
