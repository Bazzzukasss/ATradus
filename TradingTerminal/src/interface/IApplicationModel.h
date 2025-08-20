#ifndef IAPPLICATIONMODEL_H
#define IAPPLICATIONMODEL_H

#include <QObject>
#include "src/common/Common.h"
#include "../RequesterLib/src/common/Common.h"

namespace atradus
{

class INodeListModel;
class INodeModel;
class IArbitrageNodeModel;

class IApplicationModel : public QObject
{
    Q_OBJECT
public:
    IApplicationModel(QObject* parent = nullptr)
        : QObject(parent)
    {
    }

    virtual ~IApplicationModel() = default;

    virtual IArbitrageNodeModel* addArbitrageNode(const MarketType& marketType, const QVector<rqs::CurrencyTrinity>& currencies = {}) = 0;
    virtual INodeModel* addNode(const NodeType& nodeType, const MarketType& marketType) = 0;
    virtual INodeListModel* nodeListModel() const = 0;
    virtual void setMarketAccount(const rqs::MarketAccount& account) = 0;
    virtual void selectNode(int i) = 0;
    virtual INodeModel* selectedNode() const = 0;

signals:
    void selectedNodeChanged(INodeModel* nodeModel);
};

} // namespace atradus

#endif // IAPPLICATIONMODEL_H
