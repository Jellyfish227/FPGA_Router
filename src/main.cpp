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
#include <memory>
#include <chrono>  // For timing

// Interfaces
#include "Interfaces/IReader.hpp"
#include "Interfaces/IRouter.hpp"
#include "Interfaces/IExporter.hpp"

// Implementations
#include "Reader/SimpleReader.hpp"
// #include "Router/SimpleRouter.hpp"
// #include "Exporter/SimpleExporter.hpp"

#include "DataType.hpp"

using namespace std;
// Forward declaration
// class Router;
const string DEVICE_PATH = "device/xcvu3p.device";
const string NETLIST_PATH = "benchmarks/design1.netlist";

int main() {
    std::cout << "FPGA Router Starting..." << std::endl;

    try {
        // Create reader instance
        IReader *reader = new SimpleReader();
        // unique_ptr<IRouter> router = make_unique<TONYRouter>();
        // unique_ptr<IExporter> exporter = make_unique<SimpleExporter>();
        
        auto start = std::chrono::high_resolution_clock::now();
        DeviceGraph deviceGraph = reader->readDevice(DEVICE_PATH);
        vector<Net> netlist = reader->readNetlist(NETLIST_PATH);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        cout << "Device and Netlist loading time: " << elapsed.count() << " seconds" << endl;

        // Create and use router when implemented
        // std::unique_ptr<IRouter> router = std::make_unique<RRRRouter>();
        // std::vector<RoutedNet> routedNets = router->route(
        //     std::make_pair(deviceGraph.nodes, deviceGraph.adjList), netlist);
        
        // Create and use exporter when implemented
        // std::unique_ptr<IExporter> exporter = std::make_unique<SimpleExporter>();
        // exporter->exportRoutingResult(routedNets);
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
