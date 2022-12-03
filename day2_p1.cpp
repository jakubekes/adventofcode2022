#include <iostream>
#include <string>
#include <fstream>
#include <vector>

int main() {

/*
 * A 65 ROCK 1 points
 * B 66 PAPER 2 points
 * C 67 SCISSORS 3 points
 * X 88 ROCK 23 remis, 22 loose, 21 win
 * Y 89 PAPER 23 remis, 22 loose, 24 win
 * Z 90 SCISSORS 23 remis, 24 win, 25 loose
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
					answer+=3;
				} else if (temp[0]=='C'){
					answer+=6;
				}
			answer+=1;	
			break;
			case 'Y':
				if(temp[0]=='A'){
					answer+=6;
				} else if (temp[0]=='B'){
					answer+=3;
				}
			answer+=2;	
			break;		
			case 'Z':
				if(temp[0]=='B'){
					answer+=6;
				} else if (temp[0]=='C'){
					answer+=3;
				}
			answer+=3;	
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
