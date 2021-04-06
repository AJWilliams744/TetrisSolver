#tetrominoes[7][4][4][4]
import random
import copy
from datetime import datetime
#I, O, T, J, L, S, Z
pieces = [
    [ #I
        [
            [1, 1, 1, 1],
            [0, 0, 0, 0],
            [0, 0, 0, 0],
            [0, 0, 0, 0]
        ], [
            [1, 0, 0, 0],
            [1, 0, 0, 0],
            [1, 0, 0, 0],
            [1, 0, 0, 0]
        ]
    ],
    [ #O
        [
            [1, 1, 0, 0],
            [1, 1, 0, 0],
            [0, 0, 0, 0],
            [0, 0, 0, 0]
        ]
    ],
    [ #T
        [
            [1, 1, 1, 0],
            [0, 1, 0, 0],
            [0, 0, 0, 0],
            [0, 0, 0, 0]
        ], [
            [1, 0, 0, 0],
            [1, 1, 0, 0],
            [1, 0, 0, 0],
            [0, 0, 0, 0]
        ], [
            [0, 1, 0, 0],
            [1, 1, 1, 0],
            [0, 0, 0, 0],
            [0, 0, 0, 0]
        ], [
            [0, 1, 0, 0],
            [1, 1, 0, 0],
            [0, 1, 0, 0],
            [0, 0, 0, 0]
        ]
    ],
    [ #J
        [
            [0, 1, 0, 0],
            [0, 1, 0, 0],
            [1, 1, 0, 0],
            [0, 0, 0, 0]
        ], [
            [1, 0, 0, 0],
            [1, 1, 1, 0],
            [0, 0, 0, 0],
            [0, 0, 0, 0]
        ], [
            [1, 1, 0, 0],
            [1, 0, 0, 0],
            [1, 0, 0, 0],
            [0, 0, 0, 0]
        ], [
            [1, 1, 1, 0],
            [0, 0, 1, 0],
            [0, 0, 0, 0],
            [0, 0, 0, 0]
        ]
    ],
    [ #L
        [
            [1, 0, 0, 0],
            [1, 0, 0, 0],
            [1, 1, 0, 0],
            [0, 0, 0, 0]
        ], [
            [1, 1, 1, 0],
            [1, 0, 0, 0],
            [0, 0, 0, 0],
            [0, 0, 0, 0]
        ], [
            [1, 1, 0, 0],
            [0, 1, 0, 0],
            [0, 1, 0, 0],
            [0, 0, 0, 0]
        ],  [
            [0, 0, 1, 0],
            [1, 1, 1, 0],
            [0, 0, 0, 0],
            [0, 0, 0, 0]
        ]
    ],
    [ #S
        [
            [0, 1, 1, 0],
            [1, 1, 0, 0],
            [0, 0, 0, 0],
            [0, 0, 0, 0]
        ], [
            [1, 0, 0, 0],
            [1, 1, 0, 0],
            [0, 1, 0, 0],
            [0, 0, 0, 0]
        ]
    ],
    [ #Z
        [
            [1, 1, 0, 0],
            [0, 1, 1, 0],
            [0, 0, 0, 0],
            [0, 0, 0, 0]
        ], [
            [0, 1, 0, 0],
            [1, 1, 0, 0],
            [1, 0, 0, 0],
            [0, 0, 0, 0]
        ]
    ]
]

piecesDic = {
    "I" : [0,4,1],
    "O" : [1,2,2],
    "T" : [2,3,2],
    "J" : [3,2,3],
    "L" : [4,2,3],
    "S" : [5,3,2],
    "Z" : [6,3,2],
}
boardHeight = 20
board = [[0 for i in range(6)] for j in range(boardHeight)]

def PrintCoor(x,y):
    print("X: " + str(x) + ", Y: " + str(y))

def PrintBoard(board):
    print("-----------------")
    
    for row in board:
        print("")
        print("|", end = "")
        for item in row:
            if(str(item) == "0"):
                print(". ", end = "")
            else:
                print(str(item) + " ", end = "")
        print("|", end = "")
    print("")
    print("-----------------")

def CountBoard(board):
    counter = 0
    #PrintBoard(board)
    for y in range(boardHeight - 1, -1, -1):
        
        found = False
        for x in range(0,6):
            if(board[y][x] == 1):
                found = True
        if(found == False):
            return counter
        counter += 1
        
    return counter           

def GetPuzzleSize(seed):
    if (seed % 2):
        return 4
    else:
        return 12

def DoesBoardExist(allBoards, newBoard):
    for board in allBoards:
        if(board == newBoard):
            return True
    return False

def GetPuzzle(seed, puzzle, size):

    pieces = "IOTJLSZ"
    random.seed(seed)

    puzzlesize = 0

    if (seed % 2):
        puzzlesize = 4
    else:
        puzzlesize = 12
    
    if (size < puzzlesize): return 0

    for x in range(0, puzzlesize):
        puzzle[x] = pieces[random.randint(0, 100000000000) % 7]

    return puzzle

def FindLowest(piece):
    result = []

    for row in range(3,-1,-1):
        if(result != []): return result
        for item in range(4):
            if(piece[row][item] == 1):
                result.append(item)

    return result

def CheckAbove(startX, endX, startY, endY, board):
    for x in range(startX, endX):
        for y in range(startY, endY, -1):
            if(board[y][x] == 1):
                return False
    return True

def CheckBelow(lowest,startX, startY, endY, board):
    if(startY > endY):
        return True
    for x in lowest:
        for y in range(startY, startY + 1):
            if(board[y][x + startX] == 1):
                return True
    return False

def CheckSquare(startX, startY, width, height, board, piece):
    for y in range(height):
        for x in range(width):
            if(board[y + startY][x + startX] == 1 and piece[y][x] == 1):
                return False
    return True

def FindValidPosition(board, pieceName):
    
    validatedMoves = []
    pieceData = piecesDic[pieceName]
    maxX = pieceData[1]
    maxY = pieceData[2]

    for y in range(boardHeight - maxY , 0 , -1):
        for x in range(6 - maxX + 1):
            if(CheckSquare(x, y, maxX, maxY, board, pieces[pieceData[0]][0])):
                if(CheckAbove(x,x+maxX, y, 0, board) and CheckBelow(FindLowest(pieces[pieceData[0]][0]),x, y + maxY, boardHeight - 1, board)):                  
                    
                    validatedMoves.append([x,y])
        

    return validatedMoves

globalBoards = []
def SolveRandom(board, puzzle):

    currentBoard = copy.deepcopy(board)
    for pieceName in puzzle:

        pieceData = piecesDic[pieceName]
        piece = pieces[pieceData[0]]

        result = FindValidPosition(currentBoard, pieceName)

        x = result[0][0]
        y = result[0][1]
           
        for row in range(pieceData[2]):
            for item in range(pieceData[1]):
                if (piece[0][row][item] != 0):        
                    currentBoard[y + row][x + item] = piece[0][row][item]

    boardCount = CountBoard(currentBoard)

    return boardCount

min = 20
bestBoard = []

def SolveRecursive(board, puzzle):

    global min
    global bestBoard
    pieceName = puzzle[0]

    pieceData = piecesDic[pieceName]
    piece = pieces[pieceData[0]]

    result = FindValidPosition(board, pieceName)
    
    for item in result:
        currentBoard = []
        currentBoard = copy.deepcopy(board)

        x = item[0]
        y = item[1]
    
        for row in range(pieceData[2]):
            for item in range(pieceData[1]):
                if (piece[0][row][item] != 0):        
                    currentBoard[y + row][x + item] = piece[0][row][item]
        if(len(puzzle) == 1):
            height = CountBoard(currentBoard)
            if(height < min):
                min = height
                bestBoard = currentBoard

        elif CountBoard(currentBoard) < min:

            SolveRecursive(currentBoard, puzzle[1:])

    return bestBoard


def SolvePuzzle(board, puzzle):
    counter = 0
    print(puzzle)

    global globalBoards
    globalBoards.append(board)

    for pieceName in puzzle:

        pieceData = piecesDic[pieceName]
        piece = pieces[pieceData[0]]
        boardCount = len(globalBoards)

        for boardNumber in range(boardCount):           

            result = FindValidPosition(globalBoards[boardNumber], pieceName)
            
            for item in result:
                currentBoard = []
                currentBoard = copy.deepcopy(globalBoards[boardNumber])

                x = item[0]
                y = item[1]
                #PrintCoor(x,y)       
                for row in range(pieceData[2]):
                    for item in range(pieceData[1]):
                        if (piece[0][row][item] != 0):        
                            currentBoard[y + row][x + item] = piece[0][row][item]
                #print(pieceName)
                #if(not(DoesBoardExist(globalBoards,currentBoard))):
                # if(CountBoard(currentBoard) < min):
                globalBoards.append(currentBoard)
                #else:
                   # pass
            # PrintBoard(board)    
            counter += 1    
            if(counter % 1000 == 0):
                print(counter)           
        del globalBoards[:boardCount]
        print(pieceName)
        # print(counter)
        # for row in totalMoves:
        #     for item in row:
        #         
    #print(counter)
    bestBoard = globalBoards[0]
    bestHeight = 15
    for checkBoard in globalBoards:
        boardCount = CountBoard(checkBoard)
        #print(boardCount)
        if(boardCount < bestHeight):
            bestHeight = boardCount
            bestBoard = checkBoard
    print(bestHeight)
    return bestBoard

seed = 0

puzzle = ["a"] * GetPuzzleSize(seed)

puzzle = GetPuzzle(seed,puzzle, len(puzzle))


print("-------------")
#print(SolveRandom(board,puzzle))
print(datetime.now())
board = SolveRecursive(board, puzzle)
print(datetime.now())
PrintBoard(board)


print("----------")

#PrintBoard(board)