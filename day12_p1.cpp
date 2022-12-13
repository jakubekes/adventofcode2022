#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stack>
#include <chrono>

struct point{
	
	point(int x, int y):x(x),y(y){}
	
	int x;
	int y;
	int val{};
	std::stack <char> connections;
};

int main() {

	auto start = std::chrono::high_resolution_clock::now();

	std::ifstream  plik;
	plik.open("day12_input.txt", std::ios::in);
	std::string temp;
	unsigned int answer{};
	std::stack <point> mainStack;
	
	if (plik.is_open()) {
		std::cout << "File opened\n";

		std::vector<std::vector<char>> v;
		std::vector<char> vtemp;
		int sx{}, sy{}, ex{}, ey{};
		int j{};
		
		while (getline(plik, temp)) {
			
			for(int i{}; i<temp.length(); i++){
				if(temp[i]=='S'){
					sx=i;
					sy=j;
				}
				if(temp[i]=='E'){
					ex=i;
					ey=j;
				}				
				vtemp.push_back(temp[i]);	
							
			}
			
			j++;
			v.push_back(vtemp);
			vtemp.clear();	
		}		
		plik.close();
		
		mainStack.push(point(sx,sy));
		if(sx-1>0 && v[sy][sx-1]<2)mainStack.top().connections.push('L');
		//if(sx+1<v[0].size() && v[sy][sx+1]<2)mainStack.top().connections.push('R');
		//if(sy-1>0 && v[sy-1][sx]<2)mainStack.top().connections.push('U');
		//if(sy+1<v.size() && v[sy][sx-1]<2)mainStack.top().connections.push('D');
		for(int i{}; i<temp.length(); i++){
		for(int i{}; i<temp.length(); i++){
		
		}
		}
		

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
