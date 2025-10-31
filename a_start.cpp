#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <stack>
#include <iomanip>
using namespace std;

/*
    Finds the shortest path from a start cell to a goal cell on a 2D grid.

    Each cell has:
      - g = cost from start to current
      - h = heuristic (estimated cost to goal)
      - f = g + h

    Time Complexity:  O(E log V)
    Space Complexity: O(V)
*/

// Directions for movement: up, down, left, right, and diagonals
int rowDir[8] = {-1, 1, 0, 0, -1, -1, 1, 1};
int colDir[8] = {0, 0, -1, 1, -1, 1, -1, 1};

// Cell structure for the grid
struct Cell {
    int parentRow, parentCol;
    double f, g, h;
    Cell() : parentRow(-1), parentCol(-1), f(FLT_MAX), g(FLT_MAX), h(FLT_MAX) {}
};

// Heuristic function — Euclidean distance
double calculateHValue(int row, int col, pair<int, int> dest) {
    return sqrt(pow(row - dest.first, 2) + pow(col - dest.second, 2));
}

// Check if cell is valid (inside grid)
bool isValid(int row, int col, int ROW, int COL) {
    return (row >= 0) && (row < ROW) && (col >= 0) && (col < COL);
}

// Check if cell is blocked (obstacle)
bool isUnBlocked(vector<vector<int>> &grid, int row, int col) {
    return grid[row][col] == 1;
}

// Check if cell is the destination
bool isDestination(int row, int col, pair<int, int> dest) {
    return row == dest.first && col == dest.second;
}

// Trace and print the final path
void tracePath(vector<vector<Cell>> &cellDetails, pair<int, int> dest) {
    cout << "\n🟦 Path Found: \n";
    int row = dest.first;
    int col = dest.second;
    stack<pair<int, int>> Path;

    while (!(cellDetails[row][col].parentRow == row &&
             cellDetails[row][col].parentCol == col)) {
        Path.push({row, col});
        int temp_row = cellDetails[row][col].parentRow;
        int temp_col = cellDetails[row][col].parentCol;
        row = temp_row;
        col = temp_col;
    }

    Path.push({row, col});

    while (!Path.empty()) {
        pair<int, int> p = Path.top();
        Path.pop();
        cout << "(" << p.first << "," << p.second << ")";
        if (!Path.empty())
            cout << " -> ";
    }
    cout << endl;
}

// A* Search Function
void aStarSearch(vector<vector<int>> &grid, pair<int, int> src, pair<int, int> dest) {
    int ROW = grid.size();
    int COL = grid[0].size();

    if (!isValid(src.first, src.second, ROW, COL)) {
        cout << "Invalid start position.\n";
        return;
    }
    if (!isValid(dest.first, dest.second, ROW, COL)) {
        cout << "Invalid destination.\n";
        return;
    }
    if (!isUnBlocked(grid, src.first, src.second) ||
        !isUnBlocked(grid, dest.first, dest.second)) {
        cout << "Source or destination is blocked.\n";
        return;
    }
    if (isDestination(src.first, src.second, dest)) {
        cout << "Already at the destination.\n";
        return;
    }

    vector<vector<bool>> closedList(ROW, vector<bool>(COL, false));
    vector<vector<Cell>> cellDetails(ROW, vector<Cell>(COL));

    int i = src.first, j = src.second;
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    cellDetails[i][j].parentRow = i;
    cellDetails[i][j].parentCol = j;

    // Priority queue for open list (min-heap)
    priority_queue<
        pair<double, pair<int, int>>,
        vector<pair<double, pair<int, int>>>,
        greater<>> openList;

    openList.push({0.0, {i, j}});
    bool foundDest = false;

    while (!openList.empty()) {
        pair<double, pair<int, int>> p = openList.top();
        openList.pop();

        i = p.second.first;
        j = p.second.second;
        closedList[i][j] = true;

        // Explore 8 possible moves
        for (int dir = 0; dir < 8; dir++) {
            int newRow = i + rowDir[dir];
            int newCol = j + colDir[dir];

            if (isValid(newRow, newCol, ROW, COL)) {
                if (isDestination(newRow, newCol, dest)) {
                    cellDetails[newRow][newCol].parentRow = i;
                    cellDetails[newRow][newCol].parentCol = j;
                    cout << "Destination found!" << endl;
                    tracePath(cellDetails, dest);
                    foundDest = true;
                    return;
                }
                // If the cell is not blocked and not already visited
                else if (!closedList[newRow][newCol] && isUnBlocked(grid, newRow, newCol)) {
                    double gNew = cellDetails[i][j].g + 1.0;
                    double hNew = calculateHValue(newRow, newCol, dest);
                    double fNew = gNew + hNew;

                    if (cellDetails[newRow][newCol].f == FLT_MAX || cellDetails[newRow][newCol].f > fNew) {
                        openList.push({fNew, {newRow, newCol}});
                        cellDetails[newRow][newCol].f = fNew;
                        cellDetails[newRow][newCol].g = gNew;
                        cellDetails[newRow][newCol].h = hNew;
                        cellDetails[newRow][newCol].parentRow = i;
                        cellDetails[newRow][newCol].parentCol = j;
                    }
                }
            }
        }
    }

    if (!foundDest)
        cout << "Failed to find the destination path.\n";
}

// MAIN FUNCTION
int main() {
    int ROW = 9, COL = 10;

    vector<vector<int>> grid = {
        {1, 1, 1, 1, 1, 1, 1, 0, 1, 1},
        {1, 1, 1, 1, 0, 1, 1, 0, 1, 1},
        {1, 1, 1, 0, 0, 0, 1, 1, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 1, 0, 1, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

    pair<int, int> src = {8, 0};
    pair<int, int> dest = {0, 0};

    aStarSearch(grid, src, dest);

    return 0;
}
