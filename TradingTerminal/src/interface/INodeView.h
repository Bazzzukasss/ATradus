#ifndef INODEVIEW_H
#define INODEVIEW_H

#include <QWidget>

namespace atradus
{

class INodeModel;

class INodeView : public QWidget
{
    Q_OBJECT
public:
    INodeView(QWidget* parent = nullptr)
        : QWidget(parent)
    {
    }

    virtual ~INodeView() = default;

    virtual void resetModel(INodeModel* model) = 0;
};

} // namespace atradus

#endif // INODEVIEW_H
