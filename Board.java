import java.util.Random;
import java.util.Scanner;

/**
 * Created by shubhangkulkarni on 6/14/16.
 */
public class Board {
    int n;
    Cell[][] board;
    public Board(int n) {
        this.n = n;
        this.board = new Cell[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                board[i][j] = new Cell();
            }
        }
    }
    public void generate_Bombs(int bombs) {
        if (bombs == 0) return;
        Random r = new Random();
        int i = r.nextInt(n);
        int j = r.nextInt(n);
        if (!board[i][j].is_bomb) {
            board[i][j].is_bomb = true;
            generate_Bombs(bombs - 1);
        } else {
            generate_Bombs(bombs);
        }
    }
    public boolean check_marker(int i , int j){
        if (board[i][j].is_bomb) return true;
        else return false;
    }
    public void setup_markers() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int count = 0;
                if (i != 0 && check_marker(i - 1, j)) count ++;
                if ( i != 0 && j!= 0 && check_marker(i - 1, j - 1)) count ++;
                if (j != 0 && check_marker(i , j - 1)) count++;
                if (i!= n-1 && check_marker(i + 1, j)) count ++;
                if (j != n-1 && check_marker(i , j + 1)) count++;
                if (j!= n-1 && i != n-1 && check_marker(i + 1, j + 1)) count++;
                if (i!= 0 && j != n-1 && check_marker(i - 1, j + 1)) count++;
                if (i!= n-1 && j != 0 && check_marker(i + 1, j - 1)) count++;
                board[i][j].mark = count;
            }
        }
    }
    public void disp_board(){
        String output = "";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j].is_flagged) output += "| X ";
                else if (board[i][j].is_hidden) output += "| - ";
                else
                    output += board[i][j].is_bomb ? ("| "+"* ") : ("| " + board[i][j].mark+ " ");
            }
            output += "|\n";
        }
        System.out.println(output);
    }
    public void toggle_hidden(int i, int j){
        if (i < 0 || j < 0 || i >= n || j >= n){
            System.out.println("Invalid input...\n");
            System.exit(1);
        }
        if (!board[i][j].is_hidden) {
            System.out.println("Cell revealed, re-enter input...\n");
            Scanner scanner = new Scanner(System.in);
            toggle_hidden(scanner.nextInt(), scanner.nextInt());
            return;
        }
        board[i][j].is_hidden = false;
    }
    public int update_moves(){
        int count = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (!board[i][j].is_hidden) continue;
                else if(board[i][j].is_bomb) continue;
                else count++;
            }
        }
        return count;
    }
    public void expand(int i, int j){
        if (board[i][j].is_bomb) return;
        else if (!board[i][j].is_hidden) return;
        else
            board[i][j].is_hidden = false;
        if (board[i][j].mark > 0) return;
        if(i != 0 && j != 0) expand(i-1,j-1);
        if(i != n-1 && j != n-1) expand(i+1,j+1);
        if(j != n-1) expand(i,j+1);
        if(i != n-1) expand(i+1,j);
        if(i != 0 && j != n-1) expand(i-1,j+1);
        if(i != n-1 && j != 0) expand(i+1,j-1);
        if(i != 0 ) expand(i-1,j);
        if(j != 0 ) expand(i,j-1);
    }

    public void toggle_flag(){
        System.out.println("Enter Co-ordinates to Flag/Unflag...\n");
        Scanner scan = new Scanner(System.in);
        System.out.println("Enter Row Co-ordinate: ");
        int i = scan.nextInt();
        System.out.println("Enter Column Co-ordinate: ");
        int j = scan.nextInt();
        if (i < 0 || j < 0 || i >=n || j >= n){
            System.out.println("\"Invalid input...\n" +
                    "Re-enter Input...");
            toggle_flag();
            return;

            
        }
        board[i][j].is_flagged = !board[i][j].is_flagged;
    }

    public void make_move(){
        System.out.println("Enter Co-ordinates to sweep...\n");
        Scanner scan = new Scanner(System.in);
        System.out.println("Enter Row Co-ordinate: ");
        int i = scan.nextInt();
        System.out.println("Enter Column Co-ordinate: ");
        int j = scan.nextInt();
        if(i < 0 || j < 0 || i >= n || j >= n){
            System.out.println("Invalid input...\nRe-enter Input...");
            make_move();
            return;
        }
        if (board[i][j].mark == 0) expand(i,j);

        else if (board[i][j].is_bomb) {
            for (int l = 0; l < n; l++) {
                for (int m = 0; m < n; m++) {
                    if (board[l][m].is_bomb)
                        board[l][m].is_hidden = false;
                }
            }
            disp_board();
            System.out.println("Game Over...\n");
            System.exit(0);
        }

        else
            toggle_hidden(i, j);
    }

    public void play(){
        int bombs = (n*n)/4 + 1;
        generate_Bombs(bombs);
        int possible_moves = n*n - bombs;
        setup_markers();
        while(possible_moves > 0) {
            disp_board();
            System.out.println("What would you like to do?\n1. Sweep\n2. Flag/Unflag\n");
            switch ((new Scanner(System.in).nextInt())){
                case 1:
                    make_move();
                    break;
                case 2:
                    toggle_flag();
                    break;
                default:
                    System.out.println("Invalid Input \n");
            }
            possible_moves = update_moves();

        }
        System.out.println("You win!\n");
    }
}
