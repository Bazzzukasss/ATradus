#include "ArbitageNodeModel.h"
#include "../RequesterLib/src/interface/IRequester.h"
#include <QDebug>

namespace atradus
{

ArbitageNodeModel::ArbitageNodeModel(std::unique_ptr<rqs::IRequester> requester,
                                     QObject* parent)
    : IArbitrageNodeModel(parent)
    , m_requester(std::move(requester))
{
    updateInfo();
}

void atradus::ArbitageNodeModel::run()
{
    static int i{0};
    QString info{"Request: " + QString::number(i++)};
    toLog(info);
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
    info << "Arbitrage";
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

void ArbitageNodeModel::toLog(const QString& info)
{
    m_log << info;
    qDebug() << info;
    emit logChanged(m_log);
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

bool atradus::ArbitageNodeModel::process(const std::map<rqs::CurrencyPair, double> &prices)
{
    return true;
}

} // namespace atradus
