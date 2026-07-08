#ifndef ARBITAGENODEMODEL_H
#define ARBITAGENODEMODEL_H

#include "src/interface/IArbitrageNodeModel.h"
#include "../RequesterLib/src/common/Common.h"
#include <memory>

namespace rqs
{
class IRequester;
}

namespace atradus
{

class ArbitageNodeModel : public IArbitrageNodeModel
{
    Q_OBJECT
public:
    ArbitageNodeModel(const std::vector<std::shared_ptr<rqs::IRequester>>& requesters,
                      QObject* parent = nullptr);

    NodeType type() const override;
    const QStringList& info() const override;
    bool isActive() const override;
    void switchState() override;
    void run() override;
    void start() override;
    void stop() override;

    const QStringList& log() const override;
    void setRequestedCurrencies(const std::vector<rqs::CoinSymbol>& currencies) override;
    void setMarketAccounts(const std::vector<rqs::MarketAccount>& accounts) override;
    void setSpredRange(double minSpred, double maxSpred) override;

protected:
    void timerEvent(QTimerEvent* event) override;

private:
    bool process();
    void setIsActive(bool isActive);
    void setInfo(const QStringList& info);
    void updateInfo();
    void toLog(const QString& info);

private:
    std::vector<std::shared_ptr<rqs::IRequester>> m_requesters;
    QStringList m_info;
    QStringList m_log;
    bool m_isActive{false};
    std::vector<rqs::CoinSymbol> m_requestedCurrencies;
    std::vector<rqs::MarketAccount> m_accounts;
    std::map<int, std::map<rqs::CoinSymbol, double>> m_marketsPrices;
    int m_requestNumber{0};
    double m_minSpred{0};
    double m_maxSpred{1000};
};

} //namespace atradus
#endif // ARBITAGENODEMODEL_H
