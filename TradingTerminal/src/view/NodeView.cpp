#include "src/view/NodeView.h"
#include "src/interface/IViewFactory.h"

namespace atradus
{

NodeView::NodeView(INodeModel* model, IViewFactory* factory, QWidget* parent)
    : INodeView(parent)
    , m_model(model)
    , m_factory(factory)
{}

}
