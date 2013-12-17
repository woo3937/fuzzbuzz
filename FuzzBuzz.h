#ifndef FUZZBUZZ_
#define FUZZBUZZ_

#include <string>
#include <vector>

/* Default Scoring Weights - These should add up to 100. */
#define DEFAULT_BUZZWORD_WEIGHT 50		// total possible points earned for buzzword presence
#define DEFAULT_STANDARD_WEIGHT 30		// total possible points earned for non-buzzword (and non-bookend) presence
#define DEFAULT_BOOKEND_WEIGHT 50		// total possible points earned for non-keyword leading and trailing words
#define DEFAULT_ORDER_WEIGHT 15			// total possible points earned for word ordering

#define EXTRA_ENTRY_BUFFER 10			// extra space in libraryStrings vector to minimize resizing

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
	std::string search(std::string input);
	int score(std::string input);
private:
	std::vector<std::string> libraryStrings;
	int buzzwordWeight;
	int standardWeight;
	int bookendWeight;
	int orderWeight;
};

#endif // FUZZBUZZ_