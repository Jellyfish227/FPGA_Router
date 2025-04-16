#ifndef DATATYPE_HPP
#define DATATYPE_HPP

#include <vector>
#include <memory>
#include <string>

// Device derived data types

// It's just node type, what do you expect?
enum class NodeType
{
    NODE_INT_INTERFACE,
    NODE_PINBOUNCE,
    NODE_PINFEED
};

struct Coordinate
{
    int x;
    int y;
};

struct Node
{
    int id;
    NodeType type;
    int length;
    Coordinate begin;
    Coordinate end;
    std::string name;
    std::vector<int>* adjacency;
};

// Can consider change it back to just a vector<vector<int>>, we will think about that
// Define AdjacencyList as a vector-like struct
struct AdjacencyList {
    std::vector<std::vector<int>> connections;
    
    // Access operators to maintain compatibility with vector interface
    std::vector<int>& operator[](size_t index) { return connections[index]; }
    const std::vector<int>& operator[](size_t index) const { return connections[index]; }
    
    // Method shadowing the STL vector
    size_t size() const { return connections.size(); }
    bool empty() const { return connections.empty(); }
    void resize(size_t n) { connections.resize(n); }
    void clear() { connections.clear(); }
    void push_back(const std::vector<int>& item) { connections.push_back(item); }

    // Iterator and type definitions for full STL compatibility
    auto begin() { return connections.begin(); }
    auto begin() const { return connections.begin(); }
    auto end() { return connections.end(); }
    auto end() const { return connections.end(); }
    using value_type = std::vector<int>;
    using reference = value_type&;
    using const_reference = const value_type&;
    using iterator = decltype(connections)::iterator;
    using const_iterator = decltype(connections)::const_iterator;

    // Associated functions for easy add item
    void addConnection(int from, int to) { 
        if (from >= connections.size()) {
            connections.resize(from + 1);
        }
        connections[from].push_back(to);
    }
};

struct DeviceGraph {
    std::vector<Node> nodes;
    AdjacencyList adjList;
};

// Netlist derived data types

struct Net
{
    int id;
    std::string name;
    int sourceNode;
    std::vector<int> sinkNodes;
};

// Routing result derived data types

// Why are you keep looking for explaination for the struct name? Isn't it self-explanatory?
struct ParentChildPair
{
    int parentNodeId;
    int childNodeId;
};

struct RoutedNet
{
    int netId;
    std::string netName;
    std::vector<ParentChildPair> signalPairs;
};

#endif // DATATYPE_HPP