#include <iostream>
#include <string>
#include <fstream>
#include <vector>

int main() {

	std::ifstream  plik;
	plik.open("day2_input.txt");
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
		
		std::cout << "File not opened, quitting.";
	}

	plik.close();
}