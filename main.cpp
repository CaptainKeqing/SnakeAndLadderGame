#include <random>
#include <ctime>

void setupRandomiser(){
	// setup randomiser
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	std::rand();	// throw first value away.
}
int getRandomNumber(int min, int max)
{
	static constexpr double fraction{ 1.0 / (RAND_MAX + 1.0) };  // static used for efficiency, so we only calculate this value once
	// evenly distribute the random number across our range
	return min + static_cast<int>((max - min + 1) * (std::rand() * fraction));
}
