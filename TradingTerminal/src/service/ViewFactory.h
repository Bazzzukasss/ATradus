#ifndef VIEWFACTORY_H
#define VIEWFACTORY_H

#include "src/interface/IViewFactory.h"

namespace atradus
{

class ViewFactory : public IViewFactory
{
    Q_OBJECT
public:
    explicit ViewFactory(QObject* parent = nullptr);

    INodeView* createNodeView(INodeModel* model, QWidget* parent) override;
    IApplicationView* createApplicationView(IApplicationModel* model, QWidget* parent) override;
    INodeListView* createNodeListView(INodeListModel* model, QWidget* parent) override;
    IArbitrageNodeView* createArbitrageNodeView(IArbitrageNodeModel* model, QWidget* parent) override;
};

} // namespace atradus

#endif // VIEWFACTORY_H
