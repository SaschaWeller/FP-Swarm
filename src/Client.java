import javax.bluetooth.*;
import javax.microedition.io.Connector;
import javax.microedition.io.StreamConnection;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.nio.charset.StandardCharsets;

public class Client {
    //private RemoteDevice hc05device;
    private String clientUrl;
    //private int hc05id;
    private StreamConnection streamConnection;
    private OutputStream os;
    private InputStream is;

    public Client(RemoteDevice hc05device, String hc05Url, int hc05id) {
        //this.hc05device = hc05device;
        this.clientUrl = hc05Url;
        //this.hc05id = hc05id;
    }

    public Client(String hc05Url) {
        this.clientUrl = hc05Url;
    }

    public void initClientConnection() throws IOException {
        streamConnection = (StreamConnection) Connector.open(clientUrl);
        os = streamConnection.openOutputStream();
        is = streamConnection.openInputStream();
    }

    public void closeClientConnection() throws IOException {
        os.close();
        is.close();
        streamConnection.close();
    }

    public void sentToDevice(String payload) throws IOException {
        os.write(payload.getBytes());
    }
    public void readFromDevice() throws IOException { //TODO: Rework
        int i =0;
        byte [] bytes = new byte[500];


        while (i<500) {

            is.read(bytes);
            String s = new String(bytes, StandardCharsets.UTF_8);
            System.out.println (s);

            System.out.println(i);
            i++;

        }
    }
}
