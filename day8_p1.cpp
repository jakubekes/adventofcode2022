#include <iostream>
#include <string>
#include <fstream>
#include <vector>

int checkTree (std::vector<std::vector<int>> &v, size_t i, size_t j){
	
	int treeHigh = v[i][j];
	bool visible {true};

	for (size_t k{}; k<j; k++){
		if(v[i][k]>=treeHigh){
			visible=false;
			break;
		}
	}
	if(visible)return 1;
	visible=true;
	
	for (size_t k{j+1}; k<v[0].size(); k++){
		if(v[i][k]>=treeHigh){
			visible=false;
			break;
		}
	}
	if(visible)return 1;
	visible=true;
	
	for (size_t k{}; k<i; k++){
		if(v[k][j]>=treeHigh){
			visible=false;
			break;
		}
	}
	if(visible)return 1;
	visible=true;

	for (size_t k{i+1}; k<v.size(); k++){
		if(v[k][j]>=treeHigh){
			visible=false;
			break;
		}
	}
	if(visible)return 1;
	
	return 0;
}

int main() {

	std::ifstream  plik;
	plik.open("day8_input.txt", std::ios::in);
	std::string temp;
	unsigned long int answer{};
	std::vector <std::vector<int>> v;
	std::vector<int> vtemp;
	
	if (plik.is_open()) {
		std::cout<<"File opened\n";
		while(getline(plik,temp)){
			for (size_t i{}; i<temp.length(); i++){
				vtemp.push_back(temp[i]-48);
			}
			v.push_back(vtemp);
			vtemp.clear();	
		}
		
		for (size_t i{}; i<v.size(); i++){
			for (size_t j{}; j<v[0].size(); j++){
				if(i==0 || j==0 || i==v.size()-1 || j==v[0].size()-1){
					answer++;
				} else if(checkTree(v,i,j)){
					answer++;
				}
			}
		}
		
		std::cout<<"Answer: "<<answer<<"\n";
		
	} else {
		
		std::cout << "Nie otwarto pliku";	
		
	}

	plik.close();


}
