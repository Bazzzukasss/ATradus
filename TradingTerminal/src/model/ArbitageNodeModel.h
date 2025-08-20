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
    ArbitageNodeModel(std::unique_ptr<rqs::IRequester> requester,
                      QObject* parent = nullptr);

    NodeType type() const override;
    const QStringList& info() const override;
    bool isActive() const override;
    void switchState() override;
    void run() override;
    void start() override;
    void stop() override;

    const QStringList& log() const override;
    void setRequestedCurrencies(const QVector<rqs::CurrencyTrinity>& currencies) override;

protected:
    void timerEvent(QTimerEvent* event) override;

private:
    bool process(const rqs::CurrencyTrinity& currencyTrinity, const std::map<rqs::CurrencyPair, double>& prices);
    void setIsActive(bool isActive);
    void setInfo(const QStringList& info);
    void updateInfo();
    void toLog(const QString& info);

private:
    std::unique_ptr<rqs::IRequester> m_requester{nullptr};
    QStringList m_info;
    QStringList m_log;
    bool m_isActive{false};
    QVector<rqs::CurrencyTrinity> m_requestedCurrencies;
};

} //namespace atradus
#endif // ARBITAGENODEMODEL_H
