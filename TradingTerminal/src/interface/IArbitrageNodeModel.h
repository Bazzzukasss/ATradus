#ifndef IARBITRAGENODEMODEL_H
#define IARBITRAGENODEMODEL_H

#include "src/interface/INodeModel.h"

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

signals:
    void logChanged(const QStringList& info);
};

} // namespace atradus

#endif // IARBITRAGENODEMODEL_H
