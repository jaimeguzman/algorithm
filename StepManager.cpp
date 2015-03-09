#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

class Part {
public:
	string name() {
		return "X";
	}
};

class Operation {
public:
	const string name;

	Operation(string _name) : name(_name) {}

	void operate(Part p) {
		cout << "Operation " << name << " on part " << p.name() << endl;
	}
};

class StepManager {
public:
	void add_operation(Operation operation, vector<string> prerequisites) {
		// Add your implementation here. This method is called
		// once for each type of operation during setup.
	}

	void perform_operation(string operation_name, Part p) {
		// Add your implementation here. When this method is called,
		// you must call the 'operate()' method for the named operation,
		// as well as all prerequisites for that operation.
	}
};

int main() {
	StepManager step_mgr;

	string s;
	while (getline(cin, s)) {
		if (s[0] == '#')
			continue;

		stringstream ss(s);
		string name, tmp;
		vector<string> prerequisites;

		getline(ss, name, ',');
		while (getline(ss, tmp, ',')) {
			prerequisites.push_back(tmp);
		}

		step_mgr.add_operation(Operation(name), prerequisites);		
	}

	step_mgr.perform_operation("final", Part());
}