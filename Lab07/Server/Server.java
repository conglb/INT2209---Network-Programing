/*
 *  Name: Le Ba Cong
 *  ID: 17020022
*/


import java.io.*;
import java.net.*;
import java.util.*;

public class Server {

    public static final int PORT = 9999;

    public static void main(String[] args) {
        try {
            ServerSocket server = new ServerSocket(PORT);

            while (1==1) {

                try {
                    System.out.println("Waiting for client");
                    Socket client = server.accept();

                    DataInputStream inSock = new DataInputStream(client.getInputStream());
                    DataOutputStream outSock = new DataOutputStream(client.getOutputStream());

                    String message = "";
                    
                    while (!message.equals("QUIT")) {
                        System.out.println("Waiting for message");
                        message = inSock.readLine();
                        switch (message) {
                            case "HELO":
                                outSock.writeUTF("HELO Client");
                                break;
                            case "FILE1":
                                SendFile("file1.txt", outSock);
                                break;
                            case "FILE2":
                                SendFile("file2.txt", outSock);
                                break;
                            case "QUIT":
                                outSock.writeUTF("BYE");
                                break;
                            default:
                                outSock.writeUTF("Invalid command\n");
                                break;
                        }

                        System.out.println("Received message from client: " + message);
                        
                    }
                    System.out.println("Closed connection");
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void SendFile(String filename, DataOutputStream outSock) throws Exception
    {
        File f = new File(filename);
        System.out.print("File is sending: "); System.out.println(filename);
        System.out.print("File size: "); System.out.println(f.length());
        if (!f.exists()) {
            System.out.println("File not exist \n");
            outSock.writeUTF("FILE_NOT_FOUND");
            return ;
        }
        else {
            outSock.writeUTF("START!");
            FileInputStream fin = new FileInputStream(f);
            int p;
            do {
                p = fin.read();
                outSock.writeUTF(String.valueOf(p));
            } while (p != -1);
            fin.close();
            outSock.writeUTF("FINISH!");
        }
    }


    public static HashMap<String, String> parseSimpleJson(String string) {
        try {
            HashMap<String, String> result = new HashMap<>();
            string = string.trim();
            string = string.substring(1, string.length() - 1);
            String[] fields = string.split(",");
            for (int i = 0; i < fields.length; i++) {
                String[] array = fields[i].split(":");
                if (array.length != 2) {
                    return null;
                }
                for (int j = 0; j < array.length; j++) {
                    array[j] = array[j].trim();
                    if (array[j].charAt(0) != '\"' || array[j].charAt(array[j].length() - 1) != '\"') {
                        return null;
                    }
                    array[j] = array[j].substring(1, array[j].length() - 1).trim();
                }
                result.put(array[0], array[1]);
            }
            return result;
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }
}
