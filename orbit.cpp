#include "parser.h"

Orbit::Orbit(const std::vector<std::string>& words, int& index) :
	Orbit{ std::invoke([&](){
		Orbit orbit;
		for (++index; index < words.size(); ++index) {
			auto& key{ words[index] };
			if ("-r" == key) {
				if (orbit.apocenter == orbit.apocenter || orbit.perecenter == orbit.perecenter)
					throw std::invalid_argument{ "Redefinition radius and apocenter/perecenter" };
				else if (orbit.radius == orbit.radius)
					throw std::invalid_argument{ "Redefinition radius orbit" };
				else
					orbit.radius = std::stod(words[++index]);
			}
			else if ("-a" == key) {
				if (orbit.radius == orbit.radius)
					throw std::invalid_argument{ "Redefinition radius and apocenter/perecenter" };
				else if (orbit.apocenter == orbit.apocenter)
					throw std::invalid_argument{ "Redefinition apocenter orbit" };
				else {
					orbit.apocenter = std::stod(words[++index]);
					if (orbit.perecenter > orbit.apocenter)
						throw std::invalid_argument{ "perecenter > apocenter" };
				}
			}
			else if ("-p" == key) {
				if (orbit.radius == orbit.radius)
					throw std::invalid_argument{ "Redefinition radius and apocenter/perecenter" };
				else if (orbit.perecenter == orbit.perecenter)
					throw std::invalid_argument{ "Redefinition perecenter orbit" };
				else {
					orbit.perecenter = std::stod(words[++index]);
					if (orbit.apocenter < orbit.perecenter)
						throw std::invalid_argument{ "apocenter < perecenter" };
				}
			}
		}
		if (orbit.radius == orbit.radius)
			orbit.apocenter = orbit.perecenter = orbit.radius;
		if (orbit.apocenter != orbit.apocenter || orbit.perecenter != orbit.perecenter)
			throw std::invalid_argument{ "Not definition apocenter/perecenter orbit" };
		orbit.major = (orbit.apocenter + orbit.perecenter) / 2;
		orbit.eccentricity = (orbit.major - orbit.perecenter) / orbit.major;
		orbit.focal = orbit.apocenter * (1. - orbit.eccentricity);
		orbit.minor = orbit.apocenter * std::sqrt((1 - orbit.eccentricity) / (1 + orbit.eccentricity));
		return orbit;

//		int size{ 2 * border };
//		std::vector<unsigned char> frame{};
//		frame.resize(size * size * 4);
//		GifWriter gif;
//		GifBegin(&gif, "gif.gif", size, size, delay);
//		GifWriteFrame(&gif, frame.data(), size, size, delay);
//		GifEnd(&gif);
	})}
{}
std::vector<BitMap> Orbit::GetBitMaps(const Gif& gif) {
	std::vector<BitMap> vector;
	return vector;
}
