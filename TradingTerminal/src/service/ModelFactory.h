#ifndef MODELFACTORY_H
#define MODELFACTORY_H

#include "src/interface/IModelFactory.h"
#include <memory>

namespace rqs
{
class IBuilder;

}

namespace atradus
{

class ModelFactory : public IModelFactory
{
    Q_OBJECT
public:
    ModelFactory(QObject* parent = nullptr);

    INodeModel* createNodeModel(const NodeType& nodeType, const MarketType& marketType) override;
    IApplicationModel* createApplicationModel() override;

private:
    std::unique_ptr<rqs::IBuilder> m_builder{nullptr};
};

} // namespace atradus

#endif // MODELFACTORY_H
