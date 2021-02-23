import java.io.*;
import java.util.*;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;



public class Bai4 {
    

    public static void main(String[] args) {
        String infilename = "ok.jpg";
        String outfilename = "okversion2.jpg";
        try{
            FileInputStream fis = new FileInputStream(infilename); 
            FileOutputStream fos = new FileOutputStream(outfilename); 
    
            int x; 
            while ((x=fis.read()) != -1) 
                fos.write(x); 
    
            fis.close(); 
            fos.close(); 
        } catch(IOException e) {
            System.out.println("ERROR WITH FILEs");
        }

        File file1 = new File(infilename);
        File file2 = new File(outfilename);

        String md5File1 = getMD5(file1);
        String md5File2 = getMD5(file2);
        System.out.println(md5File1);
        System.out.println(md5File2);
        if (md5File1.compareTo(md5File2) == 0) {
            System.out.println("Hai files giong nhau");
        }
        else {
            System.out.println("Hai files khac nhau");
        }
    }

    public static String convertByteToHex(byte[] data) {
        StringBuffer sb = new StringBuffer();
        for (int i = 0; i < data.length; i++) {
            sb.append(Integer.toString((data[i] & 0xff) + 0x100, 16).substring(1));
        }
        return sb.toString();
    }

    public static String getMD5(File file) {
        MessageDigest md;
        try {
            md = MessageDigest.getInstance("MD5");
            FileInputStream fis = new FileInputStream(file);
            byte[] dataBytes = new byte[1024];
            int nread = 0;
            while ((nread = fis.read(dataBytes)) != -1) {
                md.update(dataBytes, 0, nread);
            }
            byte[] byteData = md.digest();
            fis.close();
            return convertByteToHex(byteData);
        } catch (NoSuchAlgorithmException | IOException e) {
            e.printStackTrace();
            throw new RuntimeException(e);
        }
    }
}
