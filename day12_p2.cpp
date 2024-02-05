#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>
#include <chrono>

struct point{
	
	point(int y, int x, int val):y(y),x(x),val(val){}
	
	int y;
	int x;
	char val{};
	int stepVal{};
	bool used{};
};

void clearQ( std::queue<point*> &q )
{
   std::queue<point*> empty;
   std::swap( q, empty );
}

int main() {

	auto start = std::chrono::high_resolution_clock::now();

	std::ifstream  plik;
	plik.open("day12_input.txt");
	std::string temp;
	unsigned int answer{420};
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
				if(temp[i]=='S' || temp[i] == 'a'){
					sx=i;
					sy=j;
					vtemp.push_back(new point(j,i,'a'));	
					aPoints.push_back(vtemp[vtemp.size()-1]);
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
	
		for (size_t i{}; i<aPoints.size(); i++){
			
			point* p;
			mainQueue.push(aPoints[i]);
			aPoints[i]->used=true;
			aPoints[i]->stepVal=0;
			bool reachedE{};

			while(!mainQueue.empty()){
							
				p = mainQueue.front();
				vanswer.push_back(p);
				if(p->x==ex && p->y==ey){
					reachedE=true;
					break;
				}
				
				mainQueue.pop();
				sx = p->x;
				sy = p->y;
				
				if(sx-1>=0 && v[sy][sx-1]->used==false && v[sy][sx-1]->val-v[sy][sx]->val<2) {
					mainQueue.push(v[sy][sx-1]);
					mainQueue.back()->used=true;
					mainQueue.back()->stepVal=v[sy][sx]->stepVal+1;
				}
				if(sx+1<v[0].size() && v[sy][sx+1]->used==false && v[sy][sx+1]->val-v[sy][sx]->val<2) {
					mainQueue.push(v[sy][sx+1]);
					mainQueue.back()->used=true;
					mainQueue.back()->stepVal=v[sy][sx]->stepVal+1;
				}
				if(sy-1>=0 && v[sy-1][sx]->used==false && v[sy-1][sx]->val-v[sy][sx]->val<2) {
					mainQueue.push(v[sy-1][sx]);
					mainQueue.back()->used=true;
					mainQueue.back()->stepVal=v[sy][sx]->stepVal+1;
				}		
				if(sy+1<v.size() && v[sy+1][sx]->used==false && v[sy+1][sx]->val-v[sy][sx]->val<2) {
					mainQueue.push(v[sy+1][sx]);
					mainQueue.back()->used=true;
					mainQueue.back()->stepVal=v[sy][sx]->stepVal+1;
				}						
			}
			
			for(int i{}; i<vanswer.size(); i++){
				vanswer[i]->used=false;
			}
			
			if (reachedE && vanswer[vanswer.size()-1]->stepVal<answer) answer=vanswer[vanswer.size()-1]->stepVal;
			
			vanswer.clear();
			clearQ(mainQueue);
		}
		
		std::cout<<"Answer: "<<answer<<"\n";
		
		auto finish = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = finish - start;
		printf("Elapsed time: %f\n", elapsed.count());
	}
	else {
		
		std::cout << "File not opened, quitting.";
	}

	plik.close();
}