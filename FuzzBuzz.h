#ifndef FUZZBUZZ_
#define FUZZBUZZ_

#include <string>
#include <vector>

/* Default Scoring Weights - These should add up to 100. */
#define DEFAULT_BUZZWORD_WEIGHT 20		// total possible points earned for buzzword presence
#define DEFAULT_STANDARD_WEIGHT 60		// total possible points earned for word presence
#define DEFAULT_BOOKEND_WEIGHT 5		// total possible points earned for  leading and trailing words
#define DEFAULT_ORDER_WEIGHT 15			// total possible points earned for word ordering

class FuzzPair {
	std::string str;
	int score;
};

class FuzzBuzz {
public:
	FuzzBuzz();
	int load(std::string filename);
	void config(int buzzwordW, int standardW, int bookendW, int orderW);
	void add(std::string str);
	void remove(std::string str);
	std::string best(std::string input);
	std::string search(std::string input);
private:
	std::vector<std::string> libraryStrings;
	int buzzwordWeight;
	int standardWeight;
	int bookendWeight;
	int orderWeight;
	int score(std::string input, int str);
	int scoreBuzzword(std::string input, int str);
	int scoreStandard(std::string input, int str);
	int scoreBookend(std::string input, int str);
	int scoreOrder(std::string input, int str);
};

#endif // FUZZBUZZ_