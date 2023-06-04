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

			for (int i{}; i < temp.length(); i++) {


				if ((temp[i] == '[' || temp[i] == ']') && vtemp.size() > 0) {
					if (vflag) {
						v2.push_back(vtemp);
					}
					else {
						v1.push_back(vtemp);
					}
					vtemp.clear();
					if(temp[i] == '['){
						squareBracketFlag=0;
					} else {
						squareBracketFlag=1;
					}
					continue;
				}
				else if (temp[i] == '[' && temp[i + 1] == ']') {
					vtemp.push_back(-1);
					if (vflag) {
						v2.push_back(vtemp);
					}
					else {
						v1.push_back(vtemp);
					}
					vtemp.clear();
					i++;
					squareBracketFlag = 1;
					continue;
				}
				else if ((temp[i] == '[' || temp[i] == ']') && vtemp.size() == 0) {
					if(temp[i] == '['){
						squareBracketFlag=0;
					} else {
						squareBracketFlag=1;
					}
					continue;
				}

				if (temp[i] == ',' && squareBracketFlag == 1) {
					if (vflag) {
						v2.push_back(vtemp);
					}
					else {
						v1.push_back(vtemp);
					}
					vtemp.clear();
					continue;
				} else if (temp[i] == ',' && squareBracketFlag == 0){
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
				for (int i{}; i < v1.size(); i++) {
					bool breakCheck{};
					for (int j{}; j < v1[i].size(); j++) {
						if (v2.size() == i) {
							sum+=index;
							breakCheck = 1;
							break;
						}
						else if (v2[i].size() == j) { //out of items on the right
							breakCheck = 1;
							break;
						}
						else if (v2[i][j] == -1) { //out of items on the right, empty list
							breakCheck = 1;
							break;
						}
						else if (v2[i][j] < v1[i][j]) { //v2 is smaller
							breakCheck = 1;
							break;
						}
						else {
							sum+=index;
							breakCheck = 1;
							break;
						}
					}
					if (breakCheck) break;
				}

				/*std::cout<<"v1:\n";
				for(int i{}; i<v1.size(); i++){
				for(int j{}; j<v1[i].size(); j++){
					std::cout<<v1[i][j]<<", ";
				}
				std::cout<<"\n";
				}

				std::cout<<"v2:\n";
				for(int i{}; i<v2.size(); i++){
				for(int j{}; j<v2[i].size(); j++){
					std::cout<<v2[i][j]<<", ";
				}
				std::cout<<"\n";
				}*/

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