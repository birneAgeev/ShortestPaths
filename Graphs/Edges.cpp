#include "Edges.h"

Edge::Edge(){
    StartVertex = EndVertex = Weight = -1;
}

Edge::Edge(int startVertex, int endVertex, int weight){
    StartVertex = startVertex;
    EndVertex = endVertex;
    Weight = weight;
}

bool Edge::operator < (const Edge& other) const{
    return StartVertex < other.StartVertex;
}

int Edge::GetStartVertex() const{
    return StartVertex;
}

int Edge::GetEndVertex() const{
    return EndVertex;
}

int Edge::GetWeight() const{
    return Weight;
}

HalfEdge::HalfEdge(){
    EndVertex = Weight = 0;
}

HalfEdge::HalfEdge(int endVertex, int weight){
    EndVertex = endVertex;
    Weight = weight;
}

int HalfEdge::GetEndVertex(){
    return EndVertex;
}

int HalfEdge::GetWeight(){
    return Weight;
}