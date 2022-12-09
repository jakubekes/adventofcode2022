#include <iostream>
#include <string>
#include <fstream>
#include <vector>

int main() {

	std::ifstream  plik;
	plik.open("day9_input.txt", std::ios::in);
	std::string temp;
	unsigned long int answer{};
	std::vector <std::vector<int>> v;
	std::vector<int> vtemp;
	
	if (plik.is_open()) {
		std::cout<<"File opened\n";
		
		int x{},y{};
		
		while(getline(plik,temp)){
			
			if(temp[0]=='R'){
				x+=stoi(temp.substr(2,temp.length()-2));
			} else if(temp[0]=='L'){
				x-=stoi(temp.substr(2,temp.length()-2));
			} else if(temp[0]=='U'){
				y+=stoi(temp.substr(2,temp.length()-2));
			} else if(temp[0]=='D'){
				y-=stoi(temp.substr(2,temp.length()-2));
			}
			
			std::cout<<"x: "<<x<<", y: "<<y<<"\n";
		}
		
	
		
		std::cout<<"Answer: "<<answer<<"\n";
		
	} else {
		
		std::cout << "Nie otwarto pliku";	
		
	}

	plik.close();


}
