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
