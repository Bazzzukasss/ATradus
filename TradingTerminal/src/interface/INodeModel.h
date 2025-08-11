#ifndef INODEMODEL_H
#define INODEMODEL_H

#include <QObject>

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

    virtual bool run() = 0;
};

} // namespace atradus

#endif // INODEMODEL_H
