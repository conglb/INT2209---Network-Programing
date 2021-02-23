/*
 *  Name: Le Ba Cong
 *  ID: 17020022
*/

import java.io.*;
import java.net.*;
import java.util.*;

public class Client {

    public static int PORT;
    public static String HOST;
    public static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    public static int fnf;

    public static void main(String[] args) {
        try {
            System.out.println("Enter host:");
            HOST = br.readLine();
            System.out.println("Enter port:");
            PORT = Integer.parseInt(br.readLine());
            Socket socket = new Socket(HOST, PORT);

            DataInputStream inSock = new DataInputStream(socket.getInputStream());
            DataOutputStream outSock = new DataOutputStream(socket.getOutputStream());

            Scanner scanner = new Scanner(System.in);
            String message = "";
            while (!message.equals("BYE")) {
                System.out.print("Content sent to server: ");
                String sendMessage = scanner.nextLine();
                outSock.writeBytes(sendMessage + "\n");
                if (sendMessage.compareTo("FILE1") == 0) DownFile("file1.txt", inSock);
                if (sendMessage.compareTo("FILE2") == 0) DownFile("file2.txt", inSock);
                if (fnf == 0) {message = inSock.readUTF();
                System.out.println("Received from server: " + message);}
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void DownFile(String fileName, DataInputStream inSock) throws Exception 
    {
        fnf = 0;
        String message=inSock.readUTF();

        if(message.compareTo("FILE_NOT_FOUND")==0)
        {
            System.out.println("File not found on Server");
            fnf = 1;
            return ;
        }
        else if(message.compareTo("START!")==0)
        {
            System.out.println("Receiving File ...");
            File f = new File(fileName);
            if(f.exists())
            {
                String Option;
                System.out.println("File already exists. Overwrite (Y/N) ?");
                Option=br.readLine();            
                if(Option=="N") return ;         
            }
            FileOutputStream fout = new FileOutputStream(f);
            int p;
            String temp;
            do
            {
                temp=inSock.readUTF();
                p=Integer.parseInt(temp);
                if(p!=-1)
                {
                    fout.write(p);                    
                }
            }while(p!=-1);
            fout.close();
            System.out.println(f.length());

        }
    }

}
