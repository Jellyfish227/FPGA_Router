/*
 * FPGARouter - FPGA Routing Algorithm Implementation
 * 
 * This work is licensed under the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0
 * International License (CC BY-NC-ND 4.0). To view a copy of this license, visit:
 * https://creativecommons.org/licenses/by-nc-nd/4.0/
 */

/* 
 * Test result:
 * MyMac -O0: 174.743s
 * MyMac -O3: 66.3389s
 */

#include "SimpleReader.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

using namespace std;

SimpleReader::SimpleReader() {}

SimpleReader::~SimpleReader()
{
    if (inputFile.is_open()) {
        inputFile.close();
    }
}

DeviceGraph SimpleReader::readDevice(const string& filePath)
{
    DeviceGraph deviceGraph;
    inputFile.open(filePath);
    
    if (!inputFile.is_open()) {
        cerr << "Error: Cannot open device file " << filePath << endl;
        return deviceGraph;
    }
    
    string line;
    // Read number of nodes
    getline(inputFile, line);
    int numNodes = stoi(line);
    
    // Read node information
    vector<Node> nodes(numNodes);
    for (int i = 0; i < numNodes; i++) {
        getline(inputFile, line);
        istringstream iss(line);
        
        int id, length, beginX, beginY, endX, endY;
        string nodeTypeStr, name;
        
        iss >> id >> nodeTypeStr >> length >> beginX >> beginY >> endX >> endY;
        
        // Read remaining part as name (might contain spaces)
        if (iss >> name) {
            string namePart;
            while (iss >> namePart) {
                name += " " + namePart;
            }
        }
        
        // Parse node type
        NodeType type;
        
        // Use static map for efficient string to enum conversion
        static const std::unordered_map<std::string, NodeType> nodeTypeMap = {
            {"INTENT_DEFAULT", NodeType::INTENT_DEFAULT},
            {"NODE_CLE_OUTPUT", NodeType::NODE_CLE_OUTPUT},
            {"NODE_DOUBLE", NodeType::NODE_DOUBLE},
            {"NODE_HLONG", NodeType::NODE_HLONG},
            {"NODE_HQUAD", NodeType::NODE_HQUAD},
            {"NODE_INT_INTERFACE", NodeType::NODE_INT_INTERFACE},
            {"NODE_LOCAL", NodeType::NODE_LOCAL},
            {"NODE_PINBOUNCE", NodeType::NODE_PINBOUNCE},
            {"NODE_PINFEED", NodeType::NODE_PINFEED},
            {"NODE_SINGLE", NodeType::NODE_SINGLE},
            {"NODE_VLONG", NodeType::NODE_VLONG},
            {"NODE_VQUAD", NodeType::NODE_VQUAD},
        };
        
        // Look up type in the map, default to NONE if not found
        auto it = nodeTypeMap.find(nodeTypeStr);
        if (it != nodeTypeMap.end()) {
            type = it->second;
        } else {
            type = NodeType::NONE;
            cerr << "Warning: Unknown node type '" << nodeTypeStr << "' for node " << id << endl;
        }
        
        // Create node
        Node node;
        node.id = id;
        node.type = type;
        node.length = length;
        node.begin = {beginX, beginY};
        node.end = {endX, endY};
        node.name = name;
        node.adjacency = nullptr; // Will be set later
        
        // Store node
        nodes[id] = node;
    }
    
    // Read adjacency information
    AdjacencyList adjList;
    adjList.resize(numNodes);
    
    while (getline(inputFile, line)) {
        if (line.empty()) continue;
        
        istringstream iss(line);
        int parentId;
        iss >> parentId;
        
        int childId;
        while (iss >> childId) {
            adjList.addConnection(parentId, childId);
        }
    }
    
    deviceGraph.nodes = nodes;
    deviceGraph.adjList = adjList;
    
    inputFile.close();
    return deviceGraph;
}

vector<Net> SimpleReader::readNetlist(const string& filePath)
{
    vector<Net> nets;
    inputFile.open(filePath);
    
    if (!inputFile.is_open()) {
        cerr << "Error: Cannot open netlist file " << filePath << endl;
        return nets;
    }
    
    string line;
    // Skip first line (marker 'm')
    getline(inputFile, line);
    
    // Read nets
    while (getline(inputFile, line)) {
        if (line.empty()) continue;
        
        istringstream iss(line);
        Net net;
        
        iss >> net.id >> net.name >> net.sourceNode;
        
        int sinkNode;
        while (iss >> sinkNode) {
            net.sinkNodes.push_back(sinkNode);
        }
        
        nets.push_back(net);
    }
    
    inputFile.close();
    return nets;
}