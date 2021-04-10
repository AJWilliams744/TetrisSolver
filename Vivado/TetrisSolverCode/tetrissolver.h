#ifndef __TETRISSOLVER_H_
#define __TETRISSOLVER_H_

#define BOARDHEIGHT 20
#define BOARDWIDTH 6

#include <stdio.h>
#include <stdlib.h>
#include <ap_int.h>

//Typedefs
typedef unsigned int uint32;
typedef int int32;
typedef ap_uint<1> int1;
typedef ap_uint<2> int2;
//typedef ap_uint<4> int5;
typedef ap_uint<5> int5;

int32 tetrissolver(uint32 *ram, char puzzle[12], int5 length);
bool findValidPosition(int1 board[BOARDHEIGHT][BOARDWIDTH], const int1 piece[4][4], int5 width, int5 height, int5 (*result)[2]);
bool checkBelow(int1 board[BOARDHEIGHT][BOARDWIDTH], int1 lowest[4], int5 startX, int5 startY, int5 endY);
bool checkAbove(int1 board[BOARDHEIGHT][BOARDWIDTH], int5 startX, int5 endX, int5 startY, int5 endY);
bool checkSquare(int1 board[BOARDHEIGHT][BOARDWIDTH],const int1 piece[4][4],int5 startX, int5 startY, int5 width, int5 height);
bool findLowest(const int1 piece[4][4], int1 (*lowest)[4]);
void saveBoard(int1 board[BOARDHEIGHT][BOARDWIDTH],uint32 *ram );
void placePiece(int1 (*board)[BOARDHEIGHT][BOARDWIDTH], const int1 piece[4][4],  int5 result[2]);
void getPieceData(char pieceName, int *pieceNumber , int5 *width, int5 *height);

#endif
