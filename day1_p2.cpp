#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

int main() {

	std::ifstream  plik;
	plik.open("day1_input.txt");
	std::string temp;
	unsigned long int answer{}, tempnum{};

	std::vector <unsigned long int> v;
	short int smallest_idx{0};
	
	if (plik.is_open()) {
		while(getline(plik,temp) && v.size()<3){
			if(temp.length()==0){
				v.push_back(tempnum);
				tempnum=0;
				continue;
			}
			tempnum += std::stoi(temp);
		}
				
		for(int i{1}; i<3; i++){
			if(v[smallest_idx]>v[i])smallest_idx=i;
		}

		if(temp.length()!=0)tempnum += std::stoi(temp);
		
		while(getline(plik,temp)){
			if(temp.length()==0){
				bool is_larger{};
				for(int i{0}; i<3; i++){
					if(smallest_idx==i)continue;
					if(v[smallest_idx]>v[i])smallest_idx=i;
					if(tempnum>v[i])is_larger = true;				
				}
				if(is_larger == true)v[smallest_idx]=tempnum;
				tempnum = 0;
				continue;
			}
			tempnum += std::stoi(temp);
		}

		bool is_larger{};
		for(int i{0}; i<3; i++){
			if(smallest_idx==i)continue;
			if(v[smallest_idx]>v[i])smallest_idx=i;
			if(tempnum>v[i])is_larger = true;				
		}
		if(is_larger == true)v[smallest_idx]=tempnum;
		tempnum = 0;
		for(int i{}; i<3; i++){
			answer+=v[i];
		}
		
		std::cout<<"Answer: "<<answer<<"\n";
	}
	else {	
		std::cout << "File not opened, quitting.";
	}

	plik.close();
}