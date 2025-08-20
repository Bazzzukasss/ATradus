#include "src/model/ApplicationModel.h"
#include "src/model/NodeListModel.h"
#include "src/interface/IModelFactory.h"
#include "src/interface/INodeModel.h"
#include "src/interface/IArbitrageNodeModel.h"

namespace atradus
{

ApplicationModel::ApplicationModel(IModelFactory* factory, QObject* parent)
    : IApplicationModel(parent)
    , m_factory(factory)
{
    m_nodeListModel = m_factory->createNodeListModel();
}

IArbitrageNodeModel* ApplicationModel::addArbitrageNode(const MarketType& marketType,
                                                        const QVector<rqs::CurrencyTrinity>& currencies)
{
    auto nodeModel = m_factory->createArbitrageNodeModel(marketType, this);
    nodeModel->setRequestedCurrencies(currencies);
    addNode(nodeModel);

    return nodeModel;
}

INodeModel* ApplicationModel::addNode(const NodeType& nodeType, const MarketType& marketType)
{
    auto nodeModel = m_factory->createNodeModel(nodeType, marketType, this);
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

void ApplicationModel::setMarketAccount(const rqs::MarketAccount& account)
{
    m_account = account;

    for(int i = 0 ; i < m_nodeListModel->rowCount(); ++i)
    {
        auto nodeModel = m_nodeListModel->getNode(i);
        nodeModel->setMarketAccount(account);
    }
}

void ApplicationModel::addNode(INodeModel* nodeModel)
{
    nodeModel->setMarketAccount(m_account);
    m_nodeListModel->addNode(nodeModel);
}

void ApplicationModel::removeNode(INodeModel* nodeModel)
{
    m_nodeListModel->deleteNode(nodeModel);
}

} // namespace atradus
