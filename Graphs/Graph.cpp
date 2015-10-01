#include "Graph.h"
#include <algorithm>

Graph::Graph(IReader& reader) {
	this->vertexCount = 0;
	this->linksCount = 0;
	this->links = nullptr;
	this->linksStarts = nullptr;

	Arc* unsortedArcs = nullptr;
	int arcsInFile = 0;
	while (char c = reader.NextChar()) {
		if (c == 'c') {
			reader.ReadLine();
		}
		else if (c == 'a') {
			int from = reader.NextUnsignedInt() - 1;
			int to = reader.NextUnsignedInt() - 1;
			int weight = reader.NextUnsignedInt();

			if (from >= this->vertexCount || to >= this->vertexCount ||
				arcsInFile >= this->linksCount)
				throw std::runtime_error("Unexpected arc definition");

			unsortedArcs[arcsInFile++] = Arc(from, to, weight);
		}
		else if (c == 'p') {
			reader.NextChar();
			reader.NextChar();

			this->vertexCount = reader.NextUnsignedInt();
			this->linksCount = reader.NextUnsignedInt();

			unsortedArcs = new Arc[this->linksCount];
			this->links = new Link[this->linksCount];
			this->linksStarts = new Link*[this->vertexCount];
		}
		else
			throw std::runtime_error("Unexpected token " + c);
	}
	SortArcs(unsortedArcs);

	delete[] unsortedArcs;
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

void Graph::SortArcs(const Arc* unsortedArcs) {
	int* degreeCounts = new int[this->vertexCount];
	Link** linksPointers = new Link*[this->vertexCount];

	memset(degreeCounts, 0, this->vertexCount * sizeof(int));
	const Arc* arcsEnd = unsortedArcs + this->linksCount;
	for (const Arc* edge = unsortedArcs; edge != arcsEnd; ++edge) {
		++degreeCounts[edge->GetStart()];
	}

	this->linksStarts[0] = linksPointers[0] = links;
	for (int i = 1; i < this->vertexCount; ++i) {
		this->linksStarts[i] = linksPointers[i] = linksPointers[i - 1] + degreeCounts[i];
	}

	for (const Arc* edge = unsortedArcs; edge != arcsEnd; ++edge) {
		*(linksPointers[edge->GetStart()]++) = Link(edge->GetEnd(), edge->GetWeight());
	}

	for (int i = 0; i < this->vertexCount; ++i) {
		Link* linksEnd = this->linksStarts[i] + GetVertexDegree(i);
		std::sort(this->linksStarts[i], linksEnd);
	}

	delete[] degreeCounts;
	delete[] linksPointers;
}
