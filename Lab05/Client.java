/*
 *  Name: Le Ba Cong
 *  ID: 17020022
*/

import java.io.*;
import java.net.Socket;
import java.util.Scanner;

public class Client {

    public static final int PORT = 9999;

    public static void main(String[] args) {
        try {

            Socket socket = new Socket("127.0.0.1", PORT);

            BufferedReader input = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            DataOutputStream output = new DataOutputStream(socket.getOutputStream());

            Scanner scanner = new Scanner(System.in);
            String message = "";
            while (!message.equals("500 bye")) {
                System.out.print("Content sent to server: ");
                output.writeBytes(scanner.nextLine() + "\n");
                message = input.readLine();
                System.out.println("Received from server: " + message);
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

}
