#include "ArbitageNodeModel.h"
#include "../RequesterLib/src/interface/IRequester.h"

namespace atradus
{

ArbitageNodeModel::ArbitageNodeModel(std::unique_ptr<rqs::IRequester> requester,
                                     QObject* parent)
    : INodeModel(parent)
    , m_requester(std::move(requester))
{
}

bool atradus::ArbitageNodeModel::run()
{
    return true;
}

bool atradus::ArbitageNodeModel::process(const std::map<rqs::CurrencyPair, double> &prices)
{
    return true;
}

} // namespace atradus
