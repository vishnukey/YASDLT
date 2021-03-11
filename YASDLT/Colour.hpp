#pragma once
#ifndef _COLOUR_HPP_
#define _COLOUR_HPP_

#include <iostream>

namespace Violet::gfx {
    struct Colour {
        private:
            union Data {
                uint32_t raw;
                struct Packed {
                    uint8_t b;
                    uint8_t g;
                    uint8_t r;
                    uint8_t a;

                    constexpr Packed(uint8_t _a, uint8_t _r, uint8_t _g, uint8_t _b) :
                        b{ _b }, g{ _g }, r{ _r }, a{ _a } { }
                    constexpr Packed(uint32_t data) :
                        b{ (data >> 0) & 0xff },
                        g{ (data >> 8) & 0xff },
                        r{ (data >> 16) & 0xff },
                        a{ (data >> 24) & 0xff } { }

                    constexpr Packed() : b{ 0 }, g{ 0 }, r{ 0 }, a{ 0 } { }
                    constexpr Packed(const Packed& other) = default;
                    constexpr Packed(Packed&& other) = default;
                    constexpr Packed& operator=(const Packed& other) = default;
                    constexpr Packed& operator=(Packed&& other) = default;

                } packed;
                constexpr Data(uint32_t bytes) : raw{ bytes }, packed{ bytes } { }
                constexpr Data(uint8_t _a, uint8_t _r, uint8_t _g, uint8_t _b) :
                    packed{ _a, _r, _g, _b } { }

                constexpr Data() : raw{ 0x00000000 }, packed{} { }
                constexpr Data(const Data& other) = default;
                constexpr Data(Data&& other) = default;
                constexpr Data& operator=(const Data& other) = default;
                constexpr Data& operator=(Data&& other) = default;
            } _data;

        public:
            // rule of 5
            constexpr Colour() : _data{ } { }
            constexpr Colour(const Colour& other) = default;
            constexpr Colour(Colour&& other) = default;
            constexpr Colour& operator=(const Colour& other) = default;
            constexpr Colour& operator=(Colour&& other) = default;

            constexpr Colour(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 0xff) : _data{ a, r, g, b } { }
            explicit constexpr Colour(uint32_t col) : _data{ col } { } // redundant, mostly
            explicit constexpr Colour(int col) : _data{
                (
                    (((0xff000000 & col) == 0) * 0xff000000) +
                    (((0xff000000 & col) != 0) * (0xff000000 & col))
                ) |
                (0x00ffffff & col) // magic but branchless, also, a constexpr so compiler can optimize
            } { }

            constexpr uint8_t a() const { return _data.packed.a; }
            constexpr uint8_t r() const { return _data.packed.r; }
            constexpr uint8_t g() const { return _data.packed.g; }
            constexpr uint8_t b() const { return _data.packed.b; }

            constexpr uint8_t& a() { return _data.packed.a; }
            constexpr uint8_t& r() { return _data.packed.r; }
            constexpr uint8_t& g() { return _data.packed.g; }
            constexpr uint8_t& b() { return _data.packed.b; }

            constexpr uint32_t raw() const { return _data.raw; }
            constexpr uint32_t& raw() { return _data.raw; }

            constexpr bool operator==(const Colour& rhs) const { return _data.raw == rhs._data.raw; }
            constexpr bool operator!=(const Colour& rhs) const { return _data.raw != rhs._data.raw; }

            friend std::ostream& operator<<(std::ostream& stream, const Colour& clr)
            {
                return
                    stream <<
                    "Colour{" <<
                    "a=" << static_cast<int>(clr.a()) << ","
                    "r=" << static_cast<int>(clr.r()) << ","
                    "g=" << static_cast<int>(clr.g()) << ","
                    "b=" << static_cast<int>(clr.b()) << "}"
                    ;
            }
    };

    namespace Colours {
        [[maybe_unused]] constexpr auto RED = Colour{ 0xFF0000 };
        [[maybe_unused]] constexpr auto GREEN = Colour{ 0x00FF00 };
        [[maybe_unused]] constexpr auto BLUE = Colour{ 0x0000FF };

        [[maybe_unused]] constexpr auto YELLOW = Colour{ 0xFFFF00 };
        [[maybe_unused]] constexpr auto CYAN = Colour{ 0x00FFFF };
        [[maybe_unused]] constexpr auto MAGENTA = Colour{ 0xFF00FF };

        [[maybe_unused]] constexpr auto DARK_RED = Colour{ 0x7F0000 };
        [[maybe_unused]] constexpr auto DARK_GREEN = Colour{ 0x007F00 };
        [[maybe_unused]] constexpr auto DARK_BLUE = Colour{ 0x00007F };

        [[maybe_unused]] constexpr auto DARK_YELLOW = Colour{ 0x7F7F00 };
        [[maybe_unused]] constexpr auto DARK_CYAN = Colour{ 0x007F7F };
        [[maybe_unused]] constexpr auto DARK_MAGENTA = Colour{ 0x7F007F };

        [[maybe_unused]] constexpr auto WHITE = Colour{ 0xFFFFFF };
        [[maybe_unused]] constexpr auto BLACK = Colour{ 0x000000 };

        [[maybe_unused]] constexpr auto GREY = Colour{ 0x7F7F7F };
        [[maybe_unused]] constexpr auto DARK_GREY = Colour{ 0x3F3F3F };
    }
}

#endif

