#ifndef ARBITRAGENODEVIEW_H
#define ARBITRAGENODEVIEW_H

#include "src/interface/IArbitrageNodeView.h"

class QTextEdit;

namespace atradus
{

class IArbitrageNodeModel;

class ArbitrageNodeView : public IArbitrageNodeView
{
    Q_OBJECT
public:
    ArbitrageNodeView(IArbitrageNodeModel* model, QWidget* parent = nullptr);

    void setModel(IArbitrageNodeModel* model);

private:
    void initialize();
    void onLogChanged(const QStringList& list);

private:
    IArbitrageNodeModel* m_model{nullptr};
    QTextEdit* m_textEdit;
};

} // namespace atradus

#endif // ARBITRAGENODEVIEW_H
