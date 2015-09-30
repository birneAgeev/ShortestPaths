#pragma once

#include <algorithm>

#include "IFileReader.h"
#include "Edges.h"

class Graph{
public:
    Graph(IFileReader& fileReader);
    virtual ~Graph();
	HalfEdge* &operator[](int vertexIndex) const;
	int GetVertexDegree(int vertexIndex) const;
	HalfEdge* SearchEdge(int startVetex, int ednVertex) const;
	int GetVertexNumber() const;
	int GetEdgesNumber() const;

private:
	void SortEdges(const Edge* unsortedEdges);
	void ThrowIfBadVertexIndex(int vertexIndex) const;

    HalfEdge* edges;
    HalfEdge** fromVertexToEdgeList;
    int vertexNumber;
    int edgesNumber;
};