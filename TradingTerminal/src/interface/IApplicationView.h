#ifndef IAPPLICATIONVIEW_H
#define IAPPLICATIONVIEW_H

#include <QObject>

namespace atradus
{

class IApplicationView : public QObject
{
    Q_OBJECT
public:
    IApplicationView(QObject* parent = nullptr)
        : QObject(parent)
    {
    }

    virtual ~IApplicationView() = default;
};

} // namespace atradus

#endif // IAPPLICATIONVIEW_H
