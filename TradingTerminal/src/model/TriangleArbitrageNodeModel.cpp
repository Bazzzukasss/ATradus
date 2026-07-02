#include "TriangleArbitrageNodeModel.h"
#include "../RequesterLib/src/interface/IRequester.h"
#include "../RequesterLib/src/common/Common.h"
#include "../RequesterLib/src/common/Utils.h"
#include "src/common/Utils.h"
#include <QDebug>

namespace atradus
{

TriangleArbitrageNodeModel::TriangleArbitrageNodeModel(std::shared_ptr<rqs::IRequester> requester,
                                                       QObject* parent)
    : ITriangleArbitrageNodeModel(parent)
    , m_requester(std::move(requester))
{
    updateInfo();
}

bool TriangleArbitrageNodeModel::process(const rqs::CurrencyTrinity& currencyTrinity,
                                         const std::map<rqs::CurrencyPair, double>& prices)
{
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

    return true;
}

void TriangleArbitrageNodeModel::run()
{
    for( const auto& currencyTrinity : m_requestedCurrencies)
    {
        m_requester->requestPrices({
                                    currencyTrinity.c1_cb,
                                    currencyTrinity.c2_cb,
                                    currencyTrinity.c2_c1
                                   },
                                [=](const std::map<rqs::CurrencyPair, double>& prices){
                                       process(currencyTrinity, prices);
                                });
    }

}

void TriangleArbitrageNodeModel::timerEvent(QTimerEvent* event)
{
    if (m_isActive)
    {
        run();
    }

    QObject::timerEvent(event);
}

NodeType TriangleArbitrageNodeModel::type() const
{
    return NodeType::TriangleArbitrage;
}

void TriangleArbitrageNodeModel::updateInfo()
{
    QStringList info;
    info << QString::fromStdString(utils::toString(type()));
    info << "request data";
    info << QString(m_isActive ? "Active" : "Not active");

    setInfo(info);
}

const QStringList& TriangleArbitrageNodeModel::info() const
{
    return m_info;
}

void TriangleArbitrageNodeModel::setInfo(const QStringList& info)
{
    if (m_info != info)
    {
        m_info = info;
        emit infoChanged(info);
    }
}

const QStringList& TriangleArbitrageNodeModel::log() const
{
    return m_log;
}

void TriangleArbitrageNodeModel::setRequestedCurrencies(const std::vector<rqs::CurrencyTrinity>& currencies)
{
    m_requestedCurrencies = currencies;
}

void TriangleArbitrageNodeModel::setMarketAccount(const rqs::MarketAccount& account)
{
    m_account = account;
    m_requester->setMarketAccount(account);
}

void TriangleArbitrageNodeModel::toLog(const QString& info)
{
    m_log << info;

    emit logChanged(m_log);
    emit logUpdated(info);
}

bool TriangleArbitrageNodeModel::isActive() const
{
    return m_isActive;
}

void TriangleArbitrageNodeModel::switchState()
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

void TriangleArbitrageNodeModel::setIsActive(bool isActive)
{
    if (m_isActive != isActive)
    {
        m_isActive = isActive;
        emit isActiveChanged(isActive);
    }
}

void TriangleArbitrageNodeModel::start()
{
    setIsActive(true);
    updateInfo();
    startTimer(1000);
}

void TriangleArbitrageNodeModel::stop()
{
    setIsActive(false);
    updateInfo();
}

} // namespace atradus
