#include "GraphStatisticsCalculator.h"
#include <algorithm>

int GraphStatisticsCalculator::GetMaximalVertexDegree(const Graph& graph) {
	int maxDegree = 0;
	for (int i = 0; i < graph.GetVertexCount(); ++i) {
		maxDegree = std::max(maxDegree, graph.GetVertexDegree(i));
	}

	return maxDegree;
}

int GraphStatisticsCalculator::GetMinimalVertexDegree(const Graph& graph) {
	int minDegree = 0;
	for (int i = 0; i < graph.GetVertexCount(); ++i) {
		minDegree = std::min(minDegree, graph.GetVertexDegree(i));
	}

	return minDegree;
}

double GraphStatisticsCalculator::GetAverageVertexDegree(const Graph& graph) {
	double sumDegrees = 0;
	for (int i = 0; i < graph.GetVertexCount(); ++i) {
		sumDegrees += (double)graph.GetVertexDegree(i);
	}

	return sumDegrees / (double)graph.GetVertexCount();
}

int GraphStatisticsCalculator::GetSingleOrientedEdgesCount(const Graph& graph) {
	int result = 0;

	for (int i = 0; i < graph.GetVertexCount(); ++i) {
		Link* adjacencyList = graph[i];
		for (Link* edge = adjacencyList; edge != adjacencyList + graph.GetVertexDegree(i); ++edge) {
			if (graph.FindLink(edge->GetTarget(), i) == nullptr)
				++result;
		}
	}

	return result;
}
