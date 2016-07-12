#include<iostream>
#include<string>
#include<stdlib.h>
using namespace std;

int generate_Random(int min,int max)
{
        return(min + (rand() % (int)(max - min + 1)));
}

class cell
{
    public:
        bool is_bomb,is_flagged,is_hidden;
        char mark;
        cell()
        {
            this->is_flagged=false;
            this->is_hidden=true;
            this->mark=0;
        }
};

class boards
{
    public:
        int n;
        cell** board;

        void set_board(int i)
        {
            cout<<"1";
            this->n=i;
           //board = new cell*[n];
            *board = (cell *)malloc(8*sizeof(cell *));
            cout<<"3";
            for(int j=0;j<n;j++)
                board[j] = new cell[8];
        }

        void generate_bombs(int bombs)
        {
            if(bombs = 0)
                return;
            int i = generate_Random(0,n);
            int j = generate_Random(0,n);
            if(!board[i][j].is_bomb)
            {
                board[i][j].is_bomb-true;
                generate_bombs(bombs-1);
            }
            else
            {
                generate_bombs(bombs);
            }
        }

        bool check_marker(int i,int j)
        {
            return board[i][j].is_bomb;
        }

        void setup_markers()
        {
            for(int i=0;i<n;i++)
                for(int j=0;j<n;j++)
                {
                    int counter=0;
                    if(i!=0&&check_marker(i-1,j))
                        counter++;
                    if(i!=0&&j!=0&&check_marker(i-1,j-1))
                        counter++;
                    if (j!=0&&check_marker(i,j-1))
                        counter++;
                    if (i!=n-1&&check_marker(i+1,j))
                        counter++;
                    if (j!=n-1&&check_marker(i,j+1))
                        counter++;
                    if (j!=n-1&&i!=n-1&&check_marker(i+1,j+1))
                        counter++;
                    if (i!=0&&j!=n-1&&check_marker(i-1,j+1))
                        counter++;
                    if (i!=n-1&&j!=0&&check_marker(i+1,j-1))
                        counter++;
                    board[i][j].mark = counter+48;
                }
        }

        void disp_board()
        {
            string output = "";
            for (int i=0;i<n;i++)
            {
                for (int j=0;j<n;j++)
                {
                    if (board[i][j].is_flagged)
                        output += "| X ";
                    else if (board[i][j].is_hidden)
                        output += "| - ";
                    else if (board[i][j].is_bomb)
                        output += "| * ";
                    else
                    {
                        output += "| ";
                        output += board[i][j].mark;
                        output += " ";
                    }
                }
                output += "|\n        ";
            }
            cout<<output;
        }

        void toggle_hidden(int i, int j)
        {
            if (i<0||j<0||i>=n||j>= n)
            {
                cout<<"    Invalid Output";
                exit(EXIT_FAILURE);
            }
            if (!board[i][j].is_hidden)
            {
                cout<<"    Cell revealed, re-enter input...\n    ";
                int temp1, temp2;
                cin>>temp1>>temp2;
                toggle_hidden(temp1, temp2);
                return;
            }
            board[i][j].is_hidden = false;
        }

        int update_moves()
        {
            int counter=0;
            for (int i=0;i<n;i++)
            {
                for (int j=0;j<n;j++)
                {
                    if (!board[i][j].is_hidden)
                        continue;
                    else if(board[i][j].is_bomb)
                        continue;
                    else
                        counter++;
                }
            }
            return counter;
        }

        void expand(int i, int j)
        {
            if(board[i][j].is_bomb)
                return;
            else if(!board[i][j].is_hidden)
                return;
            else
                board[i][j].is_hidden=false;
            if(board[i][j].mark>0)
                return;
            if(i!=0&&j!=0)
                expand(i-1,j-1);
            if(i!=n-1&&j!=n-1)
                expand(i+1,j+1);
            if(j!=n-1)
                expand(i,j+1);
            if(i!=n-1)
                expand(i+1,j);
            if(i!=0&&j!=n-1)
                expand(i-1,j+1);
            if(i!=n-1&&j!=0)
                expand(i+1,j-1);
            if(i!=0)
                expand(i-1,j);
            if(j!=0)
                expand(i,j-1);
        }

        void  toggle_flag()
        {
            cout<<"    Enter Co-ordinates to Flag/Unflag...\n    ";
            cout<<"    Enter Row Co-ordinate: ";
            int i;
            cin>>i;

            cout<<"    Enter Column Co-ordinate: ";
            int j;

            if(i<0||j<0||i>=n||j>=n)
            {
                cout<<"    Invalid input...\n    Re-enter Input...";
                toggle_flag();
                return;
            }
            board[i][j].is_flagged=!board[i][j].is_flagged;
        }

        void  make_move()
        {
            cout<<"    Enter Co-ordinates to sweep...\n    ";
            cout<<"    Enter Row Co-ordinate: ";
            int i;
            cin>>i;
            cout<<"    Enter Column Co-ordinate: ";
            int j;
            cin>>j;
            if(i < 0 || j < 0 || i >= n || j >= n)
            {
                cout<<"    Invalid input...\nRe-enter Input...";
                make_move();
                return;
            }
            if (board[i][j].mark == 0)
                expand(i,j);

            else if (board[i][j].is_bomb)
            {
                for (int l = 0; l < n; l++)
                    for (int m = 0; m < n; m++)
                        if(board[l][m].is_bomb)
                            board[l][m].is_hidden = false;
                disp_board();
                cout<<"    Game Over...\n    ";
                exit(EXIT_FAILURE);
            }

            else
                toggle_hidden(i, j);
        }

        void  play()
        {
            int bombs=10;//(n*n)/4 + 1;
            generate_bombs(bombs);
            int possible_moves = n*n - bombs;
            setup_markers();
            while(possible_moves>0)
            {
                disp_board();
                cout<<"    What would you like to do?\n    1. Sweep\n    2. Flag/Unflag\n    ";
                int temp;
                cin>>temp;
                switch (temp)
                {
                    case 1:
                        make_move();
                        break;
                    case 2:
                        toggle_flag();
                        break;
                    default:
                        cout<<"    Invalid Input \n    ";
                }
                possible_moves = update_moves();

            }
            cout<<"    You win!\n    ";
        }
};

int main()
{

        cout<<"    Enter Difficulty level: \n    ";
        int n;
        cin>>n;
        boards board;
        board.set_board(n);
        board.play();
        return 0;
}
