#include <iostream>
#include <vector>
#include <functional>
#include <stack>
#include <utility>
#include <iterator>

struct pos {
  size_t x, y;
  pos(int xval, int yval)
    : x(xval), y(yval){}

  bool operator==(const pos & other) {
    return x==other.x && y==other.y;
  }

  std::ostream & output(std::ostream & s) const {
    s << "[" << x << "," << y << "]";
    return s;
  }
};

std::ostream & operator<<(std::ostream & s, const pos & p) {
  p.output(s);
  return s;
}

// namespace std {
//   template<>
//   struct hash<pos> {
//     size_t operator()() {
//       return hash<size_t>()(x)^hash<size_t>()(y);
//     }
//   };
// }

class solution {
public:
  std::vector<pos> pacificAtlantic(const std::vector<std::vector<int>> & matrix) {
    std::vector<std::vector<int>> visited(matrix.size(), std::vector<int>(matrix[0].size(), 0));
    std::vector<pos> result;
    for (size_t i = 0; i < matrix.size(); ++i) {
      for (size_t j = 0; j < matrix[i].size(); ++j) {
    // size_t i = 2, j = 2;
	auto cpy = visited;
	pos curr(i,j);
	cpy[curr.x][curr.y] = 1;
	if (canReachPacific(matrix, std::make_pair(curr, cpy)) && canReachAtlantic(matrix, std::make_pair(curr, cpy)))
	  result.push_back(curr);
      }
    }

    return result;
  }

private:
  std::vector<pos> getNeibs(const std::vector<std::vector<int>> & mat, const pos & curr, const std::vector<std::vector<int>> & visited) {
    std::vector<pos> next;
    if (curr.y >= 1 && visited[curr.x][curr.y-1] == 0 && mat[curr.x][curr.y] >= mat[curr.x][curr.y-1])
      next.push_back(pos(curr.x, curr.y-1));
    if (curr.y < visited[0].size()-1 && visited[curr.x][curr.y+1] == 0  && mat[curr.x][curr.y] >= mat[curr.x][curr.y+1])
      next.push_back(pos(curr.x, curr.y+1));
    if (curr.x >= 1 && visited[curr.x-1][curr.y] == 0 && mat[curr.x][curr.y] >= mat[curr.x-1][curr.y])
      next.push_back(pos(curr.x-1, curr.y));
    if (curr.x < visited.size()-1 && visited[curr.x+1][curr.y] == 0  && mat[curr.x][curr.y] >= mat[curr.x+1][curr.y])
      next.push_back(pos(curr.x+1, curr.y));
    return next;
  }
  
  bool canReachPacific(const std::vector<std::vector<int>> & matrix, const std::pair<pos, std::vector<std::vector<int>>> & pr) {
    std::stack<std::pair<pos, std::vector<std::vector<int>>>> st;
    st.push(pr);
    while (!st.empty()) {
      auto curr = st.top();
      st.pop();
      // std::cout << "In reachPacific:\n";
      // std::cout << "curr = [" << curr.first.x << "," << curr.first.y << "]\n";
      if (curr.first.x == 0 || curr.first.y == 0)
	return true;
      else {
	auto next = getNeibs(matrix, curr.first, curr.second);
	// std::cout << "neibs are:\n";
	// std::copy(next.begin(), next.end(), std::ostream_iterator<pos>(std::cout, " "));
	// std::cout << std::endl;
	for (auto nx : next) {
	  auto cpy = curr.second;
	  cpy[nx.x][nx.y] = 1;
	  st.push(std::make_pair(nx, cpy));
	}
      }
    }
    return false;
  }

  bool canReachAtlantic(const std::vector<std::vector<int>> & matrix, const std::pair<pos, std::vector<std::vector<int>>> & pr) {
    std::stack<std::pair<pos, std::vector<std::vector<int>>>> st;
    st.push(pr);
    while (!st.empty()) {
      auto curr = st.top();
      // std::cout << "In reachAtlantic:\n";
      // std::cout << "curr = [" << curr.first.x << "," << curr.first.y << "]\n";
      st.pop();
      if (curr.first.x == matrix.size()-1 || curr.first.y == matrix[0].size()-1)
	return true;
      else {
	auto next = getNeibs(matrix, curr.first, curr.second);
	// std::cout << "next.size = " << next.size() << std::endl;
	for (auto nx : next) {
	  auto cpy = curr.second;
	  cpy[nx.x][nx.y] = 1;
	  st.push(std::make_pair(nx, cpy));
	}
      }
    }
    return false;
  }
};

int main() {
  std::vector<std::vector<int>> matrix{
    {1,2,2,3,5},
      {3,2,3,4,4},
	{2,4,5,3,1},
	  {6,7,1,4,5},
	    {5,1,1,2,4}
  };

  solution soln;
  std::vector<pos> result = soln.pacificAtlantic(matrix);
  std::cout << "All the pos where water can flow to both Pacific and Atlantic ocean are:\n";
  std::copy(result.begin(), result.end(), std::ostream_iterator<pos>(std::cout, " "));
  std::cout << std::endl;
}
