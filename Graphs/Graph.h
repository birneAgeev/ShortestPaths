#pragma once

#include <algorithm>

#include "IFileReader.h"
#include "Edges.h"

class Graph{
public:
    Graph(IFileReader& fileReader);
    virtual ~Graph();
	HalfEdge* &operator[](int vertexIndex) const;
	int GetVertexDegree(int vertexIndex);

private:
	void SortEdges(const Edge* unsortedEdges);

    HalfEdge* edges;
    HalfEdge** fromVertexToEdgeList;
    int vertexNumber;
    int edgesNumber;
};