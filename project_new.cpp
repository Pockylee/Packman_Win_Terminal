#include<iostream>
#include<windows.h>
#include<conio.h>
#include<fstream>
#include<string>
#include<time.h>
using namespace std;

int main(){
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO CursorInfo;
    GetConsoleCursorInfo(handle, &CursorInfo);
    CursorInfo.bVisible = false;
    SetConsoleCursorInfo(handle, &CursorInfo);

    int end_game = 0, select = 0;
    while(end_game == 0){
        int start_length, start_width, start_length_1, start_width_1;
        int map_length, map_width, moves, row, ver;
        int row_ghost_1, ver_ghost_1, moves_ghost_1 = 2, row_ghost_1_start, ver_ghost_1_start;
        int row_ghost_2, ver_ghost_2, moves_ghost_2 = 0, row_ghost_2_start, ver_ghost_2_start;
        int row_4, ver_4, row_5, ver_5, row_start, ver_start;
        int total_score = 0, total_life = 3, sum_food = 0, caught = 0, cat = 0;
        int life_times = 3;
        int map_select = 0;
        string map_pix = "", start_pix = "", start_pix_1 = "";
        char before_1 = '3', before_2 = '3';
        void gotoxy(int xpos, int ypos);
        void color_adjust(int color = 7);

        int black_length = 100, black_width = 100;
        char Black[black_length][black_width];

    for (int i = 0; i <= black_length - 1; i++){
        for (int j = 0; j <= black_width - 1; j++){
            Black[i][j] = ' ';
        }
	}//make black windows

    ifstream input_start;
	input_start.open("start.txt");
	input_start >> start_length;
	input_start >> start_width;
    char Start[start_length][start_width];
    //cout << start_length << " " << start_width << endl;

	for (int i = 0; i <= start_length - 1; i++){
        for (int j = 0; j <= start_width - 1; j++){
            input_start >> start_pix;
            Start[i][j] = start_pix[0];
        }
	}//make start windows

    ifstream input_start_1;
	input_start_1.open("start_1.txt");
	input_start_1 >> start_length_1;
	input_start_1 >> start_width_1;
    char Start_1[start_length_1][start_width_1];
    //cout << start_length << " " << start_width << endl;

	for (int i = 0; i <= start_length_1 - 1; i++){
        for (int j = 0; j <= start_width_1 - 1; j++){
            input_start_1 >> start_pix_1;
            Start_1[i][j] = start_pix_1[0];
        }
	}//make start_1 windows

    int g = 1;
	while (select == 0){
        if (g % 2 == 1){
            for (int i = 0; i <= start_length - 1; i++){
                for (int j = 0; j <= start_width - 1; j++){
                    if (Start[i][j] == '0'){
                        color_adjust(0);
                        cout << ' ';
                    }
                    else if (Start[i][j] == '1'){
                        color_adjust(240);
                        cout << ' ';
                    }
                    else {
                        color_adjust(7);
                        cout << Start[i][j];
                    }
                }
            color_adjust();
            cout << endl;
            }
        }
        else if (g % 2 ==0){
            for (int i = 0; i <= start_length_1 - 1; i++){
                for (int j = 0; j <= start_width_1 - 1; j++){
                    if (Start_1[i][j] == '0'){
                        color_adjust(0);
                        cout << ' ';
                    }
                    else if (Start_1[i][j] == '1'){
                        color_adjust(240);
                        cout << ' ';
                    }
                    else {
                        color_adjust(7);
                        cout << Start_1[i][j];
                    }
                }
            color_adjust(0);
            cout << endl;
            }
        }
        if (kbhit())
        {
            char keyboard = getch();
            if (keyboard == 32) select = 1;
    	}
        g++;
        Sleep(200);
        gotoxy(0,0);
    }//start windows

    for (int i = 0; i <= black_length - 1; i++){
            for (int j = 0; j <= black_width - 1; j++){
                cout << Black[i][j];
            }
        cout << endl;
    }//black out the background
    gotoxy(0,0);

    while (select == 1){
        cout << "Map Selection : \n\n";
        cout << "Map One   << Press number '1' on your keyboard!\n";
        cout << "Map Two   << Press number '2' on your keyboard!\n";
        cout << "Map Three << Press number '3' on your keyboard!\n";
        if (kbhit())
        {
            char keyboard = getch();
            if (keyboard == 49){
                map_select = 1;
                select = 2;
            }
            else if (keyboard == 50){
                map_select = 2;
                select = 2;
            }
            else if (keyboard == 51){
                map_select = 3;
                select = 2;
            }
    	}
        gotoxy(0,0);
    }
    gotoxy(0,0);

    ifstream input_map;
    if (map_select == 1){
        input_map.open("map.txt");
    }
    else if (map_select == 2){
    	input_map.open("map2.txt");
	}
	else if (map_select == 3){
    	input_map.open("map3.txt");
	}
	input_map >> map_length;
    input_map >> map_width;

	char Map_1[map_length][map_width];

	for (int i = 0; i <= map_length - 1; i++){
        for (int j = 0; j <= map_width - 1; j++){
            input_map >> map_pix;
            if (map_pix == "0"){
                Map_1[i][j] = map_pix[0];
            }
            else if (map_pix == "1"){
                Map_1[i][j] = map_pix[0];
                sum_food += 10;
            }
            else if (map_pix == "3"){
            	Map_1[i][j] = map_pix[0];
			}
            else if (map_pix == "4"){
            	Map_1[i][j] = map_pix[0];
            	row_4 = i;
            	ver_4 = j-1;
			}//紀錄進入右側穿透點前的座標
			else if (map_pix == "5"){
            	Map_1[i][j] = map_pix[0];
            	row_5 = i;
            	ver_5 = j+1;
			}//紀錄進入左側穿透點前的座標
            else if (map_pix == "2"){
                Map_1[i][j] = map_pix[0];
                row = i;
                ver = j;
                row_start = row;
                ver_start = ver;
            }//紀錄小精靈的起始座標
            else if (map_pix == "6"){
                Map_1[i][j] = map_pix[0];
                row_ghost_1 = i;
                ver_ghost_1 = j;
                row_ghost_1_start = row_ghost_1;
                ver_ghost_1_start = ver_ghost_1;
            }//紀錄1號鬼的起始座標
            else if (map_pix == "7"){
                Map_1[i][j] = map_pix[0];
                row_ghost_2 = i;
                row_ghost_2 = j;
                row_ghost_2_start = row_ghost_2;
                ver_ghost_2_start = ver_ghost_2;
            }
        }
	}
	/*for (int i = 0; i <= map_length - 1; i++){
        for (int j = 0; j <= map_width - 1; j++){
            cout << Map_1[i][j];
        }
        cout << endl;
	}*///output the map
    for (int i = 0; i <= black_length - 1; i++){
        for (int j = 0; j <= black_width - 1; j++){
            cout << Black[i][j];
        }
        cout << endl;
    }//black out the background
    gotoxy(0,0);

    while (select == 2){
        cout << "PAC-MAN Tutorial : \n\n";
        cout << "Go up    << Press 'W' on your keyboard!\n";
        cout << "Go down  << Press 'S' on your keyboard!\n";
        cout << "Go left  << Press 'A' on your keyboard!\n";
        cout << "Go right << Press 'D' on your keyboard!\n\n\n";
        cout << "Please press the 'space' on your keyboard while you're ready for the game!";
        if (kbhit())
        {
            char keyboard = getch();
            if (keyboard == 32){
                select = 3;
            }
    	}
        gotoxy(0,0);
    }

    for (int i = 0; i <= black_length - 1; i++){
        for (int j = 0; j <= black_width - 1; j++){
            cout << Black[i][j];
        }
        cout << endl;
    }//black out the background
    gotoxy(0,0);
    while (select == 3){
        if ((caught == 1) && (cat == 1)){
        	row = row_start;
        	ver = ver_start;
			Map_1[row][ver] = '2';
			Map_1[row_ghost_1][ver_ghost_1] = '3';
			row_ghost_1 = row_ghost_1_start;
			ver_ghost_1 = ver_ghost_1_start;
			Map_1[row_ghost_1_start][ver_ghost_1_start] = '6';
			moves_ghost_1 = 2;
			caught = 0;
			cat = 0;
		}
		int left_star = 0;
		for (int i = 0; i <= map_length - 1; i++){
            for (int j = 0; j <= map_width - 1; j++){
                if (Map_1[i][j] == '0'){
                    color_adjust(240);
                    cout << ' ';
                }
                else if (Map_1[i][j] == '1'){
                    left_star++;
					color_adjust(7);
                    cout << '*';
                }
                else if (Map_1[i][j] == '2'){
                    color_adjust(3);
                    if (moves == 1) cout << '>';
                    else if (moves == 2) cout << '<';
                    else if (moves == 3) cout << 'v';
                    else if (moves == 4) cout << '^';
                    else cout << '<';
                }
                else if (Map_1[i][j] == '3'){
                    color_adjust(0);
                    cout << ' ';
                }
                else if (Map_1[i][j] == '4'){
                	color_adjust(30);
                	cout << ' ';
				}//右側穿透點
				else if (Map_1[i][j] == '5'){
					color_adjust(30);
					cout << ' ';
				}//左側穿透點
				else if (Map_1[i][j] == '6'){
                    color_adjust(4);
                    cout << '&';
				}//ghost_1
				else if (Map_1[i][j] == '7'){
                    color_adjust(6);
                    cout << '&';
				}//ghost_2
            }
            color_adjust();
            cout << endl;
        }
        if (caught == 1){
			before_1 = '3';
			cat = 1;
			Sleep(1500);
			gotoxy(0,0);
			continue;
		}
        if (life_times == 3){
        	color_adjust(3);
        	cout << endl << "<<<";
        	color_adjust();
        	cout << "\t\tScore: " << total_score;
		}
        else if (life_times == 2){
        	color_adjust(3);
        	cout << endl << "<<";
        	color_adjust();
        	cout << "\t\tScore: " << total_score;
		}
        else if (life_times == 1){
        	color_adjust(3);
        	cout << endl << "<";
        	color_adjust();
        	cout << "\t\tScore: " << total_score;
		}
		else if (life_times == 0) moves = 5;

		if (left_star == 0){
			Sleep(1500);
			gotoxy(0, 0);
            for (int i = 0; i <= black_length - 1; i++){
                for (int j = 0; j <= black_width - 1; j++){
                    cout << Black[i][j];
                }
                cout << endl;
            }//black out the background
            gotoxy(0,0);
            while (select == 3){
                cout << "You win this game. Congratulations!!\n";
                cout << "Please press 'space' to return to the menu.\n";
                cout << "If you want to quit the game, please press 'Q' on your keyboard!\n";
                if (kbhit())
                {
                    char keyboard = getch();
                    if (keyboard == 32){
                        select = 1;
                        moves = 0;
                        break;
                    }
                    else if (keyboard == 'q' || keyboard == 'Q'){
                        select = 1;
                        end_game = 1;
                        gotoxy(0,0);
                        break;
                    }
                }
                gotoxy(0,0);
            }
		}

        if (kbhit())
        {
            char keyboard=getch();
            if (keyboard == 'z' || keyboard == 'Z') moves=5;
            else if (keyboard == 'a' || keyboard == 'A')
            {
                if (Map_1[row][ver - 1] == '0'){
                    moves = moves;
                }
                else moves = 1;
            }
            else if (keyboard == 'd' || keyboard == 'D')
            {
                if (Map_1[row][ver + 1] == '0'){
                    moves = moves;
                }
                else moves=2;
            }
            else if (keyboard == 'w' || keyboard == 'W')
            {
                if (Map_1[row - 1][ver] == '0'){
                    moves = moves;
                }
                else moves=3;
            }
            else if (keyboard == 's' || keyboard == 'S')
            {
                if (Map_1[row + 1][ver] == '0'){
                    moves = moves;
                }
                else moves=4;
            }
    	}

        int check = 0;
    	while (total_score < sum_food){
            if (moves_ghost_1 == 0){
                Map_1[row_ghost_1][ver_ghost_1] = before_1;
                before_1 = Map_1[row_ghost_1 - 1][ver_ghost_1];
                row_ghost_1 = row_ghost_1 - 1;
                if (Map_1[row_ghost_1][ver_ghost_1] == '0'){
                    if (rand() % 2 == 0) moves_ghost_1 = 2;
                    else moves_ghost_1 = 3;
                    row_ghost_1 = row_ghost_1 + 1;
                    before_1 = Map_1[row_ghost_1][ver_ghost_1];
                    continue;
                }
                else {
                    Map_1[row_ghost_1][ver_ghost_1] = '6';
                    break;
                }
            }//up
            else if (moves_ghost_1 == 1){
                Map_1[row_ghost_1][ver_ghost_1] = before_1;
                before_1 = Map_1[row_ghost_1 + 1][ver_ghost_1];
                row_ghost_1 = row_ghost_1 + 1;
                if (Map_1[row_ghost_1][ver_ghost_1] == '0'){
                    if (rand() % 2 == 0) moves_ghost_1 = 2;
                    else moves_ghost_1 = 3;
                    row_ghost_1 = row_ghost_1 - 1;
                    before_1 = Map_1[row_ghost_1][ver_ghost_1];
                    continue;
                }
                else {
                    Map_1[row_ghost_1][ver_ghost_1] = '6';
                    break;
                }
            }//down
            else if (moves_ghost_1 == 2){
                Map_1[row_ghost_1][ver_ghost_1] = before_1;
                before_1 = Map_1[row_ghost_1][ver_ghost_1 - 1];
                ver_ghost_1 = ver_ghost_1 - 1;
                if (Map_1[row_ghost_1][ver_ghost_1] == '0'){
                    if (rand() % 2 == 0) moves_ghost_1 = 0;
                    else moves_ghost_1 = 1;
                    ver_ghost_1 = ver_ghost_1 + 1;
                    before_1 = Map_1[row_ghost_1][ver_ghost_1];
                    continue;
                }
                else {
                    Map_1[row_ghost_1][ver_ghost_1] = '6';
                    break;
                }
            }//left
            else if (moves_ghost_1 == 3){
                Map_1[row_ghost_1][ver_ghost_1] = before_1;
                before_1 = Map_1[row_ghost_1][ver_ghost_1 + 1];
                ver_ghost_1 = ver_ghost_1 + 1;
                if (Map_1[row_ghost_1][ver_ghost_1] == '0'){
                    if (rand() % 2 == 0) moves_ghost_1 = 0;
                    else moves_ghost_1 = 1;
                    ver_ghost_1 = ver_ghost_1 - 1;
                    before_1 = Map_1[row_ghost_1][ver_ghost_1];
                    continue;
                }
                else {
                    Map_1[row_ghost_1][ver_ghost_1] = '6';
                    break;
                }
            }//Right
    	}

    	if (moves == 5){
            gotoxy(0, 0);
            for (int i = 0; i <= black_length - 1; i++){
                for (int j = 0; j <= black_width - 1; j++){
                    cout << Black[i][j];
                }
                cout << endl;
            }//black out the background
            gotoxy(0,0);
            while (select == 3){
                cout << "Game Over!!\n";
                cout << "Please press 'space' to return to the menu.\n";
                cout << "If you want to quit the game, please press 'Q' on your keyboard!\n";
                if (kbhit())
                {
                    char keyboard = getch();
                    if (keyboard == 32){
                        select = 1;
                        moves = 0;
                        break;
                    }
                    else if (keyboard == 'q' || keyboard == 'Q'){
                        select = 1;
                        end_game = 1;
                        gotoxy(0,0);
                        break;
                    }
                }
                gotoxy(0,0);
            }
    	}
    	if (moves == 1){
    		if ((row == row_5) && (ver == ver_5)){
				Map_1[row][ver] = '3';
    			ver = ver - 1;
    			if (Map_1[row][ver] == '5'){
    				ver = ver_4;
    				row = row_4;
    				if (Map_1[row][ver] == '1'){
    					total_score += 10;
					}
    				Map_1[row][ver] = '2';
				}
			}//從左瞬移到右
			else if ((row == row_ghost_1) && (ver == ver_ghost_1)){
				if (moves_ghost_1 == 3){
					caught = 1;
					life_times -= 1;
					row = row;
					ver = ver-1;
					Map_1[row_ghost_1][ver_ghost_1] = '6';
				}
			}//小精靈撞鬼
			else{
				Map_1[row][ver] = '3';
            	ver = ver - 1;
            	if (Map_1[row][ver] == '1'){
					total_score += 10;
				}
            	else if (Map_1[row][ver] == '0'){
					ver = ver + 1;
				}
				Map_1[row][ver] = '2';
            }
    	}//小精靈向左走 
    	else if (moves == 2){
            if ((row == row_4) && (ver == ver_4)){
				Map_1[row][ver] = '3';
    			ver = ver + 1;
    			if (Map_1[row][ver] == '4'){
    				row = row_5;
					ver = ver_5;
    				if (Map_1[row][ver] == '1'){
    					total_score += 10;
					}
    				Map_1[row][ver] = '2';
				}
			}//從右瞬移到左
			else if ((row == row_ghost_1) && (ver == ver_ghost_1)){
				if (moves_ghost_1 == 2){
					caught = 1;
					life_times -= 1;
					row = row;
					ver = ver+1;
					Map_1[row_ghost_1][ver_ghost_1] = '6';
				}
			}//小精靈撞鬼
            else{
				Map_1[row][ver] = '3';
        	    ver = ver + 1;
        	    if (Map_1[row][ver] == '1'){
					total_score += 10;
				}
        	    else if (Map_1[row][ver] == '0'){
					ver = ver - 1;
       	        }
            	Map_1[row][ver] = '2';
        	}
    	}//小精靈向右走
    	else if (moves == 3){
			if ((row == row_ghost_1) && (ver == ver_ghost_1)){
				if (moves_ghost_1 == 1){
					caught = 1;
					life_times -= 1;
					row = row-1;
					ver = ver;
					Map_1[row_ghost_1][ver_ghost_1] = '6';
				}
			}//小精靈撞鬼
			else{
            	Map_1[row][ver] = '3';
            	row = row - 1;
            	if (Map_1[row][ver] == '1'){
					total_score += 10;
				}
				else if (Map_1[row][ver] == '0'){
					row = row + 1;
            	}
            	Map_1[row][ver] = '2';
			}
    	}//小精靈向上走
    	else if (moves == 4){
			if ((row == row_ghost_1) && (ver == ver_ghost_1)){
    			if (moves_ghost_1 == 0){
    				caught = 1;
					life_times -= 1;
					row = row+1;
					ver = ver;
					Map_1[row_ghost_1][ver_ghost_1] = '6';
				}
			}//小精靈撞鬼
    		else{
    	        Map_1[row][ver] = '3';
    	        row = row + 1;
    	        if (Map_1[row][ver] == '1'){
					total_score += 10;
				}
   		        else if (Map_1[row][ver] == '0'){
					row = row - 1;
            	}
            	Map_1[row][ver] = '2';
            }
    	}//小精靈向下走
    	if (row == row_ghost_1 && ver == ver_ghost_1){
			Map_1[row_ghost_1][ver_ghost_1] = '6';
    		life_times -= 1;
    		caught = 1;
		}

        Sleep(500);
        gotoxy(0,0);
    }
    }
    int black_length = 100, black_width = 100;
    char Black[black_length][black_width];
    void gotoxy(int xpos, int ypos);
    for (int i = 0; i <= black_length - 1; i++){
        for (int j = 0; j <= black_width - 1; j++){
            cout << Black[i][j];
        }
        cout << endl;
    }//black out the background
    gotoxy(0,0);
    cout << "Bye!";
	return 0;
}

void gotoxy(int xpos, int ypos)
{
  COORD scrn;
  HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
  scrn.X = xpos; scrn.Y = ypos;
  SetConsoleCursorPosition(hOuput,scrn);
}

void color_adjust(int color = 7)
{
  HANDLE hConsole;
  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole,color);
}

