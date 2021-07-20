import javax.bluetooth.*;
import java.io.IOException;

public class BluetoothScanner {
    private static boolean scanFinished;
    private static RemoteDevice hc05device;
    private static String hc05Url;
    // private boolean scanFinished= false;

    public static String scanForDeviceByIdentifier(String identifier) throws BluetoothStateException, InterruptedException {

        LocalDevice.getLocalDevice().getDiscoveryAgent().startInquiry(DiscoveryAgent.GIAC, new DiscoveryListener() {
            @Override
            public void deviceDiscovered(RemoteDevice btDevice, DeviceClass cod) {
                try {
                    String name = btDevice.getFriendlyName(false);
                    System.out.format("%s (%s)\n", name, btDevice.getBluetoothAddress());
                    //if (name.matches("HC.*")) {
                    if (name.matches(identifier)) {
                        hc05device = btDevice;
                        System.out.println("got it!");
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }

            @Override
            public void inquiryCompleted(int discType) {
                scanFinished = true;
            }

            @Override
            public void serviceSearchCompleted(int transID, int respCode) {
            }

            @Override
            public void servicesDiscovered(int transID, ServiceRecord[] servRecord) {
            }
        });
        while (!scanFinished) {
            //this is easier to understand (for me) as the thread stuff examples from bluecove
            Thread.sleep(500);
        }

        //search for services:
        UUID uuid = new UUID(0x1101); //scan for btspp://... services (as HC-05 offers it)
        UUID[] searchUuidSet = new UUID[]{uuid};
        int[] attrIDs = new int[]{
                0x0100 // service name
        };
        scanFinished = false;

        String connectionURL = LocalDevice.getLocalDevice().getDiscoveryAgent().selectService(uuid, ServiceRecord.NOAUTHENTICATE_NOENCRYPT, false);

        System.out.println("con URL" + connectionURL);


        LocalDevice.getLocalDevice().getDiscoveryAgent().searchServices(attrIDs, searchUuidSet,
                hc05device, new DiscoveryListener() {
                    @Override
                    public void deviceDiscovered(RemoteDevice btDevice, DeviceClass cod) {
                    }

                    @Override
                    public void inquiryCompleted(int discType) {
                    }

                    @Override
                    public void serviceSearchCompleted(int transID, int respCode) {
                        scanFinished = true;
                    }

                    @Override
                    public void servicesDiscovered(int transID, ServiceRecord[] servRecord) {
                        for (int i = 0; i < servRecord.length; i++) {
                            System.out.println(servRecord[i].getConnectionURL(ServiceRecord.NOAUTHENTICATE_NOENCRYPT, false));
                            hc05Url = servRecord[i].getConnectionURL(ServiceRecord.NOAUTHENTICATE_NOENCRYPT, false);
                            if (hc05Url != null) {
                                scanFinished = true;
                                break; //take the first one

                            }
                        }
                    }
                });

        while (!scanFinished) {
            Thread.sleep(500);
        }

        System.out.println("MAc adresse: " + hc05device.getBluetoothAddress());

        hc05Url = "btspp://98D371FD49C6:1;authenticate=false;encrypt=false;master=false"; //TODO
        return  hc05Url;
    }
}
