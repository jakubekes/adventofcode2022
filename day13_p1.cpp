#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>
#include <chrono>

struct numOrList{
	
	numOrList(int a, int b, int c, int d, int e, bool f):
	idxStart(a),
	idxEnd(b),
	pos(c), 
	numDigits(d), 
	isLastNum(e),
	list (f){}
	
	int idxStart{};
	int idxEnd{};
	int pos{};
	int numDigits{};
	bool isLastNum{};
	bool list{};

};

void getNextElement(std::stack <numOrList> &stack1, std::string &s1) {
	
	if (s1[stack1.top().pos]>=48 && s1[stack1.top().pos]<=57){					
		if (s1[stack1.top().pos+1]>=48 && s1[stack1.top().pos+1]<=57){
			int stackToptemp = stack1.top().pos;
			stack1.top().pos+=3;
			bool isLastNum{false};
			if(stack1.top().pos > stack1.top().idxEnd) isLastNum = true;
			stack1.push( numOrList(stackToptemp, stackToptemp+1,stackToptemp+3,2,isLastNum,false) );
		} else {
			int stackToptemp = stack1.top().pos;
			stack1.top().pos+=2;
			bool isLastNum{false};
			if(stack1.top().pos > stack1.top().idxEnd) isLastNum = true;
			stack1.push( numOrList(stackToptemp, stackToptemp,stackToptemp+2,1,isLastNum,false) );
		}
	} else {
		int openBracketCount{1};
		int closeBracketCount{0};
		for(int i{stack1.top().pos+1}; i<=stack1.top().idxEnd; i++){
			if(s1[i] == '[') {
				openBracketCount++;
				continue;
			}
			if(s1[i] == ']') closeBracketCount++;		
			if(openBracketCount == closeBracketCount){
				int stackToptemp = stack1.top().pos;
				stack1.top().pos=i+2;
				stack1.push( numOrList(stackToptemp, i,stackToptemp+1,0,false,true) );
				break;
			}
		}
	}
}

struct Stopwatch {
	Stopwatch(std::chrono::nanoseconds& result)
		:result{ result },
		start{ std::chrono::system_clock::now() } {}
	~Stopwatch() {
		result = std::chrono::system_clock::now() - start;
	}
private:
	std::chrono::nanoseconds& result;
	const std::chrono::time_point<std::chrono::system_clock> start;
};

int main() {

	std::ifstream  plik;
	plik.open("C:\\Users\\Puszek\\source\\repos\\adventofcode2022\\day13_input.txt", std::ios::in);
	std::string temp;
	int sum{};
	
	if (plik.is_open()) {
		
		std::chrono::nanoseconds elapsed;
		{		
		std::cout << "File opened\n";
		Stopwatch stopwatch{elapsed};
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
				
				stack1.push(numOrList(0, s1.length()-1,1,0,0,true));
				stack2.push(numOrList(0, s2.length()-1,1,0,0,true));
				
				while (!stack1.empty()){
					if (stack1.top().list==true && stack2.top().list==true){
						if (stack2.top().idxEnd-stack2.top().idxStart==1 && stack1.top().idxEnd-stack1.top().idxStart==1){
							stack1.pop();
							stack2.pop();														
							continue;
						} else if (stack1.top().idxEnd-stack1.top().idxStart==1){
							sum+=index;
							break;
						} else if (stack2.top().idxEnd-stack2.top().idxStart==1){
							break;
						}
						
						if(stack1.top().pos < stack1.top().idxEnd && stack2.top().pos < stack2.top().idxEnd){
							getNextElement(stack1, s1);
							getNextElement(stack2, s2);
						} else if (stack1.top().pos < stack1.top().idxEnd){
							break;
						} else if (stack2.top().pos < stack2.top().idxEnd){
							sum+=index;
							break;
						} else {
							stack1.pop();
							stack2.pop();
							continue;
						}					
					} else if (stack1.top().list==true && stack2.top().list==false){
						
						if(stack1.top().pos >= stack1.top().idxEnd){
							sum+=index;
							break;
						}
						getNextElement(stack1, s1);
						stack2.top().isLastNum = true;						
					} else if (stack1.top().list==false && stack2.top().list==true){
						if(stack2.top().pos >= stack2.top().idxEnd){
							break;
						}
						getNextElement(stack2, s2);
						stack1.top().isLastNum = true;
					} else {
							if(std::stoi(s1.substr(stack1.top().idxStart,stack1.top().numDigits))<std::stoi(s2.substr(stack2.top().idxStart,stack2.top().numDigits))){
								sum+=index;
								break;
							} else if(std::stoi(s1.substr(stack1.top().idxStart,stack1.top().numDigits))>std::stoi(s2.substr(stack2.top().idxStart,stack2.top().numDigits))){
								break;
							} else {
								if(!stack1.top().isLastNum && stack2.top().isLastNum){
									break;
								} else if (stack1.top().isLastNum && !stack2.top().isLastNum){
									sum+=index;
									break;	
								}
								stack1.pop();
								stack2.pop();
								continue;
							}	
					}
				}								
			}	
		}
		plik.close();
		}
		std::cout << "Answer: " << sum << " / Good answer: 6428\n";	
		std::cout<< (elapsed.count() / 1000)<<"ms";
	}
	else {
		std::cout << "Nie otwarto pliku";
	}

}