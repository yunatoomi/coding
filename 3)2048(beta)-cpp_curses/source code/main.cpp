#include <curses.h>
#include <stdlib.h>
#include <time.h>

int field[4][4]={0},key,ctr = 0,randI,randJ,k,tmas[10]={2,2,2,2,4,2,2,2,2,2};
char direction;

void draw_hor_wall(){
	addch('-');
	addch('-');
	addch('-');
	addch('-');
}

void draw_var(int var){
	int n = 1,varc;
	varc=var;
	while ( ( var /= 10 ) > 0 ) n++;
	switch (n){
		case 1:
			if(varc == 0){
				attron(A_DIM | COLOR_PAIR(1));
				addch(' ');
				addch(' ');
				addch(' ');
				addch(' ');
				break;
			}else{
				attron(A_DIM | COLOR_PAIR(2));
				addch(' ');
				addch(' ');
				addch(' ');
				printw("%i", varc);
				break;
			}
		case 2:
			attron(A_DIM | COLOR_PAIR(4));
			addch(' ');
			printw("%i", varc);
			addch(' ');
			break;
		case 3:
			attron(A_DIM | COLOR_PAIR(5));
			addch(' ');
			printw("%i", varc);
			break;
		case 4:
			attron(A_DIM | COLOR_PAIR(6));
			printw("%i", varc);
			break;
	}
	attron(A_DIM | COLOR_PAIR(1));
}

void draw(int intmas[4][4]){
	move(0,0);
	addch(ACS_ULCORNER);
	draw_hor_wall();
	addch(ACS_TTEE);
	draw_hor_wall();
	addch(ACS_TTEE);
	draw_hor_wall();
	addch(ACS_TTEE);
	draw_hor_wall();
	addch(ACS_URCORNER);
	addch('\n');
	addch(ACS_VLINE);
	draw_var(intmas[0][0]);
	addch(ACS_VLINE);
	draw_var(intmas[0][1]);
	addch(ACS_VLINE);
	draw_var(intmas[0][2]);
	addch(ACS_VLINE);
	draw_var(intmas[0][3]);
	addch(ACS_VLINE);
	addch('\n');
	addch(ACS_LTEE);
	draw_hor_wall();
	addch(ACS_PLUS);
	draw_hor_wall();
	addch(ACS_PLUS);
	draw_hor_wall();
	addch(ACS_PLUS);
	draw_hor_wall();
	addch(ACS_RTEE);
	addch('\n');
	addch(ACS_VLINE);
	draw_var(intmas[1][0]);
	addch(ACS_VLINE);
	draw_var(intmas[1][1]);
	addch(ACS_VLINE);
	draw_var(intmas[1][2]);
	addch(ACS_VLINE);
	draw_var(intmas[1][3]);
	addch(ACS_VLINE);
	addch('\n');
	addch(ACS_LTEE);
	draw_hor_wall();
	addch(ACS_PLUS);
	draw_hor_wall();
	addch(ACS_PLUS);
	draw_hor_wall();
	addch(ACS_PLUS);
	draw_hor_wall();
	addch(ACS_RTEE);
	addch('\n');
	addch(ACS_VLINE);
	draw_var(intmas[2][0]);
	addch(ACS_VLINE);
	draw_var(intmas[2][1]);
	addch(ACS_VLINE);
	draw_var(intmas[2][2]);
	addch(ACS_VLINE);
	draw_var(intmas[2][3]);
	addch(ACS_VLINE);
	addch('\n');
	addch(ACS_LTEE);
	draw_hor_wall();
	addch(ACS_PLUS);
	draw_hor_wall();
	addch(ACS_PLUS);
	draw_hor_wall();
	addch(ACS_PLUS);
	draw_hor_wall();
	addch(ACS_RTEE);
	addch('\n');
	addch(ACS_VLINE);
	draw_var(intmas[3][0]);
	addch(ACS_VLINE);
	draw_var(intmas[3][1]);
	addch(ACS_VLINE);
	draw_var(intmas[3][2]);
	addch(ACS_VLINE);
	draw_var(intmas[3][3]);
	addch(ACS_VLINE);
	addch('\n');
	addch(ACS_LLCORNER);
	draw_hor_wall();
	addch(ACS_BTEE);
	draw_hor_wall();
	addch(ACS_BTEE);
	draw_hor_wall();
	addch(ACS_BTEE);
	draw_hor_wall();
	addch(ACS_LRCORNER);
} 

void process_input(){
	key = getch();
	switch (key){
		case KEY_LEFT:
			direction='L';
			break;
		case KEY_RIGHT:
			direction='R';
			break;
		case KEY_DOWN:
			direction='D';
			break;
		case KEY_UP:
			direction='U';
			break;
	}
}

void spawn_new_number(){
	do{
	randI=rand() % 4 +0;
	randJ=rand() % 4 +0;
	}while((field[randI][randJ])!=0);
	field[randI][randJ]=tmas[rand() % 9 +0];
}

bool check_motion(){
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if(field[i][j]!=0){
				switch(direction){
					case 'L':
						for(k = j-1;k >= 0;--k){
							if((field[i][k]==0)or(field[i][k]==field[i][j]))return true;
						}
						break;
					case 'R':
						for(k = j+1;k <= 3;++k){
							if((field[i][k]==0)or(field[i][k]==field[i][j]))return true;
						}
						break;
					case 'D':
						for(k = i+1;k <= 3;++k){
							if((field[k][j]==0)or(field[k][j]==field[i][j]))return true;
						}
						break;
					case 'U':
						for(k = i-1;k >= 0;--k){
							if((field[k][j]==0)or(field[k][j]==field[i][j]))return true;
						}
						break;
				}
			}
		}
	}
	return false;
}

void move(){
	if(check_motion()){
		k = 0;
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				if(field[i][j]!=0){
					switch(direction){
					case 'L':
						for(k = j-1;k>=0;--k){
							if((field[i][k]==0) || (field[i][k]==field[i][k+1])){
								field[i][k]+=field[i][k+1];
								field[i][k+1]=0;
							}
						}
						break;
					case 'R':
						k=j+1;
						while(k <= 3){
							if((field[i][k]==0) || (field[i][k]==field[i][j])){
								field[i][k]+=field[i][j];
								field[i][j]=0;
							}
							++k;
						}
						break;
					case 'D':
						k=i+1;
						while(k <= 3){
							if((field[k][j]==0) || (field[k][j]==field[k-1][j])){
								field[k][j]+=field[k-1][j];
								field[k-1][j]=0;
							}
							++k;
						}
						break;
					case 'U':
						for(k = i-1;k>=0;--k){
							if((field[k][j]==0) || (field[k][j]==field[k+1][j])){
								field[k][j]+=field[k+1][j];
								field[k+1][j]=0;
							}
						}
						break;
					}
				}
			}
		}
		spawn_new_number();
	}
}

void update_status(){
	switch(direction){
		case 'L':
			move();
			direction='q';
			break;
		case 'R':
			move();
			direction='q';
			break;
		case 'D':
			move();
			direction='q';
			break;
		case 'U':
			move();
			direction='q';
			break;
	}
}

int main(){
	srand(time(NULL));
	initscr();
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);
	//timeout(10);
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	init_pair(2, COLOR_BLACK, COLOR_RED);
	init_pair(3, COLOR_BLACK, COLOR_BLUE);
	init_pair(4, COLOR_BLACK, COLOR_YELLOW);
	init_pair(5, COLOR_BLACK, COLOR_GREEN);
	init_pair(6, COLOR_BLACK, COLOR_CYAN);
	attron(A_DIM | COLOR_PAIR(1));
	bool game_status = true;
	spawn_new_number();
	spawn_new_number();
	while(game_status){
		draw(field);
		process_input();
		update_status();
	}
	
	
	endwin();
}
