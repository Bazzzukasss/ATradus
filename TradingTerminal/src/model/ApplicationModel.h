#ifndef APPLICATIONMODEL_H
#define APPLICATIONMODEL_H

#include "src/interface/IApplicationModel.h"

namespace atradus
{

class INodeModel;
class IModelFactory;
class INodeListModel;
class IArbitrageNodeModel;
class ITriangleArbitrageNodeModel;

class ApplicationModel : public IApplicationModel
{
    Q_OBJECT
public:
    ApplicationModel(IModelFactory* factory, QObject* parent = nullptr);

    IArbitrageNodeModel* addArbitrageNode(const std::vector<MarketType>& marketTypes, const std::vector<rqs::CoinSymbol>& currencies, const std::vector<rqs::MarketAccount> &marketAccounts) override;
    ITriangleArbitrageNodeModel* addTriangleArbitrageNode(const MarketType& marketType, const std::vector<rqs::CoinTrinity>& currencies, const rqs::MarketAccount& marketAccount) override;
    INodeListModel* nodeListModel() const override;
    void selectNode(int i) override;
    INodeModel* selectedNode() const override;

private:
    void addNode(INodeModel* nodeModel);
    void removeNode(INodeModel* nodeModel);

private:
    INodeListModel* m_nodeListModel{nullptr};
    IModelFactory* m_factory{nullptr};
    INodeModel* m_selectedNode{nullptr};
    rqs::MarketAccount m_account;
};

} // namespace atradus

#endif // APPLICATIONMODEL_H
