#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>

struct monkey {

	monkey(std::vector<unsigned long long int> &vec, char& operationChar, unsigned long long int& operationNum, unsigned long long int& testNum, unsigned long long int& trueCase, unsigned long long int& falseCase) :
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

public:
	std::vector <unsigned long long int> v;
	char operationChar{};
	unsigned long long int operationNum{};
	unsigned long long int testNum{};
	unsigned long long int trueCase{};
	unsigned long long int falseCase{};
	unsigned long long int inspections{};
	
	unsigned long long int trueCaseCount{};
	unsigned long long int falseCaseCount{};

};

int main() {

	auto start = std::chrono::high_resolution_clock::now();

	std::ifstream  plik;
	plik.open("day11_input.txt");
	std::string temp;
	unsigned long long int answer{};

	if (plik.is_open()) {
		std::cout << "File opened\n";

		std::vector<monkey> m;
		std::vector<unsigned long long int> v;
		char operationChar{};
		unsigned long long int operationNum{};
		unsigned long long int testNum{};
		unsigned long long int trueCase{};
		unsigned long long int falseCase{};

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

		unsigned long long int supermodulo{1};
		
		for (unsigned long long int i=0; i<m.size(); i++){
			supermodulo*=m[i].testNum;
		}
		
		std::cout<<"Supermodulo: "<<supermodulo<<"\n";
		
		for (unsigned long long int i=0; i<10000; i++){
			for (unsigned long long int j{}; j<m.size(); j++){
				if (m[j].v.size()==0) continue;	
				for(unsigned long long int k{}; k<m[j].v.size(); k++){
					m[j].inspections++;
					m[j].operation(k);
					bool isDiv = m[j].isDivisible(k);
					if(isDiv){
						m[m[j].trueCase].v.push_back(m[j].v[k]%supermodulo);
						m[j].v.erase(m[j].v.begin() + k);
						k--;
						m[j].trueCaseCount++;
					} else {
						m[m[j].falseCase].v.push_back(m[j].v[k]%supermodulo);
						m[j].v.erase(m[j].v.begin() + k);
						k--;
						m[j].falseCaseCount++;
					}
				}
			}
		}

		std::vector<unsigned long long int> insp;
		for (unsigned long long int i=0; i<m.size(); i++){
			insp.push_back(m[i].inspections);		
		}
		
		plik.close();
		
		std::sort(insp.begin(), insp.end());
		answer = insp[insp.size()-2]*insp[insp.size()-1];
		std::cout << "Answer: " << answer << "\n";

		auto finish = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = finish - start;
		printf("Elapsed time: %f\n", elapsed.count());
	}
	else {
		
		std::cout << "File not opened, quitting.";
	}

	plik.close();
}