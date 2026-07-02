#ifndef TRIANGLEARBITAGENODEMODEL_H
#define TRIANGLEARBITAGENODEMODEL_H

#include "src/interface/ITriangleArbitrageNodeModel.h"
#include "../RequesterLib/src/common/Common.h"
#include <memory>

namespace rqs
{
class IRequester;
}

namespace atradus
{

class TriangleArbitrageNodeModel : public ITriangleArbitrageNodeModel
{
    Q_OBJECT
public:
    TriangleArbitrageNodeModel(std::shared_ptr<rqs::IRequester> requester,
                      QObject* parent = nullptr);

    NodeType type() const override;
    const QStringList& info() const override;
    bool isActive() const override;
    void switchState() override;
    void run() override;
    void start() override;
    void stop() override;

    const QStringList& log() const override;
    void setRequestedCurrencies(const std::vector<rqs::CurrencyTrinity>& currencies) override;
    void setMarketAccount(const rqs::MarketAccount& account) override;

protected:
    void timerEvent(QTimerEvent* event) override;

private:
    bool process(const rqs::CurrencyTrinity& currencyTrinity, const std::map<rqs::CurrencyPair, double>& prices);
    void setIsActive(bool isActive);
    void setInfo(const QStringList& info);
    void updateInfo();
    void toLog(const QString& info);

private:
    std::shared_ptr<rqs::IRequester> m_requester{nullptr};
    QStringList m_info;
    QStringList m_log;
    bool m_isActive{false};
    std::vector<rqs::CurrencyTrinity> m_requestedCurrencies;
    rqs::MarketAccount m_account;
};

} //namespace atradus
#endif // TRIANGLEARBITAGENODEMODEL_H
