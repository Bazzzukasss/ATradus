#ifndef MODELFACTORY_H
#define MODELFACTORY_H

#include "src/interface/IModelFactory.h"
#include <memory>

namespace rqs
{
class IBuilder;
class IRequester;
}

namespace atradus
{

class ModelFactory : public IModelFactory
{
    Q_OBJECT
public:
    ModelFactory(std::unique_ptr<rqs::IBuilder> builder, QObject* parent = nullptr);

    INodeModel* createNodeModel(const NodeType& nodeType, const MarketType& marketType, QObject* parent = nullptr) override;
    IApplicationModel* createApplicationModel(QObject* parent = nullptr) override;
    INodeListModel* createNodeListModel(QObject* parent = nullptr) override;
    IArbitrageNodeModel* createArbitrageNodeModel(const MarketType& marketType, QObject* parent = nullptr) override;

private:
    std::unique_ptr<rqs::IRequester> createRequester(const MarketType& marketType) const;

private:
    std::unique_ptr<rqs::IBuilder> m_builder{nullptr};
};

} // namespace atradus

#endif // MODELFACTORY_H
