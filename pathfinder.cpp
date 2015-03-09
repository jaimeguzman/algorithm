#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

class Path {
public:
	const string start;
	const string end;
	const string name;
	const int distance;

	Path(string _name, string _start, string _end, int _distance) :
		name(_name), 
		start(_start),
		end(_end), 
		distance(_distance) {}
};

class Route {
public:
	const int distance;
	const vector<Path> paths;

	Route(int _distance, vector<Path> _paths) : distance(_distance), paths(_paths) {}
};

void generate_routes(vector<Path> &paths, vector<Route> &routes) {
	/* Enter your code here*/

	/* Using a good implementation of A* the time complexity of the algorithm it was
	is polynomial.
	*/

	// vector<string,string,string,int> priorityQueue ;
	int i,j,k;

	vector<int> auxiliarDistance;

	for( auto n: paths){
		auxiliarDistance.push_back( n.distance );
	}

	//AStart
	while( !paths.empty() ){

		//get the current rourte for start
		// routes->push_back( paths.at(0) ):

		Path actualPath = paths.at(0); // 
		vector<Path> auxPaths;

		int minDistanceInVector=0;
		for(i=0; i< auxiliarDistance.size(); i++ ){
			if( auxiliarDistance[i] > auxiliarDistance[i+1] ){
				minDistanceInVector = (int)auxiliarDistance[i+1];
			}
		}

		// searching paths and save in container vector
		for( i =0; i< paths.size(); i++ ){

			if( actualPath.start  == paths[i].end   ){
				// int calcDistance= actualPath.distance-path[i].distance;
				auxPaths.push_back( paths[i] );
				//actualPath = paths[i]; //update to next 
				// routes.push_back(  );

			}
		}

		//generating routing fromt the finish to start

			//TODO.		


		//save routes in vector.

			//TODO
	}


}

int main() {
	vector<Path> paths; 

	string s;
	while (getline(cin, s)) {
		if (s[0] == '#')
			continue;

		stringstream ss(s);
		string name, start, end, dist_str;
		int distance;

		getline(ss, name, ',');
		getline(ss, start, ',');
		getline(ss, end, ',');		
		
		ss >> distance;
		paths.push_back(Path(name, start, end, distance));
	}

	vector<Route> routes;
	generate_routes(paths, routes);
	
	for (auto rit = routes.begin(); rit != routes.end(); ++rit) {
		cout << rit->distance << " - ";
		for (auto pit = rit->paths.begin(); pit != rit->paths.end(); ++pit) {
			cout << pit->name << " ";			
		}
		cout << endl;
	}
}