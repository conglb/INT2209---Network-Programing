import java.io.*;
import java.util.*;


public class Bai3 {
    public static void main(String[] args) {
        File f;
        String infilename = "ok.txt";
        String outfilename;
        Scanner sc = new Scanner(System.in);
        System.out.println("Nhap ten output file:");
        outfilename = sc.nextLine();
        try{
            FileInputStream fis = new FileInputStream(infilename); 
            FileOutputStream fos = new FileOutputStream(outfilename); 
    
            int x; 
            while ((x=fis.read()) != -1) 
                fos.write(x); 
    
            fis.close(); 
            fos.close(); 
        } catch(IOException e) {
            System.out.println("ERROR OPEN FILE");
        }
    }
}
