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

hashTable insertDict(string filename, hashTable hash){

	ifstream file;
    file.open(filename);
    if (!file.is_open()){
    	cout<<"ERROR"<<endl;
    } 

    string word;
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    while (file >> word){
        hash.insert(word);
    }
 
    return hash;

}

string processWord(string word, hashTable dict, int lineNum){
	string out;

	stringstream buffer;

	transform(word.begin(), word.end(), word.begin(), ::tolower);


	if(word.length()>20){
		buffer << "Long word at line "<<lineNum<<", starts: "<<word.substr(0,20);
		out = buffer.str();
		return out;
	}
	else if(!dict.contains(word)){
		buffer << "Unknown word at line "<<lineNum<<": "<<word;
		out = buffer.str();
		return out;
	}
	else{
		out = "empty";
		return out;
	}

}

void writeFile(string ans, string filename){

  	ofstream output(filename.c_str());
  	if (!output) {
    	cerr << "Error: could not open " << filename << endl;
    	exit(1);
  	}
  	
  	output << ans << endl;

  	output.close();

}



void spellcheck(string infile, string outfile, hashTable dict){ 

	ofstream output(outfile.c_str());
  	if (!output) {
    	cerr << "Error: could not open " << outfile << endl;
    	exit(1);
  	}

	string ans;
	string word;
	word.clear();
    ifstream fin;
	fin.open(infile, ios::in);

	char c;
	int number_of_lines = 1;
	int count = 0;
	bool state = false;

	while (!fin.eof() ) {

		fin.get(c);

		while(((c <= 'z' && c >= 'a') || (c <= 'Z' && c >= 'A') || c == '-' || c == '\'' || (c >= '0' && c <= '9')) && !fin.eof()){
			word = word + c;
			fin.get(c);
			state = true;
		}

		if(((word[0] <= 'z' && word[0] >= 'a') || (word[0] <= 'Z' && word[0] >= 'A') || word[0] == '-' || word[0] == '\'' || (word[0] >= '0' && word[0] <= '9'))){
			
			ans = processWord(word, dict, number_of_lines);

		}

		if(state){ // I needed this variable "state" while debugging, couldnt exactly figure out why but it works....
			if(ans != "empty"){ // It turned out my function wasnt looping through the second while loops sometimes, so I set a boolean to be...
				//cout<<ans<<endl; // True only when the while loop is executed and reset to false at the end of every iteration of the main while loop
				output << ans << endl;
			}

		}
		
		word.clear();

		if (c == '\n'){
				++number_of_lines;
		}
		state = false;

	}
	output.close();

}



int main(){
	string dictionary;
	cout<<"Enter name of dictionary: ";
	cin>>dictionary;

	hashTable dict;

	clock_t t1 = clock();
	dict = insertDict(dictionary,dict);
  	clock_t t2 = clock();
  	double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;
  	cout<<"Total time (in seconds) to load dictionary: "<<timeDiff<<endl;

  	string infile;
  	cout<<"Enter name of input file: ";
  	cin>>infile;

  	string outfile;
  	cout<<"Enter name of output file: ";
  	cin>>outfile;


  	clock_t t11 = clock();

  	spellcheck(infile, outfile, dict);

  	clock_t t21 = clock();
  	double timeDiff1 = ((double) (t21 - t11)) / CLOCKS_PER_SEC;
  	cout<<"Total time (in seconds) to check document: "<<timeDiff1<<endl;



	return 0;
}