#include "src/view/ArbitrageNodeView.h"

namespace atradus
{

ArbitrageNodeView::ArbitrageNodeView(IArbitrageNodeModel* model, QWidget* parent)
    : IArbitrageNodeView(parent)
    , m_model(model)
{}

}
