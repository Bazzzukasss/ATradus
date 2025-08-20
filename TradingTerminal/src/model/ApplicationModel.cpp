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

    emit nodeSelected(nodeModel);
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
