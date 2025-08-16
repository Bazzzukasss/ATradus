#ifndef IMODELFACTORY_H
#define IMODELFACTORY_H

#include "src/common/Common.h"
#include <QObject>

namespace atradus
{

class INodeModel;
class IApplicationModel;
class INodeListModel;
class IArbitrageNodeModel;

class IModelFactory : public QObject
{
public:
    IModelFactory(QObject* parent = nullptr)
        : QObject(parent)
    {}

    virtual ~IModelFactory() = default;

    virtual INodeModel* createNodeModel(const NodeType& nodeType, const MarketType& marketType, QObject* parent = nullptr) = 0;
    virtual IApplicationModel* createApplicationModel(QObject* parent = nullptr) = 0;
    virtual INodeListModel* createNodeListModel(QObject* parent = nullptr) = 0;
    virtual IArbitrageNodeModel* createArbitrageNodeModel(const MarketType& marketType, QObject* parent = nullptr) = 0;
};

} //namespace atradus

#endif // IMODELFACTORY_H
