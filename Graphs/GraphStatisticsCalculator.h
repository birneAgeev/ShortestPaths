#pragma once

#include "Graph.h"

static class GraphStatisticsCalculator{
public:
	static int GetMaximalVertexDegree(const Graph& graph);
	static int GetMinimalVertexDegree(const Graph& graph);
	static double GetAverageVertexDegree(const Graph& graph);
	static int GetSingleOrientedEdgesCount(const Graph& graph);
};