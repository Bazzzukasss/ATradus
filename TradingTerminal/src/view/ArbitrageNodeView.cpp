#include "src/view/ArbitrageNodeView.h"
#include "src/interface/IArbitrageNodeModel.h"
#include <QTextEdit>
#include <QVBoxLayout>

namespace atradus
{

ArbitrageNodeView::ArbitrageNodeView(IArbitrageNodeModel* model, QWidget* parent)
    : IArbitrageNodeView(parent)
{
    m_textEdit = new QTextEdit(this);
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(m_textEdit);
    setLayout(mainLayout);

    setModel(model);
}

void ArbitrageNodeView::setModel(IArbitrageNodeModel* model)
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

void ArbitrageNodeView::initialize()
{
    connect(m_model, &IArbitrageNodeModel::logChanged,
            this, &ArbitrageNodeView::onLogChanged);

    onLogChanged(m_model->log());
}

void ArbitrageNodeView::onLogChanged(const QStringList& list)
{
    QString text;
    for(const auto& line : list)
    {
        text += line + "\n";
    }

    m_textEdit->setText(text);
}

}
