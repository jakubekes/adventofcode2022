#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

int main() {

	std::ifstream  plik;
	plik.open("day6_input.txt");
	std::string temp;
	int answer{};
	std::vector <char> v;

	if (plik.is_open()) {
		
		while(getline(plik,temp)){
			
			for (size_t i{}; i<temp.length()-3; i++){
				bool flag{true};
				for (size_t j{i}; j<i+4; j++){
					v.push_back(temp[j]);
				}
				sort(v.begin(), v.end());
				for (size_t j{}; j<3; j++){
					if(v[j]==v[j+1]){
						flag=false;
						break;
					}
				}
				v.clear();
				if(flag){
					answer=i;
					break;
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