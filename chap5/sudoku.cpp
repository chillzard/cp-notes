// i was attempting to use python to implement a sudoku solver
// and now, after understanding more about backtracking,
// i decided to reimplement the sudoku solver in C++
//
// C++11


#include <bits/stdc++.h>
using namespace std;

bool valid(vector<vector<int>> sudoku) {
    // check row
    for (auto i : sudoku) {
        vector<int> checkrow;
        for (auto j : i) {
            if (j != 0) {
                checkrow.push_back(j); 
            }
        }
        unordered_set<int> rowset(checkrow.begin(), checkrow.end());
        if (rowset.size() != checkrow.size()) {
            return false; 
        }
    }
    // check column
    for (int i = 0; i < 9; i++) {
        vector<int> checkcol;
        for (auto j: sudoku) {
            if (j[i] != 0) {
                checkcol.push_back(j[i]);
            }
        }
        unordered_set<int> colset(checkcol.begin(), checkcol.end());
        if (checkcol.size() != colset.size()) {
            return false;
        }
    }
    // check grid
    for (int i = 0; i <= 6; i += 3) {
        for (int j = 0; j <= 6; j += 3) {
            vector<int> box;
            for (int x = i; x < i + 3; x++) {
                for (int y = j; y < j + 3; y++) {
                    if (sudoku[x][y] != 0) {
                        box.push_back(sudoku[x][y]);
                    }
                }
            }
            unordered_set<int> boxset(box.begin(), box.end());
            if (box.size() != boxset.size()) {
                return false;
            }
        }
    }
    
    return true;
}

tuple<int, int> nav(int row, int col) {
    if (col >= 8) {
        return make_tuple(row + 1, 0);
    } else {
        return make_tuple(row, col + 1);
    }
}

bool solve(vector<vector<int>>& sudoku, int row, int col)
{
    if (row == 9) {
        return true;
    }
    else {
        if (sudoku[row][col] != 0) {
            int r, c;
            tuple<int, int> t = nav(row, col);
            tie(r, c) = t;
            if (solve(sudoku, r, c)) {
                return true;
            }
        }
        for (int i = 1; i <= 9; i++) {
            sudoku[row][col] = i;
            if (valid(sudoku)) {
                int r, c;
                tuple<int, int> t = nav(row, col);
                tie(r, c) = t;
                if (solve(sudoku, r, c)) {
                    return true;
                }
            }
            sudoku[row][col] = 0;
        }
    }
    return false;
}

void printSudoku(vector<vector<int>>& sudoku) {
    for (auto& row : sudoku) {
        for (int num : row) {
            cout << num << " ";
        }
        cout << endl;
    }
}

int main() {
    vector<vector<int>> sudoku = {
        {0, 0, 5, 8, 0, 9, 4, 7, 0},
        {0, 2, 0, 0, 6, 0, 0, 0, 1},
        {0, 7, 0, 0, 0, 0, 0, 6, 9},
        {4, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 2, 1, 0, 8, 9, 0, 6},
        {3, 0, 0, 9, 4, 0, 0, 2, 8},
        {2, 3, 0, 7, 5, 0, 6, 9, 4},
        {5, 0, 0, 0, 0, 3, 8, 0, 0},
        {6, 9, 0, 0, 0, 2, 3, 5, 0},
    };

    solve(sudoku, 0, 0);
    printSudoku(sudoku);
    return 0;

}