

#include "hashMap.hpp"
#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;



hashNode::hashNode(string s){
	keyword = s;
	values = new string[100];
	valuesSize = 100;
	currSize = 0;
	srand(time(NULL));
}
hashNode::hashNode(){
	keyword = "";
	values = new string[100];
	valuesSize = 100;
	currSize = 0;
	srand(time(NULL));
}
hashNode::hashNode(string s, string v){
	keyword = s;
	values = new string[100];
	values[0] = v;
	valuesSize = 100;
	currSize = 1;
}
void hashNode::addValue(string v) {
	// adding a valu to the end of the value array associated 
	// with a key
	int count = 0;
	int traverse = 0;
	if(currSize >= valuesSize){
		dblArray();
	}
	while(count == 0){
		if(values[traverse] == ""){
			values[traverse] = v;
			count += 1;
		}else{
			traverse += 1;
		}
	}
	currSize += 1;

}
void hashNode::dblArray() {
	// when the value array gets full, you need to make a new 
	// array twice the size of the old one (just double, no 
	//going to next prime) and then copy over the old values 
	//to the new values, then de-allocate the old array.  
	//Again, just copying over, no hash functiosn involved 
	//here.
	string *temp = new string[(valuesSize*2)];
	for(int i = 0; i<valuesSize; i++){
		temp[i] = values[i];
	}
	valuesSize = (valuesSize *2);
	values = temp;
}

string hashNode::getRandValue() {
	//Every key has a values array - an array of words that 
	// follow that key in the text document.  You're going to 
	//randomly select one of those words and return it.  That 
	//will be the word that follows your key in your output 
	//function, and it will also be the next key.
	int max = valuesSize; // 0 to max inclusive
	bool c = true;
	string returnString;
	int attempts = 0;
	while(c == true){
		if(values[rand()%(max) + 1] != ""){
			returnString = values[rand()%(max)];
			c = false;
		}else if(attempts > valuesSize){
			returnString = "";
		}else{
			attempts += 1;
		}
	}
	return returnString;
}
