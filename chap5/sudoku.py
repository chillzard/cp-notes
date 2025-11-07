# my weird attempt to solve sudoku in python
# again, this is for the purpose of learning backtracking
# which is relevant to the current chapter
#
# also, the reason why I chose python
# is because I did try to use python to solve sudoku
# years ago so it's easier for me to redo it again
# in python since I did remember the general way to do it
# also python is easier to read :)
# sudoku somehow
from pprint import pprint
sudoku = [
    [0, 0, 5, 8, 0, 9, 4, 7, 0],
    [0, 2, 0, 0, 6, 0, 0, 0, 1],
    [0, 7, 0, 0, 0, 0, 0, 6, 9],
    [4, 0, 0, 0, 0, 0, 1, 0, 0],
    [0, 0, 2, 1, 0, 8, 9, 0, 6],
    [3, 0, 0, 9, 4, 0, 0, 2, 8],
    [2, 3, 0, 7, 5, 0, 6, 9, 4],
    [5, 0, 0, 0, 0, 3, 8, 0, 0],
    [6, 9, 0, 0, 0, 2, 3, 5, 0],
]
    
def valid(sudoku):
    # check row
    for i in sudoku:
        checkrow = [e for e in i if e != 0]
        if len(checkrow) != len(set(checkrow)):
            return False
    # check column
    for i in range(0, 9):
        reccol = []
        for j in sudoku:
            reccol.append(j[i])
        checkcol = [e for e in reccol if e != 0] 
        if len(checkcol) != len(set(checkcol)):
            return False
    # check 3x3 box
    for i in [0, 3, 6]:
        for j in [0, 3, 6]:
            box = [sudoku[r][c] for c in range(j, j + 3) for r in range(i, i + 3)]
            checkbox = [e for e in box if e != 0]
            if len(checkbox) != len(set(checkbox)):
                return False
    return True
def nav(row, col):
    if col >= 8:
        return row + 1, 0
    else:
        return row, col + 1

def solve(sudoku, row, col):
    if row == 9:
        return sudoku
    else:
        if sudoku[row][col] != 0:
            nrow, ncol = nav(row, col)
            if solve(sudoku, nrow, ncol):
                return sudoku
        else:
            for i in range(1, 10):
                sudoku[row][col] = i
                if valid(sudoku):
                    nrow, ncol = nav(row, col)
                    if solve(sudoku, nrow, ncol):
                        return sudoku
                sudoku[row][col] = 0

pprint(solve(sudoku, 0, 0))