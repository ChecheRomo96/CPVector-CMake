#include <iostream>
#include <CPVector.h>

int main()
{
    CPVector::vector<uint8_t> myVector1;
	myVector1.resize(100);
	
	for(uint16_t i = 0; i < myVector1.size(); i++)
	{
		myVector1[i] = rand();
		std::cout<<(unsigned int)myVector1[i];
		if(i < myVector1.size()-1){std::cout<<", ";}
		else{std::cout<<std::endl;}
	}

	myVector1.clear();

	CPVector::vector<uint16_t> myVector2;
	myVector2.resize(17);

	for(uint8_t i = 0; i < myVector2.size(); i++)
	{
		myVector2[i] = rand();
		std::cout <<(unsigned int)myVector2[i];
		if (i < myVector2.size() - 1) { std::cout << ", "; }
		else { std::cout << std::endl; }
	}

	myVector2.clear();

    return 0;
}