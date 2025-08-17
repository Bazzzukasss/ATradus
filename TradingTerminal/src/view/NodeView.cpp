#include "src/view/NodeView.h"
#include "src/interface/IViewFactory.h"
#include "src/interface/INodeModel.h"
#include "src/interface/IArbitrageNodeModel.h"
#include "src/interface/IArbitrageNodeView.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

namespace atradus
{

NodeView::NodeView(INodeModel* model, IViewFactory* factory, QWidget* parent)
    : INodeView(parent)
    , m_model(model)
    , m_factory(factory)
{
    setLayout(new QVBoxLayout());
    layout()->setContentsMargins(0, 0, 0, 0);

    if (m_model)
    {
        initialize();
    }
}

void NodeView::resetModel(INodeModel* model)
{
    if (m_model != model)
    {
        m_model = model;
        initialize();
    }
}

void NodeView::initialize()
{
    if (m_infoView)
    {
        m_infoView->deleteLater();
        layout()->removeWidget(m_infoView);
    }

    if (m_nodeView)
    {
        m_nodeView->deleteLater();
        layout()->removeWidget(m_nodeView);
    }

    if (m_button)
    {
        m_button->deleteLater();
        layout()->removeWidget(m_button);
    }

    m_infoView = new QLabel(this);
    m_infoView->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    m_button = new QPushButton(this);

    m_nodeView = createView(m_model);
    m_nodeView->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    m_nodeView->setFocus();

    layout()->addWidget(m_infoView);
    layout()->addWidget(m_nodeView);
    layout()->addWidget(m_button);

    connect(m_model, &INodeModel::infoChanged, this, &NodeView::onInfoChanged);
    connect(m_model, &INodeModel::isActiveChanged, this, &NodeView::onIsActiveChanged);
    connect(m_button, &QPushButton::clicked, m_model, &INodeModel::switchState);

    onInfoChanged(m_model->info());
    onIsActiveChanged(m_model->isActive());
}

QWidget* NodeView::createView(INodeModel* model)
{
    switch(model->type())
    {
    case NodeType::Arbitrage:
        return m_factory->createArbitrageNodeView(dynamic_cast<IArbitrageNodeModel*>(model), this);
        break;
    default:
        break;
    }

    return new QWidget(this);
}

void NodeView::onIsActiveChanged(bool isActive)
{
    m_button->setText(isActive ? "Active" : "Not active");
}

void NodeView::onInfoChanged(const QStringList& info)
{
    QString text;
    for(const auto& str : m_model->info())
    {
        text += str + "\n";
    }

    m_infoView->setText(text);
}

}
