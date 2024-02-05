#include <iostream>
#include <string>
#include <fstream>
#include <vector>

int main() {

	std::ifstream  plik;
	plik.open("day3_input.txt");
	std::string temp;
	unsigned long int answer{};

	if (plik.is_open()) {
		while(getline(plik,temp)){
			bool found{};
			std::cout<<temp<<" ";
			size_t l = temp.length()/2;
			for (size_t i{}; i<l; i++){
				for (size_t j{l}; j<temp.length(); j++){
					if (temp[i]==temp[j]){
						if(temp[i]>=97){
							answer+=temp[i]-96;
							std::cout<<temp[i]<<" "<<answer<<" (>) \n";
						} else {
							answer+=temp[i]-38;
							std::cout<<temp[i]<<" "<<answer<<" (<) \n";
						}
						found = true;
						break;
					}
				}
				if(found)break;						
			}
		
		}
		std::cout<<"Answer: "<<answer<<"\n";
	}
	else {
		
		std::cout << "File not opened, quitting.";
	}

	plik.close();
}