/*
 * FPGARouter - FPGA Routing Algorithm Implementation
 * 
 * This work is licensed under the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0
 * International License (CC BY-NC-ND 4.0). To view a copy of this license, visit:
 * https://creativecommons.org/licenses/by-nc-nd/4.0/
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <chrono>  // For timing
#include <filesystem> // For getting current path

// Interfaces
#include "Interfaces/IReader.hpp"
#include "Interfaces/IRouter.hpp"
#include "Interfaces/IExporter.hpp"

// Implementations
#include "Reader/Readers.hpp"
#include "Router/Routers.hpp"
#include "Exporter/Exporters.hpp"

#include "DataType.hpp"

using namespace std;
const string DEVICE_PATH = "device/xcvu3p.device";
const string NETLIST_PATH = "benchmarks/design5.netlist";

int main() {
    cout << "Current working directory: " << filesystem::current_path() << endl;
    cout << "FPGA Router Starting..." << endl;

    try {
        IReader *reader = new MTedExtLibReader();
        IRouter *router = new STRRRRouter();
        IExporter *exporter = new SimpleExporter("routing_result.txt");
        
        auto start = chrono::high_resolution_clock::now();
        DeviceGraph deviceGraph = reader->readDevice(DEVICE_PATH);
        vector<Net> netlist = reader->readNetlist(NETLIST_PATH);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;
        cout << "Device and Netlist loading time: " << elapsed.count() << " seconds" << endl;

        // vector<RoutedNet> routedNets = router->route(deviceGraph, netlist);

        // exporter->exportRoutingResult(routedNets);
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
