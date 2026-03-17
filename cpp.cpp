#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <cassert>

using namespace std;

void vector_basic() {
  vector<int> a = {1, 2, 3, 4, 5};
  a.reserve(10);  
  
  assert(a.front() == 1);
  assert(a.back() == 5);

  a.push_back(6);  
  a.insert(a.begin() + 2, 3);
  a.insert(a.begin() + 4, {5, 6, 7});


  if (auto it = std::find(a.begin(), a.end(), 2); it != a.end()) {
    a.erase(it);
  }
  std::erase(a, 3); // To remove ALL '3's.
  int value = 4;
  std::erase_if(a, [&value](int x) { 
    return x == value;
  });
  
  struct Point {
    int x;
    int y;
    bool operator<(const Point& other) const {
      return x < other.x;
    }
  };
  vector<Point> structs = {{1, 1}, {2, -2}, {3, -3}};
  sort(structs.begin(), structs.end());
  
  for (int x : a) {
  }
  
  sort(a.begin(), a.end());
  sort(a.begin(), a.end(), std::greater<int>());
  std::reverse(a.begin(), a.end());
  sort(a.begin(), a.end(), [](int x, int y){
    return x < y;
  });
  
  a = {1, 3, 5, 7, 9};
  assert(std::binary_search(a.begin(), a.end(), 3));
  assert(std::lower_bound(a.begin(), a.end(), 3) == a.begin() + 1);  // Find >=3: points at '3'.
  assert(std::upper_bound(a.begin(), a.end(), 3) == a.begin() + 2);  // Find >3: points at '5'.
}

void map_basic() {
  map<int, int> m = {{1, 10}, {2, 20}, {3, 30}};
  
  auto it = m.find(2);
  assert(it != m.end());
  assert(it->first == 2);  // Key.
  assert(it->second == 20);  // Value.
  
  assert(m.contains(2));
  assert(m[2] == 20);
  assert(m.at(2) == 20);  // Throws std::out_of_range if missing.
  
  {
    map<int, map<int, int>> nested;
    nested[8][8] = 80;  // No error: [] inserts a value if missing.  
  }
  
  {
    auto [iter, success] = m.insert({4, 40});
    assert(success);
  }
  {
    auto [iter, success] = m.insert({1, 99});
    assert(!success);
    assert(iter->second == 10);
  }
  {
    auto [iter, success] = m.insert_or_assign(1, 100);
    assert(!success);  // False because it assigned/overwritten.
    assert(iter->second == 100);  // Value is overwritten.
  }
  
  {
    map<int, int> other = {{4, 99}, {5, 50}, {6, 60}};
    m.insert(other.begin(), other.end());
    assert(m[4] == 40);  // Existing value is not overwritten.
    assert(m[5] == 50);
  }
  
  {
    auto node = m.extract(5);
    assert(!m.contains(5));
    node.key() = 55;
    m.insert(std::move(node));
    assert(m.contains(55));
  }
  
  {
    map<int, int> m = {{1, 10}, {2, 20}, {3, 30}, {4, 40}, {5, 50}, {6, 60}};
    m.erase(5);
    m.erase(m.find(6));
    
    for (auto it = m.begin(); it != m.end(); ) {
      if (it->first % 2 == 0) {
        it = m.erase(it);
      } else {
        ++it;
      }
    }
    std::erase_if(m, [](const auto& pair) {
      return pair.first == 3; 
    });
    assert(m.size() == 1 && m[1] == 10);
  }
  
  {
    for (const auto& [key, value] : m) {
    }
    for (const auto& pair : m) {
    }
  }
  
  {
    map<int, int> m = {{1, 10}, {3, 30}, {5, 50}};
    auto const iter_lb = m.lower_bound(3);
    assert(iter_lb != m.end() && iter_lb->first == 3);
    
    auto const iter_ub = m.upper_bound(3);
    assert(iter_ub != m.end() && iter_ub->first == 5);
  }
}

void set_basic() {
  set<int> s = {1, 2, 3};
  
  {
    auto it = s.find(2);
    assert(it != s.end() && *it == 2);
  }
  assert(s.contains(2));
  
  
  {
    auto it = s.insert(4);
    assert(it.first != s.end());
    assert(*it.first == 4);
    assert(it.second);  // Insertion happened.
    
    auto it2 = s.insert(4);
    assert(it.first == it2.first);  // Same iterator.
    assert(!it2.second);  // No insertion.
  }  
  for (const auto& e : s) {
  }
  
  // See map_basic() for examples shared with map<>.
}

void multiset_basic() {
  multiset<int> s = {1, 2, 2, 3, 3, 3};
  
  {
    auto it = s.find(2);
    assert(it != s.end() && *it == 2);
    ++it;  // Move to the second '2'.
    assert(it != s.end() && *it == 2);
  }
  
  
  // Iterate over unique keys.
  for (auto it = s.begin(); it != s.end(); it = s.upper_bound(*it)) {
    assert(*it == s.count(*it));
  }
  
  s.erase(s.find(3));  // Erases a single occurrence.
  assert(s.count(3) == 2);
  s.erase(3);  // Erases all occurrences.
  assert(s.count(3) == 0); 
}

void priority_queque() {
  priority_queue<int, vector<int>, std::less<int>> a;
  
  a.push(1);  
  a.push(2);
  
  assert(a.top() == 2);
  
  while (!a.empty()) {
    a.pop();
  } 
}

int main() {
  vector_basic();
  map_basic();
  set_basic();
  multiset_basic();
  priority_queque();
}