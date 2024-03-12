#ifndef TETRIS_HPP
#define TETRIS_HPP

//GAME AREA SIZE
const int X = 20;
const int Y = 11;

struct Point // a structure containing the coordinates of a point
{
	int x, y;
};

// CLASS TETRIS 
class Tetris
{
private:
	int m_color; // a color drawn for the figure
	int m_next_color; // a color drawn for the next figure
	int m_fig; // a drawn figure

	int m_game_area[X][Y]; // game of field, all figures 

	Point m_Point_position[4]; // indicates the current position of the point in the game area
	Point m_Point_pos_temp[4]; // used for copying values from Point_Position
	Point m_Point_next_figure[4]; // indicates the point at which the next figure is displayed
	Point m_Centre; //indicates the center of the figure, used to rotating figures

	int m_figures[7][4]; // seven different figures

public:
	/**********  constructor  **********/
	Tetris(void);

	/**********  getters and setters  **********/
	int get_color(void) const;
	void set_color(int new_color);
	int get_next_color(void) const;
	void set_next_color(int new_color);
	int get_fig(void) const;
	void set_fig(int new_fig);
	Point* get_Point_position(void);
	Point* get_Point_next_figure(void);
	int** get_game_area(void);

	/**********  check if it is possible to move the figure  **********/
	bool move_check();

	/**********  check if it is possible to rotate the figure  **********/
	bool rotation_check();

	/**********  <- MOVING -> control a figure left or right with the arrow keys  **********/
	void move_position(int x_position);

	/**********  ^ ROTATION ^ rotate the figure with the top arrow key **********/
	void rotate_figure(void);

	/**********  v FASTER FALLING v faster figure fall with the low arrow key **********/
	void fast_falling(void);

	/**********  check if the figure can move down or must stop  **********/
	bool point_in_free_area();

	/**********  check if the game is over  **********/
	bool end_game_check();

	/**********  clear value of game area  **********/
	void clear_game_area(void);

	/**********  the function returns the row that is complete. if the row is not complete it returns 0  **********/
	int which_row_is_full();

	/**********  deletes the specified row and moves the playing field one position  **********/
	void clear_row(int row);

	/**********  creates consecutive random shapes for the next iterations  **********/
	void create_figures(void);

};

#endif