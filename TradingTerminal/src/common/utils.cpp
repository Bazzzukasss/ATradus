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

double calculateCurrencyVolume(double price_usdt, double volume_usdt, double commision_prs)
{
    double coins = volume_usdt / price_usdt;
    double commision = coins * commision_prs / 100;
    double value = coins - commision;

    return value;
}

} // namespace utils
} // namespace atradus
