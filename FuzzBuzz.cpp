#include "FuzzBuzz.h"
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>

#include <iostream>

/* Helper Functions */
void getWords(std::vector<std::string> &words, std::string str);
bool isBuzzword(std::string word);

int FuzzBuzz::score(std::string input, int str) {
	return	scoreBuzzword(input, str) +
			scoreStandard(input, str) +
			scoreBookend(input, str) +
			scoreOrder(input, str);
}

int FuzzBuzz::scoreBuzzword(std::string input, int str) {
	double percentage;
	std::vector<std::string> inputWords, checkWords;
	int matches = 0, possibleMatches = 0;

	getWords(inputWords, input);
	getWords(checkWords, libraryStrings[str]);

	/*for(int i = 0; i < words.size(); i++) { // DEBUG
		std::cout << "word: " << words[i] << std::endl;
	}*/

	for(int i = 0; i < checkWords.size(); i++) {
		if(isBuzzword(checkWords[i])) {
			possibleMatches++;
			for(int j = 0; j < inputWords.size(); j++) {
				if("*" + inputWords[j] == checkWords[i]) {
					matches++;
					break;
				}
			}
		}
	}

	percentage = (double)matches / (double)possibleMatches;

	std::cout << "Matches: " << matches << "\nPossible Matches: " << possibleMatches << "\nPercentage: " << percentage << "\nScore: " << percentage * DEFAULT_BUZZWORD_WEIGHT << std::endl; // DEBUG

	return (int)(percentage * DEFAULT_BUZZWORD_WEIGHT);
}

/* Snagged this code from Zunino here: http://stackoverflow.com/questions/236129/how-to-split-a-string-in-c */
void getWords(std::vector<std::string> &words, std::string str) {
	std::istringstream iss(str);
	copy(std::istream_iterator<std::string>(iss),
         std::istream_iterator<std::string>(),
         std::back_inserter<std::vector<std::string> >(words));
}

bool isBuzzword(std::string word) {
	if(word[0] == '*')
		return true;
	else
		return false;
}

int FuzzBuzz::scoreStandard(std::string input, int str) {
	double percentage;
	return (int)(percentage * DEFAULT_STANDARD_WEIGHT);
}

int FuzzBuzz::scoreBookend(std::string input, int str) {
	double percentage;
	return (int)(percentage * DEFAULT_BOOKEND_WEIGHT);
}

int FuzzBuzz::scoreOrder(std::string input, int str) {
	double percentage;
	return (int)(percentage * DEFAULT_ORDER_WEIGHT);
}

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
	loadFile.clear();
	loadFile.seekg(0);
	for(i = 0; i < numEntries; i++) {
		getline(loadFile, readIn, '\n');
		libraryStrings[i] = readIn;
	}
	/*
	std::cout << libraryStrings.size() << " entries." << std::endl; // DEBUG

	for(i = 0; i < libraryStrings.size(); i++)	// DEBUG
		std::cout << "\"" << libraryStrings[i] << "\"" << std::endl;
	*/

	score("that is a buzzword", 0);
	score("single buzzwords", 5);

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