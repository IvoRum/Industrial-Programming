#include <iostream>
#include <boost/asio.hpp>

using namespace std;

// Function to send Modbus request
void sendModbusRequest(boost::asio::serial_port& port, const std::string& request) {
    try {
        // Write request to serial port
        boost::asio::write(port, boost::asio::buffer(request));

        // Read response from serial port
        boost::asio::streambuf response;
        boost::asio::read_until(port, response, "\n");
        std::istream response_stream(&response);
        std::string response_str;
        std::getline(response_stream, response_str);

        cout<< response_str;
    }
    catch (std::exception& e) {
        std::cerr << "Error sending/receiving Modbus request: " << e.what() << std::endl;
        cout<< "Nothing";
    }
}

int main() {
    cout << "bofoere connecting to port COM4"<<endl;
    try {
        // Set up serial port
        boost::asio::io_service io;
        boost::asio::serial_port port(io);

        port.open("COM4");

        // Set serial port options
        port.set_option(boost::asio::serial_port_base::baud_rate(9600));
        port.set_option(boost::asio::serial_port_base::character_size(8));
        port.set_option(boost::asio::serial_port_base::parity(boost::asio::serial_port_base::parity::none));
        port.set_option(boost::asio::serial_port_base::stop_bits(boost::asio::serial_port_base::stop_bits::one));

        // Construct Modbus request packet for reading holding register at address 801
        // Slave Address: 0x01, Function Code: 0x03, Starting Address: 0x0320, Quantity of Registers: 0x0001
        std::string modbus_request = "\x01\x03\x03\x21\x00\x01";

        // Send Modbus request
        sendModbusRequest(port, modbus_request);

        // Close serial port
        port.close();
    }
    catch (std::exception& e) {
        cout << "Error: " << e.what() << std::endl;
    }
    cout << "finished";
    cin;
    return 0;
}
