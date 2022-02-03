import java.io.*;
import java.net.Socket;
import java.net.SocketException;
import java.util.Scanner;

final class ChatClient  {
    private ObjectInputStream sInput;
    private ObjectOutputStream sOutput;
    private Socket socket;

    private final String server;
    private final String username;
    private final int port;

    private ChatClient(String server, int port, String username)throws Exception {
        this.server = server;
        this.port = port;
        this.username = username;
    }

    private ChatClient(String username, int portNumber) throws Exception {
        this.server = "localhost";
        this.username = username;
        this.port = portNumber;
    }
    
    private ChatClient(String username) throws Exception {
        this.port = 1500;
        this.server = "localhost";
        this.username = username;
    }
    
    /*
     * This starts the Chat Client
     */
    private boolean start() throws Exception {
        // Create a socket
       
        boolean tryingToConnect=true;
        while(tryingToConnect)
        {
            try
            {
                socket = new Socket(server, port);
                tryingToConnect=false;
            }
            catch(SocketException e)
            {
                System.out.println("Server, please wake up! I am waiting and trying again!");

                try
                {
                    Thread.sleep(2000); //2 seconds wait
                }
                catch(InterruptedException ie){
                        ie.printStackTrace();
                }
            } 
        }

        // Create input and output streams
        try {
            sInput = new ObjectInputStream(socket.getInputStream());
            sOutput = new ObjectOutputStream(socket.getOutputStream());
        } catch (IOException e) {
            e.printStackTrace();
        }

        // This thread will listen from the server for incoming messages
        Runnable r = new ListenFromServer();
        Thread t = new Thread(r);
        t.start();

        if (socket.isConnected()){
            System.out.printf("Connection accepted localhost/127.0.0.1:%s\n", port);
        }

        // After starting, send the clients user-name to the server.
        try {
            sOutput.writeObject(username);
            sOutput.flush();
        } catch (IOException e) {
            e.printStackTrace();
        }

        return true;
    }

    /*
     * This method is used to send a ChatMessage Objects to the server
     */
    private void sendMessage(ChatMessage msg) throws Exception{
        try {
            sOutput.writeObject(msg);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /*
     * To start the Client use one of the following command
     * > java ChatClient
     * > java ChatClient username
     * > java ChatClient username portNumber
     * > java ChatClient username portNumber serverAddress
     *
     * If the portNumber is not specified 1500 should be used
     * If the serverAddress is not specified "localHost" should be used
     * If the username is not specified "Anonymous" should be used
     */
    public static void main(String[] args) throws Exception{
        // Get proper arguments and override defaults
        String username = "Guest";
        int portNumber = 1500;
        String serverAdress = "localhost";

        if (args.length == 3){ //if its 3 then user inputs everything
            username = args[0];
            portNumber = Integer.parseInt(args[1]);
            serverAdress = args[2];
        }else if(args.length==2){ //serverAddress already set
            username=args[0];
            portNumber = Integer.parseInt(args[1]); //portNumber and serverAddress already set
        }else if (args.length==1){
            username=args[0];
        }

        // Create your client and start it
        ChatClient client = new ChatClient(serverAdress, portNumber, username);
        client.start();

        //to read in user input
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String str = "";
        
        // 0:Normal Msg 1:Logout Msg 2:List Msg 3:Direct Msg
        while (true){
            str = reader.readLine();
            if (str.equals("/logout")){
                client.sendMessage(new ChatMessage(str, 1,""));
                client.sOutput.close();
                client.sInput.close();
                client.socket.close();
                System.out.println("Server has closed the connection");
                System.exit(1);
            }else if (str.contains("/msg")){
                String [] arr = str.split(" ");
                
                StringBuilder sb = new StringBuilder();
                for (int i = 2; i < arr.length; i++) {
                    sb.append(arr[i] + " ");
                }
                String msgPart = sb.toString();
                
                // arr[1] : recipient
                client.sendMessage(new ChatMessage(msgPart, 3, arr[1]));
            }else if (str.contains("/list")){
                client.sendMessage(new ChatMessage(str, 2, username));
            }
            else
            {
                client.sendMessage(new ChatMessage(str, 0, ""));
            }
        }
    }


    /*
     * This is a private class inside of the ChatClient
     * It will be responsible for listening for messages from the ChatServer.
     * ie: When other clients send messages, the server will relay it to the client.
     */
    private final class ListenFromServer implements Runnable {
        public void run() {
            while(true) {
                try {
                    String msg = (String) sInput.readObject();
                    System.out.println(msg);
                } catch (IOException | ClassNotFoundException e) {
                    e.printStackTrace();
                }
            }
        }
    }
}
