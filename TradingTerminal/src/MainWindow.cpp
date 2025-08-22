#include "MainWindow.h"
#include "../RequesterLib/src/Builder.h"
#include "src/view/ApplicationView.h"
#include "src/model/ApplicationModel.h"
#include "src/service/ModelFactory.h"
#include "src/service/ViewFactory.h"
#include <QVBoxLayout>

namespace atradus
{
const rqs::MarketAccount BinanceTestAccount{"https://testnet.binance.vision", "", "", 0.075};
const rqs::CurrencyTrinity SOLBTC{rqs::CurrencyType::BTC, rqs::CurrencyType::SOL};
const rqs::CurrencyTrinity ETHBTC{rqs::CurrencyType::BTC, rqs::CurrencyType::ETH};
const rqs::CurrencyTrinity LINKETH{rqs::CurrencyType::ETH, rqs::CurrencyType::LINK};
const rqs::CurrencyTrinity LINKBTC{rqs::CurrencyType::BTC, rqs::CurrencyType::LINK};
const rqs::CurrencyTrinity BNBBTC{rqs::CurrencyType::BTC, rqs::CurrencyType::BNB};
const rqs::CurrencyTrinity BNBETH{rqs::CurrencyType::ETH, rqs::CurrencyType::BNB};
const rqs::CurrencyTrinity BNBSOL{rqs::CurrencyType::BNB, rqs::CurrencyType::SOL};

const QVector<rqs::CurrencyTrinity> ArbitrageTrinities {
    BNBBTC, BNBETH, BNBSOL
};

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    auto builder = std::make_unique<rqs::Builder>();
    auto viewFactory = new ViewFactory(this);
    auto modelFactory = new ModelFactory(std::move(builder), this);

    auto appModel = modelFactory->createApplicationModel(this);
    appModel->addArbitrageNode(MarketType::Binance, ArbitrageTrinities);

    auto appView = viewFactory->createApplicationView(appModel, this);

    auto mainWidget = new QWidget(this);
    setCentralWidget(mainWidget);

    auto mainLayout = new QVBoxLayout();
    mainWidget->setLayout(mainLayout);

    mainLayout->addWidget(appView);

    appModel->selectNode(0);
    appModel->setMarketAccount(BinanceTestAccount);
    setMinimumSize({1200, 800});
}

} // namespace atradus
