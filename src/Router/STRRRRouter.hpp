/*
 * FPGARouter - FPGA Routing Algorithm Implementation
 * 
 * This work is licensed under the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0
 * International License (CC BY-NC-ND 4.0). To view a copy of this license, visit:
 * https://creativecommons.org/licenses/by-nc-nd/4.0/
 */

#define IMPLEMENTED true

#if IMPLEMENTED
#ifndef STRRRROUTER_H
#define STRRRROUTER_H

#include <vector>

#include "../Interfaces/IRouter.hpp"

using namespace std;


class STRRRRouter : public IRouter
{
public:
    STRRRRouter();

    vector<RoutedNet> route(const DeviceGraph &device, 
                            const vector<Net> &netlist) override;

    bool routeNets(const DeviceGraph &device, 
                    const vector<Net> &nets, const vector<int> &routeList, 
                    vector<RoutedNet> &results) override;

};

#endif // STRRRROUTER_H
#endif // IMPLEMENTED