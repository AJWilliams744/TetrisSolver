#include "tetrissolver.h"
#define BOARDHEIGHT 20
#define BOARDWIDTH 6

uint32 mainmemory[BOARDHEIGHT * BOARDWIDTH];

int get_puzzle(uint32 seed, char *buf, int buf_size) {
    const char pieces[] = "IOTJLSZ";
    srand(seed);

    int puzzlesize = seed % 2 ? 4 : 12;
    if(buf_size < puzzlesize) return 0;

    for(int i = 0; i < puzzlesize; i++) {
        buf[i] = pieces[rand() % 7];
    }

    return 1;
}
void print_puzzle(uint32 ram[]){
	for(uint32 y = 0; y < BOARDHEIGHT; y++) {
		printf("|");
			for(uint32 x = 0; x < BOARDWIDTH; x++) {
				if(ram[y*BOARDWIDTH+x] == 0){
					printf("   ");
				}else{
					printf(" %d ", ram[y*BOARDWIDTH+x]);
				}

		    }
		printf("|\n");
		}
}

int main() {

    char puzzle[12];

    //Seed 0 is a 'hard' puzzle, so size 12
    get_puzzle(1, puzzle, sizeof(puzzle));

    //Set up the slave inputs to the hardware
    char arg1[] = "LOTS";
    int5 arg2 =  4;


    //Run the hardware
    tetrissolver(mainmemory, arg1, arg2);

    print_puzzle(mainmemory);

    //Read the slave outputs
    //printf("%.*s\n\r", 12, arg1);
    //printf("%d\n\r", arg2.to_int());


    return 0;
}


