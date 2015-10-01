#include "Graph.h"
#include <algorithm>

Graph::Graph() {
	this->vertexCount = 0;
	this->linksCount = 0;
	this->links = nullptr;
	this->linksStarts = nullptr;
}

Graph::~Graph() {
	delete[] links;
	delete[] linksStarts;
}

int Graph::GetVertexCount() const {
	return this->vertexCount;
}

int Graph::GetLinksCount() const {
	return this->linksCount;
}

void Graph::CheckVertexIndex(int vertexIndex) const {
	if (vertexIndex < 0 || vertexIndex >= this->vertexCount)
		throw std::runtime_error("Bad vertex index");
}

Link* & Graph::operator[](int vertexIndex) const {
	CheckVertexIndex(vertexIndex);
	return linksStarts[vertexIndex];
}

int Graph::GetVertexDegree(int vertexIndex) const {
	if (vertexIndex == this->vertexCount - 1)
		return (int)(this->links + this->linksCount - linksStarts[vertexIndex]);
	return (int)(linksStarts[vertexIndex + 1] - linksStarts[vertexIndex]);
}

Link* Graph::FindLink(int startVertex, int endVertex) const {
	CheckVertexIndex(startVertex);
	CheckVertexIndex(endVertex);

	int startVertexDegree = GetVertexDegree(startVertex);
	Link* adjacencyArray = this->linksStarts[startVertex];
	Link* result = std::lower_bound(adjacencyArray, adjacencyArray + startVertexDegree, Link(endVertex, 0));

	if (adjacencyArray + startVertexDegree <= result || result->GetTarget() != endVertex)
		return nullptr;

	return result;
}

Graph* Graph::ReadFrom(IReader& reader) {
	Builder* builder = nullptr;

	while (char c = reader.NextChar()) {
		switch (c) {
			case 'c': {
				reader.ReadLine();
				break;
			}
			case 'p': {
				reader.NextChar();
				reader.NextChar();

				int vertexCount = reader.NextUnsignedInt() + 1;
				int linksCount = reader.NextUnsignedInt();

				builder = new Builder(vertexCount, linksCount);
				break;
			}
			case 'a': {
				int from = reader.NextUnsignedInt();
				int to = reader.NextUnsignedInt();
				int weight = reader.NextUnsignedInt();

				builder->AddArc(Arc(from, to, weight));
				break;
			}
			default:
				throw std::runtime_error("Unexpected token " + c);
		}
	}

	Graph* graph = builder->Build();

	delete builder;
	return graph;
}

Graph::Builder::Builder(int vertexCount, int arcsCapacity) {
	this->unsortedArcs = new Arc[arcsCapacity];
	this->vertexCount = vertexCount;
	this->arcsCapacity = arcsCapacity;
	this->arcsCount = 0;
}

Graph::Builder::~Builder() {
	delete[] unsortedArcs;
}

void Graph::Builder::AddArc(const Arc& arc) {
	if (arc.GetStart() >= this->vertexCount ||
		arc.GetEnd() >= this->vertexCount ||
		arcsCount >= this->arcsCapacity)
		throw std::runtime_error("Unexpected arc definition");
	unsortedArcs[arcsCount++] = arc;
}

Graph* Graph::Builder::Build() {
	Graph* graph = new Graph();
	graph->vertexCount = this->vertexCount;
	graph->linksCount = this->arcsCount;
	graph->links = new Link[this->arcsCount];
	graph->linksStarts = new Link*[this->vertexCount];

	SortArcsAndCopyTo(graph);

	return graph;
}

void Graph::Builder::SortArcsAndCopyTo(Graph* graph) {
	int* degreeCounts = new int[this->vertexCount];
	Link** linksPointers = new Link*[this->vertexCount];

	memset(degreeCounts, 0, this->vertexCount * sizeof(int));
	const Arc* arcsEnd = unsortedArcs + this->arcsCount;
	for (const Arc* edge = unsortedArcs; edge != arcsEnd; ++edge) {
		++degreeCounts[edge->GetStart()];
	}

	graph->linksStarts[0] = linksPointers[0] = graph->links;
	for (int i = 1; i < this->vertexCount; ++i) {
		graph->linksStarts[i] = linksPointers[i] = linksPointers[i - 1] + degreeCounts[i - 1];
	}

	for (const Arc* edge = unsortedArcs; edge != arcsEnd; ++edge) {
		*(linksPointers[edge->GetStart()]++) = Link(edge->GetEnd(), edge->GetWeight());
	}

	for (int i = 0; i < this->vertexCount; ++i) {
		Link* linksEnd = graph->linksStarts[i] + graph->GetVertexDegree(i);
		std::sort(graph->linksStarts[i], linksEnd);
	}

	delete[] degreeCounts;
	delete[] linksPointers;
}
