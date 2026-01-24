#include "getInternMap.hpp"
#include "builtCd.hpp"
#include <functional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

using BuiltFn = std::function<int(const std::vector<std::string> &)>;

const std::unordered_map<std::string_view, BuiltFn> &getInternMap() {
  static const std::unordered_map<std::string_view, BuiltFn> internMap{
      {"cd", builtCd}};
  return internMap;
}
