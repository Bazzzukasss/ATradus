#include "src/view/TriangleArbitrageNodeView.h"
#include "src/interface/ITriangleArbitrageNodeModel.h"
#include <QTextEdit>
#include <QVBoxLayout>
#include <QScrollBar>

namespace atradus
{

TriangleArbitrageNodeView::TriangleArbitrageNodeView(ITriangleArbitrageNodeModel* model, QWidget* parent)
    : ITriangleArbitrageNodeView(parent)
{
    m_textEdit = new QTextEdit(this);
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(m_textEdit);
    setLayout(mainLayout);

    setModel(model);
}

void TriangleArbitrageNodeView::setModel(ITriangleArbitrageNodeModel* model)
{
    if (m_model != model)
    {
        if (m_model)
        {
            m_model->disconnect(this, nullptr, nullptr, nullptr);
            disconnect(m_model, nullptr, this, nullptr);
        }

        m_model = model;

        initialize();
    }
}

void TriangleArbitrageNodeView::initialize()
{
    connect(m_model, &ITriangleArbitrageNodeModel::logUpdated,
            this, &TriangleArbitrageNodeView::onLogUpdated);

    onLogChanged(m_model->log());
}

void TriangleArbitrageNodeView::onLogChanged(const QStringList& list)
{
    QString text;
    for(const auto& line : list)
    {
        text += line + "\n";
    }

    m_textEdit->setText(text);
    m_textEdit->verticalScrollBar()->setValue(m_textEdit->verticalScrollBar()->maximum());
}

void TriangleArbitrageNodeView::onLogUpdated(const QString& info)
{
    m_textEdit->append(info);
    m_textEdit->verticalScrollBar()->setValue(m_textEdit->verticalScrollBar()->maximum());
}

}
