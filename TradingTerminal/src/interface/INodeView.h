#ifndef INODEVIEW_H
#define INODEVIEW_H

#include <QWidget>

namespace atradus
{

class INodeView : public QWidget
{
public:
    INodeView(QWidget* parent = nullptr)
        : QWidget(parent)
    {
    }

    virtual ~INodeView() = default;
};

} // namespace atradus

#endif // INODEVIEW_H
