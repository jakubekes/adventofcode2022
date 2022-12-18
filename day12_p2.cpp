#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>
#include <chrono>
#include <algorithm>

struct point{
	
	point(int y, int x, int val):y(y),x(x),val(val){}
	
	int y;
	int x;
	char val{};
	int stepVal{};
	//std::stack <point*> connections;
	bool used{};
};

int main() {

	auto start = std::chrono::high_resolution_clock::now();

	std::ifstream  plik;
	plik.open("day12_input.txt", std::ios::in);
	std::string temp;
	unsigned int answer{};
	std::queue <point*> mainQueue;
	std::vector <point*> vanswer;
	std::vector <point*> aPoints;
	
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
					vtemp.push_back(new point(j,i,'a'));	
					continue;
				}	
				
				if(temp[i]=='E'){
					ex=i;
					ey=j;
					vtemp.push_back(new point(j,i,'z'));
					continue;
				}							
				vtemp.push_back(new point(j,i,temp[i]));	
							
			}
			
			j++;
			v.push_back(vtemp);
			vtemp.clear();	
		}		
		plik.close();
		
		mainQueue.push(v[sy][sx]);
		v[sy][sx]->used=true;
		v[sy][sx]->stepVal=0;
		
		//if(sx-1>=0 && v[sy][sx-1]->val-97<2) mainQueue.top()->connections.push(v[sy][sx-1]);
		//if(sx+1<v[0].size() && v[sy][sx+1]->val-97<2) mainQueue.top()->connections.push(v[sy][sx+1]);
		//if(sy-1>=0 && v[sy-1][sx]->val-97<2) mainQueue.top()->connections.push(v[sy-1][sx]);
		//if(sy+1<v.size() && v[sy+1][sx]->val-97<2) mainQueue.top()->connections.push(v[sy+1][sx]);
		
		long int steps{};
		std::vector<long int> stepsv;
		bool returned{};
		point* p;

		while(!mainQueue.empty()){
						
			p = mainQueue.front();
			std::cout<<p->val<<" | y: "<<p->y<<" x: "<<p->x<<"\n";
			vanswer.push_back(p);
			if(p->x==ex && p->y==ey)break;
			
			mainQueue.pop();
			
			sx = p->x;
			sy = p->y;
		
			
			if(sx-1>=0 && v[sy][sx-1]->used==false && v[sy][sx-1]->val-v[sy][sx]->val<2) {
				//std::cout<<"IF1\n";
				mainQueue.push(v[sy][sx-1]);
				mainQueue.back()->used=true;
				mainQueue.back()->stepVal=v[sy][sx]->stepVal+1;
			}
			if(sx+1<v[0].size() && v[sy][sx+1]->used==false && v[sy][sx+1]->val-v[sy][sx]->val<2) {
				//std::cout<<"IF2\n";
				mainQueue.push(v[sy][sx+1]);
				mainQueue.back()->used=true;
				mainQueue.back()->stepVal=v[sy][sx]->stepVal+1;
			}
			if(sy-1>=0 && v[sy-1][sx]->used==false && v[sy-1][sx]->val-v[sy][sx]->val<2) {
				//std::cout<<"IF3\n";
				mainQueue.push(v[sy-1][sx]);
				mainQueue.back()->used=true;
				mainQueue.back()->stepVal=v[sy][sx]->stepVal+1;
			}		
			if(sy+1<v.size() && v[sy+1][sx]->used==false && v[sy+1][sx]->val-v[sy][sx]->val<2) {
				//std::cout<<"IF4\n";
				mainQueue.push(v[sy+1][sx]);
				mainQueue.back()->used=true;
				mainQueue.back()->stepVal=v[sy][sx]->stepVal+1;
			}
						
			
		}
		
		for(int i{}; i<vanswer.size()-1; i++){
			if (vanswer[i]->stepVal!=vanswer[i+1]->stepVal)answer+=vanswer[i]->stepVal;
		}

		std::cout << "Answer: " << vanswer[vanswer.size()-1]->stepVal << "\n";

		auto finish = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = finish - start;
		printf("Elapsed time: %f\n", elapsed.count());

	}
	else {

		std::cout << "Nie otwarto pliku";

	}

	plik.close();

}
