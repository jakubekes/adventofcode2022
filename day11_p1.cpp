#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>

/*struct monkey{
	
	//monkey(){}{}
	std::vector<int>items;
	
	void operation (int index, char op, int num){
		switch (op){
			case '+':
			
			
			break;
			case '*':
			
			
			break;
			
			
			
		}
	}
	
	bool test (int index, int divider){
		if(items[index]%divider>0) return false;
		return true;		
	}
		
	
};*/

int main() {

	auto start = std::chrono::high_resolution_clock::now();
	
	std::ifstream  plik;
	plik.open("day11_input.txt", std::ios::in);
	std::string temp;
	unsigned long int answer{};
	
	if (plik.is_open()) {
		std::cout<<"File opened\n";

		std::vector<int> v;
		char operationChar{};
		int operationNum{};
		int testNum{};
		int trueCase{};
		int falseCase{};
		
		while(getline(plik,temp)){
			
			if(temp.length()==0)continue;
			
			if(temp.substr(2,2)=="St"){
				std::string n;
				for (int i{18}; i<temp.length(); i++){
					if(temp[i]>=48 && temp[i]<=57){
						n+=temp[i];
					} else{
						v.push_back(stoi(n));
						n="";
						i++;
					}
				}
				
				v.push_back(stoi(n));
				n="";
						
				for (int i{0}; i<v.size(); i++){
					std::cout<<v[i]<<", ";
				}
				std::cout<<"\n";
				v.clear();
			}				
						
		}
		
		plik.close();

		std::cout<<"Answer: "<<answer<<"\n";
		
		auto finish = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = finish - start;
        printf("Elapsed time: %f\n",elapsed.count());

	} else {
		
		std::cout << "Nie otwarto pliku";	
		
	}

	plik.close();


}
