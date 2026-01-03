#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;
using namespace chrono;

const int INF = numeric_limits<int>::max();

vector<vector<int>> generateGrid(int n) {
    vector<vector<int>> grid(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            grid[i][j] = rand() % 9 + 1;
        }
    }
    return grid;
}


int minPathSumIterative(const vector<vector<int>>& grid, int n) {
    vector<vector<int>> dp(n, vector<int>(n));

    dp[0][0] = grid[0][0];

    for (int i = 1; i < n; i++) {
        dp[i][0] = dp[i - 1][0] + grid[i][0];
    }

    for (int j = 1; j < n; j++) {
        dp[0][j] = dp[0][j - 1] + grid[0][j];
    }

    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
        }
    }

    return dp[n - 1][n - 1];
}


int minPathSumRecursive(const vector<vector<int>>& grid, int i, int j) {
    if (i == 0 && j == 0)
        return grid[0][0];

    if (i < 0 || j < 0)
        return INF;

    int up = minPathSumRecursive(grid, i - 1, j);
    int left = minPathSumRecursive(grid, i, j - 1);

    int best = min(up, left);
    if (best == INF)
        return INF;

    return best + grid[i][j];
}


int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    vector<int> testSizes = {5, 10, 15};

    cout << "Ukuran Grid  | Iteratif (ms) | Rekursif (ms) | Min Sum    | Rec Sum \n";
    cout << "------------------------------------------------------------------------\n";

    for (int n : testSizes) {
        auto grid = generateGrid(n);

        auto startIter = high_resolution_clock::now();
        int resultIter = minPathSumIterative(grid, n);
        auto endIter = high_resolution_clock::now();
        auto timeIter = duration_cast<milliseconds>(endIter - startIter).count();

        auto startRec = high_resolution_clock::now();
        int resultRec = minPathSumRecursive(grid, n - 1, n - 1);
        auto endRec = high_resolution_clock::now();
        auto timeRec = duration_cast<milliseconds>(endRec - startRec).count();

        cout << n << " x " << n << "\t\t | "
             << timeIter << "\t\t\t | "
             << timeRec << "\t\t\t"
             << " | MinSum: " << resultIter
             << " | RecSum: " << resultRec
             << endl;

    }

    return 0;
}
