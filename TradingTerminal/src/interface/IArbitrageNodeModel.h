#ifndef IARBITRAGENODEMODEL_H
#define IARBITRAGENODEMODEL_H

#include "src/interface/INodeModel.h"
#include "../RequesterLib/src/common/Common.h"

namespace atradus
{

class IArbitrageNodeModel : public INodeModel
{
    Q_OBJECT
public:
    IArbitrageNodeModel(QObject* parent = nullptr)
        : INodeModel(parent)
    {
    }

    virtual ~IArbitrageNodeModel() = default;

    virtual const QStringList& log() const = 0;
    virtual void setRequestedCurrencies(const QVector<rqs::CurrencyTrinity>& currencies) = 0;

signals:
    void logChanged(const QStringList& log);
    void logUpdated(const QString& info);
};

} // namespace atradus

#endif // IARBITRAGENODEMODEL_H
