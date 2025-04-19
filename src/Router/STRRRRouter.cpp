/*
 * FPGARouter - FPGA Routing Algorithm Implementation
 * 
 * This work is licensed under the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0
 * International License (CC BY-NC-ND 4.0). To view a copy of this license, visit:
 * https://creativecommons.org/licenses/by-nc-nd/4.0/
 */

#define IMPLEMENTED true

#if IMPLEMENTED

#include "STRRRRouter.hpp"

STRRRRouter::STRRRRouter()
{
}

vector<RoutedNet> STRRRRouter::route(const DeviceGraph &device, const vector<Net> &netlist)
{
    return vector<RoutedNet>();
}

bool STRRRRouter::routeNets(const DeviceGraph &device, const vector<Net> &nets, const vector<int> &routeList, vector<RoutedNet> &results)
{
    return false;
}

#endif // IMPLEMENTED