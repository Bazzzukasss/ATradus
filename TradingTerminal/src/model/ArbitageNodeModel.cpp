#include "ArbitageNodeModel.h"
#include "../RequesterLib/src/interface/IRequester.h"
#include "../RequesterLib/src/common/Common.h"
#include "../RequesterLib/src/common/Utils.h"
#include "src/common/Utils.h"
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
    QString info("===============\n");
    for(int i = 0; i < m_requesters.size(); ++i)
    {
        QString currencyInfo = QString("MARKET %1\n----------\n").arg(i);
        const auto& marketPrices = m_marketsPrices.at(i);

        for(const auto& currencies : marketPrices)
        {
            currencyInfo += QString("%1 : %2\n").arg(currencies.first).arg(currencies.second);
        }

        info += currencyInfo + "\n";
    }
/*
    for(const auto& currency : m_requestedCurrencies)
    {
        QString currencyInfo =
            QString("%1\t").arg(rqs::utils::toString(currency.first));

        for(int i = 0; i < m_requesters.size(); ++i)
        {
            const auto& marketPrices = m_marketsPrices.at(i);
            const auto& currencyPrice = marketPrices.at(currency);
            currencyInfo += QString("%1\t").arg(currencyPrice);
        }

        info += currencyInfo + "\n";
    }
*/
    toLog(info);

    return true;
}

void ArbitageNodeModel::run()
{
    int i{0};
    m_marketsPrices.clear();
    for(const auto& requester : m_requesters)
    {
        requester->requestPrices(m_requestedCurrencies,
                                [=](const std::map<rqs::CurrencySymbol, double>& prices){
                                     m_marketsPrices.insert({i, prices});
                                     //qDebug()<<prices.size()<<m_marketsPrices.size()<< m_requesters.size();
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
        stop();
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

void ArbitageNodeModel::setRequestedCurrencies(const std::vector<rqs::CurrencySymbol>& currencies)
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
    setIsActive(true);
    updateInfo();
    startTimer(1000);
}

void ArbitageNodeModel::stop()
{
    setIsActive(false);
    updateInfo();
}

} // namespace atradus
