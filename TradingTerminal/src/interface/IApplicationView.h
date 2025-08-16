#ifndef IAPPLICATIONVIEW_H
#define IAPPLICATIONVIEW_H

#include <QWidget>

namespace atradus
{

class IApplicationView : public QWidget
{
public:
    IApplicationView(QWidget* parent = nullptr)
        : QWidget(parent)
    {
    }

    virtual ~IApplicationView() = default;
};

} // namespace atradus

#endif // IAPPLICATIONVIEW_H
