#include "ModelFactory.h"
#include "src/model/ArbitageNodeModel.h"
#include "src/model/ApplicationModel.h"
#include "src/interface/IApplicationModel.h"
#include "../RequesterLib/src/Builder.h"
#include "../RequesterLib/src/interface/IRequester.h"

namespace atradus
{

ModelFactory::ModelFactory(QObject* parent)
    : IModelFactory(parent)
    , m_builder(std::move(std::make_unique<rqs::Builder>()))
{
}

INodeModel* ModelFactory::createNodeModel(const NodeType& nodeType, const MarketType& marketType)
{
    std::unique_ptr<rqs::IRequester> requester;
    switch(marketType)
    {
        case MarketType::Binance:
        requester = m_builder->binanceRequester();
        break;
    }

    switch(nodeType)
    {
        case NodeType::Arbitrage:
        return new ArbitageNodeModel(std::move(requester), this);
        break;
    }

    return nullptr;
}

IApplicationModel* ModelFactory::createApplicationModel()
{
    return new ApplicationModel(this);
}

} // namespace atradus
