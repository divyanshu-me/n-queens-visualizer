#include "BacktrackingSolver.hpp"

// Constructor
BacktrackingSolver::BacktrackingSolver(int N_)
: N(N_), cols(N_, -1), board(N_, std::vector<int>(N_, 0))
{}

// Reset everything to start over
void BacktrackingSolver::start()
{
    while (!stk.empty()) stk.pop();
    std::fill(cols.begin(), cols.end(), -1);
    for (auto& row : board)
        std::fill(row.begin(), row.end(), 0);

    stk.push({0, 0, false});
}

// Returns true if a *new* full solution was just completed
bool BacktrackingSolver::step()
{
    while (!stk.empty())
    {
        Frame& f = stk.top();

        // If we've reached beyond the last row → full solution
        if (f.row == N)
        {
            // first time we see this frame, report solution
            if (!f.tried)
            {
                f.tried = true;
                return true;
            }
            // on the next step, pop and begin backtracking
            stk.pop();
            continue;
        }

        // Try placing queen at (row, col)
        if (!f.tried)
        {
            f.tried = true;
            if (isValid(f.row, f.col))
            {
                cols[f.row] = f.col;
                updateBoard();
                // descend to next row
                stk.push({f.row + 1, 0, false});
                return false;
            }
        }

        // Advance to next column in this row
        if (f.col + 1 < N)
        {
            f.col++;
            f.tried = false;
            continue;
        }

        // No more columns: backtrack
        cols[f.row] = -1;
        updateBoard();
        stk.pop();
    }

    // completely finished (no more frames)
    return false;
}

// Check against previously placed rows only
bool BacktrackingSolver::isValid(int row, int col)
{
    for (int r = 0; r < row; ++r)
    {
        int c = cols[r];
        if (c == col)                        return false;
        if (abs(r - row) == abs(c - col))    return false;
    }
    return true;
}

// Update 2D board for drawing
void BacktrackingSolver::updateBoard()
{
    for (int r = 0; r < N; ++r)
        for (int c = 0; c < N; ++c)
            board[r][c] = (cols[r] == c ? 1 : 0);
}

// Draw checkerboard + queens
void BacktrackingSolver::draw(sf::RenderWindow& window)
{
    float sizeF = window.getSize().x / float(N);
    sf::RectangleShape cell({ sizeF, sizeF });
    sf::CircleShape queen(sizeF / 3.f);

    for (int r = 0; r < N; ++r)
    for (int c = 0; c < N; ++c)
    {
        cell.setPosition({ c * sizeF, r * sizeF });
        cell.setFillColor(((r + c) % 2 == 0)
            ? sf::Color::White
            : sf::Color::Black);
        window.draw(cell);

        if (board[r][c])
        {
            queen.setPosition({ c * sizeF + sizeF/6.f,
                                r * sizeF + sizeF/6.f });
            queen.setFillColor(sf::Color::Red);
            window.draw(queen);
        }
    }
}
