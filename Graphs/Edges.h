#pragma once

class Edge{
public:
    Edge();
    Edge(int startVertex, int endVertex, int weight);
    bool operator < (const Edge& other) const;
    int GetStartVertex() const;
    int GetEndVertex() const;
    int GetWeight() const;

private:
    int StartVertex;
    int EndVertex;
    int Weight;
};

struct HalfEdge{
public:
    HalfEdge();
    HalfEdge(int endVertex, int weight);
    int GetEndVertex();
    int GetWeight();

private:
    int EndVertex;
    int Weight;
};