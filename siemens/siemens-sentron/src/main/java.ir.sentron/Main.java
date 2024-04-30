import java.net.InetAddress;
import net.wimpi.modbus.Modbus;
import net.wimpi.modbus.ModbusCoupler;
import net.wimpi.modbus.io.ModbusTCPTransaction;
import net.wimpi.modbus.msg.ReadMultipleRegistersRequest;
import net.wimpi.modbus.msg.ReadMultipleRegistersResponse;
import net.wimpi.modbus.net.TCPMasterConnection;

public class Main {

    public static void main(String[] args) {
        try {
            // Define the Modbus TCP connection parameters
            InetAddress address = InetAddress.getByName("your_modbus_device_ip");
            int port = Modbus.DEFAULT_PORT;
            int unitId = 1; // Modbus device unit identifier

            // Create a TCP connection
            TCPMasterConnection connection = new TCPMasterConnection(address);
            connection.setPort(port);
            connection.connect();

            // Setup Modbus coupler
            ModbusCoupler.getReference().setMaster(true);

            // Prepare a request to read holding registers
            ReadMultipleRegistersRequest request = new ReadMultipleRegistersRequest(0, 10); // Read 10 registers starting from address 0
            request.setUnitID(unitId);

            // Execute the transaction
            ModbusTCPTransaction transaction = new ModbusTCPTransaction(connection);
            transaction.setRequest(request);
            transaction.execute();

            // Get the response
            ReadMultipleRegistersResponse response = (ReadMultipleRegistersResponse) transaction.getResponse();
            if (response != null) {
                // Process the response data
                int[] registers = response.getRegisters();
                for (int i = 0; i < registers.length; i++) {
                    System.out.println("Register " + i + ": " + registers[i]);
                }
            } else {
                System.out.println("No response received");
            }

            // Close the connection
            connection.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
