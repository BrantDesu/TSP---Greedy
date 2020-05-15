#include <iostream>
#include <fstream>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
#include <limits>
#include <sstream>

using namespace std;

struct city {
	/// Constructor.
	city(int id, double x, double y) : id(id), x(x), y(y)
	{
	}
	int id;
	double x;
	double y;
};

struct instanceInput {
	int n;
	vector<city> cities;
};
struct solution {
	int start;
	int value = 0;
	vector<int> tour;
};

instanceInput getInstance(string path){
	instanceInput instance;
	ifstream instance_file (path);
	string line, a, b, c;
	int dimension, id;
	double x, y;
	if (instance_file.is_open())
	{
		getline(instance_file, line);
		istringstream iss;
		iss.str(line);
		iss >> a >> b >> c;
		cout << "Procesando instancia: " << c << endl;
		getline(instance_file, line);
		getline(instance_file, line);
		getline(instance_file, line);
		iss.clear();
		iss.str(line);
		iss >> a >> b >> dimension;
		cout << "Tamaño instancia: " << dimension << endl;
		getline(instance_file, line);
		getline(instance_file, line);
		iss.clear();

		for (int i = 0; i < dimension; i++)
		{
			getline(instance_file, line);
			iss.str(line);
			iss >> id >> x >> y;
			//cout << "datos: " << id << ", "<< x << ", " << y << endl;
			instance.cities.push_back(city(id, x, y));
			iss.clear();
		}
	}
	instance.n = dimension;
	return instance;
}

double calculateDistance(double x1, double y1, double x2, double y2){
	return sqrt(pow((x2-x1), 2.0) + pow((y2-y1), 2.0));
}

void eraseValue(vector<int> &array, int value){
	array.erase(remove(array.begin(), array.end(),value), array.end());
}

void generateOutput(solution greedy, string file_name, int seed, double time){
	vector<int> tour = greedy.tour;

	ofstream myfile;
	myfile.open ("Outputs_TSP/" + file_name + ".output", std::ios_base::app);
	if (myfile.is_open())
	{
		myfile << "Seed Value: " << seed << endl;
		myfile << "Tiempo de Ejecución: " << time << " segundos"<< endl;
		myfile << "Costo del tour: " << greedy.value << endl << "Tour encontrado:" << endl << endl;
 		for (auto content: tour)
		{
			myfile << content << " ";
			//cout << content << " ";
		}
		myfile << endl << endl << "--------------------------------------------------------------------------------------------------" << endl << endl;
	}
	myfile.close();
		
	
}

solution greedySolution(vector<vector<double>> instanceMatrix){
	solution greedy;
	int dimension = (int) instanceMatrix.size();
	int next, start = rand()%dimension; //obtenemos una ciudad inicial random
	int first = start;
	double minimalDistance;

	vector<int> remainingCities;
	for (int i = 0; i < dimension; ++i) //Creamos una lista con las ciudades
	{
		remainingCities.push_back(i);
	}
	eraseValue(remainingCities, start);
	greedy.tour.push_back(start+1);

	for (int i = 0; i < dimension-1; ++i)
	{
		minimalDistance = numeric_limits<double>::infinity();
		for (auto candidate: remainingCities)
		{
			if (instanceMatrix[start][candidate] < minimalDistance)	//buscamos la ciudad de menor costo
			{
				minimalDistance = instanceMatrix[start][candidate];
				next = candidate;
			}
		}
		eraseValue(remainingCities, next);	//La borramos de los candidatos y agregamos al tour con su costo
		start = next;
		greedy.tour.push_back(start+1);
		greedy.value += minimalDistance;	
	}
	greedy.tour.push_back(first+1); //cerramos el tour ciclico
	greedy.value += instanceMatrix[start][first]; //le sumamos el ultimo camino de vuelta
	greedy.start = first+1;
	return greedy;
}
vector<string> list_dir(const char *path) {
	struct dirent *entry;
	DIR *dir = opendir(path);
	vector<string> instancesArray; 

	if (dir == NULL) {
		cout << "Error abriendo directorio de instancias..." << endl;
		exit(0);
 	}
	while ( ((entry = readdir(dir)) != NULL) ){
		if ((strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..")) && strcmp(entry->d_name, ".DS_Store"))
		{
			instancesArray.push_back(entry->d_name);
		}
		
	}
	closedir(dir);
	return instancesArray;
}

int main(int argc, char * argv[])
{
	

	vector<string> instancesArray = list_dir("Instancias_TSP");

	for (int i = 1; i < argc; ++i)
	{
		int seed = strtol(argv[i], nullptr, 0);
		srand(seed);
		clock_t start, end;
		for (unsigned i = 0; i < instancesArray.size(); ++i)
		{
			start = clock();
			instanceInput instanceData = getInstance("Instancias_TSP/" + instancesArray[i] );
			int dimension = instanceData.n;
			//generating matrix
			double distance;
			double x1, y1, x2, y2;
			vector<vector<double>> instanceMatrix(dimension, vector<double>(dimension,0.0));
			for (int i = 0; i < dimension; ++i)
			{
				for (int j = i+1; j < dimension; ++j)
				{
					x1 = instanceData.cities[i].x;
					y1 = instanceData.cities[i].y;

					x2 = instanceData.cities[j].x;
					y2 = instanceData.cities[j].y;

					//cout << x1 << " " << y1 << " " << x2 << " " << y2 << endl;

					distance = calculateDistance(x1, y1, x2, y2);
					instanceMatrix[i][j] = distance;
					instanceMatrix[j][i] = distance;

					//cout << "camino: | " << i << " -> " << j << " | posee costo: " << instanceMatrix[i][j] << endl;
				}
			}
			solution greedy = greedySolution(instanceMatrix);
			end = clock();
			double time_taken = double(end - start) / double(CLOCKS_PER_SEC);

			cout << "Tiempo de ejecucion: " << time_taken << " segundos" << endl;

			cout << "inicio: " << greedy.start << " - costo: " << greedy.value << endl << endl;
			generateOutput(greedy, instancesArray[i], seed, time_taken);
		}
	}

	return 0;
}