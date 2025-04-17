/*
 * FPGARouter - FPGA Routing Algorithm Implementation
 * 
 * This work is licensed under the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0
 * International License (CC BY-NC-ND 4.0). To view a copy of this license, visit:
 * https://creativecommons.org/licenses/by-nc-nd/4.0/
 */

#define IMPLEMENTED true

#if IMPLEMENTED
#ifndef MTED_EXT_LIB_READER_HPP
#define MTED_EXT_LIB_READER_HPP

#include "../Interfaces/IReader.hpp"
#include "../DataType.hpp"
#include <string>
#include <vector>

using namespace std;

struct Line
{
    const char *start;
    const char *end;
};

/**
 * Optimized reader implementation that uses concurrent data structures
 * for better performance in multithreaded environments
 */
class MTedExtLibReader : public IReader {
public:
    MTedExtLibReader();
    virtual ~MTedExtLibReader();
    
    /**
     * Reads device info from the specified file path
     * @param filePath Path to the input file
     * @return Parsed device graph
     */
    DeviceGraph readDevice(const std::string& filePath) override;
    
    /**
     * Reads net list from the specified file using multithreaded parsing
     * @param filePath Path to the netlist file
     * @return Vector of parsed nets or empty vector if parsing fails
     */
    std::vector<Net> readNetlist(const std::string& filePath) override;

private:
    const int MAX_THREADS = 8;
};

#endif // MTED_EXT_LIB_READER_HPP
#endif // IMPLEMENTED