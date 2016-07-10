#include "graph.h" 
#include <iostream> 
#include <algorithm> 
#include <time.h>


node::node()
{

}


node::node(string datain, node * nodein) : visited(false) 
{
	data = datain;
	next = nodein; 
}

// Time Stamp Set up constructor . Pass string ex format: 2016-03-28T23:23:12Z
// Then parse the string and extract the year, month, day, hour, minute, and second. 
timeStamp::timeStamp(string timestamp) : year(-1), month(-1), day(-1), hour(-1), minute(-1), second(-1)
{
	string number = string(); 
	int place = 0; 
	for (int i = 0; i < timestamp.size(); ++i)
	{
		if (timestamp[i] >= '0' && timestamp[i] <= '9')
		{
			number += timestamp[i]; 
		}
		else
		{
			if (year == -1)
			{
				year = atoi(number.c_str());
			}
			else if (month == -1)
			{
				month = atoi(number.c_str());
			}
			else if (day == -1)
			{
				day = atoi(number.c_str()); 
			}
			else if (hour == -1)
			{
				hour = atoi(number.c_str()); 
			}
			else if (minute == -1)
			{
				minute = atoi(number.c_str()); 
			}
			else if (second == -1)
			{
				second = atoi(number.c_str()); 
			}
			number = string(); 
		}
	}
}

// T2 is the LATEST timestamp. 
bool isWithin60(timeStamp t1, timeStamp t2)
{
	time_t raw;
	time(&raw);

	struct tm time1, time2;
	localtime_s(&time1, &raw);
	localtime_s(&time2, &raw);

	time1.tm_year = t1.year - 1900; time1.tm_mon = t1.month - 1; time1.tm_mday = t1.day;
	time1.tm_hour = t1.hour; time1.tm_min = t1.minute; time1.tm_sec = t1.second;

	time2.tm_year = t2.year - 1900; time2.tm_mon = t2.month - 1; time2.tm_mday = t2.day;
	time2.tm_hour = t2.hour; time2.tm_min = t2.minute; time2.tm_sec = t2.second;

	time_t tt1, tt2;
	tt1 = mktime(&time1);
	tt2 = mktime(&time2);

	if (tt2 - tt1 <= 60) // tt2 - tt1 is the difference in SECONDS 
		return true;
	else
		return false; 
	
}

// returns true if t2 is greater than or equal t1.
// t2 is the LATEST timestamp . 
bool compareTimeStamps(timeStamp t1, timeStamp t2)
{
	time_t raw;
	time(&raw);

	struct tm time1, time2;
	localtime_s(&time1, &raw);
	localtime_s(&time2, &raw);

	time1.tm_year = t1.year - 1900; time1.tm_mon = t1.month - 1; time1.tm_mday = t1.day;
	time1.tm_hour = t1.hour; time1.tm_min = t1.minute; time1.tm_sec = t1.second;

	time2.tm_year = t2.year - 1900; time2.tm_mon = t2.month - 1; time2.tm_mday = t2.day;
	time2.tm_hour = t2.hour; time2.tm_min = t2.minute; time2.tm_sec = t2.second;

	time_t tt1, tt2;
	tt1 = mktime(&time1);
	tt2 = mktime(&time2);

	if (tt2 - tt1 >= 0)
	{
		return true;
	}
	else
	{
		return false; 
	}
}

/*graphnode class implementation*/
// UNDIRECTED. 


bool graphnode::already_in(string key)
{
	for (int i = 0; i < nodeandedge.size(); ++i)
	{
		if (nodeandedge[i]->data == key)
			return true;
	}
	return false; 
}

bool graphnode::already_edge(string key, string link)
{
	for (int i = 0; i < nodeandedge.size(); ++i)
	{
		if (nodeandedge[i]->data == key)
		{
			for (node * j = nodeandedge[i]; j != NULL; j = j->next)
			{
				if (j->data == link)
				{
					return true; 
				}
			}
		}
	}
	return false;
}

void graphnode::insert_vertex(string key)
{
	if (!already_in(key))
	{
		nodeandedge.push_back(new node(key, NULL));
		//printf("Inserted vertex \n"); 
	}
	else
	{
		//printf("Already In ! \n"); 
		return; 
	}
}

// undirected, so both vertices form an edge with each other 
void graphnode::add_edge(string key, string link)
{
	if (!already_in(key))
	{
		this->insert_vertex(key); 
	}
	if (!already_in(link))
	{
		this->insert_vertex(link); 
	}

	if (already_in(key) && already_in(link) && !already_edge(key, link))
	{
		// form first edge
		for (int i = 0; i < nodeandedge.size(); ++i)
		{
			if (nodeandedge[i]->data == key)
			{
				for (node * j = nodeandedge[i]; j != NULL; j = j->next)
				{
					if (j->next == NULL)
					{
						j->next = new node(link, NULL); 
						add_timestamp(j->next, timestamps[timestamps.size() - 1]); 
						printf("Added Edge. \n");
						break; 
					}
				}
			}
		}
		// form second edge
		for (int i = 0; i < nodeandedge.size(); ++i)
		{
			if (nodeandedge[i]->data == link)
			{
				for (node * j = nodeandedge[i]; j != NULL; j = j->next)
				{
					if (j->next == NULL)
					{
						j->next = new node(key, NULL); 		
						add_timestamp(j->next, timestamps[timestamps.size() - 1]);
						printf("Added Edge. \n"); 
						break; 
					}
				}
			}
		}
		return; 
	}
	else
	{
		return; 
	}
}

int graphnode::numberOfVerticies()
{
	return nodeandedge.size(); 
}

void graphnode::delete_edge(string key, string link)
{
	if (already_edge(key, link))
	{ // then delete the edges. 
		// First delete edge between key and link
		for (int i = 0; i < nodeandedge.size(); ++i)
		{
			if (nodeandedge[i]->data == key && nodeandedge[i]->next != NULL)
			{
				node * prev = nodeandedge[i]; 
				for (node * j = nodeandedge[i]->next; j != NULL; j = j->next)
				{
					if (j->data == link)
					{
						// 2 cases, j is either the END of the linked list (just set it to null) or it is not. Then we set prev->next = j->next. Then delete j. 
						if (j->next == NULL)
						{
							std::cout << "deleting link between: " << key << " " << link << std::endl;
							node * temp = prev->next; 
							prev->next = NULL; 
							delete temp->timestamp; 
							delete temp; 

							break;
						}
						else
						{
							std::cout << "deleting link between: " << key << " " << link << std::endl; 
							node * temp = prev; 
							prev = prev->next; 
							temp->next = j->next; 
							j = j->next; 
							delete prev->timestamp; 
							delete prev; 

							break; 
						}
						break; 
					}
					prev = prev->next; 
				}
				break; 
			}
		}

		// Second, delete edge between link and key. 
		for (int i = 0; i < nodeandedge.size(); ++i)
		{
			if (nodeandedge[i]->data == link && nodeandedge[i]->next != NULL)
			{
				node * prev = nodeandedge[i]; 
				for (node * j = nodeandedge[i]->next; j != NULL; j = j->next)
				{
					if (j->data == key)
					{
						if (j->next == NULL)
						{
							std::cout << "deleting link between: " << link << " " << key << std::endl;
							node * temp = prev->next;
							prev->next = NULL;
							delete temp->timestamp; 
							delete temp;
	
							break;
						}
						else
						{
							std::cout << "deleting link between: " << link << " " << key << std::endl;
							node * temp = prev;
							prev = prev->next;
							temp->next = j->next;
							j = j->next;
							delete prev->timestamp; 
							delete prev;

							break;
						}
						break; 
					}
					prev = prev->next; 
				}
				break; 
			}
		}
	}
	else
	{
		printf("An Edge Does not exist between these 2 keys \n");
		return; 
	}
}


// Count every edge in each node and put into vector then sort them. 
void graphnode::getDegrees()
{
	int count = 0; 
	degreeCounter = vector<int>(); // clear the vector before every count So that each time this fcn is called we have the updated degrees 
	// 1st gather number of edges per node. 
	for (int i = 0; i < nodeandedge.size(); ++i)
	{
		if (nodeandedge[i]->next != NULL)
		{
			count = 0; 
			for (node * j = nodeandedge[i]->next; j != NULL; j = j->next)
			{
				++count; 
			}
			degreeCounter.push_back(count); 
		}
	}

	
}

// get Median degree
void graphnode::storeMedian()
{
	// first sort the degree array
	std::sort(degreeCounter.begin(), degreeCounter.end());

	double median; 
	int midpt = (degreeCounter.size() - 1) / 2;
	if (degreeCounter.size() % 2 == 0)
	{
		median = (double(degreeCounter[midpt]) + double(degreeCounter[midpt + 1])) / 2.0;
		rollingMedian.push_back(median);
	}
	else
	{
		median = double(degreeCounter[midpt]) / 2.0; 
		rollingMedian.push_back(median); 
	}
}

void graphnode::printLatestMedian()
{
	std::cout << rollingMedian[rollingMedian.size() - 1] << std::endl; 
}

double graphnode::getLatestMedian()
{
	return rollingMedian[rollingMedian.size() - 1]; 
}

void graphnode::add_timestamp(node * attachToThis, string timestamp)
{
	attachToThis->timestamp = new node(timestamp, NULL); 
}

void graphnode::store_timestamp(string timestamp)
{
	if (timestamps.size() == 0)
	{
		timestamps.push_back(timestamp);
		latestTimeStamp = timestamp;
	}
	else
	{
		timestamps.push_back(timestamp); 
		if (compareTimeStamps(latestTimeStamp, timestamp)) // if timestamp > latestTimeStamp
		{
			latestTimeStamp = timestamp; 
		}
	}
		//std::cout << latestTimeStamp << std::endl; 
}



void graphnode::removeEdgesLessThanLatestTimeStamp()
{
	timeStamp latest(latestTimeStamp);  
	for (int i = 0; i < nodeandedge.size(); ++i)
	{
		if (nodeandedge[i]->next != NULL)
		{
			for (node * j = nodeandedge[i]->next; j != NULL; j = j->next) // go through each edge and make sure its within 60 seconds of latest timestamp. If it isn't delete the edge
			{
				timeStamp check(j->timestamp->data); 
				if (!isWithin60(check, latest))
				{ 
					if (j->next == NULL)
					{
						this->delete_edge(nodeandedge[i]->data, j->data); 
						break; 
					}
					else
					{
						node * temp = j->next; 
						this->delete_edge(nodeandedge[i]->data, j->data); 
						j = temp; 
					}
				}
			}
		}
		else // if node doesn't have edge, remove this node. 
		{ 
			nodeandedge.erase(nodeandedge.begin() + i); // deletes the node from graph if the node doesn't have any edges. 
		}
	}
}
