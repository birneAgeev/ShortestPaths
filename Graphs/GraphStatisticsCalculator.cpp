#include "GraphStatisticsCalculator.h"

int GraphStatisticsCalculator::GetMaximalVertexDegree(const Graph& graph){
	int maxDegree = 0;
	for (int i = 0; i < graph.GetVertexNumber(); ++i){
		maxDegree = std::max(maxDegree, graph.GetVertexDegree(i));
	}

	return maxDegree;
}

int GraphStatisticsCalculator::GetMinimalVertexDegree(const Graph& graph){
	int minDegree = 0;
	for (int i = 0; i < graph.GetVertexNumber(); ++i){
		minDegree = std::min(minDegree, graph.GetVertexDegree(i));
	}

	return minDegree;
}

double GraphStatisticsCalculator::GetAverageVertexDegree(const Graph& graph){
	double sumDegrees = 0;
	for (int i = 0; i < graph.GetVertexNumber(); ++i){
		sumDegrees += (double)graph.GetVertexDegree(i);
	}

	return sumDegrees / (double)graph.GetVertexNumber();
}

int GraphStatisticsCalculator::GetSingleOrientedEdgesCount(const Graph& graph){
	int  result = 0;

	for (int i = 0; i < graph.GetVertexNumber(); ++i){
		HalfEdge* adjacencyList = graph[i];
		for (HalfEdge* edge = adjacencyList; edge != adjacencyList + graph.GetVertexDegree(i); ++edge){
			if (graph.SearchEdge(edge->GetEndVertex(), i) == NULL)
				++result;
		}
	}

	return result;
}