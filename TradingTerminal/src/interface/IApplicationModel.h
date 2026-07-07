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
class ITriangleArbitrageNodeModel;

class IApplicationModel : public QObject
{
    Q_OBJECT
public:
    IApplicationModel(QObject* parent = nullptr)
        : QObject(parent)
    {
    }

    virtual ~IApplicationModel() = default;

    virtual IArbitrageNodeModel* addArbitrageNode(const std::vector<MarketType>& marketTypes, const std::vector<rqs::CoinSymbol>& currencies, const std::vector<rqs::MarketAccount>& marketAccounts) = 0;
    virtual ITriangleArbitrageNodeModel* addTriangleArbitrageNode(const MarketType& marketType, const std::vector<rqs::CoinTrinity>& currencies, const rqs::MarketAccount& marketAccount) = 0;
    virtual INodeListModel* nodeListModel() const = 0;
    virtual void selectNode(int i) = 0;
    virtual INodeModel* selectedNode() const = 0;

signals:
    void selectedNodeChanged(INodeModel* nodeModel);
};

} // namespace atradus

#endif // IAPPLICATIONMODEL_H
