#ifndef INODELISTVIEW_H
#define INODELISTVIEW_H

#include <QTableView>

namespace atradus
{

class INodeListView : public QTableView
{
public:
    INodeListView(QWidget* parent = nullptr)
        : QTableView(parent)
    {
    }

    virtual ~INodeListView() = default;
};

} // namespace atradus


#endif // INODELISTVIEW_H
