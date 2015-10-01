#pragma once

#include "IFileReader.h"
#include "Edges.h"

class Graph {
public:
	Graph(IFileReader& fileReader);
	virtual ~Graph();
	Link* & operator[](int vertexIndex) const;
	int GetVertexDegree(int vertexIndex) const;
	Link* FindLink(int startVertex, int endVertex) const;
	int GetVertexCount() const;
	int GetLinksCount() const;

private:
	void SortArcs(const Arc* unsortedEdges);
	void CheckVertexIndex(int vertexIndex) const;

	Link* links;
	Link** linksStarts;
	int vertexCount;
	int linksCount;
};