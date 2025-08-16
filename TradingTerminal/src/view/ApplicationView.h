#ifndef APPLICATIONVIEW_H
#define APPLICATIONVIEW_H

#include "src/interface/IApplicationView.h"

namespace atradus
{

class IApplicationModel;
class INodeView;
class IViewFactory;
class INodeListView;

class ApplicationView : public IApplicationView
{
    Q_OBJECT
public:
    explicit ApplicationView(IApplicationModel* model, IViewFactory* factory, QWidget* parent = nullptr);

private:
    IApplicationModel* m_model{nullptr};
    IViewFactory* m_factory{nullptr};
    INodeView* m_nodeView{nullptr};
    INodeListView* m_nodeListView{nullptr};
};

} // namespace atradus

#endif // APPLICATIONVIEW_H
