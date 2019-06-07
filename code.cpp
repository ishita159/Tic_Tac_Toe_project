#include <bits/stdc++.h>
using namespace std;
#define Blank ' '
#define Character '+'
#define Cross 'X'
#define Circle 'O'
#define empty '0'
bool Turn = 0;
char Board_Layout[7][7];
char Check_Board[3][3] = {empty};

std::string reset = "\033[0m";
std::string black = "\033[0;30m";
std::string blackb = "\033[1;30m";
std::string white = "\033[0;37m";
std::string whiteb = "\033[1;37m";
std::string red = "\033[0;31m";
std::string redb = "\033[1;31m";
std::string green = "\033[0;32m";
std::string greenb = "\033[1;32m";
std::string yellow = "\033[0;33m";
std::string yellowb = "\033[1;33m";
std::string blue = "\033[0;34m";
std::string blueb = "\033[1;34m";
std::string purple = "\033[0;35m";
std::string purpleb = "\033[1;35m";
std::string lightblue = "\033[0;36m";
std::string lightblueb = "\033[1;36m";
#define underline "\033[4m"
#define closeunderline "\033[0m"

int randNum(int min, int max)
{
    return rand() % max + min;
}

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
        cout << "\t\t\t\t\t";
        for (int j = 0; j < 7; j++)
        {
            if (Board_Layout[i][j] == Character)
            {
                cout << blue << Board_Layout[i][j] << reset << " ";
            }
            else
            {
                cout << yellow << Board_Layout[i][j] << reset << " ";
            }
        }
        printf("\n");
    }
    /* BOARD DESIGN
       + + + + + + + 
       +   +   +   + 
       + + + + + + + 
       +   +   +   + 
       + + + + + + + 
       +   +   +   + 
       + + + + + + + 
    */
}

void Board::changeBoard(int x, int y)
{
    x = (2 * x) + 1;
    y = (2 * y) + 1;
    if (Turn == 0)
    {
        Board_Layout[x][y] = Cross;
    }
    else
    {
        Board_Layout[x][y] = Circle;
    }
}

void showInstructions()
{
    cout << underline << "\t\t\t\t\tTic-Tac-Toe\n\n";
    Board board;
    board.initialize();
    board.showBoard();
    cout << "\n\n1.Give input as x and y to choose your desired cell.\n2.Play the FIRST MOVE\n\t\t\t\t\tBEGIN...\n\n";
}
void GameOver()
{
    cout << underline << "\t\t\t\t\tMAIN MENU\n\n"<<closeunderline;
    cout << "\t\t\t\t1. Press 1 to START NEW GAME\n\t\t\t\t2. Press 2 to EXIT\nEnter Choice...\n\t";
    int choice;
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        cout << "\t\t\t\tExiting Game...";
        break;

    case 2:
        system("cls");
        cout << "\t\t\t\tNEW GAME\n";
        showInstructions();
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
    virtual bool Intelligence_Level_Computer() = 0;
    virtual bool Intelligence_Level_User() = 0;
    virtual void randomMove() = 0;
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
    if (diagonalCrossed() || columnCrossed() || rowCrossed())
    {
        std::cout << "\t\t\t\tGAME OVER!!";
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
public:
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
        if (!verifyMove(x - 1, y - 1))
        {
            std::cout << "\t\t\t\tINVALID INPUT\n"
                      << "\t\t\t\tENTER AGAIN\n";
            continue;
        }
        else
        {
            Check_Board[x - 1][y - 1] = Cross;
            std::cout << "Changing Board...\n";
            changeBoard(x - 1, y - 1);
            cout << "\n\n";
            showBoard();
            valid = 1;
            Turn = 1;
            if (CheckWin())
            {
                std::cout << "\n\t\t\t\tCONGRATULATIONS YOU WON!!!\n\n\n";
                showBoard();
                GameOver();
            }
        }
    }
}

class Computer : public InputGenerator, public Board
{
public:
    void move();
    bool Intelligence_Level_Computer();
    bool Intelligence_Level_User();
    void randomMove();
};
bool Computer::Intelligence_Level_Computer()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (Check_Board[i][j] == empty)
            {
                Check_Board[i][j] = Circle;
                if (CheckWin())
                {
                    changeBoard(i, j);
                    showBoard();
                    cout << "\n\t\t\t\tCOMPUTER WON!!!\n\n\n";
                    return (true);
                }
                else
                {
                    Check_Board[i][j] = empty;
                }
            }
        }
    }
    return (false);
}
bool Computer::Intelligence_Level_User()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (Check_Board[i][j] == empty)
            {
                Check_Board[i][j] = Cross;
                if (CheckWin())
                {
                    Check_Board[i][j] = Circle;
                    Turn = 0;
                    changeBoard(i, j);
                    return (true);
                }
                else
                {
                    Check_Board[i][j] = empty;
                }
            }
        }
    }
    return (false);
}
void Computer::randomMove()
{
    int run = 0;
    while (run == 0)
    {
        int x = randNum(0, 2);
        int y = randNum(0, 2);
        if (Check_Board[x][y] == empty)
        {
            Check_Board[x][y] = Circle;
            changeBoard(x, y);
            run = 1;
            Turn = 0;
        }
    }
}

void Computer::move()
{
    if (Intelligence_Level_Computer())
    {
        GameOver();
    }
    else
    {
        if (Intelligence_Level_User())
        {
            cout << "\n\n";
            showBoard();
        }
        else
        {
            randomMove();
            cout << "\n\n";
            showBoard();
        }
    }
}
/*void playGame()
{
    showInstructions();
    Computer computer;
    User user;
    int moves = 9;
    while (moves--)
    {
        if (Turn == 0)
        {
            user.Move();
        }
        if (Turn == 1)
        {
            computer.move();
        }
    }
}
*/
int main()
{
    // playGame();
    showInstructions();
    GameOver();

    return 0;
}