#ifndef GRAPH_H
#define GRAPH_H

#include <vector> 
#include <string> 

using std::string; 
using std::vector; 

struct node {
	node();  // default constructor 
	// constructor 
	node(string datain = string(), node * nodein = NULL);


	string data; 
	node * next; 
	node * timestamp; // edgeandedge[0] -> edge1  -> edge2
					 //                      |           |
					//                     time node   timenode. 
	bool visited; 
};

// * Prase timestamps in this struct. 
struct timeStamp {
	timeStamp(string timestamp);
	int year, month, day, hour, minute, second; 
};


// ******** 

// undirected graph 
class graphnode {
public:
	// default constructor 
	graphnode(vector<node *> in = vector<node *>())
	{
		nodeandedge = in; 
	}

	//insertion functions:
	void insert_vertex(string key); 
	void add_edge(string key, string link); 

	// deletion: 
	void delete_node(string key); 
	void delete_edge(string key, string link); 

	//Get Degree
	void getDegrees(); 
	// Get Median Degree
	void storeMedian(); 
	void printLatestMedian(); 
	double getLatestMedian(); 

	// Add timestamp to an edge
	void store_timestamp(string timestamp); 
	void add_timestamp(node * attachToThis, string timestamp); 
	void removeEdgesLessThanLatestTimeStamp(); // Implement This. 
	//checker functions: 
	bool already_in(string key);
	bool already_edge(string key, string link); // checks if edge already exists between two. 
	int numberOfVerticies(); 
	// For DFS and BFS
	bool is_marked(string key); 

private:
	std::vector<node *> nodeandedge; // array of linked list, where head of list is the source node
								  // and everything after is it's neighbors. 
	std::vector<int> degreeCounter; // keeps track of every degree in each node and sorts them in ascending order. 
	std::vector<double> rollingMedian; // keeps track of median after every transaction. 
	std::vector<string> timestamps; // timestamps[size() - 1] is the latest timestamp. 
	string latestTimeStamp; 
};


#endif
