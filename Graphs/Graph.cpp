#include "Graph.h"

Graph::Graph(IFileReader& fileReader){
    this->vertexNumber = 0;
    this->edgesNumber = 0;
    this->edges = NULL;
    this->fromVertexToEdgeList = NULL;

    Edge* unsortedEdges = NULL;
    int edgesInFile = 0;
    while(!fileReader.IsEof()){
        char c = fileReader.NextChar();
        if(c == 'c'){
            fileReader.ReadLine();
        }
        else if(c == 'a'){
            int from = fileReader.NextInt() - 1;
            int to = fileReader.NextInt() - 1;
            int weight = fileReader.NextInt();

            if(from >= this->vertexNumber || to >= this->vertexNumber ||
                edgesInFile >= this->edgesNumber)
                continue;

            unsortedEdges[edgesInFile++] = Edge(from, to, weight);
        }
        else if(c == 'p'){
            fileReader.NextChar();
            fileReader.NextChar();

            this->vertexNumber = fileReader.NextInt();
            this->edgesNumber = fileReader.NextInt();
            
            unsortedEdges = new Edge[this->edgesNumber];
            this->edges = new HalfEdge[this->edgesNumber];
            this->fromVertexToEdgeList = new HalfEdge*[this->vertexNumber];
        }
    }

	SortEdges(unsortedEdges);

    delete[] unsortedEdges;
}

Graph::~Graph(){
    delete[] edges;
    delete[] fromVertexToEdgeList;
}

HalfEdge* &Graph::operator[](int vertexIndex) const{
	if (vertexIndex < 0 || vertexIndex >= this->vertexNumber)
		throw "Bad vertex index";
	return fromVertexToEdgeList[vertexIndex];
}

int Graph::GetVertexDegree(int vertexIndex){
	if (vertexIndex == this->vertexNumber - 1)
		return (int)(this->edges + this->edgesNumber - fromVertexToEdgeList[vertexIndex]);
	return (int)(fromVertexToEdgeList[vertexIndex + 1] - fromVertexToEdgeList[vertexIndex]);
}

void Graph::SortEdges(const Edge* unsortedEdges){
	int* count = new int[this->vertexNumber];
	HalfEdge** pointers = new HalfEdge*[this->vertexNumber];

	memset(count, 0, this->vertexNumber * sizeof(int));
	const Edge* end = unsortedEdges + this->edgesNumber;
	for (const Edge* edge = unsortedEdges; edge != end; ++edge){
		++count[edge->GetStartVertex()];
	}

	this->fromVertexToEdgeList[0] = pointers[0] = edges;
	for (int i = 1; i < this->vertexNumber; ++i){
		this->fromVertexToEdgeList[i] = pointers[i] = pointers[i - 1] + count[i];
	}

	for (const Edge* edge = unsortedEdges; edge != end; ++edge){
		*(pointers[edge->GetStartVertex()]++) = HalfEdge(edge->GetEndVertex(), edge->GetWeight());
	}

	for (int i = 0; i < this->vertexNumber; ++i){
		HalfEdge* end = this->fromVertexToEdgeList[i] + GetVertexDegree(i);
		std::sort(this->fromVertexToEdgeList[i], end);
	}

	delete[] count;
	delete[] pointers;
}