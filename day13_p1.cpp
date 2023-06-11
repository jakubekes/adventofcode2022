#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>
#include <chrono>
#include <algorithm>

struct numOrList{
	
	numOrList(int a, int b, int c, int d, bool e):
	idxStart(a),
	idxEnd(b),
	pos(c), 
	level(d), 
	list (e){}
	
	int idxStart{};
	int idxEnd{};
	int pos{};
	int level{};
	bool list{};
};

void getNextElement(std::stack <numOrList> &stack1, std::string &s1) {
	
	if (s1[stack1.top().pos]>=48 && s1[stack1.top().pos]<=57){
		if (s1[stack1.top().pos+1]>=48 && s1[stack1.top().pos+1]<=57){
			int stackToptemp = stack1.top().pos;
			stack1.top().pos+=3;
			stack1.push( numOrList(stackToptemp, stackToptemp+1,0,0,false) );
			std::cout << "++ adding stack num 10\n";
		} else {
			int stackToptemp = stack1.top().pos;
			stack1.top().pos+=2;
			stack1.push( numOrList(stackToptemp, stackToptemp,0,0,false) );
			std::cout << "++ adding stack num 0-9\n";
		}
	} else {
		int openBracketCount{1};
		int closeBracketCount{0};
		for(int i{stack1.top().pos+1}; i<=stack1.top().idxEnd; i++){
			if(s1[i] == '[') openBracketCount++;
			if(s1[i] == ']') closeBracketCount++;		
			if(openBracketCount == closeBracketCount){
				int stackToptemp = stack1.top().pos;
				stack1.top().pos=i+2;
				stack1.push( numOrList(stackToptemp+1, i-1,0,0,true) );
				std::cout << "++ adding stack list\n";
				break;
			}
		}
	}
}

int main() {

	auto start = std::chrono::high_resolution_clock::now();

	std::ifstream  plik;
	plik.open("C:\\Users\\Puszek\\source\\repos\\adventofcode2022\\day13_input.txt", std::ios::in);
	std::string temp;
	int sum{};

	if (plik.is_open()) {
		std::cout << "File opened\n";

		std::vector<std::vector<int>> v1, v2;
		std::vector<int> vtemp;
		bool vflag{ 1 };
		std::string s1,s2;
		int index{};
		
		while (getline(plik, temp)) {

			if (temp.length() == 0) continue;

			if (vflag) {
				vflag = 0;
				index++;
				s1 = temp;
			}
			else {
				vflag = 1;
				s2 = temp;
				
				// we have now lines pair and can compare
				std::stack <numOrList> stack1;
				std::stack <numOrList> stack2;
				
				stack1.push(numOrList(1, s1.length()-2,1,0,true));
				stack2.push(numOrList(1, s2.length()-2,1,0,true));
				
				while (!stack1.empty()){
					std::cout<<"<<while>> stack1 is not empty\n";
					std::cout<<"--stack1 pos: "<<stack1.top().pos<<"\n";
					std::cout<<"--stack2 pos: "<<stack2.top().pos<<"\n";
					if(stack1.top().pos < stack1.top().idxEnd && stack2.top().pos < stack2.top().idxEnd){
						std::cout<<"both pos are under idxEnd\n";
						if(stack1.top().list==true && stack2.top().list==true){
							std::cout<<"both stack top are lists\n";
							getNextElement(stack1, s1);
							getNextElement(stack2, s2);
						} else if (stack1.top().list==true && stack2.top().list==false){
							std::cout<<"stack1 is list\n";
							getNextElement(stack2, s2);
						} else if (stack1.top().list==false && stack2.top().list==true){
							std::cout<<"stack2 is list\n";
							getNextElement(stack1, s1);
						} else {
							std::cout<<"both stack top are nums\n";
							std::cout<<"---Num1: "<<s1.substr(stack1.top().idxStart,stack1.top().idxEnd)<<"\n";
							std::cout<<"---Num2: "<<s2.substr(stack2.top().idxStart,stack2.top().idxEnd)<<"\n";
							if(std::stoi(s1.substr(stack1.top().idxStart,stack1.top().idxEnd))<std::stoi(s2.substr(stack2.top().idxStart,stack2.top().idxEnd))){
								std::cout<<"----Num1 < Num2\n";
								sum+=index;
								break;
							} else if(std::stoi(s1.substr(stack1.top().idxStart,stack1.top().idxEnd))>std::stoi(s2.substr(stack2.top().idxStart,stack2.top().idxEnd))){
								std::cout<<"----Num1 > Num2\n";
								break;
							} else {
								std::cout<<"----Num1 == Num2\n";
								stack1.pop();
								stack2.pop();
								continue;
							}
						}
					
						
					} else if(stack1.top().pos >= stack1.top().idxEnd && stack2.top().pos < stack2.top().idxEnd){
						
						//left side finished, OK
					} else if(stack1.top().pos < stack1.top().idxEnd && stack2.top().pos >= stack2.top().idxEnd){
						
						//right side finished, BAD
					} else{
						
						// both sides finished without break, OK
						stack1.pop();
						stack2.pop();
						continue;
					}
					
				}
			}	
		}
		plik.close();
		std::cout << "Answer: " << sum;
	}
	else {
		std::cout << "Nie otwarto pliku";
	}

}