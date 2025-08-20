#ifndef INODEMODEL_H
#define INODEMODEL_H

#include <QObject>
#include "src/common/Common.h"
#include "../RequesterLib/src/common/Common.h"

namespace atradus
{

class INodeModel : public QObject
{
    Q_OBJECT
public:
    INodeModel(QObject* parent = nullptr)
        : QObject(parent)
    {
    }

    virtual ~INodeModel() = default;

    virtual void setMarketAccount(const rqs::MarketAccount& account) = 0;
    virtual NodeType type() const = 0;
    virtual const QStringList& info() const = 0;
    virtual bool isActive() const = 0;
    virtual void switchState() = 0;
    virtual void run() = 0;
    virtual void start() = 0;
    virtual void stop() = 0;

signals:
    void infoChanged(const QStringList& info);
    void isActiveChanged(bool isActive);
};

} // namespace atradus

#endif // INODEMODEL_H
