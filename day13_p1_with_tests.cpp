#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>
#include <chrono>
#include <algorithm>

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

		std::cout<<"from getNextElement: --stack1 pos: "<<stack1.top().pos<<", idxEnd: "<<stack1.top().idxEnd<<"\n";
					
		if (s1[stack1.top().pos+1]>=48 && s1[stack1.top().pos+1]<=57){
			int stackToptemp = stack1.top().pos;
			stack1.top().pos+=3;
			bool isLastNum{false};
			if(stack1.top().pos > stack1.top().idxEnd) isLastNum = true;
			stack1.push( numOrList(stackToptemp, stackToptemp+1,stackToptemp+3,2,isLastNum,false) );
			std::cout << "++ adding stack num 10\n";
		} else {
			int stackToptemp = stack1.top().pos;
			stack1.top().pos+=2;
			bool isLastNum{false};
			if(stack1.top().pos > stack1.top().idxEnd) isLastNum = true;
			stack1.push( numOrList(stackToptemp, stackToptemp,stackToptemp+2,1,isLastNum,false) );
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
				stack1.push( numOrList(stackToptemp, i,stackToptemp+1,0,false,true) );
				std::cout << "++ adding stack list\n";
				std::cout << "\t idxStart: "<<stackToptemp<<"\n";
				std::cout << "\t idxEnd: "<<i<<"\n";
				break;
			}
		}
	}
}


	
void checkIndexCorrectness (int &index, std::queue<int> &correctIndexes, std::string &s1, std::string &s2, bool result, std::fstream &plik3){
	
	if(index == correctIndexes.front()){
		if(result==true){
			std::cout<<"INDEX: "<<index<<"\n";	
			std::cout<<"INDEX_Q: "<<correctIndexes.front()<<"\n";				
			std::cout<<"Should be true and it's true\n";			
		} else {
			std::cout<<"INDEX: "<<index<<"\n";	
			std::cout<<"INDEX_Q: "<<correctIndexes.front()<<"\n";			
			std::cout<<"Should be true and it's false!!!\n";
			std::cout<<s1<<"\n";
			std::cout<<s2<<"\n\n";
			plik3<<"Index: "<<index<<"\n";			
			plik3<<s1<<"\n";
			plik3<<s2<<"\n\n";
		}
		correctIndexes.pop();
	} else {
		if(result==true){
			std::cout<<"INDEX: "<<index<<"\n";
			std::cout<<"INDEX_Q: "<<correctIndexes.front()<<"\n";			
			std::cout<<"Should be false and it's true!!!\n";
			std::cout<<s1<<"\n";
			std::cout<<s2<<"\n\n";	
			plik3<<"Index: "<<index<<"\n";
			plik3<<s1<<"\n";
			plik3<<s2<<"\n\n";			
		} else {
			std::cout<<"INDEX: "<<index<<"\n";	
			std::cout<<"INDEX_Q: "<<correctIndexes.front()<<"\n";			
			std::cout<<"Should be false and it's false\n";
		}
	}
}

int main() {

	
	std::fstream plik3;
	plik3.open("C:\\Users\\Puszek\\source\\repos\\adventofcode2022\\day13_falses.txt", std::ios::out | std::ios::app);

	auto start = std::chrono::high_resolution_clock::now();

	std::ifstream  plik;
	plik.open("C:\\Users\\Puszek\\source\\repos\\adventofcode2022\\day13_input.txt", std::ios::in);
	std::string temp;
	int sum{};
	
	std::queue<int> correctIndexes;
	std::ifstream plik2;
	
	plik2.open("C:\\Users\\Puszek\\source\\repos\\adventofcode2022\\day13_input2.txt", std::ios::in);
	
	if (plik2.is_open()) {
		while (getline(plik2, temp)) {
			correctIndexes.push(std::stoi(temp));
		}
		plik2.close();
	} else {
		std::cout << "Nie otwarto pliku";
	}

	
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
				
				stack1.push(numOrList(0, s1.length()-1,1,0,0,true));
				stack2.push(numOrList(0, s2.length()-1,1,0,0,true));
				
				while (!stack1.empty()){
					std::cout<<"<<while>> stack1 is not empty\n";
					std::cout<<"--stack1 pos: "<<stack1.top().pos<<", idxEnd: "<<stack1.top().idxEnd<<"\n";
					std::cout<<"--stack2 pos: "<<stack2.top().pos<<", idxEnd: "<<stack2.top().idxEnd<<"\n";
					
					if (stack1.top().list==true && stack2.top().list==true){

						if (stack2.top().idxEnd-stack2.top().idxStart==1 && stack1.top().idxEnd-stack1.top().idxStart==1){
							std::cout<<"empty both list, OK\n";
							stack1.pop();
							stack2.pop();														
							continue;
						} else if (stack1.top().idxEnd-stack1.top().idxStart==1){
							std::cout<<"empty left list, OK\n";
							sum+=index;
//plik3<<index<<"\n";
							checkIndexCorrectness(index, correctIndexes, s1, s2, true, plik3);
							break;
						} else if (stack2.top().idxEnd-stack2.top().idxStart==1){
							std::cout<<"empty right list, BAD\n";
							checkIndexCorrectness(index, correctIndexes, s1, s2, false, plik3);
							break;
						}
	
						if(stack1.top().pos < stack1.top().idxEnd && stack2.top().pos < stack2.top().idxEnd){
							std::cout<<"both stack top are unfinished lists\n";
							getNextElement(stack1, s1);
							getNextElement(stack2, s2);
						} else if (stack1.top().pos < stack1.top().idxEnd){
							std::cout<<"right side finished, BAD\n";
							checkIndexCorrectness(index, correctIndexes, s1, s2, false, plik3);
							break;
						} else if (stack2.top().pos < stack2.top().idxEnd){
							std::cout<<"left side finished, OK\n";
							checkIndexCorrectness(index, correctIndexes, s1, s2, true, plik3);
							sum+=index;
//plik3<<index<<"\n";
							break;
						} else {				 //??????????????????????			
							//if(stack1.size()==1){
								//std::cout<<"both side finished, OK\n";	
								//checkIndexCorrectness(index, correctIndexes, s1, s2, true, plik3);
								//sum+=index;
//plik3<<index<<"\n";
							//	break;
							//} else {
								stack1.pop();
								stack2.pop();
								continue;
							//}
						}
						
					} else if (stack1.top().list==true && stack2.top().list==false){
						
						if(stack1.top().pos >= stack1.top().idxEnd){
							std::cout<<"left side finished, OK\n";
							checkIndexCorrectness(index, correctIndexes, s1, s2, true, plik3);
							sum+=index;
//plik3<<index<<"\n";
							break;
						}
						std::cout<<"stack1 is list\n";
						getNextElement(stack1, s1);
						stack2.top().isLastNum = true;
						
					} else if (stack1.top().list==false && stack2.top().list==true){
						
						if(stack2.top().pos >= stack2.top().idxEnd){
							std::cout<<"right side finished, BAD\n";
							checkIndexCorrectness(index, correctIndexes, s1, s2, false, plik3);
							break;
						}
						std::cout<<"stack2 is list\n";
						getNextElement(stack2, s2);
						stack1.top().isLastNum = true;
					} else {
						
						std::cout<<"both stack top are nums\n";
							std::cout<<"---Num1: "<<s1.substr(stack1.top().idxStart,stack1.top().numDigits)<<"\n";
							std::cout<<"---Num2: "<<s2.substr(stack2.top().idxStart,stack2.top().numDigits)<<"\n";
							if(std::stoi(s1.substr(stack1.top().idxStart,stack1.top().numDigits))<std::stoi(s2.substr(stack2.top().idxStart,stack2.top().numDigits))){
								std::cout<<"----Num1 < Num2\n";
								checkIndexCorrectness(index, correctIndexes, s1, s2, true, plik3);
								sum+=index;
//plik3<<index<<"\n";
								break;
							} else if(std::stoi(s1.substr(stack1.top().idxStart,stack1.top().numDigits))>std::stoi(s2.substr(stack2.top().idxStart,stack2.top().numDigits))){
								std::cout<<"----Num1 > Num2\n";
								checkIndexCorrectness(index, correctIndexes, s1, s2, false, plik3);
								break;
							} else {
								std::cout<<"----Num1 == Num2\n";
								if(!stack1.top().isLastNum && stack2.top().isLastNum){
									std::cout<<"...but diff isLastNum, right out of items\n";
									checkIndexCorrectness(index, correctIndexes, s1, s2, false, plik3);
									break;
								} else if (stack1.top().isLastNum && !stack2.top().isLastNum){
									std::cout<<"...but diff isLastNum, left out of items\n";
									checkIndexCorrectness(index, correctIndexes, s1, s2, true, plik3);
									sum+=index;
//plik3<<index<<"\n";
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
		plik3.close();
		std::cout << "Answer: " << sum << " / Good answer: 6428\n";
	}
	else {
		std::cout << "Nie otwarto pliku";
	}

}
/*
part 1 - solution : 6428
part 2 - solution : 22464
[[1],[2,3,4]]
[[1],2,3,4]

6
7
11
12
14
17
18
19
21
22
23
25
26
27
28
29
31
33
37
38
40
41
42
44
46
49
50
51
53
57
60
63
65
66
68
72
74
75
76
77
78
80
81
82
84
85
87
88
90
91
93
94
98
102
107
109
111
112
113
114
116
118
119
120
121
125
126
127
129
130
132
134
135
136
138
139
140
141
145
147
148
150
part 1 - solution : 6428
part 2 - solution : 22464

Process finished with exit code 0

*/