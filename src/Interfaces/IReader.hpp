/* 
 * Interface class for data reader
 */
#ifndef IREADER_HPP
#define IREADER_HPP

#include <string>
#include <vector>
#include <memory>

class Circuit;
class Net;
class Block;

class IReader {
public:
    virtual ~IReader() = default;
    
    /**
     * Reads circuit data from the specified file path
     * @param filePath Path to the input file
     * @return Pointer to parsed circuit data or nullptr if parsing fails
     */
    virtual std::shared_ptr<Circuit> readDevice(const std::string& filePath) = 0; // TODO: incase of performance issue, change it back to normal pointer
    
    /**
     * Reads net list from the specified file
     * @param filePath Path to the netlist file
     * @return Vector of parsed nets or empty vector if parsing fails
     */
    virtual std::vector<std::shared_ptr<Net>> readNetlist(const std::string& filePath) = 0;
    
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
