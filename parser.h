#include <tuple>
#include <limits>
#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <functional>
#include "bitmap.h"

constexpr double qDNAN{ std::numeric_limits<double>::quiet_NaN() };
using BitMap = bitmap::BitMap<bitmap::RGBA>;
struct Gif {
	unsigned border{ 5 };	// default size of border;
	unsigned delay{ 100 };	// delay between of frame
	double scale{ qDNAN };	// km in pixel
	Gif() = default;
	Gif(const Gif&) = default;
	Gif(const std::vector<std::string>& words, int& index);
	void Print();
};
struct Celestial {
	std::string name;
	double radius{ qDNAN };
	Celestial() = default;
	Celestial(const Celestial&) = default;
	Celestial(const std::vector<std::string>& words, int& index);
	BitMap GetBitMap(const Gif& gif);
	void Print();
};
struct Orbit {
	float radius{ std::numeric_limits<float>::quiet_NaN() };
	float apocenter{ std::numeric_limits<float>::quiet_NaN() };
	float pericenter{ std::numeric_limits<float>::quiet_NaN() };
	Orbit() = default;
	Orbit(const Orbit&) = default;
	Orbit(const std::vector<std::string>& words, int& index);
};
const std::tuple<Gif, Celestial, Orbit> Parser(int argc, char** argv);
