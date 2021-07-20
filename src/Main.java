import java.io.IOException;

public class Main {
    public static void main(String[] args) throws IOException, InterruptedException {

        Client client1 = new Client(BluetoothScanner.scanForDeviceByIdentifier("HC.*"));
        client1.initClientConnection();
        client1.sentToDevice("Hello World");
        client1.readFromDevice();
        client1.closeClientConnection();

        Client client2 = new Client("btspp://98D371FD49C6:1;authenticate=false;encrypt=false;master=false");
        client2.initClientConnection();
        client2.sentToDevice("Hello World");
        client2.readFromDevice();
        client2.closeClientConnection();


    }
}
