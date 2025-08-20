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
const rqs::CurrencyTrinity SOLBTC{{rqs::CurrencyType::BTC, rqs::CurrencyType::USDT},
                                  {rqs::CurrencyType::SOL, rqs::CurrencyType::USDT},
                                  {rqs::CurrencyType::SOL, rqs::CurrencyType::BTC}};

const rqs::CurrencyTrinity ETHBTC{{rqs::CurrencyType::BTC, rqs::CurrencyType::USDT},
                                  {rqs::CurrencyType::ETH, rqs::CurrencyType::USDT},
                                  {rqs::CurrencyType::ETH, rqs::CurrencyType::BTC}};

const rqs::CurrencyTrinity LINKETH{{rqs::CurrencyType::ETH, rqs::CurrencyType::USDT},
                                   {rqs::CurrencyType::LINK, rqs::CurrencyType::USDT},
                                   {rqs::CurrencyType::LINK, rqs::CurrencyType::ETH}};

const rqs::CurrencyTrinity LINKBTC{{rqs::CurrencyType::BTC, rqs::CurrencyType::USDT},
                                   {rqs::CurrencyType::LINK, rqs::CurrencyType::USDT},
                                   {rqs::CurrencyType::LINK, rqs::CurrencyType::BTC}};
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    auto builder = std::make_unique<rqs::Builder>();
    auto viewFactory = new ViewFactory(this);
    auto modelFactory = new ModelFactory(std::move(builder), this);

    auto appModel = modelFactory->createApplicationModel(this);
    appModel->addArbitrageNode(MarketType::Binance, {LINKBTC});

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
