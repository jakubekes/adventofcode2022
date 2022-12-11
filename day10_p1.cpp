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
		
		while(getline(plik,temp)){
			
			if(temp.substr(0,4)=="noop"){
					
				if(cycle==19 || cycle==59 || cycle==99 || cycle==139 || cycle==179 || cycle==219){
					answer+=val*(cycle+1);
					std::cout<<"val: "<<val<<"\n";
				}
				cycle++;
			} else {

				if(cycle==19 || cycle==59 || cycle==99 || cycle==139 || cycle==179 || cycle==219){
					answer+=val*(cycle+1);
					std::cout<<"val: "<<val<<"\n";
				}
				cycle++;

				if(cycle==19 || cycle==59 || cycle==99 || cycle==139 || cycle==179 || cycle==219){
					answer+=val*(cycle+1);
					std::cout<<"val: "<<val<<"\n";
				}
				cycle++;
				
				val+=stoi(temp.substr(5,temp.length()-5));
			}
			
		}
		
		plik.close();

		std::cout<<"Answer: "<<answer<<"\n";
		
		auto finish = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = finish - start;
        printf("Elapsed time: %f\n",elapsed.count());

	} else {
		
		std::cout << "Nie otwarto pliku";	
		
	}

	plik.close();


}
