#ifndef IVIEWFACTORY_H
#define IVIEWFACTORY_H

#include "src/common/Common.h"
#include <QObject>

namespace atradus
{

class INodeView;
class INodeModel;
class IApplicationView;
class IApplicationModel;
class INodeListView;
class INodeListModel;
class IArbitrageNodeModel;
class IArbitrageNodeView;

class IViewFactory : public QObject
{
public:
    IViewFactory(QObject* parent = nullptr)
        : QObject(parent)
    {}

    virtual ~IViewFactory() = default;

    virtual INodeView* createNodeView(INodeModel* model, QWidget* parent) = 0;
    virtual IApplicationView* createApplicationView(IApplicationModel* model, QWidget* parent) = 0;
    virtual INodeListView* createNodeListView(INodeListModel* model, QWidget* parent) = 0;
    virtual IArbitrageNodeView* createArbitrageNodeView(IArbitrageNodeModel* model, QWidget* parent) = 0;
};

} //namespace atradus

#endif // IVIEWFACTORY_H
