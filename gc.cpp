/******************************************************************************

Graph Creator by Neevan Abedin
6.8.2021

*******************************************************************************/
#include <iostream>
#include <math.h>
#include <iomanip>
#include <queue>
#include <cstring>
using namespace std;

int main(){
	
	vector<char*> Vertices;

	//adjacency matrix
	int adj[20][20];
	//initialize values as -1
	for(int columns = 0; columns <= 19; columns++){
		for (int rows = 0; rows <= 19; rows++){
			adj[columns][rows] = -1;
		}
	}
  	bool running = true;
	while (running ) {
		cout << "What would you like to do?\n" << 
		"1. Add vertex\n" << 
		"2. Add edge\n" <<
		"3. Delete vertex\n" <<
		"4. Delete edge\n" << 
		"5. Print adjacency matrix\n" << 
		"6. Find shortest path between 2 vertices\n" <<
		"7. Quit\n>>";

		int commandInput;
		cin >> commandInput;
		cin.get();
		
		if (commandInput == 1){ //create vertex
			cout << "Vertex label: \n>>";
			char* input = new char[100];
			cin.get(input,100);
			cin.get();

			if (Vertices.size() != 0) {
				int z;
				for(z = 0; z <= Vertices.size()-1; z++){
					if (strcmp(Vertices[z], input) == 0){	      
						break;
					}
				}
				if (z <= Vertices.size()-1){
						cout << "Cannot repeat labels. Please enter different character." << endl;
						break;
				}
				else{
						cout << "Vertex " << input << " created. " << endl;
						Vertices.push_back(input);
						adj[Vertices.size()-1][Vertices.size()-1] = 0; //distance between node and itself is 0
				}  
			}
			else{
				cout << "Vertex " << input << " is created. " << endl;
				Vertices.push_back(input);
				adj[Vertices.size()-1][Vertices.size()-1] = 0; ////distance between node and itself is 0
			}
		}
		else if (commandInput == 2){ //create edge
			char* vertex1 = new char[100];
			char* vertex2 = new char[100];
			int weight = 0;
			cout << "Starting vertex label: \n";

			cin.get(vertex1,100);
			cin.get();
			
			cout << "Ending vertex label: \n";
			
			cin.get(vertex2,100);
			cin.get();
			
			cout<< "Edge weight from " << vertex1 << " to " << vertex2 << ": \n";

			cin >> weight;
			cin.get();
			
			if (strcmp(vertex1,vertex2) == 0){
				cout << "Can't connect node to itself."  << endl;
			}
			else{
				int column;
				for(column = 0; column <= Vertices.size()-1; column++){
					if (strcmp(Vertices[column] , vertex1) == 0){
						break;
					}
				}
				int row;
				for(row = 0; row <= Vertices.size()-1; row++){
					if (strcmp(Vertices[row],vertex2) == 0){
						break;
					}
				}

				if (column > Vertices.size()-1){
					cout << "Starting vertex not found." << endl;
				}
				else if (row > Vertices.size()-1){
					cout << "Ending vertex not found." << endl;
				}
				else{
					adj[column][row] = weight;
					cout << "The weight that goes from "<< vertex1 << " to " << vertex2 << " is: " << weight << endl;
				}
			}
		}
		else if (commandInput == 3 ){ //delete vertex
			cout << "What's the name of the vertex that you would like to delete?\n>>";

			char* input = new char[100];
			cin.get(input,100);
			cin.get();

			if(Vertices.size() != 0){
				int z = 0;
				for(z = 0; z <= Vertices.size()-1; z++){
					if (strcmp(Vertices[z],input) == 0){	      
						break;
					}
				}
				if ((z <= Vertices.size()-1)){
					cout << "Vertex " << input << " deleted." << endl;
					
					Vertices.erase(Vertices.begin() + z);
					for(int i = 0; i < Vertices.size(); i++ ){
						cout << Vertices.at(i) << endl;
					}
					cout << z << endl;
					//set row and column to default if deleted vertex is last in list 
					if (z == Vertices.size()){
						for(int row = 0; row<Vertices.size(); row++){
							adj[z][row] = -1;
						}
						for(int column = 0; column < Vertices.size(); column++){
							adj[column][z] = -1;
						}
					}
				//else fill the empty space
				else{
					for(int g = 0; g < z;g++){
						for(int i = z+1; i <= Vertices.size();i++){
							adj[i-1][g]=adj[i][g];
							adj[i][g] = -1;
						}
					}
					for(int g = 0; g < z; g++){
						for(int i = z+1; i <= Vertices.size(); i++){
							adj[g][i-1]=adj[g][i];
							adj[g][i] = -1;
						}
					}
					for(int g = z+1; g <= Vertices.size(); g++ ){
						for(int i = z+1; i <= Vertices.size(); i++ ){
							adj[i-1][g-1]=adj[i][g];
							adj[i][g] = -1;
						}
					}
					for(int i = Vertices.size();i< 20; i++){
						for(int g = 0; g < 20; g++){
							adj[i][g] = -1;
						}
					}
					for(int g = Vertices.size(); g< 20; g++){
						for(int i = 0; i < 20; i++){
							adj[i][g] = -1;
						}
					}
					for(int i = 0; i < 20; i++){
						adj[i][i] = 0;
					}
				}
			}
				else{
					cout << "Vertex " << input << " does not exist." << endl;
				}
			}
			else{
				cout << "No such vertex." << endl;
			}
		}
		else if (commandInput == 4){ //delete edge
			char* vertex1 = new char[100];
			char* vertex2 = new char[100];
			int weight = 0;
			cout << "Starting vertex label: \n";

			cin.get(vertex1,100);
			cin.get();
			cout << "Ending vertex label: \n";
			
			cin.get(vertex2,100);
			cin.get();
			if (strcmp(vertex1,vertex2) == 0){
				cout << "Invalid connection."  << endl;
			}
			else{
				int q;
				for(q = 0; q <= Vertices.size()-1; q++){
					if (strcmp(Vertices[q],vertex1) == 0){
						break;
					}
				}
				int w;
				for(w = 0; w <= Vertices.size()-1; w++){
					if (strcmp(Vertices[w],vertex2) == 0){
						break;
					}
				}

				if (q > Vertices.size()-1){
					cout << "Starting vertex not found." << endl;
				}
				else if (w > Vertices.size()-1){
					cout << "Ending vertex not found." << endl;
				}
				else{
					adj[q][w] = -1;
					cout << "Edge from "<< vertex1 << " to " << vertex2 << " deleted." << endl;
				}
			}
		}
		else if (commandInput == 5){ //print adjacency list

			//a b c on top
			for(vector<char*>::iterator v = Vertices.begin(); v != Vertices.end(); v++ ){
				cout << "  " << *v << " ";
			}
			cout << endl;
			//print distances
			vector<char*> :: iterator b = Vertices.begin();
			for (int a = 0; a<= Vertices.size()-1; a++){
				cout << *b << " ";
				for (int c = 0; c<= Vertices.size()-1; c++){
					cout << adj[a][c] << "  ";
				}
				cout << endl;
				b++;
			}
		}
		else if (commandInput == 6) { //shortest distance
			char* vertex1 = new char[100];
			char* vertex2 = new char[100];
			int weight = 0;
			cout << "Starting vertex label: \n"; 
			
			cin.get(vertex1,100);
			cin.get();
			cout << "Ending vertex label: \n";
			cin.get(vertex2,100);
			cin.get();	 
			if (strcmp(vertex1,vertex2) == 0){
				cout << "Distance between a node and itself is 0."  << endl;
			}
			else{
				int q;
				for( q = 0; q <= Vertices.size()-1; q++){
					if (strcmp(Vertices[q],vertex1) == 0){
						break;
					}
				}
				int w;
				for(w = 0; w <= Vertices.size()-1; w++){
					if (strcmp(Vertices[w],vertex2) == 0){
						break;
					}
				}

				if (q > Vertices.size()-1){
					cout << "Starting vertex not found." << endl;
				}
				else if (w > Vertices.size()-1){
					cout << "Ending vertex not found." << endl;
				}
				else{
					//queue for path
					int size = Vertices.size();
					int arra [size][size];
					int go = q;
					int stop = w;
					for(int i = 0; i< size; i++){
						for(int k = 0; k< size; k++){
							arra[i][k] = -1;
						}  
					}
					int shortest = 0;
					int index = go;
					int indexx = 0;
					vector <int> tracker;
					for(int i=0; i<size; i++){
						for(int k = 0; k < size; k++){
							if(adj[index][k] != -1){
								if ((i == 0) || (arra[i-1][k] == -1)){
									arra[indexx][k] = adj[index][k] + shortest;
									// cout << arr[index][k] <<" + " << shortest << " = " << arra[i][k] << endl;
								}
								else{
									arra[indexx][k] = adj[index][k] + shortest;
									//cout << arr[index][k] <<" + " << shortest << " = " << arra[i][k] << endl;
									if (arra[indexx][k] > arra[indexx-1][k]){
										arra[indexx][k] = arra[indexx-1][k];
										//      cout << "same as last row" << endl;
									}
								}
							}
							else if (i != 0){
								arra[indexx][k] = arra[i-1][k];
							//  cout << "same as last row: " << arra[i-1][k] << endl;
							}
						}	
						tracker.push_back(index);
						shortest = 999;
						int yesno = 0;
						for(int k = 0; k < size; k++){
							yesno = 0;
							for (int gg = 0; gg < tracker.size(); gg++ ){
								if (k - (tracker.at(gg)) == 0 ){
									yesno = 1;
								}
							}		  
							if ((arra[indexx][k] > 0 ) && (arra[indexx][k] < shortest) && (yesno == 0)){
								shortest = arra[indexx][k];
								index = k;
								//cout << "new shortest " << shortest << " at " << index << endl;
							}
					else if ((arra[indexx][k] > 0) && (shortest == 999 ) && (yesno == 0)){
						shortest = arra[indexx][k];
						index = k;
						//  cout << "new shortest " << shortest << " at " << index << endl;
					}
				} 
				indexx++;
						}     
					for(int i = 0; i< size; i++){
							cout << endl;
						}
					if (arra[size-1][stop] == -1){
							cout << "No possible path" << endl; 
						}
					else{
							int weight = 9999999;
							cout << Vertices.at(go); 
							for(int l = 0; l < tracker.size(); l++){
								if (l == 0){
									weight =  arra[l][stop];
								}
								else{
									if (arra[l][stop] != arra[l-1][stop]){
										cout << "->" << Vertices.at(tracker.at(l));
										weight = arra[l][stop];
									}
								}
							}
							cout << "->" << Vertices.at(stop);
							cout << " Weight: " << weight << endl;
						}
				}
			}
		}
		else if (commandInput == 7) {
		    cout << "Goodbye.";
			running = false;
		}
		else {
			cout << "Invalid input. Please try again." << endl;
		}
    }
}