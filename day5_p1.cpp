#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stack>

int main() {

	std::ifstream  plik;
	plik.open("day5_input.txt", std::ios::in);
	std::string temp;
	std::string answer{};
	std::vector <std::stack<char>*> v, vec;
	for(size_t i{}; i<9; i++){
		v.push_back(new std::stack<char>);
		vec.push_back(new std::stack<char>);
	}
	
	if (plik.is_open()) {
		
		while(getline(plik,temp)){
			
			if(temp[1]=='1')break;
			for(size_t i{}; i<temp.length(); i+=4){
				if(temp[i]=='['){
					v[i/4]->push(temp[i+1]);
				}
			}
			
		}
		
		for(size_t i{}; i<9; i++){
			while(!v[i]->empty()){
				vec[i]->push(v[i]->top());
				v[i]->pop();
			}
			std::cout<<"vec "<<i<<" "<<vec[i]->top()<<"\n";
		}
		
		getline(plik,temp);
		while(getline(plik,temp)){
			const char* ch = temp.c_str();
			std::cout<<ch<<"\n";
			char chtemp[20];
			int a,b,c;
			sscanf(ch,"%s %d %s %d %s %d", chtemp, &a, chtemp, &b, chtemp, &c);
			std::cout<<a<<" "<<b<<" "<<c<<"\n";
			
			for(size_t i{}; i<a; i++){
				vec[c-1]->push(vec[b-1]->top());
				vec[b-1]->pop();
			}
		}
		
				
		for(size_t i{}; i<9; i++){
			answer+=vec[i]->top();
		}
		
		std::cout<<"Answer: "<<answer<<"\n";
		
		
		
		
	}
	else {
		
		std::cout << "Nie otwarto pliku";
		
	}

	plik.close();


}
