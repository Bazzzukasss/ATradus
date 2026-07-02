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

    toLog(info);
    /*
    static int i{0};
    QString info, info_c1_cb, info_c2_cb, info_c2_c1;
    double volume_usdt{1000};
    double price_c1_cb, price_c2_cb, price_c2_c1;

    info = QString("%1)").arg(i);

    for(const auto& [curPair, price] : prices)
    {
        if (curPair == currencyTrinity.c1_cb)
        {
            price_c1_cb = price;
            info_c1_cb = QString("\t[%1, %2] = %3")
                        .arg(rqs::utils::toString(curPair.first))
                        .arg(rqs::utils::toString(curPair.second))
                        .arg(price);
        }
        else if (curPair == currencyTrinity.c2_cb)
        {
            price_c2_cb = price;
            info_c2_cb = QString("\t[%1, %2] = %3")
                             .arg(rqs::utils::toString(curPair.first))
                             .arg(rqs::utils::toString(curPair.second))
                             .arg(price);
        }
        else if (curPair == currencyTrinity.c2_c1)
        {
            price_c2_c1 = price;
            info_c2_c1 = QString("\t[%1, %2] = %3")
                             .arg(rqs::utils::toString(curPair.first))
                             .arg(rqs::utils::toString(curPair.second))
                             .arg(price);
        }
    }

    auto volume_c1 = utils::calculateCurrencyVolume(price_c1_cb, volume_usdt, m_account.commision_prs);
    auto volume_c2 = utils::calculateCurrencyVolume(price_c2_c1, volume_c1, m_account.commision_prs);
    auto volume_cb = utils::calculateCurrencyVolume(1.0 / price_c2_cb, volume_c2, m_account.commision_prs);
    auto delta = volume_cb - volume_usdt;

    info += info_c1_cb + info_c2_cb +info_c2_c1;
    info += QString("\tRESULT = %1, %2, %3\t%4")
                .arg(volume_c1)
                .arg(volume_c2)
                .arg(volume_cb)
                .arg(delta);

    toLog(info);
    i++;
*/
    return true;
}

void ArbitageNodeModel::run()
{
    int i{0};
    m_marketsPrices.clear();
    for(const auto& requester : m_requesters)
    {
        requester->requestPrices(m_requestedCurrencies,
                                [=](const std::map<rqs::CurrencyPair, double>& prices){
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

void ArbitageNodeModel::setRequestedCurrencies(const std::vector<rqs::CurrencyPair>& currencies)
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
