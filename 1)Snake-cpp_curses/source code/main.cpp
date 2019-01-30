#include <curses.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sys/time.h>

bool game_status;
char field[24][80],head,tail,food,direction,last_direction;
int head_pos_x,head_pos_y,last_head_pos_x[100],last_head_pos_y[100],food_position_x,food_position_y,key,score,counter,length,highscore;
unsigned int start_time, search_time, end_time;


unsigned long get_time_ms(){
  struct timeval tv;
  unsigned long time_ms;
  gettimeofday(&tv,NULL);
  time_ms = tv.tv_usec/1000 + tv.tv_sec*1000;
  return time_ms;
}

unsigned long next_game_tick;

void set_food(){
	do{
	food_position_x = rand() % 78 + 1;
	food_position_y = rand() % 22 + 1;
	}while(field[food_position_y][food_position_x] != ' ');
	field[food_position_y][food_position_x] = food;
}

void draw(){
	move(0,0);
    for (int i = 0; i < 24; ++i) {
        for (int j = 0; j < 80; ++j){
			if(field[i][j] == food)addch(field[i][j] | A_BOLD | COLOR_PAIR(2));else{
				if(field[i][j] == head)addch(field[i][j] | A_BOLD | COLOR_PAIR(3));else{
					if(field[i][j] == tail)addch(field[i][j] | COLOR_PAIR(3));else
					addch(field[i][j] | A_BOLD | COLOR_PAIR(1));
				}
			}
		}
        move(i+1,0);
    }
	attrset(A_BOLD);
	printw("SCORE: %i", score);
	printw(" ");
	printw("HIGHSCORE: %i", highscore);
	printw(" ");
	printw("TIME: %5.1f", search_time / 1000.0);
	printw("s");
	attrset(A_NORMAL);
}

void check_input(){
	key = getch();
	last_direction = direction;
	switch (key){
		case KEY_DOWN:
			if (last_direction != 'U')direction = 'D';
			break;
		case KEY_UP:
			if (last_direction != 'D')direction = 'U';
			break;
		case KEY_LEFT:
			if (last_direction != 'R')direction = 'L';
			break;
		case KEY_RIGHT:
			if (last_direction != 'L')direction = 'R';
			break;
	}
}

void init(){
	std::ifstream in("highscore.txt");
	in >> highscore;
	in.close();
	noecho();
    curs_set(0);
    start_color();
	init_pair(1, COLOR_BLUE, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_WHITE, COLOR_BLACK);
    timeout(10);
    set_escdelay(0);
    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS, NULL);
    cbreak();
    leaveok(stdscr,false);
    nonl();
	for (int i = 0; i < 24; ++i){for (int j = 0; j < 80; ++j)field[i][j]=' ';}
	for (int i = 0; i < 24; ++i)field[i][0] = '#';
	for (int i = 0; i < 24; ++i)field[i][79] = '#';
	for (int i = 1; i < 80; ++i)field[0][i] = '#';
	for (int i = 1; i < 80; ++i)field[23][i] = '#';
	start_time = clock();
	search_time = 0;
	score = 0;
	head = '@';
	tail = 'o';
	food ='O';
	head_pos_x = 15;
	head_pos_y = 11;
	counter = 0;
	length = 3;
	srand(time(NULL));
	set_food();
}

void move(){
	field[last_head_pos_y[counter - 1]][last_head_pos_x[counter - 1]] = ' ';
	field[0][0] = '#';
	last_head_pos_x[counter - 1] = head_pos_x;
	last_head_pos_y[counter - 1] = head_pos_y;
	switch (direction)
	{
	case 'L':
		head_pos_x -= 1;
		break;
	case 'R':
		head_pos_x += 1;
		break;
	case 'D':
		head_pos_y += 1;
		break;
	case 'U':
		head_pos_y -= 1;
		break;
	}field[last_head_pos_y[counter - 1]][last_head_pos_x[counter - 1]] = tail;
	if (length == counter) {
		for (int i = 1; i <= length; ++i)field[last_head_pos_y[counter - i]][last_head_pos_x[counter - i]] = tail;
	}
	if (counter == length)counter = 0;
	++counter;
}

void check_position(){
	if (field[head_pos_y][head_pos_x] == '#')game_status = false;
	if (score != 0 && field[head_pos_y][head_pos_x] == tail)game_status = false;
	if (field[head_pos_y][head_pos_x] == food){
		++score;
		++length;
		set_food();
	}
}

void update(){
	move();
	check_input();
	check_position();
	end_time = clock();
	search_time = end_time - start_time;
	field[head_pos_y][head_pos_x]=head;
}

void menu(){
	attron(A_BOLD | COLOR_PAIR(3));
	addstr("                       ______                _            \n" );
	addstr("                      / _____)              | |           \n" );
	addstr("                     ( (____   ____   _____ | |  _  _____ \n" );
	addstr("                      \\____ \\ |  _ \\ (____ || |_/ )| ___ |\n" );
	addstr("                      _____) )| | | |/ ___ ||  _ ( | ____|\n" );
	addstr("                     (______/ |_| |_|\\_____||_| \\_)|_____)\n" );
	addstr("                                                          \n" );
	attron(A_BLINK |COLOR_PAIR(4));
	addstr("                         Press ENTER to start new game\n");
	while (true) {
		key = getch();
		if (key == 13) {
			game_status = true;
			attrset(A_NORMAL);
			break;
		}
	}
}

void end_game(){
	clear();
	attron(A_BOLD | COLOR_PAIR(3));
	addstr("                       ______                _            \n" );
	addstr("                      / _____)              | |           \n" );
	addstr("                     ( (____   ____   _____ | |  _  _____ \n" );
	addstr("                      \\____ \\ |  _ \\ (____ || |_/ )| ___ |\n" );
	addstr("                      _____) )| | | |/ ___ ||  _ ( | ____|\n" );
	addstr("                     (______/ |_| |_|\\_____||_| \\_)|_____)\n" );
	addstr("                                                          \n" );
	printw("\n");
	if (score > highscore) {
		highscore = score;
		attron(A_BOLD | COLOR_PAIR(4));
		printw("                           Your new highscore: ");
		attron(A_BOLD | COLOR_PAIR(2));
		printw("%i", highscore);
		printw("\n");
		printw("\n");
		std::ofstream out("highscore.txt");
		out << highscore;
		out.close();
	}
	attron(A_BLINK | A_BOLD | COLOR_PAIR(4));
	addstr("                     Press ENTER to restart,or ESC to exit");
	do {
		key = getch();
		if (key == 13) {
			game_status = true;
			direction = ' ';
			attrset(A_NORMAL);
		}
	} while ((key != 27) and (key != 13));
}

int main(){
	
	initscr();
	init();
	menu();
	while(game_status){
		init();
		while(game_status){
			update();
			next_game_tick = get_time_ms()+140;
			while( get_time_ms() < next_game_tick)draw();
		}
		end_game();
	}
	endwin();
	return 0;
}
