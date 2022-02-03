import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

final class ChatServer {
    private static int uniqueId = 0;
    private final List<ClientThread> clients = new ArrayList<>();
    private final int port;
    private ChatFilter chatFilter;
    private String fileName;
    private String ignoreUsernameWhenListing;

    private ChatServer(int port, String fileName) throws IOException {
        this.port = port;
        this.fileName = fileName;
        chatFilter = new ChatFilter("badwords.txt"); 
    }
    
    private void broadcast(String message) throws IOException {
        boolean serverSideMsgIsWritten = false;
        DateFormat dateFormat = new SimpleDateFormat("HH:mm:ss");
        Date myDate = new Date();
        String datestr = dateFormat.format(myDate);
        
        message = datestr + " " + message;
        
        synchronized (this) {
            for (int i = 0; i < clients.size(); i++) {
                if (clients.get(i).writeMessage(message)) {
                    if(!serverSideMsgIsWritten)
                    {
                        System.out.println(message);
                        serverSideMsgIsWritten = true;
                    }
                }
            }
        }
    }

    private void remove(int id) throws IOException {
        synchronized (this) {
            for (int i = 0; i < clients.size(); i++) {
                if (id == clients.get(i).id) {
                    clients.get(i).close();
                    clients.remove(i);
                }
            }
        }
    }
    
    private void directMessage(String message, String usrname)  throws IOException {
        boolean serverSideMsgIsWritten = false;
        
        DateFormat dateFormat = new SimpleDateFormat("HH:mm:ss");
        Date myDate = new Date();
        String datestr = dateFormat.format(myDate);
        
        message = datestr + " " + message;
        
        for (int i = 0; i < clients.size(); i++) {
            if (clients.get(i).username.equals(usrname)) {
                clients.get(i).writeMessage(message);
                
                if(!serverSideMsgIsWritten)
                {
                    System.out.println(message);
                    serverSideMsgIsWritten = true;
                }
            }
        }
    }
    
    private void list() throws IOException
    {
        String usersToBeListed = "";
        
        for(int i = 0; i<clients.size(); i++)
        {
            if(!clients.get(i).username.equals(ignoreUsernameWhenListing))
                usersToBeListed = usersToBeListed + "\n" + clients.get(i).username ;  
        }    
          
        for(int j = 0; j<clients.size(); j++)
        {
            if(clients.get(j).username.equals(ignoreUsernameWhenListing))
                clients.get(j).writeMessage(usersToBeListed);   
        }
    }

    /*
     * This is what starts the ChatServer.
     * Right now it just creates the socketServer and adds a new ClientThread to a list to be handled
     */
    private void start() throws Exception {
        try {
            ServerSocket serverSocket = new ServerSocket(port);
            while(true) {
                Socket socket = serverSocket.accept();
                Runnable r = new ClientThread(socket, uniqueId++);
                Thread t = new Thread(r);
                clients.add((ClientThread) r);
                t.start();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /*
     *  > java ChatServer
     *  > java ChatServer portNumber
     *  If the port number is not specified 1500 is used
    */
    public static void main(String[] args) throws Exception{
        int portNumber =1500;
        String fileName = "badwords.txt";

        if (args.length == 1){
            portNumber = Integer.parseInt(args[0]);

        }else if (args.length == 2){  
            fileName = args[1];
        }
        
        System.out.println("Banned File Name: " + fileName);
        
        ChatServer server = new ChatServer(portNumber, fileName);

        server.start();
    }

    /*
     * This is a private class inside of the ChatServer
     * A new thread will be created to run this every time a new client connects.
     */
    private final class ClientThread implements Runnable {
        Socket socket;
        ObjectInputStream sInput;
        ObjectOutputStream sOutput;
        int id;
        String username;
        ChatMessage cm;

        private ClientThread(Socket socket, int id) throws Exception{
            this.id = id;
            this.socket = socket;
            try {
                sOutput = new ObjectOutputStream(socket.getOutputStream());
                sInput = new ObjectInputStream(socket.getInputStream());
                username = (String) sInput.readObject();
            } catch (IOException | ClassNotFoundException e) {
                e.printStackTrace();
            }
        }

        private boolean writeMessage(String msg) throws IOException{
            if (!socket.isConnected()){
                return false;
            }else{
                sOutput.writeObject(msg); //write to the output strem
                sOutput.flush();
                return true;
            }
        }

        private void close() throws IOException{
            sOutput.close();
            sInput.close();
            socket.close();
        }

        /*
         * This is what the client thread actually runs.
         */
        @Override
        public void run() {
           String filteredString = "";
           while (true) {
                try {
                    cm = (ChatMessage) sInput.readObject();
                    if (cm.getMsgType() == 1){
                        remove(this.id);
                        
                        if(socket.isClosed())
                            System.out.println(username + " is disconnected with a LOGOUT message");
                        
                        break;
                    }
                    else if(cm.getMsgType() == 2)
                    {
                        ignoreUsernameWhenListing = cm.getRecipient();
                        
                        list();
                    }
                    else if(cm.getMsgType() == 3)
                    {
                        filteredString = chatFilter.filter(cm.getMsg());
                        filteredString = username + " -> " + cm.getRecipient() + " " + filteredString;
                        directMessage(filteredString, cm.getRecipient());
                    }
                    else{
                        filteredString = chatFilter.filter(cm.getMsg());
                        filteredString = username + ": " + filteredString;
                        broadcast(filteredString);
                    }
                } catch (IOException | ClassNotFoundException e) {
                    e.printStackTrace();
                }
            }
        }
    }
}
