

//------------------------------------
//	Include Libraries
//------------------------------------
#include "game.h"

//---------------------------------------------
//	01. FUNCTION create_new_game (IMPLEMENTED)
//---------------------------------------------
game* create_new_game(char* p1, char* p2, int im) {
	//1. We declare the variable to be returned
	game* res = NULL;

	//2. We create memory space for it with malloc.
	res = (game*)malloc(1 * sizeof(game));

	//3. We use the names passed as arguments to initialise p1 and p2.
	(*res).p1 = (char*)malloc((strlen(p1) + 1) * sizeof(char));
	strcpy((*res).p1, p1);

	(*res).p2 = (char*)malloc((strlen(p1) + 1) * sizeof(char));
	strcpy((*res).p2, p2);

	//4. We set the mode based on the names of the players.
	// Human vs. Human --> mode = 1
	// Human vs. Computer --> mode = 2
	// Computer vs. Human --> mode = 3
	// Computer vs. Computer --> mode = 4
	int mode = 0;
	if (strcmp(p1, "Computer") == 0)
		mode = mode + 2;
	if (strcmp(p2, "Computer") == 0)
		mode = mode + 1;
	(*res).mode = mode;

	//5. We set the status to be 1; (i.e., player1 moves first)
	(*res).status = 1;

	//6. We initialise the board so that all its positions are empty
	int i;
	int j;
	for ( i = 0; i < 3; i++)
		for ( j = 0; j < 3; j++)
			(*res).board[i][j] = ' ';

	//7. We use the im passed as arguments to initialise intelligent_machine.
	if (im == 0)
		(*res).intelligent_machine = False;
	else
		(*res).intelligent_machine = True;

	//8. ---Computer Intelligent Movement Only --- We We initialise the avenues
	//avenue 0 --> [0,1,2]
	//avenue 1 --> [3,4,5]
	//avenue 2 --> [6,7,8]
	//avenue 3 --> [0,3,6]
	//avenue 4 --> [1,4,7]
	//avenue 5 --> [2,5,8]
	//avenue 6 --> [0,4,8]
	//avenue 7 --> [2,4,6]
	(*res).avenue_positions[0][0] = 0;
	(*res).avenue_positions[0][1] = 1;
	(*res).avenue_positions[0][2] = 2;

	(*res).avenue_positions[1][0] = 3;
	(*res).avenue_positions[1][1] = 4;
	(*res).avenue_positions[1][2] = 5;

	(*res).avenue_positions[2][0] = 6;
	(*res).avenue_positions[2][1] = 7;
	(*res).avenue_positions[2][2] = 8;

	(*res).avenue_positions[3][0] = 0;
	(*res).avenue_positions[3][1] = 3;
	(*res).avenue_positions[3][2] = 6;

	(*res).avenue_positions[4][0] = 1;
	(*res).avenue_positions[4][1] = 4;
	(*res).avenue_positions[4][2] = 7;

	(*res).avenue_positions[5][0] = 2;
	(*res).avenue_positions[5][1] = 5;
	(*res).avenue_positions[5][2] = 8;

	(*res).avenue_positions[6][0] = 0;
	(*res).avenue_positions[6][1] = 4;
	(*res).avenue_positions[6][2] = 8;

	(*res).avenue_positions[7][0] = 2;
	(*res).avenue_positions[7][1] = 4;
	(*res).avenue_positions[7][2] = 6;

	//9. ---Computer Intelligent Movement Only --- We initialise all avenues to state2
	for ( i = 0; i < 8; i++)
		(*res).avenue_states[i] = 2;

	//10. We return res
	return res;
}

//-------------------------------------
//	02. FUNCTION display_board_content
//-------------------------------------
void display_board_content(game* g) {
	//1. We print both (1) Indicative Indexes and (2) Actual Board Content
	//printf("\n------- Board Content -------\n|0|1|2|   |%c|%c|%c|\n|3|4|5|   |%c|%c|%c|\n|6|7|8|   |%c|%c|%c|\n"
    //,(*g).board[0][0],(*g).board[0][1],(*g).board[0][2],(*g).board[1][0],(*g).board[1][1],(*g).board[1][2],(*g).board[2][0],(*g).board[2][1],(*g).board[2][2] );

	//2. We print the flag of board content
	printf("\n------- Board Content -------\n");

	//3. We create an auxiliary variable for indicative indexes
	int i;

	//4. We make a loop of 3 iterations
	//On each iteration we first print some lines "------------"         "-------------"
	//Then we print a row of (1) Indicative Indexes and (2) Actual Board Content
	for(i = 0; i < 3; i++){
        printf("\n-------   -------\n|%d|%d|%d|   |%c|%c|%c|",(i+(i*2)),(i+(i*2)+1),(i+(i*2)+2),(*g).board[i][0],(*g).board[i][1],(*g).board[i][2]);
	}
}

//------------------------------------
//	03. FUNCTION display_game_status
//------------------------------------
void display_game_status(game* g) {
	//1. We clean the screen by printing 100 empty lines
	int i;
	for(i = 0; i < 10; i++){
        printf("\n");
	}

	//2. We call to display_board_content to print both (1) Indicative Indexes and (2) Actual Board Content
	display_board_content(g);

	//3. We print the flag of game status
	printf("\n------- \nGame Status \n-------\n");

	//4. We display the status
	// status = 1 --> Game is on. Player P1_name moves next.
	// status = 2 --> Game is on. Player P2_name moves next.
	// status = 3 --> Game is over. Player P1_name has won.
	// status = 4 --> Game is over. Player P2_name has won.
	// status = 5 --> Game is over. Draw.
	if((*g).status == 1){
	    printf("Game is on. Player %s moves next.\n", (*g).p1);

	}else if((*g).status == 2){
	    printf("Game is on. Player %s moves next.\n", (*g).p2);

	}else if((*g).status == 3){
	    printf("Game is over. Player %s has won.\n", (*g).p1);

	}else if((*g).status == 4){
	    printf("Game is over. Player %s has won.\n", (*g).p2);

	}else{
	    printf("Game is over. Draw\n");

	}
}

//--------------------------------------------------
// 04. gen_num (IMPLEMENTED)
//--------------------------------------------------
int gen_num(int lb, int ub) {
	//1. We create the output variable with an initial value.
	int res = 0;

	//2. We assign num to a random value in the desired range
	res = (rand() % (ub - lb)) + lb;

	//3. We return the output variable
	return res;
}

//--------------------------------------------------
// 05. FUNCTION my_getchar (IMPLEMENTED)
//--------------------------------------------------
char my_get_char() {
	//1. We create the variable to be returned
	char res = ' ';

	//2. We create an extra variable to consume any other characters entered until a return is pressed
	boolean line_consumed = False;
	char dummy_char = ' ';

	//3. We consume the first char entered, i.e., the one we are interested at
	res = getchar();

	//4. While still there are remaining characters
	while (line_consumed == False) {
		//4.1. We consume the next character
		dummy_char = getchar();

		//4.2. If the new character is the end of line one, we can ensure we have consumed the entire line.
		if (dummy_char == '\n')
			line_consumed = True;
	}

	//5. We return res
	return res;
}

//------------------------------------
//	06. FUNCTION is_position_empty
//------------------------------------
boolean is_position_empty(game* g, int pos) {
	//1. We create the variable to be returned
	boolean res = False;

	//2. We check if the index is a valid one and if the board is empty at that index.
	//If it is valid and free, we return True.
	//Otherwise, we return False and write a warning message.
	if(pos > 8 || pos < 0){
        printf("invalid index");
	}else{
	    if((*g).board[pos/3][pos%3] == ' '){
            res = True;
	    }else{printf("%c Position is filled",(*g).board[pos/3][pos%3] );}

	}

	//3. We return res
	return res;
}

//---------------------------------------
//	07. FUNCTION user_get_movement_index
//---------------------------------------
int user_get_movement_index(game* g) {
	//1. We create the variable to be returned
	int res = -1;

	//2. We create a boolean variable to control that we have received a valid movement index.
	boolean valid = False;

	//3. We create a char variable to control the index we are receiving by keyboard.
	char cindex;
	int index;

	//4. While we have not received a valid movement index.
	//We print a message asking for a new movement.
	//We call to my_get_char to get the index and we convert it to an integer.
	//We call to is_position_empty to check that the index is a valid one.
	while(valid == False){
        printf("\nInput desired index\n");
        cindex = my_get_char();
        index = cindex - '0';
        if(is_position_empty(g, index) == True){
            res = index;
            valid = True;
            printf("%d", res);
        }else{
            printf("%d", index);
            printf("\nThat position is not empty\n");

        }

        }

	//5. We return res
	return res;
}

//-------------------------------------------
//	08. FUNCTION computer_get_movement_index
//-------------------------------------------
int computer_get_movement_index(game* g) {
	//1. We create the variable to be returned
	int res = -1;
	int index;

	//2. We create a boolean variable to control that we have received a valid movement index.
	boolean valid = False;

	//3. While we have not received a valid movement index.
	//If the machine is not intelligent we generate a random index to move for.
	//Otherwise we call to the function intelligent_selection to pick the best index to move for.
	//In both cases we call to is_position_empty to double check that the selected index is a valid one.

    while(valid==False){
	if((*g).intelligent_machine == False){
            index = gen_num(0,8);
            if(is_position_empty(g, index) == True){
              res = index;
              valid = True;

           }else{
              printf("\nThat position is not empty\n");

           }

	}else{
	       index = intelligent_selection(g);
	       if(is_position_empty(g, index) == True){
              res = index;
              valid = True;

           }else{
              printf("\nThat position is not empty\n");

           }

	}}

	//4. We display a message of pressing a key to continue
	printf("Press any key to continue");

	//5. We call to my_get_char() to wait for the user to press a key before continuing.
	my_get_char();

	//6. We return res
	return res;
}

//---------------------------------------
//	09. FUNCTION get_next_movement_index
//---------------------------------------
int get_next_movement_index(game* g) {
	//1. We create the variable to be returned
	int res = -1;

	//2. We ask for the next valid movement to be selected.
	//Depending on the game status and the players name we call to the function
	//user_get_movement_index or computer_get_movement_index
	if((*g).status == 1){
        if(strcmp((*g).p1, "Computer") == 0){
            res = computer_get_movement_index(g);
        }else{
            res = user_get_movement_index(g);
        }
	}else if( (*g).status == 2){
	    if(strcmp((*g).p2, "Computer")== 0){
            res = computer_get_movement_index(g);
        }else{
            res = user_get_movement_index(g);
        }


	}


	//3. We return res
	return res;
}

//------------------------------------
//	10. FUNCTION is_there_a_winner
//------------------------------------
int is_there_a_winner(game* g) {
	//1. We create the variable to be returned
	int res = 0;
	int i;
	int j;
	int w1;
	int w2;

	//2. We check the 8 possible ways (avenues) of winning the game,
	//to see if either player P1 or player P2 have won in any of them.
	//avenue 0 --> [0,1,2]
	//avenue 1 --> [3,4,5]
	//avenue 2 --> [6,7,8]
	//avenue 3 --> [0,3,6]
	//avenue 4 --> [1,4,7]
	//avenue 5 --> [2,5,8]
	//avenue 6 --> [0,4,8]
	//avenue 7 --> [2,4,6]
	for(i=0;i<8;i++){
        w1 = 0;
        w2 = 0;
        for(j=0;j<3;j++){
                if((*g).board[((*g).avenue_positions[i][j])/3][((*g).avenue_positions[i][j])%3] == 'O' ){
                    w2++;
                    if(w2 == 3){
                        res = 2;
                    }


                }else if((*g).board[((*g).avenue_positions[i][j])/3][((*g).avenue_positions[i][j])%3] == 'X'  ){
                    w1++;
                    if(w1 == 3){
                        res = 1;
                    }

                }

        }

	}


	//3. We return res
	return res;
}

//------------------------------------
//	11. FUNCTION is_board_full
//------------------------------------
boolean is_board_full(game* g) {
	//1. We create the variable to be returned
	boolean res = True;
	int i;
	int j;

	//2. We check if the 9 positions of the board are busy.
	//If all positions are busy, we return True.
	//If at least one position is empty, we return False.
	for(i = 0; i < 3; i++){
        for(j = 0; j<3; j++){
            if((*g).board[i][j] == ' '){
                res = False;
            }
        }
	}

	//3. We return res
	return res;
}

//------------------------------------
//	12. FUNCTION process_movement
//------------------------------------
void process_movement(game* g, int pos) {
	// 1. We update board with the new movement at index 'pos'.
	// This requires checking the current status to know if the movement is an 'X' or a 'O'.
	if((*g).status == 1){
        (*g).board[pos/3][pos%3] = 'X';

	}else if((*g).status == 2){
	    (*g).board[pos/3][pos%3] = 'O';


	}

	//2. ---Computer Intelligent Movement Only ---
	//We traverse each avenue: If pos belongs to it, we call to update_avenue_states to update its state.

	int i;
	int j;
	for(i=0;i<3;i++){
        for(j=0;j<3;j++){
                if((*g).avenue_positions[i][j] == pos){
                    update_avenue_states(g,pos);
                }

        }

	}


	//3. We create a variable winner and call to the function is_there_a_winner
	//to see if this movement has lead to a winner.
	int winner;
	winner = is_there_a_winner(g);

	//4. We create a variable winner and call to the function is_board_full to see if the board is full.
	boolean draw;
	draw = is_board_full(g);

	//5. We update the status accordingly.
	// (Case 1) winner == 1 --> Game Status = 3.
	// (Case 2) winner == 2 --> Game Status = 4.
	// (Case 3) winner == 0 and full == True --> Game Status = 5.
	// (Case 4) winner == 0 and full == False --> Depending on current Game Status.
	//											  If Game Status == 1 --> Game Status = 2.
	//											  If Game Status == 2 --> Game Status = 1.
	if(winner == 1){
        (*g).status = 3;
	}else if(winner == 2){
	    (*g).status = 4;

	}else if(winner == 0 && draw == True){
	    (*g).status = 5;

	}else if(winner == 0 && draw == False){
	    if((*g).status == 1){(*g).status = 2;}
	    else if((*g).status == 2){(*g).status = 1;}


	}

}

//------------------------------------
//	13. FUNCTION play_game
//------------------------------------
void play_game(char* p1, char* p2, int im){
	//1. We create a variable pointer game* g and call to the function
	//create_new_game so as to initialise it.

    printf("%s\n", p1);
    printf("%s\n", p2);

	game* g = create_new_game(p1, p2, im);

	//2. Game loop: While the game is on (i.e., Game Status = 1 or Game Status = 2)
	//2.1. We call to display_game_status to print the board content and the next player to move.
	while((*g).status == 1 ||(*g).status == 2){



	display_game_status(g);



	//2.2. We call to get_next_movement_index to force the human player or the computer
	//to select a valid index to move for.
	int move;
	move = get_next_movement_index(g);



	//2.3. We call to process_movement to update the board content and the Game Status.
	process_movement(g, move);


	}
	//3. Once the game is over we call to display_game_status to print the last Game Status of the game.
    display_game_status(g);

}

//------------------------------------
//	14. FUNCTION update_avenue_states
//------------------------------------
void update_avenue_states(game* g, int avenue) {
	// 1. We update the state
	// CASE State 1 --> We keep still at State 1.
	if((*g).avenue_states[avenue] == 1){
        (*g).avenue_states[avenue] = 1;
	}else if((*g).avenue_states[avenue] == 2){
	    if((*g).status == 1){
            (*g).avenue_states[avenue] = 3;
	    }else if((*g).status == 2){
	        (*g).avenue_states[avenue] = 4;

	    }

	}else if((*g).avenue_states[avenue] == 3){
	    if((*g).status == 1){
            (*g).avenue_states[avenue] = 5;
	    }else if((*g).status == 2){
	        (*g).avenue_states[avenue] = 1;

	    }

	}else if((*g).avenue_states[avenue] == 4){
	    if((*g).status == 1){
            (*g).avenue_states[avenue] = 1;
	    }else if((*g).status == 2){
	        (*g).avenue_states[avenue] = 6;

	    }

	}else if((*g).avenue_states[avenue] == 5){
	    if((*g).status == 1){
            (*g).avenue_states[avenue] = 7;
	    }else if((*g).status == 2){
	        (*g).avenue_states[avenue] = 1;

	    }

	}else if((*g).avenue_states[avenue] == 6){
	    if((*g).status == 1){
            (*g).avenue_states[avenue] = 1;
	    }else if((*g).status == 2){
	        (*g).avenue_states[avenue] = 8;

	    }

	}else{}

	// CASE State 2 --> If Player1 is moving --> State 3.
	//					If Player2 is moving --> State 4.

	// CASE State 3 --> If Player1 is moving --> State 5.
	//					If Player2 is moving --> State 1.

	// CASE State 4 --> If Player1 is moving --> State 1.
	//					If Player2 is moving --> State 6.

	// CASE State 5 --> If Player1 is moving --> State 7.
	//					If Player2 is moving --> State 1.

	// CASE State 6 --> If Player1 is moving --> State 1.
	//					If Player2 is moving --> State 8.

	// CASE State 7 --> This case does not make sense, as the game is over.

	// CASE State 8 --> This case does not make sense, as the game is over.

}

//----------------------------------------
//	15. FUNCTION get_position_points
//----------------------------------------
int get_position_points(game* g, int pos) {
	//1. We create the variable to be returned
	int res = 0;

	//2. We traverse the 8 avenues, to see if pos in on it.
	//Remember that each pos will belong to multiple avenues:
	//pos = 1; pos = 3; pos = 5; pos = 7 belong to 2 avenues.
	//pos = 0; pos = 2; pos = 6; pos = 8 belong to 3 avenues.
	//pos = 4 belongs to 4 avenues.

	//For each avenue pos belongs to, it gets points from it.
	//How many points? It depends of the state of the avenue.
	// CASE State 1 --> 0 points.

	// CASE State 2 --> 1 point.
	//

	// CASE State 3 --> If Player1 is moving --> 4 points.
	//					If Player2 is moving --> 2 points.

	// CASE State 4 --> If Player1 is moving --> 2 points.
	//					If Player2 is moving --> 4 points.

	// CASE State 5 --> If Player1 is moving --> 16 points.
	//					If Player2 is moving --> 8 points.

	// CASE State 6 --> If Player1 is moving --> 8 points.
	//					If Player2 is moving --> 16 points.

	// CASE State 7 --> This case does not make sense, as the game is over.

	// CASE State 8 --> This case does not make sense, as the game is over.
	int i;
	int j;
	for(i=0;i<9;i++){
        for(j=0;j<3;j++){
            if((*g).avenue_positions[i][j] == pos){
                    if((*g).avenue_states[pos] == 1){

	                }else if((*g).avenue_states[pos] == 2){
	                      res = res + 1;

	       }else if((*g).avenue_states[pos] == 3){
	                if((*g).status == 1){
                          res = res + 4;
	                }else if((*g).status == 2){
	                      res = res + 2;

                    }

           }else if((*g).avenue_states[pos] == 4){
	                if((*g).status == 1){
                         res = res + 2;
	                }else if((*g).status == 2){
                         res = res + 4;

                    }

            }else if((*g).avenue_states[pos] == 5){
	                if((*g).status == 1){
                          res = res + 16;
	                }else if((*g).status == 2){
	                      res = res + 8;

	                }

	        }else if((*g).avenue_states[pos] == 6){
	                if((*g).status == 1){
                          res = res + 8;
	                }else if((*g).status == 2){
	                      res = res + 16;

                    }

	}else{}

            }

        }

        }


	//3. We return the accumulated amount of points of pos
	return res;
}

//----------------------------------------
//	16. FUNCTION intelligent_selection
//----------------------------------------
int intelligent_selection(game* g) {
	//1. We create the variable to be returned
	int res = -1;

	//2. We create an auxiliary variable max_points to compute the maximum amount of points we have found so far.
	int max_points = 0;

	//3. We traverse all the positions of boards to pick the one leading to maximum points.
	//If a position is not empty then we do not consider it.
	//If a position is empty, then we call to get_position_points to get its points.
	//We compare the result with max_points.
	//If the new position gets more points than max_points, then we update:
	//(1) The selected position and (2) The proper variable max_points with the new points computed.
	int i;
	int j;

	for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            if((*g).board[i][j] == ' '){
                if(max_points < get_position_points(g,((i*3) + j))){
                    max_points = get_position_points(g,((i*3) + j));
                    res = (i*3) + j;
                }
            }
        }
	}



	//4. We return res
	return res;
}
