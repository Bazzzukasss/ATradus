#ifndef IMODELFACTORY_H
#define IMODELFACTORY_H

#include "src/common/Common.h"
#include <QObject>

namespace atradus
{

class INodeModel;
class IApplicationModel;

class IModelFactory : public QObject
{
    Q_OBJECT
public:
    IModelFactory(QObject* parent = nullptr)
        : QObject(parent)
    {}

    virtual ~IModelFactory() = default;

    virtual INodeModel* createNodeModel(const NodeType& nodeType, const MarketType& marketType) = 0;
    virtual IApplicationModel* createApplicationModel() = 0;
};

} //namespace atradus

#endif // IMODELFACTORY_H
