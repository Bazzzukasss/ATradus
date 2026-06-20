#ifndef TRADINGTERMINAL_COMMON_H
#define TRADINGTERMINAL_COMMON_H

namespace atradus
{

enum class NodeType
{
    Unknown,
    Arbitrage,
    TriangleArbitrage
};

enum class MarketType
{
    Unknown,
    Binance
};

} // namespace atradus

#endif // ATRADUS_COMMON_H
