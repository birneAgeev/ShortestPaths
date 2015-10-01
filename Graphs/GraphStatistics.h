#pragma once

#include "Graph.h"

namespace GraphStatistics {
	int GetMaximalVertexDegree(const Graph& graph);
	int GetMinimalVertexDegree(const Graph& graph);
	double GetAverageVertexDegree(const Graph& graph);
	int GetSingleOrientedEdgesCount(const Graph& graph);
}
