import java.io.*;
import java.net.*;
import java.nio.charset.StandardCharsets;
import java.util.*;

public class Main {
    public static final int SERVER_PORT = 9000;

    public static void main(String[] args) throws IOException {

        ServerSocket serverSocket = new ServerSocket(SERVER_PORT);
        Socket clientSocket;
        ArrayList<Connection> connectionList = new ArrayList<Connection>();
        System.out.println("Waiting for a client...");

        int count = 0;
        while (true) {
            count += 1;
            clientSocket = serverSocket.accept();

            Connection connection = new Connection(clientSocket, count);
            connectionList.add(connection);
            MyThread userThread = new MyThread(connection, connectionList);
            userThread.start();
        }
    }
}

public class Connection {
    private Socket socketConnection;
    private int id;
    private DataOutputStream dataOutputStream;
    private DataInputStream dataInputStream;

    public Connection(Socket socketConnection, int count) throws IOException {
        this.socketConnection = socketConnection;
        this.id = count;
        this.dataInputStream = new DataInputStream(socketConnection.getInputStream());
        this.dataOutputStream = new DataOutputStream(socketConnection.getOutputStream());
    }

    public String getIpAddress () {
        return this.socketConnection.getInetAddress().toString();
    }

    public int getId() {
        return this.id;
    }

    public void write (String buffer) throws IOException {
        this.dataOutputStream.writeUTF(buffer);
    }

    public String read () throws IOException {
        return this.dataInputStream.readUTF();
    }

    public void close() throws IOException {
        this.socketConnection.close();
    }
    
    public void println() {
        System.out.println();
        System.out.print("Client_id: " + this.id + " " + this.getIpAddress());
    }
}



public class MyThread extends Thread {
    private Connection connection;
    private ArrayList<Connection> connectionList;

    public MyThread (Connection connection, ArrayList<Connection> connectionList) throws IOException {
        this.connection = connection;
        this.connectionList = connectionList;
    }

    @Override
    public void run() {
        while (true) {
            byte[] buffer = new byte[1024];
            try {
                String readString = connection.read();
                
                String outString = "";
                if (readString.length() == 0) {
                    this.connection.close();
                    break;
                }

                System.out.println("Message from client: " + readString);
                if (readString.equals("LIST")){
                    outString = "Server IP list: \n";
                    for (Connection con: connectionList) {
                        outString += " " + con.getIpAddress() + '\n';
                    }
                }
                else if (readString.equals("HELO")) {
                    outString = "HELO Client";
                }
                else if (readString.equals("SEND")) {
                    outString = "Write your message";
                    connection.write(outString);
                    readString = connection.read();
                    for (Connection con: connectionList) {
                        if (con.getId() != connection.getId()) {
                            con.write(readString);
                        }
                    }
                }
                else {
                    outString = "Invalid command";
                }

                connection.write(outString);
                System.out.println("Message to client: " + outString);
                if (readString.equals("QUIT") || readString.equals("BYE")) {
                    break;
                }
            }
            catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
}

