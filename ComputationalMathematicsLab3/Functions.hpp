#include <cassert>
#include <string>
#include <type_traits>

namespace KHAS {

    template <typename Str>
        requires std::is_convertible_v<Str, std::string>
    std::string generateString(Str&& str, size_t width_screen) noexcept {

        std::string s{ std::forward<Str>(str) };

        size_t size{ s.size() };

        assert(size + 4 <= width_screen);
        size_t part_size{ (width_screen - size - 4) >> 1 };
        size_t offset{ width_screen - ((part_size << 1) + 4 + size) };

        return "| " + std::string(part_size, ' ') + s + std::string(part_size + offset, ' ') + " |";
    }
}