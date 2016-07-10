#include <iostream>
#include <stdio.h> 
#include "graph.h"
#include <string> 
#include <fstream> 
#include <sstream> 
#include <memory> 
#include <time.h>
#include <cmath>
#include <iomanip> // for std::precision() std::fixed

int counter = 0; 

// clears the output text file before anything is written into it (called at the beginning of the program) 
void clear_output_text_file(graphnode * g)
{
	std::ofstream ofs; 
	// the ofstream::trunc option deletes the content before writing anything in 
	ofs.open("output.txt", std::ofstream::out | std::ofstream::trunc);  

	ofs.close(); 
}

void writeMedianToOutputFile(graphnode * g)
{
	std::ofstream ofs;
	double median = g->getLatestMedian(); // Now set Precision of median to 3
	double intpart; 
	double fractpart = modf(median, &intpart);
	fractpart = roundf(fractpart * 1000.0) / 1000.0;
	double medianFinal = intpart + fractpart; 
	ofs.open("output.txt", std::ios_base::app); // appends to text file.  
	ofs << std::fixed << std::setprecision(2) << medianFinal << std::endl; // so every median is in x.xx format . 
	ofs.close(); 
}

void parse_string(string s, graphnode *g)
{
	// Parses each part of the transaction, actor, target, and timestamp. 
	string target, actor; 
	std::istringstream iss(s);
	for (int i = 0; i < 6; ++i)
	{
		string temp; 
		iss >> temp; 
		if (i == 1) // parse timestamp 
		{
			temp.erase(0, 1); // pop front 
			temp.erase(temp.size() - 2, 2); 
			g->store_timestamp(temp); 
		}
		if (i == 3) // parse target
		{
			temp.erase(0, 1); 
			temp.erase(temp.size() - 2, 2); 
			target = temp; 
		}
		if (i == 5) // parse actor
		{ 
			temp.pop_back(); // remove right bracket 
			if (temp.size() > 2) // is not ""
			{
				temp.erase(0, 1);
				temp.pop_back();
				g->add_edge(target, temp); 
				g->removeEdgesLessThanLatestTimeStamp(); 
				g->getDegrees(); 
				g->storeMedian(); 
				writeMedianToOutputFile(g); 
			}
		}	
	}
	++counter; 
}

int main()
{
	string line; 
	graphnode * g = new graphnode(); 

	clear_output_text_file(g);
	
	std::ifstream transactions("venmo-trans.txt"); 
	if (transactions.is_open())
	{
		while (getline(transactions,line))
		{
			parse_string(line, g); 
		}
		transactions.close();
	}
	else
		std::cout << "Unable to open file" << std::endl; 

	std::cout << g->numberOfVerticies() << std::endl; 
	
	std::cout << "Latest Median is: ";
	g->printLatestMedian(); 


 	return 0; 
}
