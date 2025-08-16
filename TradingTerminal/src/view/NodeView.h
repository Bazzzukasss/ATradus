#ifndef NODEVIEW_H
#define NODEVIEW_H

#include "src/interface/INodeView.h"

namespace atradus
{

class INodeModel;
class IViewFactory;

class NodeView : public INodeView
{
    Q_OBJECT
public:
    NodeView(INodeModel* model, IViewFactory* factory, QWidget* parent = nullptr);

private:
    INodeModel* m_model{nullptr};
    IViewFactory* m_factory{nullptr};
};

} // namespace atradus


#endif // NODEVIEW_H
