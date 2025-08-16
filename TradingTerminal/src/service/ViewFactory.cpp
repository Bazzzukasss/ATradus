#include "src/service/ViewFactory.h"
#include "src/view/ApplicationView.h"
#include "src/view/ArbitrageNodeView.h"
#include "src/view/NodeView.h"
#include "src/view/NodeListView.h"

namespace atradus
{

ViewFactory::ViewFactory(QObject* parent)
    : IViewFactory(parent)
{}

INodeView* ViewFactory::createNodeView(INodeModel* model, QWidget* parent)
{
    return new NodeView(model, this, parent);
}

IApplicationView* ViewFactory::createApplicationView(IApplicationModel* model, QWidget* parent)
{
    return new ApplicationView(model, this, parent);
}

INodeListView* ViewFactory::createNodeListView(INodeListModel* model, QWidget* parent)
{
    return new NodeListView(model, parent);
}

IArbitrageNodeView* ViewFactory::createArbitrageNodeView(IArbitrageNodeModel* model, QWidget* parent)
{
    return new ArbitrageNodeView(model, parent);
}

} // namespace atradus
