#include "src/common/utils.h"
#include <map>

namespace atradus
{
namespace utils
{

const std::map<NodeType, std::string> NodeMap { {NodeType::Arbitrage, "Arbitrage"} };

std::string toString(const NodeType& nodeType)
{
    auto itr = NodeMap.find(nodeType);
    return itr != NodeMap.end() ? itr->second : "Unknown";
}

} // namespace utils
} // namespace atradus
