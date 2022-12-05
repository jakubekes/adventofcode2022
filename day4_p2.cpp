#include <iostream>
#include <string>
#include <fstream>
#include <vector>

int main() {

	std::ifstream  plik;
	plik.open("day4_input.txt", std::ios::in);
	std::string temp;
	unsigned long int answer{};
	std::vector <int> v;
	
	if (plik.is_open()) {
		
		while(getline(plik,temp)){
			std::string numtemp;
			for (size_t i{}; i<temp.length(); i++){
				if(temp[i]=='-' || temp[i]==','){
					//std::cout<<numtemp<<"\n";
					v.push_back(std::stoi(numtemp));
					numtemp="";
					continue;
				}
				numtemp+=temp[i];
			}
			v.push_back(std::stoi(numtemp));

			if(v[0]>=v[2] && v[0]<=v[3]){
				answer++;
			} else if(v[2]>=v[0] && v[2]<=v[1]){
				answer++;
			}
			v.clear();
		}
		std::cout<<"Answer: "<<answer<<"\n";
		
		
	}
	else {
		
		std::cout << "Nie otwarto pliku";
		
	}

	plik.close();


}
