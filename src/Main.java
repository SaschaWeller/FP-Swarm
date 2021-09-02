import java.io.IOException;
import java.util.*;
import java.util.stream.Collectors;

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
        LinkedList<String> droneResults = new LinkedList<String>();
        String newWeights ="";


        //collect data from all drones
        for (Client client : allDrones){
            droneResults.add(client.readFromDevice());
        }

        //ML aggregation

        HashMap<String, ArrayList<Integer>> tmpMap = stringsToMap(droneResults);
        HashMap<String, Object> aggregationResults =new HashMap<>();

        tmpMap.forEach( (k,v) -> {
            Map<Object, Long> counterMap = v.stream().collect(Collectors.groupingBy(e -> e.toString().toLowerCase(),Collectors.counting()));

            long  maxValueInMap=(Collections.max(counterMap.values()));
            for (Map.Entry<Object, Long> entry : counterMap.entrySet()) {
                if (entry.getValue()==maxValueInMap) {
                    aggregationResults.put(k , entry.getKey());
                }
            }

        });


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
    static HashMap<String, ArrayList<Integer>> stringsToMap(LinkedList<String> input){
        HashMap<String, ArrayList<Integer>> result = new HashMap<String, ArrayList<Integer>>();

        for( String inputElement : input) {
            String tmp = inputElement.substring(inputElement.indexOf("/") + 1);
            tmp = tmp.replace("/", "");
            String[] segments = tmp.split("\\$");

            for(String segment : segments){
                //String key = segment.substring(0, segment.lastIndexOf("#")).replace("#", "");
                String key = segment.substring(0, segment.lastIndexOf("#"));
                Integer value = Integer.parseInt(segment.substring(segment.lastIndexOf("#") + 1));
                if (result.get(key) == null){
                    result.put(key, new ArrayList<Integer>());
                }
                result.get(key).add(value);
            }
        }
        return  result;
    }
}
