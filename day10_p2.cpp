#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>

int main() {

	auto start = std::chrono::high_resolution_clock::now();
	
	std::ifstream  plik;
	plik.open("day10_input.txt", std::ios::in);
	std::string temp;
	unsigned long int answer{};
	
	if (plik.is_open()) {
		std::cout<<"File opened\n";
		
		int cycle{};
		int val{1};
		std::vector<std::vector<char>> v (6,std::vector<char>(40,'.'));
		
		for (int i{}; i<v.size(); i++){
			for (int j{}; j<v[0].size(); j++){
				std::cout<<v[i][j];
			}
			std::cout<<"\n";
			
		}
		
		while(getline(plik,temp)){
			
			if(temp.substr(0,4)=="noop"){
					
				if(abs(cycle%40-val)<2){
					v[cycle/40][cycle%40]='#';	
				}
				cycle++;
			} else {

				if(abs(cycle%40-val)<2){
					v[cycle/40][cycle%40]='#';	
				}
				cycle++;

				if(abs(cycle%40-val)<2){
					v[cycle/40][cycle%40]='#';	
				}
				cycle++;
				
				val+=stoi(temp.substr(5,temp.length()-5));
			}
			
		}
		
		plik.close();

		std::cout<<"\nAnswer:\n";
		for (int i{}; i<v.size(); i++){
			for (int j{}; j<v[0].size(); j++){
				std::cout<<v[i][j];
			}
			std::cout<<"\n";
			
		}
		
		//std::cout<<"Answer: "<<answer<<"\n";
		
		auto finish = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = finish - start;
        printf("Elapsed time: %f\n",elapsed.count());

	} else {
		
		std::cout << "Nie otwarto pliku";	
		
	}

	plik.close();


}
