#include <iostream>
#include <vector>
#include <functional>

struct pos {
    size_t x, y;
    pos(int xval, int yval)
        : x(xval), y(yval){}

    bool operator==(const pos & other) {
        return x==other.x && y==other.y;
    }
};

namespace std {
    template<>
    struct hash<pos> {
        size_t operator()() {
            return hash<size_t>()(x)^hash<size_t>()(y);
        }
    };
}

class solution {
  public:
    std::vector<pos> pacificAtlantic(const std::vector<std::vector<int>> & matrix) {
        
    }
};
