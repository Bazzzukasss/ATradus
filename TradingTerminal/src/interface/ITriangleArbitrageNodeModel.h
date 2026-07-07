#ifndef ITRIANGLEARBITRAGENODEMODEL_H
#define ITRIANGLEARBITRAGENODEMODEL_H

#include "src/interface/INodeModel.h"
#include "../RequesterLib/src/common/Common.h"

namespace atradus
{

class ITriangleArbitrageNodeModel : public INodeModel
{
    Q_OBJECT
public:
    ITriangleArbitrageNodeModel(QObject* parent = nullptr)
        : INodeModel(parent)
    {
    }

    virtual ~ITriangleArbitrageNodeModel() = default;

    virtual const QStringList& log() const = 0;
    virtual void setRequestedCurrencies(const std::vector<rqs::CoinTrinity>& currencies) = 0;
    virtual void setMarketAccount(const rqs::MarketAccount& account) = 0;

signals:
    void logChanged(const QStringList& log);
    void logUpdated(const QString& info);
};

} // namespace atradus

#endif // ITRIANGLEARBITRAGENODEMODEL_H
