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

class IViewFactory : public QObject
{
    Q_OBJECT
public:
    IViewFactory(QObject* parent = nullptr)
        : QObject(parent)
    {}

    virtual ~IViewFactory() = default;

    virtual INodeView* createNodeView(const NodeType& nodeType, INodeModel* model) = 0;
    virtual IApplicationView* createApplicationView(IApplicationModel* model) = 0;
};

} //namespace atradus

#endif // IVIEWFACTORY_H
