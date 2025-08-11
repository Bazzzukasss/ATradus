#ifndef ARBITRAGENODEVIEW_H
#define ARBITRAGENODEVIEW_H

#include "src/interface/INodeView.h"

namespace atradus
{

class ArbitrageNodeView : public INodeView
{
public:
    ArbitrageNodeView(QObject* parent = nullptr);
};

} // namespace atradus

#endif // ARBITRAGENODEVIEW_H
