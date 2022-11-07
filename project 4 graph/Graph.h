#include <iostream>
#include <queue>
#include <unordered_map>
#include <set>
#include <limits>
#include <string>

using namespace std;


class Vertex {

private:
	string value;
	bool mark;

public:

	int numIn;
	int numOut;

	Vertex(string value) {
		this->value = value;
		this->mark = false;
		numIn = 0;
		numOut = 0;
	}

	string getValue() { return value; }

	void setMark() {
		mark = true;
	}

	bool getMark() {
		return mark;
	}

	void clearMark() {
		mark = false;
	}
};


class Edge {

private:
	Vertex* from;
	Vertex* to;
	int weight;

public:
	Edge(Vertex* from, Vertex* to) {
		this->from = from;
		this->to = to;
		weight = 0;
	}

	Edge(Vertex* from, Vertex* to, int weight) {
		this->from = from;
		this->to = to;
		this->weight = weight;
	}

	string getFrom() {
		if (from) {
			return from->getValue();
		}
		else {
			return "\0";
		}
	}

	string getTo() {
		if (to) {
			return to->getValue();
		}
		else {
			return "\0";
		}
	}

	Vertex* getToVertex() {
		return to;
	}

	int getWeight() {
		return weight;
	}
};


class Graph {

private:
	Vertex** vertices;
	Edge** edges;
	int numVertices;
	int numEdges;
	int vertexCapacity;
	int edgeCapacity;

	void clearMarks() {
		for (int i = 0; i < numVertices; i++) {
			vertices[i]->clearMark();
		}
	}

	void dfsHelper(Vertex* v) {

		if (v->getMark()) {
			return;
		}

		cout << v->getValue() << " ";
		v->setMark();

		int numNeighbors = 0;
		Edge** outEdges = getOutgoingEdges(v, numNeighbors);

		for (int i = 0; i < numNeighbors; i++) {
			dfsHelper(getVertex(outEdges[i]->getTo()));
		}

		delete outEdges;
	}


public:

	Graph() {
		numVertices = numEdges = 0;
		vertexCapacity = edgeCapacity = 30;

		vertices = new Vertex * [vertexCapacity];
		edges = new Edge * [edgeCapacity];
	}


	~Graph() {
		delete vertices;
		delete edges;
	}

	Vertex** getVertices() {
		return vertices;
	}

	Vertex* getVertex(string label) {

		for (int i = 0; i < numVertices; i++) {
			if (vertices[i]->getValue() == label) {
				return vertices[i];
			}
		}

		return nullptr;
	}


	Edge* getEdge(string from, string to) {

		for (int i = 0; i < numEdges; i++) {
			if (edges[i]->getFrom() == from && edges[i]->getTo() == to) {
				return edges[i];
			}
		}

		return nullptr;
	}


	Edge** getOutgoingEdges(Vertex* v, int& numNeighbors) {
		int count = 0;

		for (int i = 0; i < numEdges; i++) {
			if (edges[i]->getFrom() == v->getValue()) {
				count++;
			}
		}

		if (count == 0) {
			numNeighbors = 0;
			return nullptr;

		}
		else {
			Edge** outgoingEdges = new Edge * [count];
			numNeighbors = count;
			count = 0;
			for (int i = 0; i < numEdges; i++) {
				if (edges[i]->getFrom() == v->getValue()) {
					outgoingEdges[count++] = edges[i];
				}
			}
			return outgoingEdges;
		}
	}


	void addVertex(string label) {

		if (getVertex(label)) {
			return; // a vertex with this label already exists
		}

		Vertex* newVertex = new Vertex(label);

		if (numVertices + 1 >= vertexCapacity) {
			// TODO need to make the vertex array bigger
		}

		vertices[numVertices++] = newVertex;
	}


	void addEdge(string from, string to) {

		Vertex* fromVertex = getVertex(from);
		if (fromVertex == nullptr) {
			return; // from vertex doesn't exist
		}
		fromVertex->numOut++;

		Vertex* toVertex = getVertex(to);
		if (toVertex == nullptr) {
			return; // to vertex doesn't exist
		}
		toVertex->numIn++;

		Edge* newEdge1 = new Edge(fromVertex, toVertex);

		if (numEdges + 2 >= edgeCapacity) {
			// TODO need to make the edges array bigger
		}

		edges[numEdges++] = newEdge1;
	}

	void addEdge(string from, string to, int weight) {

		Vertex* fromVertex = getVertex(from);
		if (fromVertex == nullptr) {
			return; // from vertex doesn't exist
		}
		fromVertex->numOut++;

		Vertex* toVertex = getVertex(to);
		if (toVertex == nullptr) {
			return; // to vertex doesn't exist
		}
		toVertex->numIn++;

		Edge* newEdge1 = new Edge(fromVertex, toVertex, weight);

		if (numEdges + 2 >= edgeCapacity) {
		}

		edges[numEdges++] = newEdge1;
	}

	void depthFirstSearch(string from) {

		Vertex* fromVertex = getVertex(from);
		if (fromVertex == nullptr) {
			return;
		}

		dfsHelper(fromVertex);
		cout << endl;

		clearMarks();
	}


	void breadthFirstSearch(string from) {

		Vertex* fromVertex = getVertex(from);
		if (fromVertex == nullptr) {
			return;
		}

		queue<Vertex*> q;
		q.push(fromVertex);

		while (!q.empty()) {

			Vertex* v = q.front();
			q.pop();

			if (v->getMark()) {
				continue;
			}

			cout << v->getValue() << " ";
			v->setMark();

			int numNeighbors = 0;
			Edge** outEdges = getOutgoingEdges(v, numNeighbors);

			for (int i = 0; i < numNeighbors; i++) {
				q.push(getVertex(outEdges[i]->getTo()));
			}

			delete outEdges;
		}

		cout << endl;

		clearMarks();
	}

	string getMostIn() {
		string most;
		int mostint = 0;

		for (int i = 0; i < numVertices; i++) {
			if (vertices[i]->numIn > mostint) {
				most = vertices[i]->getValue();
				mostint = vertices[i]->numIn;
			}
		}

		return most;
	}

	string getMostOut() {
		string most;
		int mostint = 0;

		for (int i = 0; i < numVertices; i++) {
			if (vertices[i]->numOut > mostint) {
				most = vertices[i]->getValue();
				mostint = vertices[i]->numOut;
			}
		}

		return most;
	}


	unordered_map<Vertex*, int> dijkstra(string from) {

		unordered_map<Vertex*, int> distances;
		for (int i = 0; i < numVertices; i++) {
			distances.insert(pair<Vertex*, int>(vertices[i], INT_MAX));
		}

		Vertex* fromVertex = getVertex(from);
		if (fromVertex == nullptr) {
			return distances;
		}

		// the distance from the starting vertex to itself is zero
		distances.erase(fromVertex);
		distances.insert(pair<Vertex*, int>(fromVertex, 0));

		Vertex* current = fromVertex;

		while (current) {
			current->setMark();

			// distance from the start vertex to the current one 
			int distSoFar = distances.at(current);

			// find all of the edges coming out of the current vertex
			// update the distances if necessary
			int numNeighbors = 0;
			Edge** outgoing = getOutgoingEdges(current, numNeighbors);

			for (int i = 0; i < numNeighbors; i++) {
				Edge* edge = outgoing[i];

				int weight = edge->getWeight();
				Vertex* to = edge->getToVertex();

				int currentDist = distances.at(to);

				if (distSoFar + weight < currentDist) {
					distances.erase(to);
					distances.insert(pair<Vertex*, int>(to, distSoFar + weight));
				}
			}

			delete outgoing;

			// set current to the unmarked vertex with the smallest distance
			int best = INT_MAX;
			current = nullptr;

			for (pair<Vertex*, int> entry : distances) {
				if ((!entry.first->getMark()) && entry.second < best) {
					best = entry.second;
					current = entry.first;
				}
			}
		}

		clearMarks();

		return distances;
	}

};