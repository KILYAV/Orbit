#include <vector>
#include "orbit.h"

Orbit::Orbit(const std::vector<std::string>& words, int& index) :
	Orbit{ std::invoke([&](){
		Orbit orbit;
		for (++index; index < word.size(); ++index) {
			auto& key{ words[index] };
			if ("-a" == key)
				orbit.apocenter = words[++index];
			else if ("-p" == key)
				orbit.pericenter = words[++index];
		}
		return orbit;
//		int size{ 2 * border };
//		std::vector<unsigned char> frame{};
//		frame.resize(size * size * 4);
//		GifWriter gif;
//		GifBegin(&gif, "gif.gif", size, size, delay);
//		GifWriteFrame(&gif, frame.data(), size, size, delay);
//		GifEnd(&gif);
	})}
}
