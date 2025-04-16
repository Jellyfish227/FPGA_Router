/* 
 * Interface class for FPGA routing engine
 */
#ifndef IROUTER_HPP
#define IROUTER_HPP

#include <memory>
#include <string>
#include <vector>

class Circuit;
class Net;
class RoutingResult;
struct RouterConfig;

class IRouter {
public:
    virtual ~IRouter() = default;
    
    /**
     * Initializes the router with configuration parameters
     * @param config Router configuration parameters
     * @return true if initialization succeeds, false otherwise
     */
    virtual bool initialize(const RouterConfig& config) = 0;
    
    /**
     * Routes the entire circuit
     * @param circuit Circuit to be routed
     * @return Routing result containing the complete solution or error information
     */
    virtual RoutingResult routeCircuit(const std::shared_ptr<Circuit>& circuit) = 0;
    
    /**
     * Routes a specific net within the circuit
     * @param circuit Circuit containing the net
     * @param net Net to be routed
     * @return true if routing succeeds, false otherwise
     */
    virtual bool routeNet(const std::shared_ptr<Circuit>& circuit, const std::shared_ptr<Net>& net) = 0;
    
    /**
     * Routes a subset of nets within the circuit
     * @param circuit Circuit containing the nets
     * @param nets Collection of nets to be routed
     * @return Number of successfully routed nets
     */
    virtual int routeNets(const std::shared_ptr<Circuit>& circuit, 
                            const std::vector<std::shared_ptr<Net>>& nets) = 0;
    
    /**
     * Returns last error message if any routing operation fails
     * @return Error message or empty string if no error
     */
    // virtual std::string getLastError() const = 0;
};

#endif // IROUTER_HPP
