#define _CRT_SECURE_NO_WARNINGS

#pragma once

#include<ctime>

#include "FileReader.h"
#include "Graph.h"
#include "GraphStatisticsCalculator.h"

int main(){
	double time = clock();

    FileReader fileReader;
    //fileReader.Open("input.txt");
	fileReader.Open("osm-bawu.gr");
	//fileReader.Open("osm-ger.gr");

    Graph g = Graph(fileReader);

    fileReader.Close();

	printf("Max Degree: %d\n", GraphStatisticsCalculator::GetMaximalVertexDegree(g));
	printf("Min Degree: %d\n", GraphStatisticsCalculator::GetMinimalVertexDegree(g));
	printf("Average Degree: %.3lf\n", GraphStatisticsCalculator::GetAverageVertexDegree(g));
	printf("Single oriented edges count: %d\n", GraphStatisticsCalculator::GetSingleOrientedEdgesCount(g));

	printf("Elapsed time: %.3lf\n", (clock() - time) / CLOCKS_PER_SEC);
	scanf("%lf", &time);

    return 0;
}