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
	double focal{ qDNAN };
	double major{ qDNAN };
	double minor{ qDNAN };
	double radius{ qDNAN };
	double apocenter{ qDNAN };
	double perecenter{ qDNAN };
	double eccentricity{ qDNAN };
	Orbit() = default;
	Orbit(const Orbit&) = default;
	Orbit(const std::vector<std::string>& words, int& index);
	std::vector<BitMap> GetBitMaps(const Gif& gif); 
};
const std::tuple<Gif, Celestial, Orbit> Parser(int argc, char** argv);
