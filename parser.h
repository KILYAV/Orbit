#include <tuple>
#include <string>
#include <vector>
#include <iostream>
#include <functional>
#include "bitmap.h"

using BitMap = bitmap::BitMap<bitmap::RGBA>;
struct Gif {
	unsigned border{ 5 };	// default size of border;
	unsigned delay{ 100 };	// delay between of frame
	unsigned scale{ 100 };	// km in pixel
	Gif() = default;
	Gif(const Gif&) = default;
	Gif(const std::vector<std::string>& words, int& index);
};
struct Celestial {
	std::string name{ "earth" };
	float radius = 6371.;
	Celestial() = default;
	Celestial(const Celestial&) = default;
	Celestial(const std::vector<std::string>& words, int& index);
	BitMap GetBitMap(const Gif& gif);
};
const std::tuple<Gif, Celestial> Parser(int argc, char** argv);
