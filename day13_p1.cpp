#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>
#include <chrono>
#include <algorithm>

int main() {

	auto start = std::chrono::high_resolution_clock::now();

	std::ifstream  plik;
	plik.open("C:\\Users\\Puszek\\source\\repos\\adventofcode2022\\day13_input.txt", std::ios::in);
	std::string temp;
	int sum{};

	if (plik.is_open()) {
		std::cout << "File opened\n";

		std::vector<std::vector<int>> v1, v2;
		std::vector<int> vtemp;
		bool vflag{ 1 };
		bool squareBracketFlag{};
		int index{};
		
		while (getline(plik, temp)) {

			if (temp.length() == 0) continue;

			if (vflag) {
				vflag = 0;
				index++;
			}
			else {
				vflag = 1;
			}
			//if closing bracket flag then next number is 'alone'/not in any list, must be put into the list
			//all single elements  between 2x [ should be put into new list
			for (int i{}; i < temp.length(); i++) {

				if (temp[i] == '[' && temp[i+1] == ']') {
					
					if(vtemp.size()>0){
						if (vflag) {
						v2.push_back(vtemp);
						}
						else {
						v1.push_back(vtemp);
						}
						vtemp.clear();
					}
					vtemp.push_back(-1);
					if (vflag) {
						v2.push_back(vtemp);
					}
					else {
						v1.push_back(vtemp);
					}
					vtemp.clear();
					squareBracketFlag = 1;
					continue;
				
				} else if (temp[i] == '[' && vtemp.size()>0) {
					if (vflag) {
						v2.push_back(vtemp);
					}
					else {
						v1.push_back(vtemp);
					}
					vtemp.clear();
					squareBracketFlag=0;
					continue;
				} else if (temp[i] == ']' && vtemp.size()>0){
					if (vflag) {
						v2.push_back(vtemp);
					}
					else {
						v1.push_back(vtemp);
					}
					vtemp.clear();
					squareBracketFlag = 1;
					continue;
				} else if (temp[i] == '[' && vtemp.size()==0){
					squareBracketFlag=0;
					continue;
				} else if (temp[i] == ']'){
					continue;
				}
				
				if (temp[i] == ','){
					continue;
				}
				
				if (temp[i + 1] <= 57 && temp[i + 1] >= 48) {
					vtemp.push_back(10);
					i++;
				}
				else {
					vtemp.push_back(int(temp[i]) - 48);
				}


			}

			if (vflag == 1) {
				std::cout<<"	INDEX: "<<index<<" ";
				for (int i{}; i < v1.size(); i++) {	
					bool breakCheck{};				
					for (int j{}; j < v1[i].size(); j++) {	
					
						if (i == v2.size()){
							breakCheck = 1;
							std::cout<<"STAGE0 NO\n";
							break;
						}
						
						if (j==v2[i].size()){
							breakCheck = 1;
							std::cout<<"STAGE1 NO\n";
							break;
						}
						
						if (v2[i][j] == -1){
							breakCheck = 1;
							std::cout<<"STAGE1.1 NO\n";
							break;
						}
						
						if(v1[i][j] > v2[i][j]){
							breakCheck = 1;
							std::cout<<"STAGE2 NO\n";
							break;
						} else if(v1[i][j] < v2[i][j]){
							sum += index;
							breakCheck = 1;
							std::cout<<"STAGE3 YES\n";
							break;
						}
						
						if(i==v1.size()-1 && j==v1[i].size()-1){
						sum += index;
						std::cout<<"STAGE4 YES\n";
						}
					}

					if(breakCheck) break;
					
					
				}

				std::cout<<"v1: "<<v1.size()<<"\n";
				for(int i{}; i<v1.size(); i++){
				for(int j{}; j<v1[i].size(); j++){
					std::cout<<v1[i][j]<<", ";
				}
				std::cout<<"size: "<<v1[i].size()<<"\n";
				}

				std::cout<<"v2: "<<v2.size()<<"\n";
				for(int i{}; i<v2.size(); i++){
				for(int j{}; j<v2[i].size(); j++){
					std::cout<<v2[i][j]<<", ";
				}
				std::cout<<"size: "<<v2[i].size()<<"\n";
				}

				v1.clear();
				v2.clear();
			}
		}
		plik.close();

		std::cout << "Answer: " << sum;

	}
	else {

		std::cout << "Nie otwarto pliku";

	}

}