import java.io.IOException;

public class Main {
    public static void main(String[] args) throws IOException, InterruptedException {

        String board2 = "btspp://98D311FC1B55:1;authenticate=false;encrypt=false;master=false";

        String board1 = "btspp://98D361FD57F8:1;authenticate=false;encrypt=false;master=false";
        //Sascha's Board
        String board3 = "btspp://98D371FD49C6:1;authenticate=false;encrypt=false;master=false";


        /*Client client1 = new Client(BluetoothScanner.scanForDeviceByIdentifier("HC.*"));
        client1.initClientConnection();
        client1.sentToDevice("Hello World");
        client1.readFromDevice();
        client1.closeClientConnection();
        //alola
        */


//        Client client2 = new Client(board1);
//        client2.initClientConnection();
//        client2.sentToDevice("Hello World longer Tesdzdfgdsafkljasdlkfjölaskdjfklöjadlökfjlkasjdf dfj aslökdfjklöasdjflösaf");
//        System.out.println("receive board1: " + client2.readFromDevice());
//        client2.closeClientConnection();


        Client client = new Client(board2);
        client.initClientConnection();
        System.out.println("Send start");
        client.sentToDevice("m");
        System.out.println("send end");
        System.out.println("receive board2: " + client.readFromDevice());
        client.closeClientConnection();





    }
}
