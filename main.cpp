#include <iostream>
#include <boost/property_tree/json_parser.hpp>

#include "SerialIO.h"

namespace pt = boost::property_tree;
namespace su = serial_utils;

int main(int argc, char **argv)
{
    pt::ptree tree;
    char *device;
    if (argc > 1)
    {
        device = argv[1];
    }
    else
    {
        std::cerr << "Use: SerialUtils <device-path>" << std::endl;
        exit(-1);
    }
    tree.put("Device.name", std::string(device));
    tree.put("Device.baud", 9600);
    tree.put("Device.bits", 8);
    tree.put("Device.stopbits", 1);
    tree.put("Device.parity", "none");
    // Construct SerialIO
    pt::ptree node = tree.get_child("Device");

    write_json("/dev/stdout", tree);
    std::cout << "Device: " << node.get<std::string>("name") << std::endl;
    try
    {
        su::SerialIO sio(tree.get_child("Device")); // construct, open and config.

        uint8_t b;
        do
        {
            if (sio.ReadByte(&b, std::chrono::milliseconds(500)))
                std::cout << b << std::flush;
            else
                std::cout << "." << std::flush;
            
        } while (b != 13 /*cr*/);
        std::cout << std::endl << std::flush;
        uint8_t oBuf[] = "acknowlege input.";
        if ( sio.WriteBuf(oBuf, sizeof(oBuf),
                    std::chrono::milliseconds(500)));
    }
    catch (boost::system::system_error &ec)
    {
        std::cerr << "Device port open/config error: " << ec.what() << std::endl;
    }
}
