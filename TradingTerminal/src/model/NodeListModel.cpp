#include "src/model/NodeListModel.h"
#include "src/interface/INodeModel.h"

namespace atradus
{

NodeListModel::NodeListModel(QObject *parent)
    : INodeListModel(parent)
{
}

void NodeListModel::addNode(INodeModel* nodeModel)
{
    beginResetModel();
    m_nodeModels.push_back(nodeModel);
    connect(nodeModel, &INodeModel::infoChanged,
            this, [&](){ emit dataChanged({},{}); });
    endResetModel();
}

void NodeListModel::deleteNode(INodeModel *nodeModel)
{
    beginResetModel();
    m_nodeModels.removeOne(nodeModel);
    endResetModel();
}

INodeModel* NodeListModel::getNode(const int number)
{
    return number < m_nodeModels.size() ? m_nodeModels.at(number)
                                        : nullptr;
}

int NodeListModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : m_nodeModels.size();
}

int NodeListModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 3;
}

QVariant NodeListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    if (role == Qt::DisplayRole)
    {
        return m_nodeModels[index.row()]->info().at(index.column());
    }
    return QVariant();
}

QModelIndex NodeListModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent) || parent.isValid())
    {
        return QModelIndex();
    }

    return createIndex(row, column);
}

QModelIndex NodeListModel::parent(const QModelIndex &index) const
{
    Q_UNUSED(index)
    return QModelIndex();
}

} // namespace atradus
