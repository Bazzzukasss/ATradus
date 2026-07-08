#include "ArbitageNodeModel.h"
#include "../RequesterLib/src/interface/IRequester.h"
#include "../RequesterLib/src/common/Common.h"
#include "../RequesterLib/src/common/Utils.h"
#include "src/common/Utils.h"
#include <string>
#include <QDebug>

namespace atradus
{

ArbitageNodeModel::ArbitageNodeModel(const std::vector<std::shared_ptr<rqs::IRequester>>& requesters,
                                     QObject* parent)
    : IArbitrageNodeModel(parent)
    , m_requesters(requesters)
{
    updateInfo();
}

bool ArbitageNodeModel::process()
{
    std::map<rqs::CoinSymbol, std::vector<double>> coinSymbolsPrices;

    for(int i = 0; i < m_requesters.size(); ++i)
    {
        //QString currencyInfo = QString("MARKET %1\n----------\n").arg(i);
        const auto& marketPrices = m_marketsPrices.at(i);

        for(const auto& [coinSymbol, price] : marketPrices)
        {
            if (coinSymbol.find("USDT") != std::string::npos)
            {
                coinSymbolsPrices[coinSymbol].push_back(price);
                //currencyInfo += QString("%1 : %2\n").arg(coinSymbol).arg(price);
            }
        }

        //info += currencyInfo + "\n";
    }

    QString info;
    for(const auto& [coinSymbol, prices] : coinSymbolsPrices)
    {
        if (prices.size() < m_requesters.size())
        {
            continue;
        }

        QString pricesInfo;
        for(const auto& price : prices)
        {
            pricesInfo += QString("%1\t").arg(price);
        }

        auto p0 = prices.at(0);
        auto p1 = prices.at(1);
        auto spred_prs = abs(p0 - p1) * 100 / qMin(p0, p1) ;

        if (spred_prs < m_minSpred || spred_prs > m_maxSpred)
        {
            continue;
        }

        info += QString("%1\t:\t%2\t[%3\%]\n").arg(coinSymbol).arg(pricesInfo).arg(spred_prs);
    }

    if (!info.isEmpty())
    {
        info = QString("[%1]========\n%2").arg(m_requestNumber).arg(info);
        toLog(info);
    }

    m_requestNumber++;

    return true;
}

void ArbitageNodeModel::setSpredRange(double minSpred, double maxSpred)
{
    m_minSpred = minSpred;
    m_maxSpred = maxSpred;
}

void ArbitageNodeModel::run()
{
    int i{0};
    m_marketsPrices.clear();
    for(const auto& requester : m_requesters)
    {
        requester->requestPrices(m_requestedCurrencies,
                                [=](const std::map<rqs::CoinSymbol, double>& prices){
                                     m_marketsPrices.insert({i, prices});
                                     if (m_marketsPrices.size() == m_requesters.size())
                                     {
                                         process();
                                     }
                                });
        i++;
    }
}

void ArbitageNodeModel::timerEvent(QTimerEvent* event)
{
    if (m_isActive)
    {
        run();
    }

    QObject::timerEvent(event);
}

NodeType ArbitageNodeModel::type() const
{
    return NodeType::Arbitrage;
}

void ArbitageNodeModel::updateInfo()
{
    QStringList info;
    info << QString::fromStdString(utils::toString(type()));
    info << "request data";
    info << QString(m_isActive ? "Active" : "Not active");

    setInfo(info);
}

const QStringList& ArbitageNodeModel::info() const
{
    return m_info;
}

void ArbitageNodeModel::setInfo(const QStringList& info)
{
    if (m_info != info)
    {
        m_info = info;
        emit infoChanged(info);
    }
}

const QStringList& ArbitageNodeModel::log() const
{
    return m_log;
}

void ArbitageNodeModel::setRequestedCurrencies(const std::vector<rqs::CoinSymbol>& currencies)
{
    m_requestedCurrencies = currencies;
}

void ArbitageNodeModel::setMarketAccounts(const std::vector<rqs::MarketAccount>& accounts)
{
    if (accounts.size() != m_requesters.size())
    {
        qDebug()<<"setMarketAccounts failed: accounts.size() != m_requesters.size()";
        return;
    }

    m_accounts = accounts;
    for(int i = 0; i < accounts.size(); ++i)
    {
        m_requesters.at(i)->setMarketAccount(accounts.at(i));
    }

}

void ArbitageNodeModel::toLog(const QString& info)
{
    m_log << info;

    emit logChanged(m_log);
    emit logUpdated(info);
}

bool ArbitageNodeModel::isActive() const
{
    return m_isActive;
}

void ArbitageNodeModel::switchState()
{
    if(m_isActive)
    {
        stop();
    }
    else
    {
        start();
    }
}

void ArbitageNodeModel::setIsActive(bool isActive)
{
    if (m_isActive != isActive)
    {
        m_isActive = isActive;
        emit isActiveChanged(isActive);
    }
}

void ArbitageNodeModel::start()
{
    m_requestNumber = 0;
    setIsActive(true);
    updateInfo();
    startTimer(5000);
}

void ArbitageNodeModel::stop()
{
    setIsActive(false);
    updateInfo();
}

} // namespace atradus
