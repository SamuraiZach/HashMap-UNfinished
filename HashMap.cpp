

#include "hashMap.hpp"
#include "hashNode.hpp"
#include <iostream>
#include <math.h>
using namespace std;

hashMap::hashMap(bool hash1, bool coll1) {
	hashfn = hash1;
	collfn = coll1;
	numKeys = 0;
	collisions = 0;
	hashcoll = 0;
	mapSize = 13; //primes end in 1,3,7, or a 9 (1009) (83) (13)
	map = new hashNode*[mapSize];
	for(int i = 0; i<mapSize;i++){
		map[i] = NULL;
	}
	first = "";
}
void hashMap::addKeyValue(string k, string v) { // yet everywhere else is ok (k is the key and v is the value at k) k is the key like "Cat" and the v is put into the array of node and increase the count of njumkeys
	int x = getIndex(k);
	//cout << "back in hash" << endl;
	if(x == 0){
		first = k;
		cout<<"FIRST = "<<first<<endl;
	}
	if(map[x] == NULL){
		map[x] = new hashNode(k,v);
		numKeys += 1;
	}else if(map[x]->keyword == k){
		map[x]->addValue(v);
	}
	//first = map[0]->keyword;
	//cout<<"MAP SIZE = "<<mapSize<<endl;
	//cout<<"Index = "<<x<<endl;
}
int hashMap::getIndex(string k) { // cannot loop check boolean]
	//cout<<"getting index"<<endl;
	int x = numKeys;
	int y = mapSize *(0.7);
	//cout<<"threshhold"<<y<<endl;
	int indexReturn = 0;
	if(x >= y){
		cout<<"rehash?"<<endl;
		reHash();
	}
	if(hashfn == true){
		indexReturn = calcHash1(k);
		//cout << "here" << endl;
		if(map[indexReturn] != NULL && map[indexReturn]->keyword != k){
			//cout<<"print"<<endl;
			hashcoll += 1;
			if(collfn == true){
				indexReturn = coll1(indexReturn, 0, k);
			}else if(collfn == false){
				indexReturn = coll2(indexReturn, 0, k);
			}
		}
	}else if(hashfn == false){
		indexReturn = calcHash2(k);
		if(map[indexReturn] != NULL && map[indexReturn]->keyword != k){
			hashcoll +=1;
			if(collfn == true){
				indexReturn = coll1(indexReturn, 0, k);
			}else if(collfn == false){
				indexReturn = coll2(indexReturn, 0, k);
			}
		}
	}
	//cout<<"INDEX RETURN = "<<indexReturn<<endl;
	return indexReturn;
}

int hashMap::calcHash2(string k){
	int len = k.length();
	int returnValue = 0;
	for(int i = 0; i<len; i++){
		returnValue += (((i*11)+(int)k[i])%mapSize);
	}
	returnValue = returnValue%mapSize;
	return returnValue;
}
int hashMap::calcHash1(string k){
	int len = k.length();
	int returnValue = 0;
	for(int i = 0; i<len; i++){
		returnValue += ((27^(i)) + (int)k[i]);
	}
	returnValue = returnValue%mapSize;
	//cout<<"CalcHash1 Return = "<<returnValue<<endl;
	return returnValue;
}
void hashMap::getClosestPrime() {
	//cout<<"getclosestactivated"<<endl;
	bool check = true;
	int x = mapSize*2;
	while (check){
		if(x%10 == 1 || x%10 == 3 || x%10 == 7 || x%10 == 9){
			if((x%2 != 0) && (x%3 != 0) && (x%4 != 0) && (x%5 != 0) && (x%6 != 0) && (x%7 != 0) && (x%8 != 0) && (x%9 != 0)){
				check = false;
			}else{
				x -= 1;
			}
		}else{
			x -= 1;
		}
	}
	mapSize = x;
}
void hashMap::reHash() {
	int prioSize = mapSize;
	//cout<<"Prio mapsize = "<<prioSize<<endl;
	//cout<<"rehash started"<<endl;
	getClosestPrime();
	//cout<<"MapSize = "<<mapSize<<endl;
	hashNode **temp = new hashNode*[mapSize];
	for(int i = 0; i<prioSize; i++){
		temp[i] = map[i];
	}
	//getClosestPrime();
	map = temp;
}
int hashMap::coll1(int h, int i, string k) { //ask the difference between h and i (recursive if area is full) THE REHASH CREATES A PROBLEM SINCE 46 IS TECH NULL BUT NOT PRIME
	//cout<<"coll1"<<endl;
	int valueFromHash = h;
	int insertionAttempt = i;
	int finalIndex = 0;
	int returnIndex = 0;
	int stringVal = 0;
	int keyLength = k.length();
	//function
	returnIndex = valueFromHash;
	for(int i = 0; i < keyLength; i++){
		stringVal += (int)k[i];
	}
	returnIndex += insertionAttempt * (insertionAttempt+(stringVal%mapSize));
	//cout<<"Return Index="<<returnIndex<<endl;
	//cout<<"MAP SIZE = "<<mapSize<<endl;
	//cout<<"function end"<<endl;
	//function
	if(returnIndex > mapSize){
		//cout<<"greater than"<<endl;
		collisions += 1;
		returnIndex = returnIndex%mapSize;
	}
	if((map[returnIndex] == NULL || map[returnIndex]->keyword == k)){
		//cout << "firdt if" << endl;
		finalIndex = returnIndex;
		return finalIndex;
		//cout<<"returning"<<endl;
	}else{
		//cout<<"probing"<<endl;
		collisions +=1;
		finalIndex = (coll1(valueFromHash,insertionAttempt+1,k));
	}
	//cout<<"Coll1 Return = "<<finalIndex<<endl;
	return finalIndex;
}
int hashMap::coll2(int h, int i, string k) { //ask where to input the h and i
	int valueFromHash = h;
	int insertionAttempt = i;
	int finalIndex = 0;
	int returnIndex = 0;
	//function
	returnIndex = h + i;
	//function
	if(returnIndex > mapSize){
		collisions += 1;
		returnIndex = returnIndex%mapSize;
	}
	if(map[returnIndex] == NULL || map[returnIndex]->keyword == k){
		finalIndex = returnIndex;
	}else{
		collisions +=1;
		finalIndex = (coll1(valueFromHash,insertionAttempt+1,k));
	}
	return finalIndex;
}

void hashMap::printMap() {
	cout << "In printMap()" << endl;
	for (int i = 0; i < mapSize; i++) {
		//cout << "In loop" << endl;
		if (map[i] != NULL) {
			cout << map[i]->keyword << ": ";
			for (int j = 0; j < map[i]->currSize;j++) {
				cout << map[i]->values[j] << ", ";
			}
			cout << endl;
		}
	}
}


