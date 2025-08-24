#include "parser.h"

Celestial::Celestial(const std::vector<std::string>& words, int& index) :
	Celestial{ std::invoke([&](){
		Celestial celestial;
		for (++index; index < words.size(); ++index) {
			auto& key{ words[index] };
			if ("-n" == key)
				celestial.name = words[++index];
			else if ("-r" == key)
				celestial.radius = std::stof(words[++index]);
			else if ("-earth" == name) {
				//celestial.name = Celestial::earth;
				break;
			}
			else
				break;
		}
		return celestial;
	})}
{}
BitMap Celestial::GetBitMap(const Gif& gif) {
	const unsigned size{ static_cast<unsigned>(radius / gif.scale) + 1 };
	BitMap quad{ nullptr, { size, size } };
	return quad;
}
