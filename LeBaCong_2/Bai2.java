import java.io.*;
import java.util.*;

public class Bai2 {
    public static void main(String[] args) {
        
        String endChar = "@";
        Scanner sc = new Scanner(System.in);
        System.out.println("File name:");
        String filename = sc.nextLine();
        String s = "";
        String ch = "";
        do {
            ch = sc.next();
            s += "\n"+ ch;
        } while (ch.compareTo(endChar) != 0);
        //System.out.println(s);
        File f = new File(filename);
        try{
            FileWriter fw = new FileWriter(filename);
            fw.write(s);
            fw.close();
        } catch(IOException e) {
            System.out.println("ERROR WRITE FILE");
        }
        System.out.print("File size:"); System.out.println(f.length());
    }
}