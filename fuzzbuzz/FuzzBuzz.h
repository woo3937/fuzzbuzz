#ifndef FUZZBUZZ_
#define FUZZBUZZ_

#include <string>

class FuzzBuzz {
public:
	FuzzBuzz();
	int load(std::string filename);
	void config();
	void add(std::string str);
	void remove(std::string str);
	std::string search(std::string input);
	int score(std::string input);
};

#endif // FUZZBUZZ_