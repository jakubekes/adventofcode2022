#include <iostream>
#include <string>
#include <fstream>

int main() {

	std::ifstream  plik;
	plik.open("day1_input.txt", std::ios::in);
	std::string temp;
	unsigned long int answer{}, tempnum{};
	
	if (plik.is_open()) {
		while(getline(plik,temp)){
			if(temp.length()==0){
				if(answer<tempnum)answer=tempnum;
				tempnum=0;
				continue;
			}
			tempnum += std::stoi(temp);
		}
		
		if(answer<tempnum)answer=tempnum;
		tempnum=0;
		
		std::cout<<"Answer: "<<answer<<"\n";

	}
	else {
		
		std::cout << "Nie otwarto pliku";
		
	}

	plik.close();


}