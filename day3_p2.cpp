#include <iostream>
#include <string>
#include <fstream>
#include <vector>

int main() {

	std::ifstream  plik;
	plik.open("day3_input.txt");
	std::string temp;
	unsigned long int answer{};
	std::vector <std::string> v;
	
	if (plik.is_open()) {
		while(getline(plik,temp)){
			char ch{};
			bool found{};
			v.push_back(temp);
			
			if(v.size()==3){
				for(size_t i{}; i<3; i++){
					std::cout<<v[i]<<"\n";
				}
							
				for (size_t i{}; i<v[0].length(); i++){
					for (size_t j{}; j<v[1].length(); j++){
						if(v[0][i]==v[1][j]){
							ch = v[0][i];
							break;
						}
					}
					for (size_t j{}; j<v[2].length(); j++){
						if(v[2][j]==ch){
							if(ch>=97){
								answer+=ch-96;
								std::cout<<ch<<(int)ch<<" "<<answer<<" >\n";
							} else {
								answer+=ch-38;
								std::cout<<ch<<(int)ch<<" "<<answer<<" <\n";
							}
							found=true;
							break;
						}
					
					}
					if (found)break;
				}
				v.clear();
			}
		}
		std::cout<<"Answer: "<<answer<<"\n";
	}
	else {
		
		std::cout << "File not opened, quitting.";
	}

	plik.close();
}