// Todd J Myers
//

#include <iostream>
#include <fstream>
#include <sstream>
#include "Graph.h"

int main()
{
	Graph g;
	
	string fileinput;
	cout << "Graph filename? ";
	cin >> fileinput;

	ifstream file(fileinput);
	string line;
	int numvertices = 0;
	int numedges = 0;

	//part 1
	while (getline(file, line)) {
		if (line.compare("Vertices") == 0) {
		}
		else if (line.compare("Edges") == 0) {
		}
		else if (line.find(' ') != string::npos) {
			stringstream ss(line);
			string word1;
			string word2;
			ss >> word1;
			ss >> word2;
			g.addEdge(word1, word2, 1);
			numedges++;
		}
		else {
			g.addVertex(line);
			numvertices++;
		}
	}
	file.close();
	cout << endl;
	
	//part 2
	cout << "Ingested graph from " << fileinput << ": " << numvertices << " vertices and " << numedges << " edges." << endl;
	cout << endl;

	//part 3
	cout << g.getMostOut() << " communicated with the most others (" << g.getVertex(g.getMostOut())->numOut << ")" << endl;
	cout << g.getMostIn() << " is who others communicate with the most (" << g.getVertex(g.getMostIn())->numIn << ")" << endl;
	cout << endl;

	//part 4
	string startvertex;
	string endvertex;
	cout << "Starting vertex? ";
	cin >> startvertex;
	cout << "Ending vertex? ";
	cin >> endvertex;

	unordered_map<Vertex*, int> testmap = g.dijkstra(startvertex);
	
	for (auto it : testmap) {
		if (it.first->getValue().compare(endvertex) == 0) {
			int distance = it.second;
			if (distance == INT_MAX) {
				cout << "There is no path from " << startvertex << " to " << endvertex << endl;
			}
			else {
				cout << startvertex << " is " << distance << " hops away from " << endvertex << endl;
			}
		}
	}

	//part 5
	int neighborsize = 0;
	string neighbors;
	cout << "Neighborhood size? ";
	cin >> neighborsize;

	unordered_map<Vertex*, int> neighbormap = g.dijkstra(startvertex);

	for (auto nit : testmap) {
		if (nit.second <= neighborsize) {
			neighbors.append(nit.first->getValue() + " ");
		}
	}

	cout << startvertex << "'s " << neighborsize << "-hop neighbors are: " << neighbors << endl;

	//part 6
	Vertex** vertices = g.getVertices();
	int largestcomponent = 0;

	for (int i = 0; i < numvertices; i++) {
		unordered_map<Vertex*, int> componentmap = g.dijkstra(vertices[i]->getValue());
		int componentsize = 0;
		for (auto cit : componentmap) {
			if (cit.second == INT_MAX) {
			}
			else {
				componentsize++;
			}
		}
		if (componentsize > largestcomponent) {
			largestcomponent = componentsize;
		}
	}

	cout << "The largest connected component contains " << largestcomponent << " vertices" << endl;

	Vertex** components = g.getVertices();
	vector<string> componentvec;
	int totalcomponents = 0;

	for (int i = 0; i < numvertices; i++) {
		componentvec.push_back(components[i]->getValue());
	}

	while (componentvec.empty() == false) {
		totalcomponents++;
		unordered_map<Vertex*, int> componentmap2 = g.dijkstra(componentvec[0]);

		for (auto cit2 : componentmap2) {
			if (cit2.second == INT_MAX) {
			}
			else {
				for (int i = 0; i < componentvec.size(); i++) {
					if (componentvec[i].compare(cit2.first->getValue()) == 0) {
						componentvec.erase(componentvec.begin() + i);
					}
				}
			}
		}
	}

	cout << "There are " << totalcomponents << " connected components" << endl;
}
