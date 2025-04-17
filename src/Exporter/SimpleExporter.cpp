/*
 * FPGARouter - FPGA Routing Algorithm Implementation
 * 
 * This work is licensed under the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0
 * International License (CC BY-NC-ND 4.0). To view a copy of this license, visit:
 * https://creativecommons.org/licenses/by-nc-nd/4.0/
 */

#include "SimpleExporter.hpp"

using namespace std;

SimpleExporter::SimpleExporter(const string& filePath) : filePath(filePath)
{
    outputFile.open(filePath);
}

SimpleExporter::~SimpleExporter()
{
    outputFile.close();
}

bool SimpleExporter::exportRoutingResult(const std::vector<RoutedNet> &results)
{
    for (const RoutedNet &result : results)
    {
        outputFile << result.netId << " " << result.netName << endl;
        for (const ParentChildPair &signalPair : result.signalPairs)
        {
            outputFile << signalPair.parentNodeId << " " << signalPair.childNodeId << endl;
        }
        outputFile << endl;
    }
    return true;
}
