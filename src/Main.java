import java.io.IOException;
import java.util.LinkedList;
import java.util.List;

public class Main {
    public static void main(String[] args) throws IOException, InterruptedException {
        
        //init drones and conections
        String board1 = "btspp://98D361FD57F8:1;authenticate=false;encrypt=false;master=false"; // Jan 1
        String board2 = "btspp://98D311FC1B55:1;authenticate=false;encrypt=false;master=false"; // Jan 2
        String board3 = "btspp://98D371FD49C6:1;authenticate=false;encrypt=false;master=false"; // Sascha 1

        LinkedList<Client> allDrones = new LinkedList<Client>();

        Client client1 = new Client(board1);
        client1.initClientConnection();
        allDrones.add(client1);

        Client client2 = new Client(board2);
        client2.initClientConnection();
        allDrones.add(client2);

        Client client3 = new Client(board3);
        client2.initClientConnection();
        allDrones.add(client3);
        
        //init ML-Algo
        LinkedList<String> results = new LinkedList<String>();
        String newWeights ="";


        //collect data from all drones
        for (Client client : allDrones){
            results.add(client.readFromDevice());
        }
        
        //ML aggregation



        //sent new Weights to all drones
        for(Client client : allDrones){
            client.sentToDevice(newWeights);
        }


        //close all conections
        for (Client client : allDrones){
            client.closeClientConnection();
            allDrones.remove(client);
        }



/*      Here two comlete conections for exampel:

        Client client1 = new Client(BluetoothScanner.scanForDeviceByIdentifier("HC.*"));
        client1.initClientConnection();
        client1.sentToDevice("Hello World");
        System.out.println(client1.readFromDevice());
        client1.closeClientConnection();


        Client client2 = new Client(board3);
        client2.initClientConnection();
        client2.sentToDevice("Hello World");
        System.out.println(client2.readFromDevice());
        client2.closeClientConnection();
*/

    }
}
