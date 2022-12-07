#include <iostream>
#include <string>
#include <fstream>
#include <vector>

int main() {

	std::ifstream  plik;
	plik.open("day7_input.txt", std::ios::in);
	std::string temp;
	unsigned long int answer{70000000};
	std::vector <unsigned long int> v;
	std::vector <unsigned long int> v_indexes;
	
	if (plik.is_open()) {
		
		while(getline(plik,temp)){
			
			if (temp=="$ cd .."){
				v_indexes.pop_back();
			} else if (temp.substr(2,2)== "cd"){
				v.push_back(0);
				v_indexes.push_back(v.size()-1);
			} else if (temp[0]>=49 && temp[0]<=57) {//49-57
				unsigned int a;
				char chtemp[50];
				const char* ch = temp.c_str();
				sscanf(ch,"%d %s", &a, chtemp);
				
				for (size_t i{}; i<v_indexes.size();i++){
					v[v_indexes[i]]+=a;
				}
				
			}
		}
			
		for (size_t i{}; i<v.size();i++){
			if(v[i]>=268565 && v[i]<answer)answer=v[i];
		}
		
		std::cout<<"/ space: "<<v[0]<<"\n";
		std::cout<<"Total FS space: "<<70000000<<"\n";
		std::cout<<"Needed space: "<<30000000<<"\n";
		std::cout<<"Current free space: "<<70000000-v[0]<<"\n";
		std::cout<<"Needed to free space: "<<30000000 - (70000000-v[0])<<"\n";
		std::cout<<"Answer: "<<answer<<"\n";
		//40268565 too high
		
	} else {
		
		std::cout << "Nie otwarto pliku";	
		
	}

	plik.close();


}
