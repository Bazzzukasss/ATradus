#include "src/view/NodeListView.h"
#include "src/interface/INodeListModel.h"
#include <QHeaderView>

namespace atradus
{

NodeListView::NodeListView(INodeListModel* model, QWidget* parent)
    : INodeListView(parent)
{
    setModel(model);
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    horizontalHeader()->hide();
}

} // namespace atradus
