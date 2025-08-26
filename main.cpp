#include <iostream>
#include "parser.h"

int main(int argc, char** argv) {
	auto [gif, celestial, orbit] { Parser(argc, argv) };
	gif.Print();
	celestial.Print();
	auto bitmap{ celestial.GetBitMap(gif) };
}
