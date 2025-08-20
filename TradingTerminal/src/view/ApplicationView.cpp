#include "src/view/ApplicationView.h"
#include "src/view/NodeView.h"
#include "src/view/NodeListView.h"
#include "src/interface/IApplicationModel.h"
#include "src/interface/INodeListModel.h"
#include "src/interface/IViewFactory.h"

#include <QVBoxLayout>


namespace atradus
{

ApplicationView::ApplicationView(IApplicationModel* model,
                                 IViewFactory* factory,
                                 QWidget* parent)
    : IApplicationView(parent)
    , m_model(model)
    , m_factory(factory)
{
    m_nodeListView = m_factory->createNodeListView(model->nodeListModel(), this);
    m_nodeListView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_nodeView = m_factory->createNodeView(nullptr, this);
    m_nodeView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    auto mainlayout = new QVBoxLayout();
    mainlayout->addWidget(m_nodeView, 3);
    mainlayout->addWidget(m_nodeListView, 1);
    setLayout(mainlayout);

    connect(model, &IApplicationModel::selectedNodeChanged,
            this, &ApplicationView::onNodeSelected);

    connect(m_nodeListView->selectionModel(), &QItemSelectionModel::currentRowChanged,
            this, [=](const QModelIndex& current, const QModelIndex& previous){
        model->selectNode(current.row());
    });
}

void ApplicationView::onNodeSelected(INodeModel* nodeModel)
{
    m_nodeView->resetModel(nodeModel);
}

} // namespace atradus
