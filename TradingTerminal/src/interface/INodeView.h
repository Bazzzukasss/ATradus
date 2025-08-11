#ifndef INODEVIEW_H
#define INODEVIEW_H

#include <QObject>

namespace atradus
{

class INodeView : public QObject
{
    Q_OBJECT
public:
    INodeView(QObject* parent = nullptr)
        : QObject(parent)
    {
    }

    virtual ~INodeView() = default;
};

} // namespace atradus

#endif // INODEVIEW_H
