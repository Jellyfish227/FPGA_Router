/*
 * FPGARouter - FPGA Routing Algorithm Implementation
 * 
 * This work is licensed under the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0
 * International License (CC BY-NC-ND 4.0). To view a copy of this license, visit:
 * https://creativecommons.org/licenses/by-nc-nd/4.0/
 */

/* 
 * Interface class for routed result exporter
 */
#ifndef IEXPORTER_HPP
#define IEXPORTER_HPP

#include "../DataType.hpp"

class IExporter {
public:
    virtual ~IExporter() = default;
    
    /**
     * Exports the complete routing solution to the specified file
     * @param results The vector of routing results to be exported
     * @return true if export succeeds, false otherwise
     */
    virtual bool exportRoutingResult(const std::vector<RoutedNet>& results) = 0;
    
    /**
     * Returns last error message if any export operation fails
     * @return Error message or empty string if no error
     */
    // virtual std::string getLastError() const = 0;
};

#endif // IEXPORTER_HPP
