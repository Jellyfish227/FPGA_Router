/*
 * FPGARouter - FPGA Routing Algorithm Implementation
 * 
 * This work is licensed under the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0
 * International License (CC BY-NC-ND 4.0). To view a copy of this license, visit:
 * https://creativecommons.org/licenses/by-nc-nd/4.0/
 *
 * Interface class for FPGA routing engine
 */
#ifndef IROUTER_HPP
#define IROUTER_HPP

#include "../DataType.hpp"

class IRouter {
public:
    virtual ~IRouter() = default;
    
    /**
     * Initializes the router with configuration parameters
     * @param config Router configuration parameters
     * @return true if initialization succeeds, false otherwise
     */
    // virtual bool initialize(const RouterConfig& config) = 0;
    
    /**
     * Routes the entire circuit
     * @param device Pair containing the device nodes and adjacency list
     * @param netlist The netlist to be routed
     * @return Vector of routed nets
     */
    virtual std::vector<RoutedNet> route(const DeviceGraph &device, 
                                            const std::vector<Net> &netlist) = 0;
    
    /** DISABLED, can be done by routeNets by only passing one net in the routeList
     * Routes a specific net within the device
     * @param device Pair containing the device nodes and adjacency list
     * @param net The specific net to be routed
     * @param results Vector to be updated with routing results
     * @return true if routing succeeds, false otherwise
     */
    // virtual bool routeSingleNet(const std::pair<std::vector<Node>, AdjacencyList> &device, 
    //                            const Net &net, 
    //                            std::vector<RoutedNet> &results) = 0;

    /**
     * Routes a subset of nets within the device, probably use for Rerouting or Partial Routing
     * @param device Pair containing the device nodes and adjacency list
     * @param nets Collection of nets to be routed
     * @param results Vector to be updated with routing results
     * @return true if routing succeeds, false otherwise
     */
    virtual bool routeNets(const DeviceGraph &device, 
                            const std::vector<Net> &nets, const std::vector<int> &routeList, 
                            std::vector<RoutedNet> &results) = 0;

    /**
     * Returns last error message if any routing operation fails
     * @return Error message or empty string if no error
     */
    // virtual std::string getLastError() const = 0;
};

#endif // IROUTER_HPP
