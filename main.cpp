#include <iostream>
#include <climits>
#include <vector>
#include "tsp.h"
#include "twoOpt.h"

#define CPS CLOCKS_PER_SEC

// TSP controller : wrapper
class TSPController
{
private:
	string inFname;
public:
	// Constructor
	TSPController(string in);

	// run
	vector<pair<double,double> > run();
};

TSPController::TSPController(string in){
	inFname = in;
}

vector< pair<double,double> > TSPController::run() {
	vector< pair<double,double> > pts;

	// Read file names from input, output is in "o.tour"
	string f, o;
	f = o = inFname;
	o.append(".tour");

	// Create new tsp object
	TSP tsp(f, o);

	// Start timing
	clock_t t = clock();
	clock_t t2;

	// Read cities from file
	if (DEBUG)
		cout << "Reading cities" << endl;
	tsp.readCities();
	if (DEBUG)
		cout << "Time to read cities: "
				<< ((float) (clock() - t)) / CLOCKS_PER_SEC << " s\n";

	cout << "number of cities: " << tsp.n << endl;

	// Fill N x N matrix with distances between nodes
	if (DEBUG)
		cout << "\nFilling matrix" << endl;
	t2 = clock();
	tsp.fillMatrix();
	if (DEBUG)
		cout << "Time to fill matrix: " << ((float) (clock() - t2)) / CPS
				<< " s\n";

	// Find a MST T in graph G
	if (DEBUG)
		cout << "\nFinding mst" << endl;
	t2 = clock();
	tsp.findMST_old();
	if (DEBUG)
		cout << "Time to find mst: " << ((float) (clock() - t2)) / CPS
				<< " s\n";

	// Find a minimum weighted matching M for odd vertices in T
	if (DEBUG)
		cout << "\nFinding perfect matching" << endl;
	t2 = clock();
	tsp.perfect_matching();
	if (DEBUG)
		cout << "Time to find matching: " << ((float) (clock() - t2)) / CPS
				<< " s\n\n";

	// Store best path
	tsp.create_tour(0);
	tsp.make_shorter();
	tsp.make_shorter();
	tsp.make_shorter();
	tsp.make_shorter();
	tsp.make_shorter();

	cout << "\nFinal length: " << tsp.pathLength << endl;

	// Print to file
	tsp.printResult();

	// Print to file
	tsp.printPath();

	if (DEBUG)
		cout << "\nTotal time: " << ((float) (clock() - t)) / CPS << "s\n";

	// Wrap up the output
	for (vector<int>::iterator it = tsp.circuit.begin(); it != tsp.circuit.end(); ++it) {
		double x, y;
		x = tsp.cities[*it].x;
		y = tsp.cities[*it].y;
		pts.push_back(make_pair (x,y));
	}

	return pts;
}


int main(int argc, char** argv) {

	// example input: ./tsp example_input
	if (argc < 2)
	{
		exit(-1);
	}

	// Create controller
	TSPController controller(argv[1]);
	vector< pair<double,double> > pts = controller.run();

	cout << "In the main loop:" << endl;
	for (unsigned int i = 0; i<pts.size(); ++i) {
		cout << "x: " << pts[i].first << "\t" << "y: " << pts[i].second << endl;
	}

	return 0;
}
