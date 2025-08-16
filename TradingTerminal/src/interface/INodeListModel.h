#ifndef INODELISTMODEL_H
#define INODELISTMODEL_H

#include <QAbstractListModel>

namespace atradus
{

class INodeModel;

class INodeListModel : public QAbstractItemModel
{
public:
    INodeListModel(QObject* parent = nullptr)
        :QAbstractItemModel(parent)
    {}

    virtual void addNode(INodeModel* nodeModel) = 0;
    virtual void deleteNode(INodeModel* nodeModel) = 0;
    virtual INodeModel* getNode(const int number) = 0;
};

} // namespace atradus

#endif // INODELISTMODEL_H
