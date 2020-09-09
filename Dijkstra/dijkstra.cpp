#include<chrono>
#include <iostream>
#include<functional>
#include <string>
#include <map>
#include <queue>
#include <utility>
#include<locale>
#include<vector>
#include <ctype.h>
#include<unordered_map>
#include <stack>
#include <algorithm>
#include <list>
#include <cstdlib>
#include <assert.h>
#include <stdio.h>
#include <ctype.h>
#include <set>
#include <cmath>
#include <cstring>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <stdlib.h>
#include <vector>
#include <iomanip>
#include <time.h>
using namespace std;
const int MAX = 175000;
const int INF = 1e8;
struct node {                           // to read nodes (X,Y) from file5
	double X;
	double Y;
};                     
struct Quiry
{                                            // to read  queries from file
	node Destnation;
	node Soure;
	double Radius;
};     
		
struct Edge {
	int to;
	double weigth;					
};


/**/   vector<unordered_map<int,double>> gg(175000);
/**/   vector<string> pth(175000);
/**/   vector<double> len(175000);


vector<pair<double, double>> Adj[MAX];

double dist[MAX];

bool visited[MAX];


void initialize(int ll)                             //all vertices are infinite and not visited
{
	for (int i = 0; i < ll; i++)    //O(V)
	{
		dist[i] = INF;	 //O(1)		
		visited[i] = 0;  //O(1)
	}
}



// time complexity: O(V + ElogV)
double dijkstra(int source, int des, vector<pair<double, double>> g2[MAX])
{
	
	multiset<pair<double, double>> s;   // using as min-priority queue (multiset is sorted by pair.first with duplicate values)
	s.insert({ 0, source });  // O(log(V))
	dist[source] = 0; // O(1)

	while (!s.empty())
	{
		pair<double, double> m = *s.begin();
		s.erase(s.begin());   //O(1)
		int u = m.second;    //O(1)
		if (visited[u]) continue;

		visited[u] = true;      //O(1)
		/**/  len[source] = 0;  //O(1)
		int cou = g2[u].size();
		for (int i1 = 0; i1 < cou; i1++) {           //O(adjecents) ---> O(E)
			pair<double, double> e = g2[u][i1];    //O(1)

			int v = e.first;     //O(1)
			double w = e.second;  //O(1)
			if (dist[u] + w < dist[v]) 
			{
				/**/	len[v] = len[u];    //O(1)
				/**/	pth[v] = pth[u];//O(1)
				/**/	if (v != des)
					/**/ {
					/**/		pth[v] += to_string(v) + ",";    //?
					/**/
				         }
				/**/	len[v] += gg[u][v];    //O(1)
				dist[v] = dist[u] + w;         //O(1)
				s.insert({ dist[v], v });          // O(log(V))
			}
		}
	}
	return dist[des];
}

int main() {
	
	//cout << "hello world ";
	double total = 0;  //O(1)
	
	//************************************************************************************
	int from;
	double counte1, counte2, counte3, speed, Dist;
	Edge ED, ED2;
	ifstream myfile;
	myfile.open("SFMap.txt");  //?
	vector<node> nodes(175000); 
	int indx;
	// read all node
	myfile >> counte1;          // //O(1)             // NumOfVertices

	for (int i = 0; i<counte1; i++)  //O(V)
	{
		myfile >> indx;      //O(1)
		myfile >> nodes[indx].X;    //O(1)
		myfile >> nodes[indx].Y;   //O(1)
	}
	// read all edges in adjList
	myfile >> counte2;               //O(1)       // // NumOfEdges
	for (int i = 0; i<counte2; i++)    //O(E)
	{
		myfile >> from;     //O(1)
		myfile >> ED.to;    //O(1)
		myfile >> Dist;     //O(1)
		myfile >> speed;    //O(1)
		ED.weigth = (Dist / speed) * 60;     //O(1)      // * 60 to change H to Min              1
		ED2.weigth = ED.weigth;             //O(1)
		ED2.to = from;                    //O(1)
																	   // tow edges to make underected graph
		Adj[from].push_back({ ED.to, ED.weigth }); // ?
		Adj[ED.to].push_back({ from, ED.weigth }); // ?

		/**/	gg[from][ED.to] = Dist;   //O(1)
		/**/	gg[ED.to][from] = Dist;    //O(1)


	}
	myfile.close();     // ?
	// read sour and dest from file
	vector<Quiry> queries(1000);
	double in_range;
	int dest = counte1 + 1 ; //O(1)
	int sou = counte1 ;   //O(1)
	fstream Write;
	Write.open("outOLOutput.txt", ios::app);   //?
	ifstream myfile1;
	myfile1.open("SFQueries.txt");
	myfile1 >> counte3;                            //O(n)                 // NumOfQuiries
	for (int i = 0; i<counte3; i++)
	{
		myfile1 >> queries[i].Soure.X;      //O(1)
		myfile1 >> queries[i].Soure.Y;     //O(1)
		myfile1 >> queries[i].Destnation.X;          //O(1)
		myfile1 >> queries[i].Destnation.Y;          //O(1)
		myfile1 >> queries[i].Radius;               //O(1)
		queries[i].Radius = queries[i].Radius / 1000;        //O(1)       // to change to Km
	}
	
	for (int i = 0; i<counte3; i++)    //O(n)      // num of quiry
	{

		initialize(counte1 + 2);                     //O(V)
		vector<pair<double, double>> New_Adj[MAX];
		for (int ii = 0; ii < counte1; ii++)
		{
			New_Adj[ii] = Adj[ii];               //O(1)
		}


		// get all possible start and end node
		for (int j = 0; j<counte1; j++)           //O(V)
		{
			// get dist between soure and node
			in_range = sqrt(pow(queries[i].Soure.X - nodes[j].X, 2) + pow(queries[i].Soure.Y - nodes[j].Y, 2));   //?
			if (in_range <= queries[i].Radius)  // if it possible add edg conect between them
			{
				New_Adj[sou].push_back({ j, (in_range / 5) * 60 });  //?
				New_Adj[j].push_back({ sou, (in_range / 5) * 60 });   //?
				/**/	gg[sou][j] = in_range;  //O(1)
				/**/	gg[j][sou] = in_range;  //O(1)
			}
			// get dist between des and node
			in_range = sqrt(pow(queries[i].Destnation.X - nodes[j].X, 2) + pow(queries[i].Destnation.Y - nodes[j].Y, 2));  //?
			if (in_range <= queries[i].Radius)  // if it possible add edg conect between them
			{
				New_Adj[dest].push_back({ j, (in_range / 5) * 60 });   //?
				New_Adj[j].push_back({ dest, (in_range / 5) * 60 });   //?
				/**/	gg[dest][j] = in_range;   //O(1)
				/**/	gg[j][dest] = in_range;   //O(1)
			}
		}
		auto start = chrono::steady_clock::now();
		cout << "Time " << " -> " << dijkstra(sou, dest, New_Adj) << endl;     // time complexity: O(V + ElogV)
		string start1, enD1, enD; 
		int st, en;
		for (int co = 0; co <pth[dest].size(); co++) 
		{
			if (pth[dest][co] == ',')
				break;
			else
				start1 += pth[dest][co];
		}
		st = atoi(start1.c_str());
		for (int co = pth[dest].size() - 2; co >= 0; co--)
		{
			if (pth[dest][co] == ',')
				break; 
			else
				enD1 += pth[dest][co]; 
		}
		for (int co = enD1.size() - 1; co >= 0; co--)
		{
			enD += enD1[co];
		}
		en = atoi(enD.c_str());


		cout <<  len[dest] << endl;
		cout <<  gg[dest][en] + gg[sou][st] << endl;
		cout <<  len[dest] - (gg[dest][en] + gg[sou][st]) << endl;
		cout << "path " << " -> " << pth[dest] << endl;
		cout << "**************************************" << endl;
		auto end = chrono::steady_clock::now(); //end time for each
		double timee = double(chrono::duration_cast<chrono::milliseconds>(end - start).count());
		cout << "execution time : " << timee << " Ms " << endl;
		total += timee; // add each time
		double ret = dijkstra(sou, dest, New_Adj);
		//cout << "***************************************************************" << endl;
		////Write << fixed << setprecision(2) << pth[dest] << endl;
		////Write << fixed << setprecision(2) << ret << " mins" << endl;
		////Write << fixed << setprecision(2) << len[dest] << " km " << endl;
		////Write << fixed << setprecision(2) << gg[dest][en] + gg[sou][st] << " km " << endl;
		////Write << fixed << setprecision(2) << len[dest] - (gg[dest][en] + gg[sou][st]) << " km " << endl;
		//Write << pth[dest] << endl;
		//Write << "execution time : " << timee << " Ms " << endl;
		////Write << endl << endl;
	}
	//Write  << total << " ms" << endl;
	Write.close();
	myfile1.close();
	//************************************************************************************
	return 0;
}



///////////////////////////////////////////////////////////////////////////////////////////////////







