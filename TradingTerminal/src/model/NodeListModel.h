#ifndef NODELISTMODEL_H
#define NODELISTMODEL_H

#include "src/interface/INodeListModel.h"

namespace atradus
{

class INodeModel;

class NodeListModel : public INodeListModel
{
    Q_OBJECT
public:
    NodeListModel(QObject* parent = nullptr);

    void addNode(INodeModel* nodeModel) override;
    void deleteNode(INodeModel* nodeModel) override;
    INodeModel* getNode(const int number) override;

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &index) const override;

private:
    QList<INodeModel*> m_nodeModels;
};

} // namespace atradus

#endif // COMPONENTLISTMODEL_H
