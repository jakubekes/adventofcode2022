#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>

int main() {

	auto start = std::chrono::high_resolution_clock::now();
	
	std::ifstream  plik;
	plik.open("day9_input.txt", std::ios::in);
	std::string temp;
	unsigned long int answer{};
	
	if (plik.is_open()) {
		std::cout<<"File opened\n";
		
		std::vector<std::vector<int>>v (2, std::vector<int> (10,0));
		std::vector <std::string> v9;
		v9.push_back("0,0");
		const int x{0},y{1};
		
		while(getline(plik,temp)){
			
			int steps = stoi(temp.substr(2,temp.length()-2));					
			if(temp[0]=='R'){
				for (int i{}; i<steps; i++){
					v[x][0]++;
					for (int j{1}; j<10; j++){
						int xdiff = v[x][j-1]-v[x][j];
						int ydiff = v[y][j-1]-v[y][j];
						if(abs(xdiff)<2 && abs(ydiff)<2) continue;					
						if(abs(xdiff)>0) v[x][j]+=xdiff/abs(xdiff);
						if(abs(ydiff)>0) v[y][j]+=ydiff/abs(ydiff);
					}			
					if(v9[v9.size()-1]!=std::to_string(v[x][9])+","+std::to_string(v[y][9])) v9.push_back(std::to_string(v[x][9])+","+std::to_string(v[y][9]));
				}
			} else if(temp[0]=='L'){
				for (int i{}; i<steps; i++){
					v[x][0]--;
					for (int j{1}; j<10; j++){
						int xdiff = v[x][j-1]-v[x][j];
						int ydiff = v[y][j-1]-v[y][j];
						if(abs(xdiff)<2 && abs(ydiff)<2) continue;					
						if(abs(xdiff)>0) v[x][j]+=xdiff/abs(xdiff);
						if(abs(ydiff)>0) v[y][j]+=ydiff/abs(ydiff);
					}		
					if(v9[v9.size()-1]!=std::to_string(v[x][9])+","+std::to_string(v[y][9])) v9.push_back(std::to_string(v[x][9])+","+std::to_string(v[y][9]));
				}
			} else if(temp[0]=='U'){
				for (int i{}; i<steps; i++){
					v[y][0]++;
					for (int j{1}; j<10; j++){
						int xdiff = v[x][j-1]-v[x][j];
						int ydiff = v[y][j-1]-v[y][j];
						if(abs(xdiff)<2 && abs(ydiff)<2) continue;					
						if(abs(xdiff)>0) v[x][j]+=xdiff/abs(xdiff);
						if(abs(ydiff)>0) v[y][j]+=ydiff/abs(ydiff);
					}			
					if(v9[v9.size()-1]!=std::to_string(v[x][9])+","+std::to_string(v[y][9])) v9.push_back(std::to_string(v[x][9])+","+std::to_string(v[y][9]));
				}
			} else if(temp[0]=='D'){
				for (int i{}; i<steps; i++){
					v[y][0]--;
					for (int j{1}; j<10; j++){
						int xdiff = v[x][j-1]-v[x][j];
						int ydiff = v[y][j-1]-v[y][j];
						if(abs(xdiff)<2 && abs(ydiff)<2) continue;					
						if(abs(xdiff)>0) v[x][j]+=xdiff/abs(xdiff);
						if(abs(ydiff)>0) v[y][j]+=ydiff/abs(ydiff);
					}			
					if(v9[v9.size()-1]!=std::to_string(v[x][9])+","+std::to_string(v[y][9])) v9.push_back(std::to_string(v[x][9])+","+std::to_string(v[y][9]));
				}
			}
		}
		
		plik.close();
		
		std::sort(v9.begin(),v9.end());
		std::cout<<v9.size()<<"\n";
		for (size_t i{}; i<v9.size()-1; i++){
			if(v9[i]!=v9[i+1]) answer++;
		}
		
		std::cout<<"Answer: "<<answer+1<<"\n";
		
		auto finish = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = finish - start;
        printf("Elapsed time: %f\n",elapsed.count());

	} else {
		
		std::cout << "Nie otwarto pliku";	
		
	}

	plik.close();


}
