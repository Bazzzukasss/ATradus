#include "src/model/ApplicationModel.h"
#include "src/model/NodeListModel.h"
#include "src/interface/IModelFactory.h"
#include "src/interface/INodeModel.h"
#include "src/interface/IArbitrageNodeModel.h"
#include "src/interface/ITriangleArbitrageNodeModel.h"

namespace atradus
{

ApplicationModel::ApplicationModel(IModelFactory* factory, QObject* parent)
    : IApplicationModel(parent)
    , m_factory(factory)
{
    m_nodeListModel = m_factory->createNodeListModel();
}

IArbitrageNodeModel* ApplicationModel::addArbitrageNode(const std::vector<MarketType>& marketTypes,
                                                        const std::vector<rqs::CoinSymbol>& currencies,
                                                        const std::vector<rqs::MarketAccount>& marketAccounts)
{
    auto nodeModel = m_factory->createArbitrageNodeModel(marketTypes, this);
    nodeModel->setRequestedCurrencies(currencies);
    nodeModel->setMarketAccounts(marketAccounts);
    addNode(nodeModel);

    return nodeModel;
}

ITriangleArbitrageNodeModel* ApplicationModel::addTriangleArbitrageNode(const MarketType& marketType,
                                                                        const std::vector<rqs::CoinTrinity>& currencies,
                                                                        const rqs::MarketAccount& marketAccount)
{
    auto nodeModel = m_factory->createTriangleArbitrageNodeModel(marketType, this);
    nodeModel->setRequestedCurrencies(currencies);
    nodeModel->setMarketAccount(marketAccount);
    addNode(nodeModel);

    return nodeModel;
}

INodeListModel* ApplicationModel::nodeListModel() const
{
    return m_nodeListModel;
}

void ApplicationModel::selectNode(int i)
{
    auto nodeModel = m_nodeListModel->getNode(i);

    if(m_selectedNode != nodeModel)
    {
        m_selectedNode = nodeModel;
        emit selectedNodeChanged(m_selectedNode);
    }
}

INodeModel* ApplicationModel::selectedNode() const
{
    return m_selectedNode;
}

void ApplicationModel::addNode(INodeModel* nodeModel)
{
    m_nodeListModel->addNode(nodeModel);
}

void ApplicationModel::removeNode(INodeModel* nodeModel)
{
    m_nodeListModel->deleteNode(nodeModel);
}

} // namespace atradus
