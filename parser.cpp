#include "parser.h"

void Help(int& index) {
	std::cout
		<< "-h help\n"
		<< "-b border\n"
		<< "-c celestial\n"
		<< "-d delay\n"
		<< "-g gif\n"
		<< "-n name\n"
		<< "-r radius\n"
		<< "-s scale\n";
	++index;
}
Gif::Gif(const std::vector<std::string>& words, int& index) :
	Gif{ std::invoke([&](){
		Gif gif;
		for (++index; index < words.size(); ++index) {
			auto& key{ words[index] };
			if ("-b" == key)
				gif.border = std::stoi(words[++index]);
			else if ("-d" == key)
				gif.delay = std::stoi(words[++index]);
			else if ("-s" == key)
				gif.scale = std::stoi(words[++index]);
			else
				break;
		}
		return gif;
	})}
{}
void Gif::Print() {
	std::cout
		<< "border - " << border << "\n"
		<< "delay - " << delay << "\n"
		<< "scale - " << scale << "\n";
}
const std::tuple<Gif, Celestial, Orbit> Parser(int argc, char** argv) {
	const auto words{ std::invoke([&]() {
		std::vector<std::string> words;
		for (int index = 1; index < argc; ++index) {
			words.push_back(argv[index]);
		}
		return std::move(words);
	})};
	Gif gif;
	Celestial celestial;
	Orbit orbit;
	for (int index = 0; index < words.size();) {
		auto& key{ words[index] };
		if ("-h" == key)
			Help(index);
		else if ("-g" == key)
			gif = Gif{ words, index };
		else if ("-c" == key)
			celestial = Celestial{ words, index };
		else {
			std::cout << "unknow key = " << key << "\n";
			break;
		}
	}
	return { gif, celestial, orbit };
}
