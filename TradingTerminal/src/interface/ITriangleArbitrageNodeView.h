#ifndef ITRIANGLEARBITRAGENODEVIEW_H
#define ITRIANGLEARBITRAGENODEVIEW_H

#include <QWidget>

namespace atradus
{

class ITriangleArbitrageNodeView : public QWidget
{
    Q_OBJECT
public:
    ITriangleArbitrageNodeView(QWidget* parent = nullptr)
        : QWidget(parent)
    {
    }

    virtual ~ITriangleArbitrageNodeView() = default;
};

} // namespace atradus


#endif // ITRIANGLEARBITRAGENODEVIEW_H
