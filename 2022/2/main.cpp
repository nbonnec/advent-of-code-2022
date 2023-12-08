// Rock		A X 1
// Paper	B Y 2
// Scissor	C Z 3

// Lost 0
// Draw 3
// Won  6

#include <filesystem>
#include <fstream>
#include <iostream>
#include <source_location>

namespace fs = std::filesystem;

static constexpr char myRock = 'X';
static constexpr char myPaper = 'Y';
static constexpr char myScissor = 'Z';

static bool isRock(char c) {
	return c == 'A' || c == 'X';
}

static bool isPaper(char c) {
	return c == 'B' || c == 'Y';
}

static bool isScissor(char c) {
	return c == 'C' || c == 'Z';
}

static bool needToLose(char c) {
	return c == 'X';
}

static bool needToDraw(char c) {
	return c == 'Y';
}

static bool needToWin(char c) {
	return c == 'Z';
}

static int getValue(char c) {
	if (isRock(c)) {
		return 1;
	}
	if (isPaper(c)) {
		return 2;
	}
	// Scissors
	return 3;
}

static int getScore(char c1, char c2) {

	if (isRock(c1)) {
		if (isRock(c2)) {
			return 3;
		}
		if (isPaper(c2)) {
			return 6;
		}
		// Scissors
		return 0;
	}

	if (isPaper(c1)) {
		if (isRock(c2)) {
			return 0;
		}
		if (isPaper(c2)) {
			return 3;
		}
		// Scissors
		return 6;
	}

	// Scissors
	if (isRock(c2)) {
		return 6;
	}
	if (isPaper(c2)) {
		return 0;
	}
	return 3;
}

static char getHand(char c1, char c2) {
	if (isRock(c1)) {
		if (needToLose(c2)) {
			return myScissor;
		}
		if (needToDraw(c2)) {
			return myRock;
		}
		return myPaper;
	} else if (isPaper(c1)) {
		if (needToLose(c2)) {
			return myRock;
		}
		if (needToDraw(c2)) {
			return myPaper;
		}
		return myScissor;
	}
	// Scissors
	if (needToLose(c2)) {
		return myPaper;
	}
	if (needToDraw(c2)) {
		return myScissor;
	}
	return myRock;
}

int main() {
	const auto thisSourceLocation = std::source_location::current();
	const auto samplePath = fs::path{thisSourceLocation.file_name()}.parent_path() / "input.txt";

	{
		auto ifs = std::ifstream{samplePath, std::ios::in};

		int sum{};
		for (std::string line{}; std::getline(ifs, line);) {
			auto iss = std::istringstream{line};
			char one{};
			char two{};
			iss >> one >> two;
			sum += getValue(two) + getScore(one, two);
		}

		std::cout << "Part one\n";
		std::cout << sum << '\n';
	}

	{
		// X lose
		// Y draw
		// Z win
		auto ifs = std::ifstream{samplePath, std::ios::in};

		int sum{};
		for (std::string line{}; std::getline(ifs, line);) {
			auto iss = std::istringstream{line};
			char one{};
			char two{};
			iss >> one >> two;
			const auto hand = getHand(one, two);
			sum += getValue(hand) + getScore(one, hand);
		}

		std::cout << "Part two\n";
		std::cout << sum << '\n';
	}

	return 0;
}