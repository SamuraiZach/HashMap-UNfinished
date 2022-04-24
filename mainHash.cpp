#include <iostream>
#include "makeSeuss.hpp"
#include <time.h>
#include <stdlib.h>

//can only work at least one voice at a time and goes through the whole list yet the output is short?
using namespace std;
int main() {
	srand(time(NULL));
	cout << "~START~" << endl;
	makeSeuss voice1("DrSeuss.txt","Seussout1.txt",true,true);
	cout<<"MAKE VOICE 1"<<endl;
	//makeSeuss voice2("DrSeuss.txt","Seussout2.txt",false,true);
	//cout<<"MAKE VOICE 2"<<endl;
	//makeSeuss voice3("DrSeuss.txt","Seussout3.txt",true,false);
	//cout<<"MAKE VOICE 3"<<endl;
	//makeSeuss voice4("DrSeuss.txt","Seussout4.txt",false,false);
	//cout<<"MAKE VOICE 4"<<endl;
////OR
	//makeSeuss voice5("GEChap1a.txt","GEout1.txt",true,true);
//	makeSeuss voice6("GEChap1a.txt","GEout2.txt",false,true);
//	makeSeuss voice7("GEChap1a.txt","GEout3.txt",true,false);
//	makeSeuss voice8("GEChap1a.txt","GEout4.txt",false,false);
	cout<<"~END~"<<endl;
	return 0;
}
