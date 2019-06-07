#include <bits/stdc++.h>
#define Blank ' '
#define Character '+'
#define Cross 'X'
#define Circle 'O'
#define empty '0'
int move = 0;
char Board_Layout[7][7];
char Check_Board[3][3] = {empty};

class Board
{
public:
    void initialize();
    void changeBoard(int x, int y);
    void showBoard();
};

void Board::initialize()
{
    for (int i = 0; i < 7; i++)
    {

        for (int j = 0; j < 7; j++)
        {

            if ((i + 1) % 2 == 0 && (j + 1) % 2 == 0)
            {
                Board_Layout[i][j] = Blank;
            }
            else
            {
                Board_Layout[i][j] = Character;
            }
        }
    }
}

void Board::showBoard()
{
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            printf("%c ", Board_Layout[i][j]);
        }
        printf("\n");
    }
}

void Board::changeBoard(int x, int y)
{
    x = (2 * x) + 1;
    y = (2 * y) + 1;
    if (move % 2 == 0)
    {
        Board_Layout[x][y] = Cross;
    }
    else
    {
        Board_Layout[x][y] = Circle;
    }
}

class InputGenerator
{
public:
    virtual void Move() = 0;
    virtual int verifyMove(int x, int y) = 0;
    virtual bool CheckWin() = 0;
    virtual bool rowCrossed() = 0;
    virtual bool columnCrossed() = 0;
    virtual bool diagonalCrossed() = 0;
};
bool InputGenerator::rowCrossed()
{
    for (int i = 0; i < 3; i++)
    {
        if (Check_Board[i][0] == Check_Board[i][1] &&
            Check_Board[i][1] == Check_Board[i][2] &&
            Check_Board[i][0] != ' ')
            return (true);
    }
    return (false);
}
bool InputGenerator::columnCrossed()
{
    for (int i = 0; i < 3; i++)
    {
        if (Check_Board[0][i] == Check_Board[1][i] &&
            Check_Board[1][i] == Check_Board[2][i] &&
            Check_Board[0][i] != ' ')
            return (true);
    }
    return (false);
}
bool InputGenerator::diagonalCrossed()
{
    if (Check_Board[0][0] == Check_Board[1][1] &&
        Check_Board[1][1] == Check_Board[2][2] &&
        Check_Board[0][0] != ' ')
        return (true);

    if (Check_Board[0][2] == Check_Board[1][1] &&
        Check_Board[1][1] == Check_Board[2][0] &&
        Check_Board[0][2] != ' ')
        return (true);

    return (false);
}
bool InputGenerator::CheckWin()
{
    if(diagonalCrossed() || columnCrossed() || rowCrossed())
    {
        return (true);
    }
    return (false);
}
int InputGenerator::verifyMove(int x, int y)
{
    if (x > 2 || y > 2 || x < 0 || y < 0 || Check_Board[x][y] != empty)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

class User : public InputGenerator, public Board
{
    void Move();
    
};

void User::Move()
{
    int x, y, valid = 0;

    while (valid == 0)
    {
        std::cout << "Give Values:"
                  << "\nX : ";
        scanf("%d", &x);
        std::cout << "\nY : ";
        scanf("%d", &y);
        if (!verifyMove(x, y))
        {
            std::cout << "INVALID INPUT\n"
                      << "ENTER AGAIN\n";
            continue;
        }
        else
        {
            Check_Board[x][y] = Cross;
            std::cout << "Changing Board...\n";
            changeBoard(x, y);
            if (CheckWin())
            {
                std::cout << "CONGRATULATIONS YOU WON!!!";
            }
        }
    }
}

class Computer : public InputGenerator, public Board
{
};
void showInstructions()
{
    printf("\t\t\t  Tic-Tac-Toe\n\n");
    Board board;
    board.initialize();
    board.showBoard();
    std::cout << "Give input as x and y to choose your desired cell.\n";
}

int main()
{
    showInstructions();
    return 0;
}