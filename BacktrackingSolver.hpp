#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <stack>

// A single backtracking “frame”: which row, which column, and
// whether we already tried placing here.
struct Frame {
    int  row, col;
    bool tried;
};

class BacktrackingSolver {
public:
    BacktrackingSolver(int N);
    // reset solver
    void start();
    // perform exactly one backtracking action;
    // returns true if a *new* full solution was just reached
    bool step();
    // render current board
    void draw(sf::RenderWindow&);

private:
    bool isValid(int row, int col);
    void updateBoard();

    int N;
    std::vector<int> cols;                  // cols[r] = column of queen or -1
    std::stack<Frame> stk;
    std::vector<std::vector<int>> board;    // for drawing
};
