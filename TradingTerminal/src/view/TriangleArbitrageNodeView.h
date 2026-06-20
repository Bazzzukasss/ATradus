#ifndef TRIANGLEARBITRAGENODEVIEW_H
#define TRIANGLEARBITRAGENODEVIEW_H

#include "src/interface/ITriangleArbitrageNodeView.h"

class QTextEdit;

namespace atradus
{

class ITriangleArbitrageNodeModel;

class TriangleArbitrageNodeView : public ITriangleArbitrageNodeView
{
    Q_OBJECT
public:
    TriangleArbitrageNodeView(ITriangleArbitrageNodeModel* model, QWidget* parent = nullptr);

    void setModel(ITriangleArbitrageNodeModel* model);

private:
    void initialize();
    void onLogChanged(const QStringList& list);
    void onLogUpdated(const QString& info);

private:
    ITriangleArbitrageNodeModel* m_model{nullptr};
    QTextEdit* m_textEdit;
};

} // namespace atradus

#endif // TRIANGLEARBITRAGENODEVIEW_H
