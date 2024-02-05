#include <iostream>
#include <string>
#include <fstream>
#include <vector>

void checkTree (const std::vector<std::vector<int>> &v, int i, int j, unsigned long int &answer){
	
	int treeHigh = v[i][j];
	int x1{},x2{},y1{},y2{};
	
	for (int k{j-1}; k>=0; k--){
		if(v[i][k]>=treeHigh){
			x1++;
			break;
		}
		x1++;
	}
	
	for (int k{j+1}; k<v[0].size(); k++){
		if(v[i][k]>=treeHigh){
			x2++;
			break;
		}
		x2++;
	}
	
	for (int k{i-1}; k>=0; k--){
		if(v[k][j]>=treeHigh){
			y1++;
			break;
		}
		y1++;
	}

	
	for (int k{i+1}; k<v.size(); k++){
		if(v[k][j]>=treeHigh){
			y2++;
			break;
		}
		y2++;
	}

	if(x1*x2*y1*y2>answer) answer = x1*x2*y1*y2;
	
}

int main() {

	std::ifstream  plik;
	plik.open("day8_input.txt");
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
					continue;
				} else {
					checkTree(v,i,j,answer);
				}
			}
		}
		
		std::cout<<"Answer: "<<answer<<"\n";
	}
	else {
		
		std::cout << "File not opened, quitting.";
	}

	plik.close();
}