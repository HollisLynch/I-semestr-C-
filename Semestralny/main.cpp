#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
#include <conio.h>

// con1.h to alternatywa pdcurses(ncurses)
#include "con1.h"

using namespace std;
using namespace con1;

class Maze {

public:

	int height = 16;
	int width = 49;

	char maze_1[16][49]
	{
	  "################################################",
	  "#           #            #                     #",
	  "######      #######  ##########     #######    #",
	  "#                    #        #         #      #",
	  "#           #        #    #   ########  #   ####",
	  "# ###########        #    #        #    #      #",
	  "#      #    #######  #             #    #      #",
	  "#      #          #  #########  ####   #########",
	  "#                 #                    #       #",
	  "###############   ######## #############       #",
	  "#                 #      #       #             #",
	  "#   ###########   #      ######       #  #######",
	  "#      #                      #       #        #",
	  "#      #    ##############    ###############  #",
	  "#      #                 #            #        #",
	  "################################################"
	};

	


	int player_x;
	int player_y;
	
	// koordynaty (x,y) na owoce
	int fruit_x; 
	int fruit_y;

	int score;

	void new_game()
	{
		

		srand(time(NULL));

		// poczatkowe koordynaty gracza
		player_x = player_y = 1;
		score = 0;
		
		// losujemy koordynaty lokalizacji owoca
		fruit_x = rand() % (width-2); 
		fruit_y = rand() % (height-2);

	}

	
	

	void draw_maze()
	{
		
		at(0, 0); // ustalic kursor na koordynaty 0,0
		ink(color::dark_magenta); // wybieramy kolor labirynta
		
		// wyswietlamy kazdy rzad labirynta
		for (auto &row : maze_1) 
			cout << row << endl;


		ink(color::blue);
		cout << "Score: " << score;

		// ustalamy kolor owoca
		ink(color::red);

		// je¿eli losowe koordynaty owoca nie znajduja sie na symbole sciany labirynta
		// to ustalic symbol owoca jako 'O'
		if (maze_1[fruit_y][fruit_x] != '#') {
			for (auto &row : maze_1)
			{
				at(fruit_x, fruit_y);
				cout << 'O';

			}
		}

		// w przeciwnym przypadku ponownie losowac
		else {
			fruit_x = rand() % (width-2);
			fruit_y = rand() % (height-2);
		}

		

	}

	

	void draw_player()
	{
		// ustalamy symbol gracza '@' na poczatkowe koordynaty 0,0
		at(player_x, player_y);
		ink(color::yellow);
		cout.put('@');
	}

	//    bool is_pressed(unsigned key_code)
	//	                auto &obj = impl::Console::object();
	//	          if (obj.input_mode == mode::async_input)
	//	              	obj.parse_input_events();
	//	                return obj.kbd[key_code & 0xFF];


	void move_player()
	{


		if (is_pressed(key::left))
		{
			if (maze_1[player_y][player_x - 1] != '#') { 
				player_x--;
			}
		}

		if (is_pressed(key::right))
		{
			if (maze_1[player_y][player_x + 1] != '#') {
				player_x++;
			}
		}

		if (is_pressed(key::down))
		{
			if (maze_1[player_y + 1][player_x] != '#') {
				player_y++;
			}
		}

		if (is_pressed(key::up))
		{
			if (maze_1[player_y - 1][player_x] != '#') {
				player_y--;
			}
		}

		
		// jezeli gracz trafil na owoc to zlosowac ponownie koordynaty owoca i dodac 5 punktow do score'a
		if (player_x == fruit_x && player_y == fruit_y) {
			fruit_x = rand() % (width-2);
			fruit_y = rand() % (height-2);
			score = score + 5;

			
		}

		

	}

	

};


int main() {

	Maze labirynt;
	
	labirynt.new_game();

	

	while (!is_pressed(key::escape))
	{
		
		if (is_pressed('r')) // restart gry, powrot symbola na (0,0)
		{
			cls();
			labirynt.new_game();

			
		}

		

		
		
		labirynt.draw_maze();
		labirynt.draw_player();
		labirynt.move_player();
		

		sleep(60);

		

	}

	
	


	system("pause");
	cout << endl;
	return 0;
}