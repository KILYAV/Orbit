#include <memory>
#include <cstring>
#include <iostream>
#include "glm.hpp"

namespace bitmap {
	struct RED
	{
		unsigned char r = -1;
	};
	struct RGB :
		RED
	{
		unsigned char g = -1;
		unsigned char b = -1;
	};
	struct RGBA :
		RGB
	{
		unsigned char a = -1;
	};
	template<typename Pixel>
	class BitMap :
		std::unique_ptr<Pixel[]>
	{
	private:
		glm::uvec2 size;
		unsigned height;
	public:
		//using std::unique_ptr<Pixel[]>::empty;

		BitMap() = default;
		BitMap(BitMap&& bitmap);
		BitMap(const BitMap& bitmap);
		BitMap(const glm::uvec2 size, const Pixel* data);
		BitMap(const glm::uvec2 size, const Pixel pixel);
		void operator= (const BitMap& other);

		BitMap& SetSize(const glm::uvec2 size);
		BitMap& SetPixel(const glm::uvec2 pos, const Pixel pixel);
		BitMap& Insert(const BitMap& other, const glm::uvec2 pos);
		BitMap& Fill(const Pixel pixel);
		BitMap& Border(const Pixel pixel);
		BitMap& MirrorXX();
		BitMap& MirrorUp();
		BitMap& MirrorLeft();
		const BitMap& Print() const;

		Pixel GetPixel(const glm::uvec2 pos) const;

		const unsigned char* Data() const;
		glm::uvec2 GetSize() const {
			return size;
		}
	private:
		std::unique_ptr<Pixel[]> Data(const glm::uvec2 size, const Pixel* data);
		std::unique_ptr<Pixel[]> Data(const glm::uvec2 size, const Pixel pixel);
	};
	template<typename Pixel>
	std::unique_ptr<Pixel[]> BitMap<Pixel>::Data(const glm::uvec2 size, const Pixel* data) {
		unsigned count = size.x * size.y;
		if (count) {
			Pixel* bitmap{ new Pixel[count]{} };
			if (data) 
				std::memcpy(bitmap, data, count * sizeof(Pixel));
			return std::unique_ptr<Pixel[]>{ bitmap };
		}
		else
			return std::unique_ptr<Pixel[]>{};
	}
	template<typename Pixel>
	std::unique_ptr<Pixel[]> BitMap<Pixel>::Data(const glm::uvec2 size, const Pixel pixel) {
		unsigned count = size.x * size.y;
		if (count) {
			Pixel* bitmap{ new Pixel[count]{} };
			for (unsigned index = 0; index < count; ++index)
				bitmap[index] = pixel;
			return std::unique_ptr<Pixel[]>{ bitmap };
		}
		else
			return std::unique_ptr<Pixel[]>{};
	}
	template<typename Pixel>
	BitMap<Pixel>::BitMap(BitMap&& bitmap) :
		std::unique_ptr<Pixel[]>{ std::move(static_cast<std::unique_ptr<Pixel[]>&>(bitmap)) },
		size{ std::invoke([&]() {
			auto temp = bitmap.size;
			bitmap.size = { 0, 0 };
			return temp;
			}) }
	{};
	template<typename Pixel>
	BitMap<Pixel>::BitMap(const BitMap& bitmap) :
		BitMap{ bitmap.get(), bitmap.size }
	{}
	template<typename Pixel>
	BitMap<Pixel>::BitMap(const glm::uvec2 size, const Pixel* data) :
		std::unique_ptr<Pixel[]>{ Data(size,data) },
		size{ size }
	{}
	template<typename Pixel>
	BitMap<Pixel>::BitMap(const glm::uvec2 size, const Pixel pixel) :
		std::unique_ptr<Pixel[]>{ Data(size,pixel) },
		size{ size }
	{}
	template<typename Pixel>
	void BitMap<Pixel>::operator= (const BitMap& other) {
		static_cast<std::unique_ptr<Pixel[]>&>(*this) = Data(other.get(),other.size);
		size = other.size;
	}
	template<typename Pixel>
	BitMap<Pixel>& BitMap<Pixel>::SetSize(const glm::uvec2 new_size) {
		static_cast<std::unique_ptr<Pixel[]>&>(*this) = Data(nullptr, new_size);
		size = new_size;
		return *this;
	}
	template<typename Pixel>
	BitMap<Pixel>& BitMap<Pixel>::SetPixel(const glm::uvec2 pos, const Pixel pixel) {
		if (0 <= pos.x || pos.x < size.x || 0 <= pos.y || pos.y < size.y) {
			this->get()[pos.x + pos.y * size.x] = pixel;
		}
		return *this;
	}
	template<typename Pixel>
	BitMap<Pixel>& BitMap<Pixel>::Insert(const BitMap& other, const glm::uvec2 pos) {
		for (unsigned y = 0; y < other.GetSize().y; ++y) {
			for (unsigned x = 0; x < other.GetSize().x; ++x) {
				this->SetPixel({ pos.x + x,pos.y + y }, other.GetPixel({ x,y }));
			}
		}
		return *this;
	}
	template<typename Pixel>
	BitMap<Pixel>& BitMap<Pixel>::Fill(const Pixel pixel) {
		for (unsigned y = 0; y < size.y; ++y) {
			for (unsigned x = 0; x < size.x; ++x) {
				SetPixel({ x,y }, pixel);
			}
		}
		return *this;
	}
	template<typename Pixel>
	BitMap<Pixel>& BitMap<Pixel>::MirrorXX() {
		auto halfY{ size.y >> 1 };
		for (unsigned d = 0, s = size.y - 1; d < halfY; ++d, --s) {
			for (unsigned x = 0; x < size.x; ++x) {
				Pixel temp = this->get()[x + d * size.x];
				this->get()[x + d * size.x] = this->get()[x + s * size.x];
				this->get()[x + s * size.x] = temp;
			}
		}
		return *this;
	}
	template<typename Pixel>
	BitMap<Pixel>& BitMap<Pixel>::MirrorUp() {
		const unsigned column{ size.y << 1 };
		const unsigned count{ size.x * column };
		if (count) {
			std::unique_ptr<Pixel[]> bitmap{ new Pixel[count]{} };
			for (unsigned y = 0; y < size.y; ++y) {
				for (unsigned x = 0; x < size.x; ++x) {
					Pixel pixel{ static_cast<std::unique_ptr<Pixel[]>&>(*this).get()[size.x * y + x] };
					bitmap.get()[size.x * (size.y - y - 1) + x] = pixel;
					bitmap.get()[size.x * (size.y + y + 0) + x] = pixel;
				}
			}
			static_cast<std::unique_ptr<Pixel[]>&>(*this) = std::move(bitmap);
			size.y <<= 1;
		}
		return *this;
	}
	template<typename Pixel>
	BitMap<Pixel>& BitMap<Pixel>::MirrorLeft() {
		const unsigned row{ size.x << 1 };
		const unsigned count{ row * size.y };
		if (count) {
			std::unique_ptr<Pixel[]> bitmap{ new Pixel[count]{} };
			for (unsigned y = 0; y < size.y; ++y) {
				for (unsigned x = 0; x < size.x; ++x) {
					Pixel pixel{ static_cast<std::unique_ptr<Pixel[]>&>(*this).get()[size.x * y + x] };
					bitmap.get()[row * y + size.x - x - 1] = pixel;
					bitmap.get()[row * y + size.x + x + 0] = pixel;
				}
			}
			static_cast<std::unique_ptr<Pixel[]>&>(*this) = std::move(bitmap);
			size.x <<= 1;
		}
		return *this;
	}
	template<typename Pixel>
	BitMap<Pixel>& BitMap<Pixel>::Border(const Pixel pixel) {
		for (auto y : { 0,size.y - 1 }) {
			for (auto x = 0; x < size.x; ++x) {
				this->get()[x + y * size.x] = pixel;
			}
		}
		for (auto x : { 0,size.x - 1 }) {
			for (auto y = 0; y < size.y; ++y) {
				this->get()[x + y * size.x] = pixel;
			}
		}
		return *this;
	}
	template<typename Pixel>
	const BitMap<Pixel>& BitMap<Pixel>::Print() const {
		for (unsigned y = 0; y < size.y; ++y) {
			for (unsigned x = 0; x < size.x; ++x) {
				if (127 < this->GetPixel({ x,y }).r)
					std::cout << '#';
				else
					std::cout << '.';
			}
			std::cout << '\n';
		}
		return *this;
	}
	template<typename Pixel>
	Pixel BitMap<Pixel>::GetPixel(const glm::uvec2 pos) const {
		if (0 <= pos.x || pos.x < size.x || 0 <= pos.y || pos.y < size.y)
			return this->get()[pos.x + pos.y * size.x];
	}
	template<typename Pixel>
	const unsigned char* BitMap<Pixel>::Data() const {
		return static_cast<const unsigned char*>(static_cast<const void*>(this->get()));
	}
}
