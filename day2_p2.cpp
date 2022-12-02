#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

int main() {

/*
 * A 65 ROCK 1 points
 * B 66 PAPER 2 points
 * C 67 SCISSORS 3 points
X loose
Y draw
Z win
 * 
 * */
	std::ifstream  plik;
	plik.open("day2_input.txt", std::ios::in);
	std::string temp;
	unsigned long int answer{};
	
	if (plik.is_open()) {

		while(getline(plik,temp)){
		
		switch(temp[2]){
			case 'X':
				if(temp[0]=='A'){
					answer+=3; //scissors +3
				} else if (temp[0]=='B'){
					answer+=1;
				} else if (temp[0]=='C'){
					answer+=2;
				}
			break;
			case 'Y':
				if(temp[0]=='A'){
					answer+=1; 
				} else if (temp[0]=='B'){
					answer+=2;
				} else if (temp[0]=='C'){
					answer+=3;
				}
			answer+=3;	
			break;		
			case 'Z':
				if(temp[0]=='A'){
					answer+=2; 
				} else if (temp[0]=='B'){
					answer+=3;
				} else if (temp[0]=='C'){
					answer+=1;
				}
			answer+=6;	
			break;			
			
			
		}
			
		}
		std::cout<<"Answer: "<<answer<<"\n";
		
	}
	else {
		
		std::cout << "Nie otwarto pliku";
		
	}

	plik.close();


}
