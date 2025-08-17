#ifndef APPLICATIONMODEL_H
#define APPLICATIONMODEL_H

#include "src/interface/IApplicationModel.h"

namespace atradus
{

class INodeModel;
class IModelFactory;
class INodeListModel;

class ApplicationModel : public IApplicationModel
{
    Q_OBJECT
public:
    ApplicationModel(QObject* parent = nullptr);

    INodeModel* addNode(const NodeType& nodeType, const MarketType& marketType) override;
    INodeListModel* nodeListModel() const override;

private:
    void addNode(INodeModel* nodeModel);
    void removeNode(INodeModel* nodeModel);

private:
    INodeListModel* m_nodeListModel;
    IModelFactory* m_factory;
};

} // namespace atradus

#endif // APPLICATIONMODEL_H
