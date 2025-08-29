#include "parser.h"

Celestial::Celestial(const std::vector<std::string>& words, int& index) :
	Celestial{ std::invoke([&](){
		Celestial celestial;
		for (++index; index < words.size(); ++index) {
			auto& key{ words[index] };
			if ("-n" == key) {
				if (celestial.name.empty())
					celestial.name = words[++index];
				else
					throw std::invalid_argument{ "Redefinition name celestial" };
				}
			else if ("-r" == key) {
				if (celestial.radius != celestial.radius)
					celestial.radius = std::stod(words[++index]);
				else
					throw std::invalid_argument{ "Redefinition radius celestial" }; 
				}
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
void Celestial::Print() {
	std::cout
		<< "\nCelestial:\n"
		<< "Name - " << name << "\n"
		<< "Radius - " << radius << "\n";
}
BitMap Celestial::GetBitMap(const Gif& gif) {
	const unsigned size{ static_cast<unsigned>((radius + gif.scale * .5) / gif.scale) };
	BitMap quad{ glm::uvec2{ size, size }, bitmap::RGBA{ 0, 0, 0, 0 } };
	for (unsigned y = 0; y < size; ++y) {
		const double delta{ gif.scale * .5 + gif.scale * y };
		const unsigned b = std::sqrt(radius * radius - delta * delta) / gif.scale;
		for (unsigned x = 0; x < b; ++x) {
			quad.SetPixel({ x,y }, bitmap::RGBA{});
		}
	}
	quad.MirrorLeft().MirrorUp();
	return quad;
}
