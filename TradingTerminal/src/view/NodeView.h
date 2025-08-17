#ifndef NODEVIEW_H
#define NODEVIEW_H

#include "src/interface/INodeView.h"

class QLabel;
class QPushButton;

namespace atradus
{

class INodeModel;
class IViewFactory;

class NodeView : public INodeView
{
    Q_OBJECT
public:
    NodeView(INodeModel* model, IViewFactory* factory, QWidget* parent = nullptr);

    void resetModel(INodeModel* model) override;

private:
    void initialize();
    QWidget* createView(INodeModel* model);
    void onInfoChanged(const QStringList& info);
    void onIsActiveChanged(bool isActive);

private:
    INodeModel* m_model{nullptr};
    IViewFactory* m_factory{nullptr};
    QLabel* m_infoView{nullptr};
    QWidget* m_nodeView{nullptr};
    QPushButton* m_button{nullptr};
};

} // namespace atradus


#endif // NODEVIEW_H
