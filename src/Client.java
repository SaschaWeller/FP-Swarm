import javax.bluetooth.*;
import javax.microedition.io.Connector;
import javax.microedition.io.StreamConnection;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.nio.charset.StandardCharsets;

public class Client {
    private String clientUrl;
    private StreamConnection streamConnection;
    private OutputStream os;
    private InputStream is;


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
        payload= "#"+payload.getBytes(StandardCharsets.UTF_8).length + "|" +payload;
        byte [] bytes = payload.getBytes(StandardCharsets.UTF_8);
        for(int i=0 ; i<bytes.length; i++) {
            os.write(bytes[i]);
        }
    }
    public String readFromDevice() throws IOException {
        this.sentToDevice("/sent");
        byte [] initBytes = new byte[8];
        byte [] tmp = new byte[1];
        boolean msgNotStarted = true;

        while(msgNotStarted){
            is.read(tmp,0 ,1);
            String input = new String(tmp, StandardCharsets.UTF_8);
            if(input.equals("#"))
            msgNotStarted = false;

        }



        for (int i=0; i<8 ; i++){
            is.read(tmp,0 ,1);
            String input = new String(tmp, StandardCharsets.UTF_8);

            if(input.equals("|"))
                break;
            initBytes[i]=tmp[0];
        }

        String input = new String(initBytes, StandardCharsets.UTF_8);
        for (int i=0; i<8; i++){
            if (input.charAt(i) == '\0') {
                input = input.substring(0, i);
                break;
            }

        }
        int numberReceiveBytes = Integer.parseInt(input);

        byte [] payloadBytes = new byte[numberReceiveBytes];
        for(int i=0; i<numberReceiveBytes; i++){
            is.read(tmp,0 ,1);
            payloadBytes[i]=tmp[0];
        }
        return new String(payloadBytes, StandardCharsets.UTF_8);
    }
}
