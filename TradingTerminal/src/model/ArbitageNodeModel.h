#ifndef ARBITAGENODEMODEL_H
#define ARBITAGENODEMODEL_H

#include "src/interface/INodeModel.h"
#include "../RequesterLib/src/common/Common.h"
#include <memory>

namespace rqs
{
class IRequester;
}

namespace atradus
{

class ArbitageNodeModel : public INodeModel
{
    Q_OBJECT
public:
    ArbitageNodeModel(std::unique_ptr<rqs::IRequester> requester,
                      QObject* parent = nullptr);

    bool run() override;

private:
    bool process(const std::map<rqs::CurrencyPair, double>& prices);

private:
    std::unique_ptr<rqs::IRequester> m_requester{nullptr};
};

} //namespace atradus
#endif // ARBITAGENODEMODEL_H
