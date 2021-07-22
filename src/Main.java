import java.io.IOException;

public class Main {
    public static void main(String[] args) throws IOException, InterruptedException {

        String board2 = "btspp://98D311FC1B55:1;authenticate=false;encrypt=false;master=false";

        String board1 = "btspp://98D361FD57F8:1;authenticate=false;encrypt=false;master=false";
        //Sascha's Board
        String board3 = "btspp://98D371FD49C6:1;authenticate=false;encrypt=false;master=false"


        /*Client client1 = new Client(BluetoothScanner.scanForDeviceByIdentifier("HC.*"));
        client1.initClientConnection();
        client1.sentToDevice("Hello World");
        client1.readFromDevice();
        client1.closeClientConnection();
        */
        Client client2 = new Client(board3);
        client2.initClientConnection();
        client2.sentToDevice("Hello World");
        System.out.println(client2.readFromDevice());
        client2.closeClientConnection();
    }
}
