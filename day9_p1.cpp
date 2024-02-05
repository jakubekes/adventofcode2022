#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

int main() {

	std::ifstream  plik;
	plik.open("day9_input.txt");
	std::string temp;
	unsigned long int answer{};
	std::vector <std::string> v;
	
	if (plik.is_open()) {
		std::cout<<"File opened\n";
		int x{},y{},vx{},vy{};

		while(getline(plik,temp)){
			
			int steps = stoi(temp.substr(2,temp.length()-2));					
			if(temp[0]=='R'){
				for (int i{}; i<steps; i++){
					x++;
					if(x-vx>1 && y!=vy){
						vx++;
						vy=y;
					} else if (x-vx>1){
						vx++;
					}
					v.push_back(std::to_string(vx)+","+std::to_string(vy));
				}
				
			} else if(temp[0]=='L'){
				for (int i{}; i<steps; i++){
					x--;
					if(vx-x>1 && y!=vy){
						vx--;
						vy=y;
					} else if (vx-x>1){
						vx--;
					}
					v.push_back(std::to_string(vx)+","+std::to_string(vy));
				}
			} else if(temp[0]=='U'){
				for (int i{}; i<steps; i++){
					y++;
					if(y-vy>1 && x!=vx){
						vy++;
						vx=x;
					} else if (y-vy>1){
						vy++;
					}
					v.push_back(std::to_string(vx)+","+std::to_string(vy));
				}				
			} else if(temp[0]=='D'){
				for (int i{}; i<steps; i++){
					y--;
					if(vy-y>1 && x!=vx){
						vy--;
						vx=x;
					} else if (vy-y>1 && x==vx){
						vy--;
					}
					v.push_back(std::to_string(vx)+","+std::to_string(vy));
				}
			}
			
			
		}
		
		std::sort(v.begin(),v.end());
		
		for (size_t i{}; i<v.size()-1; i++){
			if(v[i]!=v[i+1]){
				answer++;
			} else {
				continue;
			}
		}
		
		std::cout<<"Answer: "<<answer+1<<"\n";
	}
	else {
		
		std::cout << "File not opened, quitting.";
	}

	plik.close();
}