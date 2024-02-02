#include <iostream>
#include <vector>
#include <queue>
#include <climits> // for INT_MAX

using namespace std;

struct Point {
    int x;
    int y;

    Point(int x, int y) : x(x), y(y) {}
};

bool isValid(int x, int y, int rows, int cols) {
    return (x >= 0 && x < rows && y >= 0 && y < cols);
}

int bfs(const vector<vector<char>>& labyrinth, const vector<Point>& initialPositions) {
    const int rows = labyrinth.size();
    const int cols = labyrinth[0].size();
    const Point destination(rows - 1, cols - 1);

    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    vector<vector<int>> timeTaken(rows, vector<int>(cols, INT_MAX)); // Time taken for each position
    queue<pair<Point, int>> q; // Pair of position and time

    for (const auto& initialPosition : initialPositions) {
        q.push({initialPosition, 0}); //adding wizards to initial position
        visited[initialPosition.x][initialPosition.y] = true;
        timeTaken[initialPosition.x][initialPosition.y] = 0;
    }

    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    while (!q.empty()) {
        Point current = q.front().first;
        int time = q.front().second;
        q.pop();

        if (current.x == destination.x && current.y == destination.y) {
            return timeTaken[current.x][current.y];
        }

        for (const auto& direction : directions) {
            int newX = current.x + direction.first;
            int newY = current.y + direction.second;

            if (isValid(newX, newY, rows, cols) && labyrinth[newX][newY] != '#' && !visited[newX][newY]) {
                q.push({Point(newX, newY), time + 1});
                visited[newX][newY] = true;
                timeTaken[newX][newY] = time + 1;
            }
        }
    }

    return -1; // If no wizard can reach the exit
}

int main() {
    // Example labyrinth map
    vector<vector<char>> labyrinth = {
        {'S', '.', '.', '#', '#'},
        {'#', '#', '.', '#', '#'},
        {'.', '.', '.', '.', '#'},
        {'#', '#', '#', '.', '.'},
        {'.', '#', '#', '.', 'D'}
    };

    // Example initial positions of three competing wizards
    vector<Point> initialPositions = {
        Point(0, 0),  // Wizard 1
        Point(1, 0),  // Wizard 2
        Point(2, 1)   // Wizard 3
    };

    int result = bfs(labyrinth, initialPositions);
    if (result != -1) {
        cout << "The first wizard to reach the exit will take " << result << " minutes." << endl;

        // Find the wizard that reaches the exit first and the fastest wizard
        int fastestWizard = 0;
        for (int i = 1; i < initialPositions.size(); ++i) {
            int wizardTime = bfs(labyrinth, {initialPositions[i]});
            if (wizardTime != -1 && wizardTime < result) {
                result = wizardTime;
                fastestWizard = i;
            }
        }

        cout << "Wizard " << fastestWizard + 1 << " will get out of the labyrinth first." << endl;
        cout << "The speed of Wizard " << fastestWizard + 1 << " is " << 1.0 / result << " corridors per minute." << endl;
    } else {
        cout << "None of the wizards can reach the exit." << endl;
    }

    return 0;
}