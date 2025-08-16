#ifndef ARBITRAGENODEVIEW_H
#define ARBITRAGENODEVIEW_H

#include "src/interface/IArbitrageNodeView.h"

namespace atradus
{

class IArbitrageNodeModel;

class ArbitrageNodeView : public IArbitrageNodeView
{
    Q_OBJECT
public:
    ArbitrageNodeView(IArbitrageNodeModel* model, QWidget* parent = nullptr);

private:
    IArbitrageNodeModel* m_model{nullptr};
};

} // namespace atradus

#endif // ARBITRAGENODEVIEW_H
