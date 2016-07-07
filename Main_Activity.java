    import java.util.Scanner;

    /**
     * Created by shubhangkulkarni on 6/14/16.
     */
    public class Main_Activity {

        public static void main(String[] args) {
            Scanner scan = new Scanner(System.in);
            System.out.println("Enter Difficulty level: \n");
            int n = scan.nextInt();
            Board b = new Board(n);
            b.play();
        }

    }
