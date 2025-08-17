#ifndef IAPPLICATIONMODEL_H
#define IAPPLICATIONMODEL_H

#include <QObject>
#include "src/common/Common.h"

namespace atradus
{

class INodeListModel;
class INodeModel;

class IApplicationModel : public QObject
{
public:
    IApplicationModel(QObject* parent = nullptr)
        : QObject(parent)
    {
    }

    virtual INodeModel* addNode(const NodeType& nodeType, const MarketType& marketType) = 0;
    virtual INodeListModel* nodeListModel() const = 0;

    virtual ~IApplicationModel() = default;
};

} // namespace atradus

#endif // IAPPLICATIONMODEL_H
