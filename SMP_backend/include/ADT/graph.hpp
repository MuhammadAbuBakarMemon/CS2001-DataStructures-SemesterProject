#pragma once

#include "hash_map.hpp"
#include "set.hpp"
#include <vector>

using NodeID = unsigned long long;

class Graph
{
private:
    HashMap<NodeID, Set<NodeID>> outAdj;
    HashMap<NodeID, Set<NodeID>> inAdj;

public:
    Graph() {}
    Graph(size_t reserveNodes)
    {
        outAdj.reserve(reserveNodes);
        inAdj.reserve(reserveNodes);
    }

    bool addEdges(NodeID from, NodeID to)
    {
        bool changed1 = outAdj[from].insert(to);
        bool changed2 = inAdj[to].insert(from);

        return changed1 || changed2;
    }

    bool removeEdges(NodeID from, NodeID to)
    {
        bool changed1 = outAdj[from].erase(to);
        bool changed2 = inAdj[to].erase(from);

        return changed1 || changed2;
    }

    bool hasEdges(NodeID from, NodeID to) const
    {
        if (!outAdj.contains(from))
            return false;

        return outAdj[from].contains(to);
    }

    const Set<NodeID> *outNeighbors(NodeID from) const
    {
        if (!outAdj.contains(from))
            return nullptr;

        return &outAdj[from];
    }

    const Set<NodeID> *inNeighbors(NodeID to) const
    {
        if (!inAdj.contains(to))
            return nullptr;

        return &inAdj[to];
    }

    size_t outDegree(NodeID from) const
    {
        if (!outAdj.contains(from))
            return 0;
        return outAdj[from].size();
    }

    size_t inDegree(NodeID to) const
    {
        if (!inAdj.contains(to))
            return 0;
        return inAdj[to].size();
    }

    void clear()
    {
        outAdj.clear();
        inAdj.clear();
    }

    void reserve(size_t sz)
    {
        outAdj.reserve(sz);
        inAdj.reserve(sz);
    }
};