#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

int main() {

	std::ifstream  plik;
	plik.open("day9_input.txt", std::ios::in);
	std::string temp;
	unsigned long int answer{};
	
	if (plik.is_open()) {
		std::cout<<"File opened\n";
		
		std::vector<std::vector<int>>v (2, std::vector<int> (10,0));
		std::vector <std::string> v9;
		const int x{0},y{1};
		
		for (int i{}; i<v.size(); i++){
			for (int j{}; j<v[0].size(); j++){
				std::cout<<v[i][j]<<" ";
			}
			std::cout<<"\n";
		}
		while(getline(plik,temp)){
			
			int steps = stoi(temp.substr(2,temp.length()-2));					
			if(temp[0]=='R'){
				for (int i{}; i<steps; i++){
					v[x][0]++;
					for (int j{1}; j<10; j++){
							   if(v[x][j-1]-v[x][j]>1 && v[y][j-1]!=v[y][j]){
							v[x][j]++;
							v[y][j]=v[y][j-1];
						} else if(v[x][j-1]-v[x][j]>1 && v[y][j-1]==v[y][j]){
							v[x][j]++;
						} else if(v[x][j-1]-v[x][j]<1 && v[y][j-1]!=v[y][j]){
							v[x][j]--;
							v[y][j]=v[y][j-1];
						} else if(v[x][j-1]-v[x][j]<1 && v[y][j-1]==v[y][j]){
							v[x][j]--;
						} else if(v[y][j-1]-v[y][j]>1 && v[x][j-1]!=v[x][j]){
							v[y][j]++;
							v[x][j]=v[x][j-1];
						} else if(v[y][j-1]-v[y][j]>1 && v[x][j-1]==v[x][j]){
							v[y][j]++;
						} else if(v[y][j-1]-v[y][j]<1 && v[x][j-1]!=v[x][j]){
							v[y][j]--;
							v[x][j]=v[x][j-1];
						} else if(v[y][j-1]-v[y][j]<1 && v[x][j-1]==v[x][j]){
							v[y][j]--;
						}
					}
					//if(v9.size() && v9[v9.size()-1]!=std::to_string(v[x][9])+","+std::to_string(v[y][9]))					
					v9.push_back(std::to_string(v[x][9])+","+std::to_string(v[y][9]));
				}
			} else if(temp[0]=='L'){
				for (int i{}; i<steps; i++){
					v[x][0]--;
					for (int j{1}; j<10; j++){
							   if(v[x][j-1]-v[x][j]>1 && v[y][j-1]!=v[y][j]){
							v[x][j]++;
							v[y][j]=v[y][j-1];
						} else if(v[x][j-1]-v[x][j]>1 && v[y][j-1]==v[y][j]){
							v[x][j]++;
						} else if(v[x][j-1]-v[x][j]<1 && v[y][j-1]!=v[y][j]){
							v[x][j]--;
							v[y][j]=v[y][j-1];
						} else if(v[x][j-1]-v[x][j]<1 && v[y][j-1]==v[y][j]){
							v[x][j]--;
						} else if(v[y][j-1]-v[y][j]>1 && v[x][j-1]!=v[x][j]){
							v[y][j]++;
							v[x][j]=v[x][j-1];
						} else if(v[y][j-1]-v[y][j]>1 && v[x][j-1]==v[x][j]){
							v[y][j]++;
						} else if(v[y][j-1]-v[y][j]<1 && v[x][j-1]!=v[x][j]){
							v[y][j]--;
							v[x][j]=v[x][j-1];
						} else if(v[y][j-1]-v[y][j]<1 && v[x][j-1]==v[x][j]){
							v[y][j]--;
						}
					}					
					v9.push_back(std::to_string(v[x][9])+","+std::to_string(v[y][9]));
				}
			} else if(temp[0]=='U'){
				for (int i{}; i<steps; i++){
					v[y][0]++;
					for (int j{1}; j<10; j++){
							   if(v[x][j-1]-v[x][j]>1 && v[y][j-1]!=v[y][j]){
							v[x][j]++;
							v[y][j]=v[y][j-1];
						} else if(v[x][j-1]-v[x][j]>1 && v[y][j-1]==v[y][j]){
							v[x][j]++;
						} else if(v[x][j-1]-v[x][j]<1 && v[y][j-1]!=v[y][j]){
							v[x][j]--;
							v[y][j]=v[y][j-1];
						} else if(v[x][j-1]-v[x][j]<1 && v[y][j-1]==v[y][j]){
							v[x][j]--;
						} else if(v[y][j-1]-v[y][j]>1 && v[x][j-1]!=v[x][j]){
							v[y][j]++;
							v[x][j]=v[x][j-1];
						} else if(v[y][j-1]-v[y][j]>1 && v[x][j-1]==v[x][j]){
							v[y][j]++;
						} else if(v[y][j-1]-v[y][j]<1 && v[x][j-1]!=v[x][j]){
							v[y][j]--;
							v[x][j]=v[x][j-1];
						} else if(v[y][j-1]-v[y][j]<1 && v[x][j-1]==v[x][j]){
							v[y][j]--;
						}
					}					
					v9.push_back(std::to_string(v[x][9])+","+std::to_string(v[y][9]));
				}
				
				/*for (int i{}; i<steps; i++){
					y++;
					if(y-vy>1 && x!=vx){
						vy++;
						vx=x;
					} else if (y-vy>1){
						vy++;
					}
					v.push_back(std::to_string(vx)+","+std::to_string(vy));
				}*/				
			} else if(temp[0]=='D'){
				for (int i{}; i<steps; i++){
					v[y][0]--;
					for (int j{1}; j<10; j++){
							   if(v[x][j-1]-v[x][j]>1 && v[y][j-1]!=v[y][j]){
							v[x][j]++;
							v[y][j]=v[y][j-1];
						} else if(v[x][j-1]-v[x][j]>1 && v[y][j-1]==v[y][j]){
							v[x][j]++;
						} else if(v[x][j-1]-v[x][j]<1 && v[y][j-1]!=v[y][j]){
							v[x][j]--;
							v[y][j]=v[y][j-1];
						} else if(v[x][j-1]-v[x][j]<1 && v[y][j-1]==v[y][j]){
							v[x][j]--;
						} else if(v[y][j-1]-v[y][j]>1 && v[x][j-1]!=v[x][j]){
							v[y][j]++;
							v[x][j]=v[x][j-1];
						} else if(v[y][j-1]-v[y][j]>1 && v[x][j-1]==v[x][j]){
							v[y][j]++;
						} else if(v[y][j-1]-v[y][j]<1 && v[x][j-1]!=v[x][j]){
							v[y][j]--;
							v[x][j]=v[x][j-1];
						} else if(v[y][j-1]-v[y][j]<1 && v[x][j-1]==v[x][j]){
							v[y][j]--;
						}
					}					
					v9.push_back(std::to_string(v[x][9])+","+std::to_string(v[y][9]));
				}
			}
		}
		
		for (int i{}; i<v.size(); i++){
			for (int j{}; j<v[0].size(); j++){
				std::cout<<v[i][j]<<" ";
			}
			std::cout<<"\n";
		}
		
		std::sort(v9.begin(),v9.end());
		std::cout<<v9.size()<<"\n";
		for (size_t i{}; i<v9.size()-1; i++){
			if(v9[i]!=v9[i+1]) answer++;
		}
		
		std::cout<<"Answer: "<<answer+1<<"\n";
		//79 wrong
	} else {
		
		std::cout << "Nie otwarto pliku";	
		
	}

	plik.close();


}
