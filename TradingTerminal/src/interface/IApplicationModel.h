#ifndef IAPPLICATIONMODEL_H
#define IAPPLICATIONMODEL_H

#include <QObject>

namespace atradus
{

class IApplicationModel : public QObject
{
    Q_OBJECT
public:
    IApplicationModel(QObject* parent = nullptr)
        : QObject(parent)
    {
    }

    virtual ~IApplicationModel() = default;
};

} //namespace atradus

#endif // IAPPLICATIONMODEL_H
