#ifndef IARBITRAGENODEVIEW_H
#define IARBITRAGENODEVIEW_H

#include <QWidget>

namespace atradus
{

class IArbitrageNodeView : public QWidget
{
public:
    IArbitrageNodeView(QWidget* parent = nullptr)
        : QWidget(parent)
    {
    }

    virtual ~IArbitrageNodeView() = default;
};

} // namespace atradus


#endif // IARBITRAGENODEVIEW_H
