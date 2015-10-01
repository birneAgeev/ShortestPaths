#pragma once

#include "IReader.h"
#include "Edges.h"

class Graph {
public:
	class Builder;

	static Graph* ReadFrom(IReader& reader);

	virtual ~Graph();
	Link* & operator[](int vertexIndex) const;
	int GetVertexDegree(int vertexIndex) const;
	Link* FindLink(int startVertex, int endVertex) const;
	int GetVertexCount() const;
	int GetLinksCount() const;

private:
	Graph();
	void CheckVertexIndex(int vertexIndex) const;

	Link* links;
	Link** linksStarts;
	int vertexCount;
	int linksCount;
};

class Graph::Builder {
public:
	Builder(int vertexCount, int arcsCapacity);
	virtual ~Builder();
	void AddArc(const Arc &arc);
	Graph* Build();
private:
	void SortArcsAndCopyTo(Graph* graph);

	Arc* unsortedArcs;
	int vertexCount;
	int arcsCount;
	int arcsCapacity;
};