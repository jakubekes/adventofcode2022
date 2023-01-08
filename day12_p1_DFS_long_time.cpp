#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stack>
#include <chrono>
#include <algorithm>

struct point{
	
	point(int y, int x, int val):y(y),x(x),val(val){}
	
	int y;
	int x;
	char val{};
	std::stack <point*> connections;
	bool used{};
};

int main() {

	auto start = std::chrono::high_resolution_clock::now();

	std::ifstream  plik;
	plik.open("day12_input.txt", std::ios::in);
	std::string temp;
	unsigned int answer{};
	std::stack <point*> mainStack;
	
	if (plik.is_open()) {
		std::cout << "File opened\n";

		std::vector<std::vector<point*>> v;
		std::vector<point*> vtemp;
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
					vtemp.push_back(new point(j,i,'b'));
					continue;
				}							
				vtemp.push_back(new point(j,i,temp[i]));	
							
			}
			
			j++;
			v.push_back(vtemp);
			vtemp.clear();	
		}		
		plik.close();
		
		mainStack.push(v[sy][sx]);
		v[sy][sx]->used=true;
		
		if(sx-1>=0 && v[sy][sx-1]->val-97<2) mainStack.top()->connections.push(v[sy][sx-1]);
		if(sx+1<v[0].size() && v[sy][sx+1]->val-97<2) mainStack.top()->connections.push(v[sy][sx+1]);
		if(sy-1>=0 && v[sy-1][sx]->val-97<2) mainStack.top()->connections.push(v[sy-1][sx]);
		if(sy+1<v.size() && v[sy+1][sx]->val-97<2) mainStack.top()->connections.push(v[sy+1][sx]);
		
		int steps{};
		std::vector<int> stepsv;
		bool returned{};
		while(!mainStack.empty()){
			//std::cout<<mainStack.top()->val<<" ";
			//if (mainStack.top()->x==ex && mainStack.top()->y==ey){
			if (mainStack.top()->x==ex && mainStack.top()->y==ey){
				//std::cout<<"IF1***: "<<mainStack.top()->y<<" "<<mainStack.top()->x<<" steps:"<<steps<<"\n";
				stepsv.push_back(steps);
				steps--;
				mainStack.top()->used=false;
				mainStack.pop();
				returned=true;
				//std::cout<<"IF1***: "<<mainStack.top()->y<<" "<<mainStack.top()->x<<" steps:"<<steps<<"\n";
			} else if(!mainStack.top()->connections.empty()){
				//std::cout<<"IF2: "<<mainStack.top()->y<<" "<<mainStack.top()->x<<"\n";
				point* p = mainStack.top();
				mainStack.push(p->connections.top());
				p->connections.top()->used=true;
				p->connections.pop();
				steps++;
				returned = false;
			} else if (returned==false) {
				//std::cout<<"IF3: "<<mainStack.top()->y<<" "<<mainStack.top()->x<<"\n";

				sx = mainStack.top()->x;
				sy = mainStack.top()->y;
				//std::cout<<"Poz x: "<<sx<<"\n";
				if(sx-1>=0 && v[sy][sx-1]->used==false && v[sy][sx-1]->val-v[sy][sx]->val<2) {
				//std::cout<<"IF3 1\n";
					mainStack.top()->connections.push(v[sy][sx-1]);
				}
				if(sx+1<v[0].size() && v[sy][sx+1]->used==false && v[sy][sx+1]->val-v[sy][sx]->val<2) {
				//std::cout<<"IF3 2\n";
					mainStack.top()->connections.push(v[sy][sx+1]);
				}
				if(sy-1>=0 && v[sy-1][sx]->used==false && v[sy-1][sx]->val-v[sy][sx]->val<2) {
				//std::cout<<"IF3 3\n";
					mainStack.top()->connections.push(v[sy-1][sx]);
				}
				
				if(sy+1<v.size() && v[sy+1][sx]->used==false && v[sy+1][sx]->val-v[sy][sx]->val<2) {
				//std::cout<<"IF3 4\n";
					mainStack.top()->connections.push(v[sy+1][sx]);
				}
						
				if(mainStack.top()->y==3 && mainStack.top()->x==7){
				std::cout<<"TEST VAL::"<<sy<<" "<<sx<<" "<<v[sy-1][sx]->val<<"\n";	
				}
						
				if(mainStack.top()->connections.empty()){ //slepy zaulek
					//std::cout<<"IF3: slepyzaulek sy:"<<sy<<" sx:"<<sx<<" val:"<<v[sy][sx]->val<<"\n";	
					steps--;
					mainStack.top()->used=false;
					mainStack.pop();
					returned=true;
				}
				
			} else if (returned==true) {
				//std::cout<<"IF4: "<<mainStack.top()->y<<" "<<mainStack.top()->x<<" RETURN\n";	
				steps--;
				mainStack.top()->used=false;
				mainStack.pop();
				returned=true;
			} 
			
			
		}
		
		std::sort(stepsv.begin(),stepsv.end());

		for(int i{}; i<stepsv.size(); i++){
			//std::cout << "V: " << stepsv[i] << ", ";		
		}

		std::cout << "\nAnswer: " << stepsv[0] << "\n";

		auto finish = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = finish - start;
		printf("Elapsed time: %f\n", elapsed.count());

	}
	else {

		std::cout << "Nie otwarto pliku";

	}

	plik.close();

}
