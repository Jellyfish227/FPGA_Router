/*
 * FPGARouter - FPGA Routing Algorithm Implementation
 *
 * This work is licensed under the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0
 * International License (CC BY-NC-ND 4.0). To view a copy of this license, visit:
 * https://creativecommons.org/licenses/by-nc-nd/4.0/
 */

/* 
 * Test result:
 * MyMac -O0: 77.0965s
 * MyMac -O3: 25.8676s
 */

#define IMPLEMENTED true

#if IMPLEMENTED

#include "MTedExtLibReader.hpp"
#include <boost/iostreams/device/mapped_file.hpp>
#include <omp.h>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <iterator>

using namespace std;

MTedExtLibReader::MTedExtLibReader() {}

MTedExtLibReader::~MTedExtLibReader() {}

DeviceGraph MTedExtLibReader::readDevice(const string &filePath)
{
    vector<Node> nodes;
    AdjacencyList adjList;

    try
    {
        boost::iostreams::mapped_file mmap(filePath, boost::iostreams::mapped_file::readonly);
        const char *data = mmap.const_data();
        size_t size = mmap.size();

        // Split file into lines
        vector<const char *> linePtrs;
        linePtrs.push_back(data);
        for (const char *p = data; p < data + size; ++p)
        {
            if (*p == '\n')
            {
                linePtrs.push_back(p + 1);
            }
        }

        if (linePtrs.empty())
            return {nodes, adjList};

        // Parse n (number of nodes)
        string firstLine(linePtrs[0], linePtrs[1] - linePtrs[0] - 1);
        int n = stoi(firstLine);
        nodes.resize(n);

        // Process node lines in parallel
        size_t nodeStart = 1;
        size_t nodeEnd = nodeStart + n;
        if (linePtrs.size() < nodeEnd)
            return {nodes, adjList};

        #pragma omp parallel for num_threads(MAX_THREADS)
        for (size_t i = nodeStart; i < nodeEnd; ++i)
        {
            const char *lineStart = linePtrs[i];
            const char *lineEnd = (i + 1 < linePtrs.size()) ? linePtrs[i + 1] - 1 : data + size;
            string line(lineStart, lineEnd - lineStart);

            istringstream iss(line);
            vector<string> tokens{istream_iterator<string>{iss}, istream_iterator<string>{}};
            if (tokens.size() < 8)
                continue;

            static const unordered_map<string, NodeType> typeMap = {
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
                {"NONE", NodeType::NONE}
            };

            int id = stoi(tokens[0]);
            auto typeIt = typeMap.find(tokens[1]);
            nodes[id] = Node{
                id,
                (typeIt != typeMap.end()) ? typeIt->second : NodeType::NONE,
                stoi(tokens[2]),
                {stoi(tokens[3]), stoi(tokens[4])},
                {stoi(tokens[5]), stoi(tokens[6])},
                tokens[7],
                nullptr};
        }

        // Process adjacency lines in parallel with thread-local storage
        vector<unordered_map<int, vector<int>>> threadMaps(MAX_THREADS);
        size_t adjStart = nodeEnd;
        #pragma omp parallel num_threads(MAX_THREADS)
        {
            int tid = omp_get_thread_num();
            #pragma omp for
            for (size_t i = adjStart; i < linePtrs.size(); ++i)
            {
                const char *lineStart = linePtrs[i];
                const char *lineEnd = (i + 1 < linePtrs.size()) ? linePtrs[i + 1] - 1 : data + size;
                string line(lineStart, lineEnd - lineStart);

                istringstream iss(line);
                vector<string> tokens{istream_iterator<string>{iss}, istream_iterator<string>{}};
                if (tokens.size() < 2)
                    continue;

                int from = stoi(tokens[0]);
                vector<int> children;
                for (size_t j = 1; j < tokens.size(); ++j)
                {
                    children.push_back(stoi(tokens[j]));
                }

                threadMaps[tid][from].insert(threadMaps[tid][from].end(), children.begin(), children.end());
            }
        }

        // Merge adjacency data
        for (auto &threadMap : threadMaps)
        {
            for (auto &[from, children] : threadMap)
            {
                for (int to : children)
                {
                    adjList.addConnection(from, to);
                }
            }
        }
    }
    catch (const exception &e)
    {
        // Handle error (e.g., log error message)
    }

    return {nodes, adjList};
}

vector<Net> MTedExtLibReader::readNetlist(const string &filePath)
{
    vector<Net> nets;

    try
    {
        boost::iostreams::mapped_file mmap(filePath, boost::iostreams::mapped_file::readonly);
        const char *data = mmap.const_data();
        size_t size = mmap.size();

        vector<const char *> linePtrs;
        linePtrs.push_back(data);
        for (const char *p = data; p < data + size; ++p)
        {
            if (*p == '\n')
                linePtrs.push_back(p + 1);
        }

        if (linePtrs.empty())
            return nets;

        // Parse m (number of nets)
        string firstLine(linePtrs[0], linePtrs[1] - linePtrs[0] - 1);
        int m = stoi(firstLine);
        nets.resize(m);

        size_t netStart = 1;
        size_t netEnd = netStart + m;
        if (linePtrs.size() < netEnd)
            return nets;

        #pragma omp parallel for num_threads(MAX_THREADS)
        for (size_t i = netStart; i < netEnd; ++i)
        {
            const char *lineStart = linePtrs[i];
            const char *lineEnd = (i + 1 < linePtrs.size()) ? linePtrs[i + 1] - 1 : data + size;
            string line(lineStart, lineEnd - lineStart);

            istringstream iss(line);
            vector<string> tokens{istream_iterator<string>{iss}, istream_iterator<string>{}};
            if (tokens.size() < 3)
                continue;

            Net net;
            net.id = stoi(tokens[0]);
            net.name = tokens[1];
            net.sourceNode = stoi(tokens[2]);
            for (size_t j = 3; j < tokens.size(); ++j)
            {
                net.sinkNodes.push_back(stoi(tokens[j]));
            }

            nets[i - netStart] = net;
        }
    }
    catch (const exception &e)
    {
        // Handle error
    }

    return nets;
}

#endif // IMPLEMENTED