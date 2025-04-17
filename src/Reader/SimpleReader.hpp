/*
 * FPGARouter - FPGA Routing Algorithm Implementation
 * 
 * This work is licensed under the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0
 * International License (CC BY-NC-ND 4.0). To view a copy of this license, visit:
 * https://creativecommons.org/licenses/by-nc-nd/4.0/
 */

#ifndef SIMPLE_READER_HPP
#define SIMPLE_READER_HPP

#include "../Interfaces/IReader.hpp"
#include <fstream>

class SimpleReader : public IReader
{
public:
    SimpleReader();
    ~SimpleReader();
    
    DeviceGraph readDevice(const std::string& filePath) override;
    std::vector<Net> readNetlist(const std::string& filePath) override;

private:
    std::string filePath;
    std::ifstream inputFile;
};

#endif // SIMPLE_READER_HPP
