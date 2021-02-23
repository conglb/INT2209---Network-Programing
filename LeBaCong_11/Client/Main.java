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
            //System.out.println("Enter host:");
            //HOST = br.readLine();
            //System.out.println("Enter port:");
            //PORT = Integer.parseInt(br.readLine());
            HOST = "127.0.0.1";
            PORT = 9000;

            Socket socket = new Socket(HOST, PORT);

            DataInputStream inSock = new DataInputStream(socket.getInputStream());
            DataOutputStream outSock = new DataOutputStream(socket.getOutputStream());

            Scanner scanner = new Scanner(System.in);
            String message = "";
            while (! (message.equals("BYE") || message.equals("QUIT")) ) {
                System.out.print("Content sent to server: ");
                String sendMessage = scanner.nextLine();
                outSock.writeUTF(sendMessage);
                message = inSock.readUTF();;
                System.out.println("Received from server: " + message);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

}
