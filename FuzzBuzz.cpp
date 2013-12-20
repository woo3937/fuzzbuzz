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
std::string removeAsterisks(std::string input);

std::string FuzzBuzz::best(std::string input) {
	std::string bestString = "";
	int bestScore = 0, tempScore = 0;

	for(int i = 0; i < libraryStrings.size(); i++) {
		tempScore = score(input, i);
		if(tempScore > bestScore) {
			bestScore = tempScore;
			bestString = libraryStrings[i];
		}
	}

	return removeAsterisks(bestString);
}

int FuzzBuzz::score(std::string input, int str) {
	/*std::cout << "Buzzword Score: " << scoreBuzzword(input, str) << std::endl;
	std::cout << "Standard Score: " << scoreStandard(input, str) << std::endl;
	std::cout << "Bookend Score: " << scoreBookend(input, str) << std::endl;
	std::cout << "Order Score: " << scoreOrder(input, str) << std::endl;*/
	return	scoreBuzzword(input, str) +
			scoreStandard(input, str) +
			scoreBookend(input, str) +
			scoreOrder(input, str);
}

int FuzzBuzz::scoreBuzzword(std::string input, int str) {
	double percentage = 0;
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

	if(possibleMatches > 0)
		percentage = (double)matches / (double)possibleMatches;

	//std::cout << "Buzzword Scoring\ninput: " << input << "\nlib: " << libraryStrings[str] << "\nMatches: " << matches << "\nPossible Matches: " << possibleMatches << "\nPercentage: " << percentage << "\nScore: " << percentage * DEFAULT_BUZZWORD_WEIGHT << "\n" << std::endl; // DEBUG

	return (int)(percentage * DEFAULT_BUZZWORD_WEIGHT);
}

int FuzzBuzz::scoreStandard(std::string input, int str) {
	double percentage = 1;
	std::vector<std::string> inputWords, checkWords;
	int matches = 0;

	getWords(inputWords, input);
	getWords(checkWords, libraryStrings[str]);

	/*for(int i = 0; i < words.size(); i++) { // DEBUG
		std::cout << "word: " << words[i] << std::endl;
	}*/

	for(int i = 0; i < checkWords.size(); i++) {
		for(int j = 0; j < inputWords.size(); j++) {
			if(isBuzzword(checkWords[i])) {
				if("*" + inputWords[j] == checkWords[i]) {
					matches++;
					break;
				}
			}
			else {
				if(inputWords[j] == checkWords[i]) {
					matches++;
					break;
				}
			}
		}
	}

	percentage = (double)matches / (double)checkWords.size();

	//std::cout << "Standard Scoring\ninput: " << input << "\nlib: " << libraryStrings[str] << "\nMatches: " << matches << "\nPossible Matches: " << checkWords.size() << "\nPercentage: " << percentage << "\nScore: " << percentage * DEFAULT_STANDARD_WEIGHT << "\n" << std::endl; // DEBUG

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
	libraryStrings.resize(numEntries);
	loadFile.clear();
	loadFile.seekg(0);
	for(i = 0; i < numEntries; i++) {
		getline(loadFile, readIn, '\n');
		libraryStrings[i] = readIn;
	}
	
	
	std::cout << libraryStrings.size() << " entries." << std::endl; // DEBUG
	
	for(i = 0; i < libraryStrings.size(); i++)	// DEBUG
		std::cout << "\"" << libraryStrings[i] << "\"" << std::endl;

	//score("that is a buzzword", 0);
	//score("single buzzwords", 5);

	return numEntries;
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

std::string removeAsterisks(std::string input) {
	int limit = input.size();
	for(int i = 0; i < limit; i++) {
		if(input[i] == '*') {
			input.erase(input.begin()+i);
			limit--;
		}
	}
	return input;
}