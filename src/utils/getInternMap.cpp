#include "utils/getInternMap.hpp"
#include "built-ins/builtCd.hpp"
#include "built-ins/builtExit.hpp"
#include "built-ins/builtHistory.hpp"
#include "core/shellContext.hpp"
#include <functional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

using BuiltFn =
    std::function<int(const std::vector<std::string> &, ShellContext &)>;

const std::unordered_map<std::string_view, BuiltFn> &getInternMap() {
  static const std::unordered_map<std::string_view, BuiltFn> internMap{
      {"cd", builtCd}, {"exit", builtExit}, {"history", builtHistory}};
  return internMap;
}
