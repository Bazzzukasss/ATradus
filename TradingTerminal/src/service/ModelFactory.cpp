#include "ModelFactory.h"
#include "src/model/ArbitageNodeModel.h"
#include "src/model/ApplicationModel.h"
#include "src/model/NodeListModel.h"
#include "../RequesterLib/src/Builder.h"
#include "../RequesterLib/src/interface/IRequester.h"

namespace atradus
{

ModelFactory::ModelFactory(QObject* parent)
    : IModelFactory(parent)
    , m_builder(std::make_unique<rqs::Builder>())
{
}

INodeModel* ModelFactory::createNodeModel(const NodeType& nodeType, const MarketType& marketType, QObject* parent)
{
    switch(nodeType)
    {
        case NodeType::Arbitrage:
            return createArbitrageNodeModel(marketType, parent);
            break;
        default:
            break;
    }

    return nullptr;
}

IApplicationModel* ModelFactory::createApplicationModel(QObject* parent)
{
    return new ApplicationModel(parent);
}

INodeListModel* ModelFactory::createNodeListModel(QObject* parent)
{
    return new NodeListModel(parent);
}

IArbitrageNodeModel* ModelFactory::createArbitrageNodeModel(const MarketType& marketType, QObject* parent)
{
    auto requester = createRequester(marketType);

    return new ArbitageNodeModel(std::move(requester), this);
}

std::unique_ptr<rqs::IRequester> ModelFactory::createRequester(const MarketType& marketType) const
{
    std::unique_ptr<rqs::IRequester> requester;

    switch(marketType)
    {
    case MarketType::Binance:
        requester = m_builder->binanceRequester();
        break;
    default:
        break;
    }

    return requester;
}

} // namespace atradus
