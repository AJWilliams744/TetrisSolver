#include "tetrissolver.h"

//Input data storage
#define NUMDATA 100

const int1 pieces[7][4][4][4] = {
    { //I
        {
            {1, 1, 1, 1},
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        }, {
            {1, 0, 0, 0},
            {1, 0, 0, 0},
            {1, 0, 0, 0},
            {1, 0, 0, 0}
        }
    },
    { //O
        {
            {1, 1, 0, 0},
            {1, 1, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        }
    },
    { //T
        {
            {1, 1, 1, 0},
            {0, 1, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        }, {
            {1, 0, 0, 0},
            {1, 1, 0, 0},
            {1, 0, 0, 0},
            {0, 0, 0, 0}
        }, {
            {0, 1, 0, 0},
            {1, 1, 1, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        }, {
            {0, 1, 0, 0},
            {1, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 0, 0}
        }
    },
    { //J
        {
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {1, 1, 0, 0},
            {0, 0, 0, 0}
        }, {
            {1, 0, 0, 0},
            {1, 1, 1, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        }, {
            {1, 1, 0, 0},
            {1, 0, 0, 0},
            {1, 0, 0, 0},
            {0, 0, 0, 0}
        }, {
            {1, 1, 1, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        }
    },
    { //L
        {
            {1, 0, 0, 0},
            {1, 0, 0, 0},
            {1, 1, 0, 0},
            {0, 0, 0, 0}
        }, {
            {1, 1, 1, 0},
            {1, 0, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        }, {
            {1, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 0, 0}
        },  {
            {0, 0, 1, 0},
            {1, 1, 1, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        }
    },
    { //S
        {
            {0, 1, 1, 0},
            {1, 1, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        }, {
            {1, 0, 0, 0},
            {1, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 0, 0}
        }
    },
    { //Z
        {
            {1, 1, 0, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        }, {
            {0, 1, 0, 0},
            {1, 1, 0, 0},
            {0, 0, 0, 0}
        }
    }
};


int2 inputdata[NUMDATA];

int32 tetrissolver(uint32 *ram, char puzzle[12], int5 length) {
	#pragma HLS INTERFACE m_axi port=ram offset=slave bundle=MAXI
	#pragma HLS INTERFACE s_axilite port=puzzle bundle=AXILiteS register
	#pragma HLS INTERFACE s_axilite port=length bundle=AXILiteS register


	int1 baseBoard[BOARDHEIGHT][BOARDWIDTH] = {
			{0,0,0,0,0,0},
			{0,0,0,0,0,0},
			{0,0,0,0,0,0},
			{0,0,0,0,0,0},
			{0,0,0,0,0,0},
			{0,0,0,0,0,0},
			{0,0,0,0,0,0},
			{0,0,0,0,0,0},
			{0,0,0,0,0,0},
			{0,0,0,0,0,0},
			{0,0,0,0,0,0},
			{0,0,0,0,0,0},
			{0,0,0,0,0,0},
			{0,0,0,0,0,0},
			{0,0,0,0,0,0},
			{0,0,0,0,0,0},
			{0,0,0,0,0,0},
			{0,0,0,0,0,0},
			{0,0,0,0,0,0},
			{0,0,0,0,0,0}
	};

	//*arg2 = int2(1);
	//*arg2 = pieces[0][0][0][0];

	//int1 board[BOARDHEIGHT][BOARDWIDTH];

	//memcpy(&board, baseBoard, BOARDHEIGHT * BOARDWIDTH);

	int5 result[2] = {0,0};

	int pieceNumber ;
	int5 width ;
	int5 height ;

	for(int5 x = 0; x < length; x++){
		getPieceData(puzzle[x], &pieceNumber, &width, &height);
		findValidPosition(baseBoard, pieces[pieceNumber][0], width,height,&result);
		placePiece(&baseBoard, pieces[pieceNumber][0], result);
	}

	saveBoard(baseBoard, ram);

	//arg1[0] = 'Y';
	return 0;
}

void getPieceData(char pieceName, int *pieceNumber , int5 *width, int5 *height){

	switch(pieceName){

		//int5 pieceNumber = int5(0);
	    case 'I':
	    	*pieceNumber = 0;
			*width = int5(4);
	    	*height = int5(1);
	      break;

	    case 'O':
	    	*pieceNumber = 1;
			*width = int5(2);
			*height = int5(2);
	      break;

	    case 'T':
	    	*pieceNumber = 2;
			*width = int5(3);
			*height = int5(2);
		  break;

	    case 'J':
	    	*pieceNumber = 3;
			*width = int5(2);
			*height = int5(3);
		  break;

	    case 'L':
	    	*pieceNumber = 4;
			*width = int5(2);
			*height = int5(3);
		  break;

	    case 'S':
	    	*pieceNumber = 5;
			*width = int5(3);
			*height = int5(2);
		  break;

	    case 'Z':
	    	*pieceNumber = 6;
			*width = int5(3);
			*height = int5(2);
		  break;

	    default:
	    	*pieceNumber = 0;
			*width = int5(4);
			*height = int5(1);
	}
}

void placePiece(int1 (*board)[BOARDHEIGHT][BOARDWIDTH], const int1 piece[4][4],  int5 result[2]){
	for(uint32 y = 0; y < 4; y++) {
		    for(uint32 x = 0; x < 4; x++) {
		    	if(piece[y][x] == 1){
		    		//printf(" %d ", (*result)[0]);
		    		(*board)[y + result[0]][x + result[1]] = int1(1);
		    	}
		    }
	}


}

void saveBoard(int1 board[BOARDHEIGHT][BOARDWIDTH],uint32 *ram ){
	for(uint32 y = 0; y < BOARDHEIGHT; y++) {
	    for(uint32 x = 0; x < BOARDWIDTH; x++) {
	        ram[y*BOARDWIDTH+x] = board[y][x];
	    }
	}
}

bool findLowest(const int1 piece[4][4], int1 (*lowest)[4]){
	bool found = false;

	for( int5 y = 3; y >= 0; y --){
		if(!found){
			for (int5 x = 0; x < 4; x++){

				(*lowest)[x] = piece[y][x];
				//printf("Lowest: %d \n\r", piece[y][x].to_int());

				if(piece[y][x] == int1(1)){
					//printf("HERE");

					found = true;
				}
			}
		}else{
			return true;
		}
	}
	return found;
}

bool checkSquare(int1 board[BOARDHEIGHT][BOARDWIDTH],const int1 piece[4][4],int5 startX, int5 startY, int5 width, int5 height){

	for(int5 y = 0; y < height; y++){
			for( int5 x = 0; x < width; x++){
				if(board[y+startY][x + startX] == int1(1) and piece[y][x] == int1(1)){
					return false;
				}
			}
	}

	return true;
}

bool checkAbove(int1 board[BOARDHEIGHT][BOARDWIDTH], int5 startX, int5 endX, int5 startY, int5 endY){

	for(int5 x = startX; x < endX; x ++){
		for(int5 y = startY; y > endY; y--){
			if(board[y][x] == int1(1)){
				return false;
			}
		}
	}

	return true;
}

bool checkBelow(int1 board[BOARDHEIGHT][BOARDWIDTH], int1 lowest[4], int5 startX, int5 startY, int5 endY){

	if(startY > endY){
		return true;
	}

	for(int5 x = 0; x < 4; x ++){
		if(board[startY][x + startX] == int1(1) and lowest[x] == int1(1)){
			return true;
		}
	}

	return false;
}

bool findValidPosition(int1 board[BOARDHEIGHT][BOARDWIDTH], const int1 piece[4][4], int5 width, int5 height, int5 (*result)[2]){

	for(int5 y = (BOARDHEIGHT - height); y > 0; y--){
		for(int5 x = 0; x < (BOARDWIDTH - width + int5(1)); x++){

			printf("Y: %d",  y.to_int());
			printf(", X: %d\n",  x.to_int());

			if( checkSquare(board, piece, x, y, width, height) ){

				if( checkAbove(board, x, x+width, y, 0 ) ){

					int1 lowest[4] = {0,0,0,0};
					//printf("Lowest: %d \n\r", lowest[0].to_int());
					findLowest(piece, &lowest);

					//printf("Lowest: %d,  ", lowest[0].to_int());
					//printf("Lowest: %d,  ", lowest[1].to_int());
					//printf("Lowest: %d,  ", lowest[2].to_int());
					//printf("Lowest: %d,  \n", lowest[3].to_int());



					if( checkBelow(board, lowest, x, y + height, BOARDHEIGHT - height ) ){
						(*result)[0] = y;
						(*result)[1] = x;

						printf("Y: %d \n\r",  y.to_int());
						return true;
					}
				}
			}

		}
	}

	return false;
}
