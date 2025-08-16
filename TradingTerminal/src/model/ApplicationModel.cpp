#include "src/model/ApplicationModel.h"
#include "src/service/ModelFactory.h"
#include "src/interface/INodeModel.h"
#include "src/model/NodeListModel.h"

namespace atradus
{

ApplicationModel::ApplicationModel(QObject* parent)
    : IApplicationModel(parent)
    , m_factory(new ModelFactory(this))
{
    m_nodeListModel = m_factory->createNodeListModel();
}

void ApplicationModel::addNode(const NodeType& nodeType, const MarketType& marketType)
{
    auto nodeModel = m_factory->createNodeModel(nodeType, marketType);
    addNode(nodeModel);
}

INodeListModel* ApplicationModel::nodeListModel() const
{
    return m_nodeListModel;
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
