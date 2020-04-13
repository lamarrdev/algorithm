#include <stdio.h>

#include <stdlib.h>



void init_board(char board[][3]);

int get_player_move(int player, char board[][3]);

void disp_board(char board[][3]);



int main(void)

{	

	char board[3][3];

	int quit=0;

	

	init_board(board);

	do

	{

		disp_board(board);

		quit = get_player_move(0, board);

		disp_board(board);

		quit = get_player_move(1, board);

	} while(quit == 0);

	return 0;

}



void init_board(char board[][3])

{

	int x, y;

	for(x=0; x<3; x++)

	{

		for(y=0; y<3; y++)

		{

			board[x][y] = ' ';

		}

	}

}



int get_player_move(int player, char board[3][3])

{

	int x, y, done = 0;

	

	while(done != 1)

	{

		printf("(x, y) 좌표(종료-1, -1): ");

		scanf("%d,%d",&x, &y);

		

		if(x == -1 && y == -1)

			return 1;

		if(board[x][y] == ' ')

			break;

		else

			printf("잘못된 위치입니다.\n"); 

	}

	if(player == 0)

		board[x][y] = 'X';

	else

		board[x][y] = '0';

		

	return 0;

}



void disp_board(char board[3][3])

{

	int i;

	for(i=0; i<3; i++)

	{

		printf("---|---|---\n");

		printf(" %c | %c | %c \n", board[i][0], board[i][1], board[i][2]);

		printf("---|---|---\n");

	}

}