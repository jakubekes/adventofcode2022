#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>

struct monkey {

	monkey(std::vector<unsigned int> &vec, char& operationChar, unsigned int& operationNum, unsigned int& testNum, unsigned int& trueCase, unsigned int& falseCase) :
		operationChar(operationChar),
		operationNum(operationNum),
		testNum(testNum),
		trueCase(trueCase),
		falseCase(falseCase),
		v(vec)
	{}

	void operation (int index){
			switch (operationChar){
				case '+':
					v[index]+=operationNum;
				break;
				case '*':
					if(operationNum==0){
						v[index]*=v[index];
					} else {
					v[index]*=operationNum;
					}
				break;
			}
	}
	
	bool isDivisible(int index){
		
		if (v[index]%testNum==0) return true;
		
		return false;
	}
			/*bool test (int index, int divider){
			if(items[index]%divider>0) return false;
			return true;
		}*/
public:
	std::vector <unsigned int> v;
	char operationChar{};
	unsigned long long int operationNum{};
	unsigned int testNum{};
	unsigned int trueCase{};
	unsigned int falseCase{};
	unsigned int inspections{};

};

int main() {

	auto start = std::chrono::high_resolution_clock::now();

	std::ifstream  plik;
	plik.open("day11_input.txt", std::ios::in);
	std::string temp;
	unsigned long int answer{};

	if (plik.is_open()) {
		std::cout << "File opened\n";

		std::vector<monkey> m;
		std::vector<unsigned int> v;
		char operationChar{};
		unsigned int operationNum{};
		unsigned int testNum{};
		unsigned int trueCase{};
		unsigned int falseCase{};

		while (getline(plik, temp)) {

			if (temp.length() == 0) {
				m.push_back(monkey(v, operationChar, operationNum, testNum, trueCase, falseCase));
				v.clear();
				operationChar = 0;
				operationNum = 0;
				testNum = 0;
				trueCase = 0;
				falseCase = 0;
				continue;
			}

			if (temp.substr(2, 2) == "St") {
				std::string n;
				for (int i{ 18 }; i < temp.length(); i++) {
					if (temp[i] >= 48 && temp[i] <= 57) {
						n += temp[i];
					}
					else {
						v.push_back(stoi(n));
						n = "";
						i++;
					}
				}

				v.push_back(stoi(n));
				n = "";

				for (int i{ 0 }; i < v.size(); i++) {
					std::cout << v[i] << ", ";
				}
				std::cout << "\n";
				
			}
			else if (temp.substr(2, 2) == "Op") {
				operationChar = temp[23];
				if (temp[25] >= 48 && temp[25] <= 57) operationNum = stoi(temp.substr(25, temp.length() - 25));
				std::cout << operationChar << "\n";
				std::cout << operationNum << "\n";
			}
			else if (temp.substr(2, 2) == "Te") {
				testNum = stoi(temp.substr(21, temp.length() - 21));
				std::cout << "testNum " << testNum << "\n";
			}
			else if (temp.substr(7, 2) == "tr") {
				trueCase = stoi(temp.substr(29, 1));
				std::cout << "trueCase " << trueCase << "\n";
			}
			else if (temp.substr(7, 2) == "fa") {
				falseCase = stoi(temp.substr(30, 1));
				std::cout << "falseCase " << falseCase << "\n";
			}
		}
		m.push_back(monkey(v, operationChar, operationNum, testNum, trueCase, falseCase));
		v.clear();
		operationChar = 0;
		operationNum = 0;
		testNum = 0;
		trueCase = 0;
		falseCase = 0;

			/*std::cout<<"Round: INIT: \n";
			for (int i=0; i<m.size(); i++){
					std::cout<<"Monkey "<<i<<" items: ";
					for (int j=0; j<m[i].v.size(); j++){
						std::cout<<m[i].v[j]<<" ";		
					}
					std::cout<<"\n";
			}*/
		
		for (int i=0; i<10000; i++){
			
			
			
			for (int j{}; j<m.size(); j++){
				if (m[j].v.size()==0) continue;
							
				for(int k{}; k<m[j].v.size(); k++){
					//std::cout<<"Checking monkey: "<<j<<" element: "<<m[j].v[k]<<"\n";
					m[j].inspections++;
					//m[j].operation(k);
					//std::cout<<"After operation: "<<m[j].v[k]<<"\n";
					//m[j].v[k]/=3;
					//std::cout<<"After div3: "<<m[j].v[k]<<"\n";
					bool isDiv = m[j].isDivisible(k);
					if(isDiv){
						m[m[j].trueCase].v.push_back(m[j].v[k]);
						m[j].v.erase(m[j].v.begin() + k);
						k--;
					} else {
						m[m[j].falseCase].v.push_back(m[j].v[k]);
						m[j].v.erase(m[j].v.begin() + k);
						k--;
					}
				}
				
			}
			
			/*std::cout<<"Round: "<<i<<"\n";
			for (int i=0; i<m.size(); i++){
					std::cout<<"Monkey "<<i<<" items: ";
					for (int j=0; j<m[i].v.size(); j++){
						std::cout<<m[i].v[j]<<" ";		
					}
					std::cout<<"\n";
			}*/
		}
		
				/*for (int i=0; i<m.size(); i++){
					std::cout<<"Monkey "<<i<<" items: ";
					for (int j=0; j<m[i].v.size(); j++){
						std::cout<<m[i].v[j]<<" ";		
					}
					std::cout<<"\n";
				}*/
		std::vector<unsigned int> insp;
		for (int i=0; i<m.size(); i++){
			insp.push_back(m[i].inspections);
					std::cout<<"Monkey: "<<i<<"\n";
					for (int j=0; j<m[i].v.size(); j++){
						std::cout<<m[i].v[j]<<" ";
					}
					std::cout<<"\n";
		}
		
		plik.close();
		
		std::sort(insp.begin(), insp.end());
		answer=insp[insp.size()-2]*insp[insp.size()-1];
		std::cout << "Answer: " << answer << "\n";

		auto finish = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = finish - start;
		printf("Elapsed time: %f\n", elapsed.count());

	}
	else {

		std::cout << "Nie otwarto pliku";

	}

	plik.close();


}
