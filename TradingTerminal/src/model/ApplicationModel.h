#ifndef APPLICATIONMODEL_H
#define APPLICATIONMODEL_H

#include "src/interface/IApplicationModel.h"

namespace atradus
{

class INodeModel;
class IModelFactory;
class INodeListModel;
class IArbitrageNodeModel;

class ApplicationModel : public IApplicationModel
{
    Q_OBJECT
public:
    ApplicationModel(IModelFactory* factory, QObject* parent = nullptr);

    IArbitrageNodeModel* addArbitrageNode(const MarketType& marketType, const QVector<rqs::CurrencyTrinity>& currencies) override;
    INodeModel* addNode(const NodeType& nodeType, const MarketType& marketType) override;
    INodeListModel* nodeListModel() const override;
    void selectNode(int i) override;

private:
    void addNode(INodeModel* nodeModel);
    void removeNode(INodeModel* nodeModel);

private:
    INodeListModel* m_nodeListModel;
    IModelFactory* m_factory;
};

} // namespace atradus

#endif // APPLICATIONMODEL_H
