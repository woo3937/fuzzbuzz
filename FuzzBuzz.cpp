#include "FuzzBuzz.h"
#include <string>
#include <fstream>
#include <vector>

#include <iostream>

FuzzBuzz::FuzzBuzz() {
	buzzwordWeight = DEFAULT_BUZZWORD_WEIGHT;
	standardWeight = DEFAULT_STANDARD_WEIGHT;
	bookendWeight  = DEFAULT_BOOKEND_WEIGHT;
	orderWeight    = DEFAULT_ORDER_WEIGHT;
}

int FuzzBuzz::load(std::string filename) {
	int numEntries = 0, i;
	std::string dummy, readIn;
	std::ifstream loadFile(filename.c_str());
	while(std::getline(loadFile, dummy))
		++numEntries;
	libraryStrings.resize(numEntries+EXTRA_ENTRY_BUFFER); // allow some extra space for added entries
	std::cout << libraryStrings.size() << " entries." << std::endl; // DEBUG
	for(i = 0; i < numEntries; i++) {
		getline(loadFile, readIn, '\n');
		libraryStrings[i] = dummy;
		std::cout << "entry: " << readIn << std::endl;
	} 
	for(i = 0; i < numEntries; i++)	// DEBUG
		std::cout << "\"" << libraryStrings[i] << "\"" << std::endl;
	return numEntries+EXTRA_ENTRY_BUFFER;
}

void FuzzBuzz::config(int buzzwordW, int standardW, int bookendW, int orderW) {
	buzzwordWeight = buzzwordW;
	standardWeight = standardW;
	bookendWeight  = bookendW;
	orderWeight    = orderW;
}

void FuzzBuzz::add(std::string str) {
	libraryStrings.push_back(str);
}

void FuzzBuzz::remove(std::string str) {
	//libraryStrings.remove(str);
}

std::string FuzzBuzz::search(std::string input) {

}

int FuzzBuzz::score(std::string input) {

}