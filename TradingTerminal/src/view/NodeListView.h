#ifndef NODELISTVIEW_H
#define NODELISTVIEW_H

#include "src/interface/INodeListView.h"

namespace atradus
{

class INodeListModel;

class NodeListView : public INodeListView
{
    Q_OBJECT
public:
    NodeListView(INodeListModel* model, QWidget* parent = nullptr);
};

} // namespace atradus

#endif // NODELISTVIEW_H
