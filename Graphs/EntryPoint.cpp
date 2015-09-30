#define _CRT_SECURE_NO_WARNINGS

#pragma once

#include<ctime>

#include "FileReader.h"
//#include "BoostFileReader.h"
#include "Graph.h"

int main(){
	double time = clock();

    FileReader fileReader;
    //fileReader.Open("input.txt");
	//fileReader.Open("osm-bawu.gr");
	fileReader.Open("osm-ger.gr");

    Graph g = Graph(fileReader);

    fileReader.Close();

	printf("Degeree: %d\n", g.GetVertexDegree(3));

	printf("Elapsed time: %.3lf\n", (clock() - time) / CLOCKS_PER_SEC);
	scanf("%lf", &time);

    return 0;
}