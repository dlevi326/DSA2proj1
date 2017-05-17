#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <iterator>
#include <ctime>
#include "hash.h"


using namespace std;


hashTable::hashTable(int size){

	capacity = getPrime(size); // Gets prime number greater than or equal to size
	filled = 0;
	data.resize(capacity); // Initializes the vector

	for(int i=0;i<capacity;i++){ // Initializes all members of hashItem
		data[i].key = "empty";
		data[i].isOccupied = false;
		data[i].isDeleted = false;
		data[i].pv = NULL;
		
	}
}

void hashTable::printHash(){ // Used for debugging

	for(int i=0;i<capacity;i++){
		cout<<data[i].key<<"--> ";
	}
	cout<<endl;

}


int hashTable::getPrime(int size){ // Obtains the prime number needed for capacity of hash table
	int prime = -1; // Returns -1 if position is not found

	int primes[] = {52709,86143,207443,507961,1008001,2008439}; // Not using vectors here because it is easier to write the data explicitly using arrays
	for(int i=0;i<6;i++){
		if(size<primes[i]){
			prime = primes[i];
			break;
		}
	}

	return prime;

}

int hashTable::insert(const string &key, void *pv){ // Check pointers

	while(filled>=capacity){
		if(rehash()==false){ // Memory allocation has failed
			return 2;
		}
		else{
			rehash(); // Rehashes hash table if it is not big enough
		}
	}

	int index = hash(key);

	while(data[index].isOccupied == true){
		if(data[index].key == key && data[index].isDeleted == false){
			return 1;
			break; // Key already exists in hashtable
		}
		index++;
		if(index>capacity){ // Loops the index back around
			index = 0;
		}
	}

	if(filled != capacity ){
		data[index].key = key;
		data[index].isOccupied = true;
		data[index].pv = pv;
		filled++;
		return 0; // Succesfully inserted
	}
	else{
		return 3; // None of these executed (used for debugging)
	}
}

bool hashTable::remove(const string &key){ // Removes key
	bool result = false;
	if(findPos(key) >= 0){
		int pos = findPos(key); // Re-Initializes members of hashItem
		data[pos].key = "empty";
		data[pos].isOccupied = false;
		data[pos].isDeleted = true;
		data[pos].pv = NULL;
		result = true;
	}
	return result;
}

int hashTable::setPointer(const string &key, void *pv){ // Check pointers

	int result = 1;
	if(findPos(key) >= 0){
		int pos = findPos(key); // Finds position of key
		data[pos].pv = pv;
		result = 0;
	}
	return result;

}

void* hashTable::getPointer(const string &key, bool *b){ // Check pointers
	if(b != NULL){ // If *b is included as a parameter
		*b = false;
	}

	void* result = NULL;
	if(findPos(key)>=0){
		result = data[findPos(key)].pv; // Obtains pointer at position of key
		if(b != NULL){
			*b = true;
		}
	}
	return result;

}


bool hashTable::contains(const string &key){

	bool result = false;
	if(findPos(key) >= 0){ // If the position of the key exists
		result = true;
	}
	return result;

}

int hashTable::findPos(const string &key){

	int result = -1; // -1 indicates it does not exist
	int index = hash(key);
	int count = 0;
	for(int i=0;i<capacity;i++){
		if(count == capacity){ // Looked through whole hash table and it doesnt exist
			break;
		}
		if(data[index].key == key && data[index].isDeleted == false){
			result = index;
		}
		if(index>capacity){
			index = 0;
		}
		index++;
		count++;
	}
	return result;

}

bool hashTable::rehash(){ // Makes hash table bigger if need be

	bool result = true; // Return true on success, false on failure
	if(getPrime(capacity+1) == -1){
		result = false; // Memory allocation has failed
	}
	else{
		int tempcap = capacity;
		capacity = getPrime(capacity+1);
		vector<hashItem> tempVect = data; // Creating temporary vector
		for(int i=0;i<tempcap;i++){
			data[i].isOccupied = false;
		}
		filled = 0;
		data.resize(capacity);

		for(int i = 0; i<tempVect.size(); i++){
      		if(tempVect[i].isOccupied && !tempVect[i].isDeleted){
        		insert(tempVect[i].key, tempVect[i].pv); // Re-Input
      		}
    	}

	}
	return result;
}



int hashTable::hash(const string &key){ // Provides unique id for a specified key

	int hash = 0;
	int len = key.size();
	int index;

	for(int i=0;i<len;i++){
		hash+=(int)key[i];
	}

	index = hash%capacity;

	return index;

}
