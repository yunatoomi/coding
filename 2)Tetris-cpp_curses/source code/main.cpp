#include <curses.h>
#include <sys/time.h>
#include <cstdlib>
#include <ctype.h>
#include <fstream>

unsigned long next_game_tick,next_tick;
bool game_status,motion,free_space_down,free_space_left,free_space_right,free_space_4_rotate,dropf,down,game_over,sr;
char field[25][12],direction,last_direction,fs,mino;
int key,fig,next_fig,y,x,ctr,maxi,jmaxi,dj,di,mini,jmini,delay,block_position,fmi,position_4_rotate,ctr1,bb,highscore,score;

unsigned long get_time_ms(){
  struct timeval tv;
  unsigned long time_ms;
  gettimeofday(&tv,NULL);
  time_ms = tv.tv_usec/1000 + tv.tv_sec*1000;
  return time_ms;
}

void init(){
	std::ifstream in("highscore_tetris.txt");
	in >> highscore;
	in.close();
	noecho();
    curs_set(0);
    start_color();
	init_pair(1, COLOR_BLUE, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_WHITE, COLOR_BLACK);
	init_pair(5, COLOR_YELLOW, COLOR_BLACK);
	init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(7, COLOR_CYAN, COLOR_BLACK);
    timeout(200);
    set_escdelay(0);
    keypad(stdscr, TRUE);
	mousemask(ALL_MOUSE_EVENTS, NULL);
    cbreak();
    leaveok(stdscr,false);
    nonl();
	srand(time(NULL));
	fs = '.';
	for (int i = 0; i < 25; ++i){for (int j = 0; j < 12; ++j)field[i][j]=fs;}
	for (int i = 0; i < 25; ++i)field[i][0] = '#';
	for (int i = 0; i < 25; ++i)field[i][11] = '#';
	for (int i = 1; i < 12; ++i)field[24][i] = '#';
	y = 0;
	ctr = 0;
	mino = 'O';
	next_fig = rand() % 7 +1;
	motion = false;
	maxi = 0;
	fmi = 0;
	mini = 999;
	delay = 50;
	ctr1=0;
	direction = 'q';
	dropf = false;
}

void find_maxi(){
	for (int i = 0; i < 25; ++i){
		for (int j = 0; j < 12; ++j){
			if ((field[i][j] != fs) && (field[i][j] != '#')) {
				if((field[i][j] == 'i') || (field[i][j] == 'o') || (field[i][j] == 's') || (field[i][j] == 'z') || (field[i][j] == 't') || (field[i][j] == 'g') || (field[i][j] == 'h')){
					if(i>=maxi){
						maxi = i;
						jmaxi = j;
					}
				}
			}
		}	
	}
}

void new_fig(){
	fig = next_fig;
	switch (fig){
		case 1:
			field[0][5]='i';
			field[1][5]='i';
			field[2][5]='i';
			field[3][5]='i';
			
			break;
		case 2:
			field[2][5]='o';
			field[2][6]='o';
			field[3][5]='o';
			field[3][6]='o';
			break;
		case 3:
			field[1][5]='s';
			field[2][5]='s';
			field[2][6]='s';
			field[3][6]='s';
			break;
		case 4:
			field[1][6]='z';
			field[2][6]='z';
			field[2][5]='z';
			field[3][5]='z';
			break;
		case 5:
			field[1][5]='t';
			field[2][5]='t';
			field[3][5]='t';
			field[2][6]='t';
			break;
		case 6:
			field[1][5]='g';
			field[2][5]='g';
			field[3][5]='g';
			field[1][6]='g';
			break;
		case 7:
			field[1][5]='h';
			field[1][6]='h';
			field[2][6]='h';
			field[3][6]='h';
			break;
	}
	motion = true;
	free_space_down = true;
	free_space_left = true;
	free_space_right = true;
	block_position = 1;
	next_fig = rand() % 7 +1;
}

void check_free_space_down(){
	free_space_down = true;
	find_maxi();
	switch(fig){
		case 1:
			if(block_position==1){
				if(field[maxi+1][jmaxi] != fs)free_space_down = false;
			}else{
				if((field[maxi+1][jmaxi] != fs) || (field[maxi+1][jmaxi-1] != fs) || (field[maxi+1][jmaxi-2] != fs) || (field[maxi+1][jmaxi-3] != fs))free_space_down = false;
			}
			break;
		case 2:
			if((field[maxi+1][jmaxi] != fs) || (field[maxi+1][jmaxi-1] != fs))free_space_down = false;
			break;
		case 3:
			if(block_position==1){
				if((field[maxi+1][jmaxi] != fs) || (field[maxi][jmaxi-1] != fs))free_space_down = false;
			}else{
				if((field[maxi+1][jmaxi] != fs) || (field[maxi+1][jmaxi-1] != fs) || (field[maxi][jmaxi+1] != fs))free_space_down = false;
			}
			break;
		case 4:
			if(block_position==1){
				if((field[maxi+1][jmaxi] != fs) || (field[maxi][jmaxi+1] != fs))free_space_down = false;
			}else{
				if((field[maxi+1][jmaxi] != fs) || (field[maxi+1][jmaxi-1] != fs) || (field[maxi][jmaxi-2] != fs))free_space_down = false;
			}
			break;
		case 5:
			switch(block_position){
				case 1:
					if((field[maxi+1][jmaxi] != fs) || (field[maxi][jmaxi+1] != fs))free_space_down = false;
					break;
				case 2:
					if((field[maxi+1][jmaxi] != fs) || (field[maxi+1][jmaxi-1] != fs) || (field[maxi+1][jmaxi-2] != fs))free_space_down = false;
					break;
				case 3:
					if((field[maxi+1][jmaxi] != fs) || (field[maxi][jmaxi-1] != fs))free_space_down = false;
					break;
				case 4:
					if((field[maxi+1][jmaxi] != fs) || (field[maxi][jmaxi-1] != fs) || (field[maxi][jmaxi+1] != fs))free_space_down = false;
					break;
			}
			break;
		case 6:
			switch(block_position){
				case 1:
					if((field[maxi+1][jmaxi] != fs) || (field[maxi-1][jmaxi+1] != fs))free_space_down = false;
					break;
				case 2:
					if((field[maxi+1][jmaxi] != fs) || (field[maxi][jmaxi-1] != fs) || (field[maxi][jmaxi-2] != fs))free_space_down = false;
					break;
				case 3:
					if((field[maxi+1][jmaxi] != fs) || (field[maxi+1][jmaxi-1] != fs))free_space_down = false;
					break;
				case 4:
					if((field[maxi+1][jmaxi] != fs) || (field[maxi+1][jmaxi-1] != fs) || (field[maxi+1][jmaxi-2] != fs))free_space_down = false;
					break;
			}
			break;
		case 7:
			switch(block_position){
				case 1:
					if((field[maxi+1][jmaxi] != fs) || (field[maxi-1][jmaxi-1] != fs))free_space_down = false;
					break;
				case 2:
					if((field[maxi+1][jmaxi] != fs) || (field[maxi+1][jmaxi-1] != fs) || (field[maxi+1][jmaxi-2] != fs))free_space_down = false;
					break;
				case 3:
					if((field[maxi+1][jmaxi] != fs) || (field[maxi+1][jmaxi-1] != fs))free_space_down = false;
					break;
				case 4:
					if((field[maxi+1][jmaxi] != fs) || (field[maxi][jmaxi+1] != fs) || (field[maxi][jmaxi+2] != fs))free_space_down = false;
					break;
			}			
			break;
	}
	maxi=0;
	jmaxi=0;
}

void check_free_space_left(){
	free_space_left = true;
	find_maxi();
	switch(fig){
		case 1:
			if(block_position==1){
				if((field[maxi][jmaxi-1] != fs) || (field[maxi-1][jmaxi-1] != fs) || (field[maxi-2][jmaxi-1] != fs) || (field[maxi-3][jmaxi-1] != fs))free_space_left = false;
			}else{
				if(field[maxi][jmaxi-4] != fs)free_space_left = false;
			}
			break;
		case 2:
			if((field[maxi-1][jmaxi-2] != fs) || (field[maxi][jmaxi-2] != fs))free_space_left = false;
			break;
		case 3:
			if(block_position==1){
				if((field[maxi-2][jmaxi-2] != fs) || (field[maxi-1][jmaxi-2] != fs) || (field[maxi][jmaxi-1] != fs))free_space_left = false;
			}else{
				if((field[maxi-1][jmaxi-1] != fs) || (field[maxi][jmaxi-2] != fs))free_space_left = false;
			}
			break;
		case 4:
			if(block_position==1){
				if((field[maxi-2][jmaxi] != fs) || (field[maxi-1][jmaxi-1] != fs) || (field[maxi][jmaxi-1] != fs))free_space_left = false;
			}else{
				if((field[maxi][jmaxi-2] != fs) || (field[maxi-2][jmaxi-3] != fs))free_space_left = false;
			}
			break;
		case 5:
			switch(block_position){
				case 1:
					if((field[maxi-2][jmaxi-1] != fs) || (field[maxi-1][jmaxi-1] != fs) || (field[maxi][jmaxi-1] != fs))free_space_left = false;
					break;
				case 2:
					if((field[maxi-1][jmaxi-2] != fs) || (field[maxi][jmaxi-3] != fs))free_space_left = false;
					break;
				case 3:
					if((field[maxi-2][jmaxi-1] != fs) || (field[maxi-1][jmaxi-2] != fs) || (field[maxi][jmaxi-1] != fs))free_space_left = false;
					break;
				case 4:
					if((field[maxi-1][jmaxi-2] != fs) || (field[maxi][jmaxi-1] != fs))free_space_left = false;
					break;
			}
			break;
		case 6:
			switch(block_position){
				case 1:
					if((field[maxi-2][jmaxi-1] != fs) || (field[maxi-1][jmaxi-1] != fs) || (field[maxi][jmaxi-1] != fs))free_space_left = false;
					break;
				case 2:
					if((field[maxi-1][jmaxi-3] != fs) || (field[maxi][jmaxi-1] != fs))free_space_left = false;
					break;
				case 3:
					if((field[maxi-1][jmaxi-1] != fs) || (field[maxi-2][jmaxi-1] != fs) || (field[maxi][jmaxi-2] != fs))free_space_left = false;
					break;
				case 4:
					if((field[maxi-1][jmaxi-3] != fs) || (field[maxi][jmaxi-3] != fs))free_space_left = false;
					break;
			}
			break;
		case 7:
			switch(block_position){
				case 1:
					if((field[maxi-2][jmaxi-2] != fs) || (field[maxi-1][jmaxi-1] != fs) || (field[maxi][jmaxi-1] != fs))free_space_left = false;
					break;
				case 2:
					if((field[maxi][jmaxi-3] != fs) || (field[maxi-1][jmaxi-1] != fs))free_space_left = false;
					break;
				case 3:
					if((field[maxi-1][jmaxi-2] != fs) || (field[maxi-2][jmaxi-2] != fs) || (field[maxi][jmaxi-2] != fs))free_space_left = false;
					break;
				case 4:
					if((field[maxi-1][jmaxi-1] != fs) || (field[maxi][jmaxi-1] != fs))free_space_left = false;
					break;
			}
			break;
	}
	maxi=0;
	jmaxi=0;
}

void check_free_space_right(){
	free_space_right = true;
	find_maxi();
	switch(fig){
		case 1:
			if(block_position==1){
				if((field[maxi][jmaxi+1] != fs) || (field[maxi-1][jmaxi+1] != fs) || (field[maxi-2][jmaxi+1] != fs) || (field[maxi-3][jmaxi+1] != fs))free_space_right = false;
			}else{
				if(field[maxi][jmaxi+1] != fs)free_space_right = false;
			}
			break;
		case 2:
			if((field[maxi-1][jmaxi+1] != fs) || (field[maxi][jmaxi+1] != fs))free_space_right = false;
			break;
		case 3:
			if(block_position==1){
				if((field[maxi-2][jmaxi] != fs) || (field[maxi-1][jmaxi+1] != fs) || (field[maxi][jmaxi+1] != fs))free_space_right = false;
			}else{
				if((field[maxi-1][jmaxi+2] != fs) || (field[maxi][jmaxi+1] != fs))free_space_right = false;
			}
			break;
		case 4:
			if(block_position==1){
				if((field[maxi-2][jmaxi+2] != fs) || (field[maxi-1][jmaxi+2] != fs) || (field[maxi][jmaxi+1] != fs))free_space_right = false;
			}else{
				if((field[maxi-1][jmaxi] != fs) || (field[maxi][jmaxi+1] != fs))free_space_right = false;
			}
			break;
		case 5:
		switch(block_position){
				case 1:
					if((field[maxi-2][jmaxi+1] != fs) || (field[maxi-1][jmaxi+2] != fs) || (field[maxi][jmaxi+1] != fs))free_space_right = false;
					break;
				case 2:
					if((field[maxi-1][jmaxi] != fs) || (field[maxi][jmaxi+1] != fs))free_space_right = false;
					break;
				case 3:
					if((field[maxi-2][jmaxi+1] != fs) || (field[maxi-1][jmaxi+1] != fs) || (field[maxi][jmaxi+1] != fs))free_space_right = false;
					break;
				case 4:
					if((field[maxi-1][jmaxi+2] != fs) || (field[maxi][jmaxi+1] != fs))free_space_right = false;
					break;
			}
			break;
		case 6:
			switch(block_position){
				case 1:
					if((field[maxi-2][jmaxi+2] != fs) || (field[maxi-1][jmaxi+1] != fs) || (field[maxi][jmaxi+1] != fs))free_space_right = false;
					break;
				case 2:
					if((field[maxi-1][jmaxi+1] != fs) || (field[maxi][jmaxi+1] != fs))free_space_right = false;
					break;
				case 3:
					if((field[maxi-2][jmaxi+1] != fs) || (field[maxi-1][jmaxi+1] != fs) || (field[maxi][jmaxi+1] != fs))free_space_right = false;
					break;
				case 4:
					if((field[maxi-1][jmaxi-1] != fs) || (field[maxi][jmaxi+1] != fs))free_space_right = false;
					break;
			}
			break;
		case 7:
			switch(block_position){
				case 1:
					if((field[maxi-2][jmaxi+1] != fs) || (field[maxi-1][jmaxi+1] != fs) || (field[maxi][jmaxi+1] != fs))free_space_right = false;
					break;
				case 2:
					if((field[maxi-1][jmaxi+1] != fs) || (field[maxi][jmaxi+1] != fs))free_space_right = false;
					break;
				case 3:
					if((field[maxi-2][jmaxi] != fs) || (field[maxi-1][jmaxi] != fs) || (field[maxi][jmaxi+1] != fs))free_space_right = false;
					break;
				case 4:
					if((field[maxi-1][jmaxi+3] != fs) || (field[maxi][jmaxi+1] != fs))free_space_right = false;
					break;
			}
			break;
	}
	maxi=0;
	jmaxi=0;
}

void move_full_rows_down(int qq){
	for(int i = qq; i >= 0; --i){
		for(int j = 12; j >= 0; --j){
			if ((field[i][j] != fs) && (field[i][j] != '#')) {
				if((field[i][j] == 'I') || (field[i][j] == 'O') || (field[i][j] == 'S') || (field[i][j] == 'Z') || (field[i][j] == 'T') || (field[i][j] == 'G') || (field[i][j] == 'H')){
					if(field[i+1][j] == fs){
						field[i+1][j] = field[i][j];
						field[i][j] = fs;
					}
				}
			}
		}
	}
}

void check_free_space_4_rotate(){
	free_space_4_rotate = false;
	find_maxi();
	switch(fig){
		case 1:
			if(block_position==1){
				if((field[maxi-2][jmaxi+1] == fs) && (field[maxi-2][jmaxi-1] == fs) && (field[maxi-2][jmaxi-2] == fs)){
					free_space_4_rotate = true;
					position_4_rotate = 1;
				}else{
					if((field[maxi-2][jmaxi+1] == fs) && (field[maxi-2][jmaxi-1] == fs) && (field[maxi-2][jmaxi+2] == fs)){
						free_space_4_rotate = true;
						position_4_rotate = 2;
					}else{
						if((field[maxi-2][jmaxi-1] == fs) && (field[maxi-2][jmaxi-2] == fs) && (field[maxi-2][jmaxi-3] == fs)){
							free_space_4_rotate = true;
							position_4_rotate = 3;
						}else{
							if((field[maxi-2][jmaxi+1] == fs) && (field[maxi-2][jmaxi+3] == fs) && (field[maxi-2][jmaxi+2] == fs)){
								free_space_4_rotate = true;
								position_4_rotate = 4;
							}
						}
					}
				}
			}else{
				if((field[maxi-3][jmaxi-2] == fs) && (field[maxi-2][jmaxi-2] == fs) && (field[maxi-1][jmaxi-2] == fs)){
					free_space_4_rotate = true;
					position_4_rotate = 1;
				}else{
					if((field[maxi-3][jmaxi-1] == fs) && (field[maxi-2][jmaxi-1] == fs) && (field[maxi-1][jmaxi-1] == fs)){
						free_space_4_rotate = true;
						position_4_rotate = 2;
					}else{
						if((field[maxi-3][jmaxi-3] == fs) && (field[maxi-2][jmaxi-3] == fs) && (field[maxi-1][jmaxi-3] == fs)){
							free_space_4_rotate = true;
							position_4_rotate = 3;
						}else{
							if((field[maxi-1][jmaxi] == fs) && (field[maxi-2][jmaxi] == fs) && (field[maxi-3][jmaxi] == fs)){
								free_space_4_rotate = true;
								position_4_rotate = 4;
							}
						}
					}
				}
			}
			break;
		case 3:
			if(block_position==1){
				if(field[maxi-1][jmaxi-2] == fs)free_space_4_rotate = true;
			}else{
				free_space_4_rotate = true;
			}
			break;
		case 4:
			if(block_position==1){
				if(field[maxi-2][jmaxi-1] == fs)free_space_4_rotate = true;
			}else{
				free_space_4_rotate = true;
			}
			break;
		case 5:
			switch(block_position){
				case 1:
					if((field[maxi-2][jmaxi+1] == fs) && (field[maxi-1][jmaxi+2] == fs))free_space_4_rotate = true;
					break;
				case 2:
					if((field[maxi-2][jmaxi] == fs) && (field[maxi-1][jmaxi] == fs))free_space_4_rotate = true;
					break;
				case 3:
					if((field[maxi-2][jmaxi-1] == fs) && (field[maxi-2][jmaxi-2] == fs))free_space_4_rotate = true;
					break;
				case 4:
					if((field[maxi][jmaxi-1] == fs) && (field[maxi+1][jmaxi-1] == fs))free_space_4_rotate = true;
					break;
			}
			break;
		case 6:
			switch(block_position){
				case 1:
					if((field[maxi-2][jmaxi-1] == fs) && (field[maxi-1][jmaxi+1] == fs))free_space_4_rotate = true;
					break;
				case 2:
					if((field[maxi-2][jmaxi] == fs) && (field[maxi-3][jmaxi] == fs))free_space_4_rotate = true;
					break;
				case 3:
					if((field[maxi-1][jmaxi-1] == fs) && (field[maxi-1][jmaxi+1] == fs) && (field[maxi-2][jmaxi-1] == fs))free_space_4_rotate = true;
					break;
				case 4:
					if((field[maxi-1][jmaxi-1] == fs) && (field[maxi-2][jmaxi-1] == fs) && (field[maxi-2][jmaxi] == fs))free_space_4_rotate = true;
					break;
			}
			break;
		case 7:
			switch(block_position){
				case 1:
					if((field[maxi-1][jmaxi-1] == fs) && (field[maxi-1][jmaxi-2] == fs))free_space_4_rotate = true;
					break;
				case 2:
					if((field[maxi-2][jmaxi-1] == fs) && (field[maxi-1][jmaxi-1] == fs))free_space_4_rotate = true;
					break;
				case 3:
					if((field[maxi-1][jmaxi] == fs) && (field[maxi-1][jmaxi+1] == fs))free_space_4_rotate = true;
					break;
				case 4:
					if((field[maxi-2][jmaxi] == fs) && (field[maxi-2][jmaxi+1] == fs) && (field[maxi][jmaxi+1] == fs))free_space_4_rotate = true;
					break;
			}
			break;
		
	}
	maxi=0;
	jmaxi=0;
}

void destroy(int q){
	for(int k = 1;k<=10;++k)field[q][k] = fs;
	score = score+10;
	move_full_rows_down(q);
}

void check_rows(){
	for (int i = 0; i < 25; ++i){
		for (int j = 0; j < 12; ++j){
			if ((field[i][j] != fs) && (field[i][j] != '#')) {
				if((field[i][j] == 'I') || (field[i][j] == 'O') || (field[i][j] == 'S') || (field[i][j] == 'Z') || (field[i][j] == 'T') || (field[i][j] == 'G') || (field[i][j] == 'H')){
					++ctr1;
				}
			}
		}
		if(ctr1 == 10)destroy(i);
		ctr1=0;
	}
}

void move_down(){
	for(int i = 25; i >= 0; --i){
		for(int j = 12; j >= 0; --j){
			if ((field[i][j] != fs) && (field[i][j] != '#')) {
				if((field[i][j] == 'i') || (field[i][j] == 'o') || (field[i][j] == 's') || (field[i][j] == 'z') || (field[i][j] == 't') || (field[i][j] == 'g') || (field[i][j] == 'h')){
					field[i+1][j] = field[i][j];
					field[i][j] = fs;
				}
			}
		}
	}
}

void move_right(){
	check_free_space_right();
	if(free_space_right){
		for (int i = 0; i < 25; ++i){
				for(int j = 12; j >= 0; --j){
					if ((field[i][j] != fs) && (field[i][j] != '#')) {
						if((field[i][j] == 'i') || (field[i][j] == 'o') || (field[i][j] == 's') || (field[i][j] == 'z') || (field[i][j] == 't') || (field[i][j] == 'g') || (field[i][j] == 'h')){
							field[i][j+1] = field[i][j];
							field[i][j] = fs;
						}
					}
				}
			}
		last_direction = direction;
		direction = 'q';
	}
}

void move_left(){
	check_free_space_left();
	if (free_space_left){
		for (int i = 0; i < 25; ++i){
			for (int j = 0; j < 12; ++j){
				if ((field[i][j] != fs) && (field[i][j] != '#')) {
					if((field[i][j] == 'i') || (field[i][j] == 'o') || (field[i][j] == 's') || (field[i][j] == 'z') || (field[i][j] == 't') || (field[i][j] == 'g') || (field[i][j] == 'h')){
						field[i][j-1] = field[i][j];
						field[i][j] = fs;
					}
				}
			}
		}
	}
	last_direction = direction;
	direction = 'q';
}

void move_stop(){
	for (int i = 0; i < 25; ++i){
			for (int j = 0; j < 12; ++j){
				if ((field[i][j] != fs) && (field[i][j] != '#')) {
					field[i][j] = toupper(field[i][j]);
				}
			}
		}
		motion = false;
}

void rotate(){
	check_free_space_4_rotate();
	if(free_space_4_rotate){
		find_maxi();
		switch(fig){
		case 1:
			if(block_position==1){
				switch(position_4_rotate){
					case 1:
						field[maxi][jmaxi]=fs;
						field[maxi-1][jmaxi]=fs;
						field[maxi-3][jmaxi]=fs;
						field[maxi-2][jmaxi+1]='i';
						field[maxi-2][jmaxi-1]='i';
						field[maxi-2][jmaxi-2]='i';
						break;
					case 2:
						field[maxi][jmaxi]=fs;
						field[maxi-1][jmaxi]=fs;
						field[maxi-3][jmaxi]=fs;
						field[maxi-2][jmaxi+1]='i';
						field[maxi-2][jmaxi-1]='i';
						field[maxi-2][jmaxi+2]='i';
						break;
					case 3:
						field[maxi][jmaxi]=fs;
						field[maxi-1][jmaxi]=fs;
						field[maxi-3][jmaxi]=fs;
						field[maxi-2][jmaxi-3]='i';
						field[maxi-2][jmaxi-1]='i';
						field[maxi-2][jmaxi-2]='i';
						break;
					case 4:
						field[maxi][jmaxi]=fs;
						field[maxi-1][jmaxi]=fs;
						field[maxi-3][jmaxi]=fs;
						field[maxi-2][jmaxi+1]='i';
						field[maxi-2][jmaxi+3]='i';
						field[maxi-2][jmaxi+2]='i';
						break;
				}
				block_position=2;
			}else{
				switch(position_4_rotate){
					case 1:
						field[maxi][jmaxi]=fs;
						field[maxi][jmaxi-1]=fs;
						field[maxi][jmaxi-3]=fs;
						field[maxi-3][jmaxi-2]='i';
						field[maxi-2][jmaxi-2]='i';
						field[maxi-1][jmaxi-2]='i';
						break;
					case 2:
						field[maxi][jmaxi]=fs;
						field[maxi][jmaxi-2]=fs;
						field[maxi][jmaxi-3]=fs;
						field[maxi-3][jmaxi-1]='i';
						field[maxi-2][jmaxi-1]='i';
						field[maxi-1][jmaxi-1]='i';
						break;
					case 3:
						field[maxi][jmaxi]=fs;
						field[maxi][jmaxi-1]=fs;
						field[maxi][jmaxi-2]=fs;
						field[maxi-3][jmaxi-3]='i';
						field[maxi-2][jmaxi-3]='i';
						field[maxi-1][jmaxi-3]='i';
						break;
					case 4:
						field[maxi][jmaxi-1]=fs;
						field[maxi][jmaxi-2]=fs;
						field[maxi][jmaxi-3]=fs;
						field[maxi-1][jmaxi]='i';
						field[maxi-2][jmaxi]='i';
						field[maxi-3][jmaxi]='i';
						break;
				}
				block_position=1;
			}
			break;
		case 3:
			if(block_position==1){
				field[maxi][jmaxi]=fs;
				field[maxi-1][jmaxi]=fs;
				field[maxi-1][jmaxi-2]='s';
				field[maxi-2][jmaxi]='s';
				block_position=2;
			}else{
				field[maxi][jmaxi-1]=fs;
				field[maxi-1][jmaxi+1]=fs;
				field[maxi-1][jmaxi-1]='s';
				field[maxi-2][jmaxi-1]='s';
				block_position=1;
			}
			break;
		case 4:
			if(block_position==1){
				field[maxi][jmaxi]=fs;
				field[maxi-2][jmaxi+1]=fs;
				field[maxi-2][jmaxi-1]='z';
				field[maxi-2][jmaxi]='z';
				block_position=2;
			}else{
				field[maxi][jmaxi]=fs;
				field[maxi-1][jmaxi-2]=fs;
				field[maxi-1][jmaxi]='z';
				field[maxi-2][jmaxi]='z';
				block_position=1;
			}
			break;
		case 5:
			switch(block_position){
				case 1:
					field[maxi][jmaxi]=fs;
					field[maxi-2][jmaxi]=fs;
					field[maxi-1][jmaxi+2]='t';
					field[maxi-2][jmaxi+1]='t';
					block_position=2;
					break;
				case 2:
					field[maxi][jmaxi-1]=fs;
					field[maxi][jmaxi-2]=fs;
					field[maxi-1][jmaxi]='t';
					field[maxi-2][jmaxi]='t';
					block_position=3;
					break;
				case 3:
					field[maxi][jmaxi]=fs;
					field[maxi-1][jmaxi]=fs;
					field[maxi-2][jmaxi-2]='t';
					field[maxi-2][jmaxi-1]='t';
					block_position=4;
					break;
				case 4:
					field[maxi-1][jmaxi]=fs;
					field[maxi-1][jmaxi+1]=fs;
					field[maxi][jmaxi-1]='t';
					field[maxi+1][jmaxi-1]='t';
					block_position=1;
					break;
			}
			break;
		case 6:
			switch(block_position){
				case 1:
					field[maxi][jmaxi]=fs;
					field[maxi-1][jmaxi]=fs;
					field[maxi-1][jmaxi+1]='g';
					field[maxi-2][jmaxi-1]='g';
					block_position=2;
					break;
				case 2:
					field[maxi][jmaxi]=fs;
					field[maxi-1][jmaxi-2]=fs;
					field[maxi-3][jmaxi]='g';
					field[maxi-2][jmaxi]='g';
					block_position=3;
					break;
				case 3:
					field[maxi][jmaxi]=fs;
					field[maxi][jmaxi-1]=fs;
					field[maxi-2][jmaxi]=fs;
					field[maxi-1][jmaxi+1]='g';
					field[maxi-1][jmaxi-1]='g';
					field[maxi-2][jmaxi-1]='g';
					block_position=4;
					break;
				case 4:
					field[maxi][jmaxi]=fs;
					field[maxi][jmaxi-2]=fs;
					field[maxi-1][jmaxi-2]=fs;
					field[maxi-1][jmaxi-1]='g';
					field[maxi-2][jmaxi-1]='g';
					field[maxi-2][jmaxi]='g';
					block_position=1;
					break;
			}
			break;
		case 7:
			switch(block_position){
				case 1:
					field[maxi][jmaxi]=fs;
					field[maxi-2][jmaxi-1]=fs;
					field[maxi-1][jmaxi-1]='h';
					field[maxi-1][jmaxi-2]='h';
					block_position=2;
					break;
				case 2:
					field[maxi-1][jmaxi]=fs;
					field[maxi][jmaxi-2]=fs;
					field[maxi-1][jmaxi-1]='h';
					field[maxi-2][jmaxi-1]='h';
					block_position=3;
					break;
				case 3:
					field[maxi][jmaxi]=fs;
					field[maxi-2][jmaxi-1]=fs;
					field[maxi-1][jmaxi]='h';
					field[maxi-1][jmaxi+1]='h';
					block_position=4;
					break;
				case 4:
					field[maxi][jmaxi]=fs;
					field[maxi-1][jmaxi]=fs;
					field[maxi-1][jmaxi+2]=fs;
					field[maxi][jmaxi+1]='h';
					field[maxi-2][jmaxi]='h';
					field[maxi-2][jmaxi+1]='h';
					block_position=1;
					break;
			}
			break;
		}
		maxi=0;
		jmaxi=0;
	}
	last_direction = direction;
	direction = 'q';
}

void drop(){
	dropf = true;
	last_direction = direction;
	direction = 'q';
}

void move(){
	switch (direction){
		case 'L':
			move_left();
			break;
		case 'R':
			move_right();
			break;
		case ' ':
			rotate();
			break;
	}
	check_free_space_down();
	if (free_space_down)move_down();
	if (!free_space_down)move_stop();
}

void check_game_status(){
	for (int i = 0; i < 25; ++i){
		for (int j = 0; j < 12; ++j){
			if ((field[i][j] != fs) && (field[i][j] != '#')) {
				if((field[i][j] == 'I') || (field[i][j] == 'O') || (field[i][j] == 'S') || (field[i][j] == 'Z') || (field[i][j] == 'T') || (field[i][j] == 'G') || (field[i][j] == 'H')){
					if(i<mini){
						mini = i;
						jmini = j;
					}
				}
			}
		}
	}
	if(mini<=4)game_status=false;
	mini = 999;
}

void update(){
	if (motion != true)new_fig();
	move();
	check_rows();
	check_game_status();
}

void draw(){
	move(0,0);
    for (int i = 4; i < 25; ++i) {
        for (int j = 0; j < 12; ++j){
			if((field[i][j] == 'i') || (field[i][j] == 'I')){
				addch('O' | A_BOLD | COLOR_PAIR(3));
			}
			else{
				if ((field[i][j] == 'o') || (field[i][j] == 'O')){
					addch('O' | A_BOLD | COLOR_PAIR(5));
				}else{
					if ((field[i][j] == 's') || (field[i][j] == 'z') || (field[i][j] == 'Z') || (field[i][j] == 'S')){
					addch('O' | A_BOLD | COLOR_PAIR(2));
					}else{
						if ((field[i][j] == 'g') || (field[i][j] == 'G') || (field[i][j] == 'h') || (field[i][j] == 'H')){
							addch('O' | A_BOLD | COLOR_PAIR(7));
						}else{
							if ((field[i][j] == 't') || (field[i][j] == 'T')){
								addch('O' | A_BOLD | COLOR_PAIR(6));
							}else{
								addch(field[i][j] | A_BOLD | COLOR_PAIR(1));
							}
						}
					}
				}
			}
		}
		addch('\n');
	}
	
	move(3,14);
	attron(A_BOLD | COLOR_PAIR(4));
	addstr("Next figure:");
	switch(next_fig){
		case 1:
			attron(A_BOLD | COLOR_PAIR(3));
			mvaddch(5,19,mino);
			mvaddch(6,19,mino);
			mvaddch(7,19,mino);
			mvaddch(8,19,mino);
			break;
		case 2:
			attron(A_BOLD | COLOR_PAIR(5));
			mvaddch(5,19,mino);
			mvaddch(6,19,mino);
			mvaddch(5,20,mino);
			mvaddch(6,20,mino);
			break;
		case 3:
			attron(A_BOLD | COLOR_PAIR(2));
			mvaddch(5,19,mino);
			mvaddch(6,19,mino);
			mvaddch(6,20,mino);
			mvaddch(7,20,mino);
			break;
		case 4:
			attron(A_BOLD | COLOR_PAIR(2));
			mvaddch(6,19,mino);
			mvaddch(7,19,mino);
			mvaddch(5,20,mino);
			mvaddch(6,20,mino);
			break;
		case 5:
			attron(A_BOLD | COLOR_PAIR(6));
			mvaddch(5,19,mino);
			mvaddch(6,19,mino);
			mvaddch(7,19,mino);
			mvaddch(6,20,mino);
			break;
		case 6:
			attron(A_BOLD | COLOR_PAIR(7));
			mvaddch(5,19,mino);
			mvaddch(6,19,mino);
			mvaddch(7,19,mino);
			mvaddch(5,20,mino);
			break;
		case 7:
			attron(A_BOLD | COLOR_PAIR(7));
			mvaddch(5,20,mino);
			mvaddch(6,20,mino);
			mvaddch(7,20,mino);
			mvaddch(5,19,mino);
			break;
	}
	attron(A_BOLD | COLOR_PAIR(4));
	move(19,13);
	printw("SCORE: %i", score);
	move(20,13);
	printw("HIGHSCORE: %i", highscore);
}

void process_input(){
	next_tick = get_time_ms()+200;
	key = getch();
	switch (key){
		case KEY_LEFT:
			direction = 'L';
			break;
		case KEY_RIGHT:
			direction = 'R';
			break;
		case KEY_DOWN:
			goto ex;
			break;
		case 32://KEY_SPACE
			direction = ' ';
			break;
	}
	
	while( get_time_ms() < next_tick);
	ex:
	bb = 0;
}

void menu(){
	init();
	move(0,0);
    clear();
	attron(A_BOLD | COLOR_PAIR(3));
	move(0,0);
	addstr("                     _______     _          _       \n" );
	addstr("                    |__   __|   | |        (_)      \n" );
	addstr("                       | |  ___ | |_  _ __  _  ___  \n" );
	addstr("                       | | / _ \\| __|| '__|| |/ __| \n" );
	addstr("                       | ||  __/| |_ | |   | |\\__ \\ \n" );
	addstr("                       |_| \\___| \\__||_|   |_||___/ \n" );
	printw("\n");printw("\n");
	if(game_over){
		if(score > highscore){
			highscore = score;
			attron(A_BOLD | COLOR_PAIR(4));
			printw("                           Your new highscore: ");
			attron(A_BOLD | COLOR_PAIR(2));
			printw("%i", highscore);
			printw("\n");
			printw("\n");
			std::ofstream out("highscore_tetris.txt");
			out << highscore;
			out.close();
		}
		game_over=false;
	}
	attron(A_BOLD | COLOR_PAIR(1));
	addstr("                  Use arrows left/right to move blocks.");
	printw("\n");
	addstr("                        Space to rotate blocks.");
	printw("\n");
	addstr("                     Arrow down to drop block down.");
	printw("\n");
	printw("\n");
	printw("\n");
	attron(A_BLINK |COLOR_PAIR(4));
	addstr("                     Press ENTER to start new game.");
	while (true) {
		key = getch();
		if (key == 13) {
			game_status = true;
			score = 0;
			attrset(A_NORMAL);
			move(0,0);
			addstr("                                                      \n");
			addstr("                                                      ");
			break;
		}
	}
}

int main(){
	initscr();
	menu();
	while(game_status){
		while(game_status){
			process_input();
			update();
			next_game_tick = get_time_ms()+delay;
			while( get_time_ms() < next_game_tick);
			draw();
		}
		game_over=true;
		menu();
	}
	endwin();
	return 0;
}
