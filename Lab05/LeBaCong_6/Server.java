/*
 *  Name: Le Ba Cong
 *  ID: 17020022
*/


import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.HashMap;

public class Server {

    public static final int PORT = 9999;

    public static void main(String[] args) {
        try {
            ServerSocket server = new ServerSocket(PORT);

            while (1==1) {

                try {
                    System.out.println("Waiting for client");
                    Socket client = server.accept();

                    BufferedReader input = new BufferedReader(new InputStreamReader(client.getInputStream()));
                    DataOutputStream output = new DataOutputStream(client.getOutputStream());

                    boolean inputUser = false;
                    String message = "";
                    
                    while (!message.equals("QUIT")) {
                        System.out.println("Waiting for message");
                        message = input.readLine();
                        switch (message) {
                            case "HELO Server":
                                output.writeBytes("200 Hello Client\n");
                                System.out.println("Sent to client: 200 Hello Client");
                                break;
                            case "USER INFO":
                                output.writeBytes("210 OK\n");
                                System.out.println("Sent to client: 210 OK");                                
                                inputUser = true;
                                break;
                            case "QUIT":
                                output.writeBytes("500 bye\n");
                                System.out.println("Sent to client: 500 bye");
                                break;
                            default:
                                output.writeBytes("410 invalid command\n");
                                System.out.println("Sent to client: 410 invalid command");
                                break;
                        }

                        System.out.println("Received message from client: " + message);
                        if (inputUser) {
                            inputUser = false;
                            HashMap<String, String> map = parseSimpleJson(message);
                            if (map == null) {
                                output.writeBytes("400 User Info Error\n");
                                continue;
                            }
                            String name = map.get("User name");
                            boolean validUser = name.length() != 0;
                            for (int i = 0; i < name.length(); i++) {
                                if (!Character.isAlphabetic(name.charAt(i)) && name.charAt(i) != ' ') {
                                    validUser = false;
                                    break;
                                }
                            }
                            String age = map.get("User age");
                            validUser &= age.length() != 0;
                            for (int i = 0; i < age.length(); i++) {
                                if (!Character.isDigit(age.charAt(i))) {
                                    validUser = false;
                                    break;
                                }
                            }
                            output.writeBytes(validUser ? "211 User Info OK\n" : "400 User Info Error\n");
                            continue;
                        }
                        
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
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
