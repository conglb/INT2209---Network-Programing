import java.io.*;
import java.util.*;


public class Bai1 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String str = "";
        str= scanner.nextLine();
        System.out.println(str);

        int countChar = 0;
        int countNum= 0;
        int countSymbol = 0;

        for (int i = 0; i < str.length(); i++) {
            char cur = str.charAt(i);
            if ((cur >= 'A' && cur <= 'Z') || (cur >= 'a' && cur <= 'z')) {
                countChar += 1;
            }
            else if (cur >= '0' && cur <='9') {
                countNum += 1;
            }
            else {
                countSymbol += 1;
            }
        }
        System.out.println("Number of charactors: " + countChar);
        System.out.println("Number of numbers: " + countNum);
        System.out.println("Number of symbols: " + countSymbol);
    }
}