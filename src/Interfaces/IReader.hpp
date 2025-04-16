/* 
 * Interface class for data reader
 */
#ifndef IREADER_HPP
#define IREADER_HPP

#include "../DataType.hpp"

class IReader {
public:
    virtual ~IReader() = default;
    
    /**
     * Reads device info from the specified file path
     * @param filePath Path to the input file
     * @return Pair of parsed node info and adjacency list
     */
    virtual DeviceGraph readDevice(const std::string& filePath) = 0; 
    
    /**
     * Reads net list from the specified file
     * @param filePath Path to the netlist file
     * @return Vector of parsed nets or empty vector if parsing fails
     */
    // virtual std::vector<std::shared_ptr<Net>> readNetlist(const std::string& filePath) = 0;
    
    /**
     * Reads block/component specifications from the specified file
     * @param filePath Path to the block specification file
     * @return Vector of parsed blocks or empty vector if parsing fails
     */
    // virtual std::vector<std::shared_ptr<Block>> readBlocks(const std::string& filePath) = 0;
    
    /**
     * Returns last error message if any parsing operation fails
     * @return Error message or empty string if no error
     */
    // virtual std::string getLastError() const = 0;
};

#endif // IREADER_HPP
