/*
 * FPGARouter - FPGA Routing Algorithm Implementation
 * 
 * This work is licensed under the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0
 * International License (CC BY-NC-ND 4.0). To view a copy of this license, visit:
 * https://creativecommons.org/licenses/by-nc-nd/4.0/
 */

#ifndef SIMPLE_EXPORTER_HPP
#define SIMPLE_EXPORTER_HPP

#include "../Interfaces/IExporter.hpp"
#include <fstream>

class SimpleExporter : public IExporter
{
public:
    SimpleExporter(const std::string& filePath);
    ~SimpleExporter();

    bool exportRoutingResult(const std::vector<RoutedNet>& results) override;

private:
    std::string filePath;
    std::ofstream outputFile;
};
#endif // SIMPLE_EXPORTER_HPP
