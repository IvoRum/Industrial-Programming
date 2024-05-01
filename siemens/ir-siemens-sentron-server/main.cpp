#include <iostream>
#include <boost/asio.hpp>

using namespace boost;

int main() {
    boost::asio::io_service io;
    boost::asio::serial_port port(io);

    // Open the serial port
    port.open("COM4"); // Change this to your serial port

    // Set serial port options
    port.set_option(boost::asio::serial_port_base::baud_rate(1200));
    port.set_option(boost::asio::serial_port_base::character_size(7));
    port.set_option(boost::asio::serial_port_base::parity(boost::asio::serial_port_base::parity::none));
    port.set_option(boost::asio::serial_port_base::stop_bits(boost::asio::serial_port_base::stop_bits::one));

    // Send Modbus request
    std::string request = "Your Modbus request here";
    boost::asio::write(port, boost::asio::buffer(request));

    // Read Modbus response
    boost::asio::streambuf response;
    boost::asio::read_until(port, response, "\n");
    std::istream response_stream(&response);
    std::string response_str;
    std::getline(response_stream, response_str);

    std::cout << "Response: " << response_str << std::endl;

    // Close the serial port
    port.close();

    return 0;
}
