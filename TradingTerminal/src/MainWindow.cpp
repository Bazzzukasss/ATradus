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
const rqs::MarketAccount ByBitTestAccount{"https://testnet.bybit.vision", "", "", 0.075};
const rqs::MarketAccount BinanceAccount{"https://api.binance.com", "", "", 0.075};
const rqs::MarketAccount ByBitAccount{"https://api.bybit.com", "", "", 0.075};

const rqs::CoinTrinity SOLBTC{"BTC", "SOL", "USDT"};
const rqs::CoinTrinity ETHBTC{"BTC", "ETH", "USDT"};
const rqs::CoinTrinity LINKETH{"ETH", "LINK", "USDT"};
const rqs::CoinTrinity LINKBTC{"BTC", "LINK", "USDT"};
const rqs::CoinTrinity BNBBTC{"BTC", "BNB", "USDT"};
const rqs::CoinTrinity BNBETH{"ETH", "BNB", "USDT"};
const rqs::CoinTrinity BNBSOL{"BNB", "SOL", "USDT"};

const std::vector<rqs::CoinTrinity> ArbitrageTrinities {
    BNBBTC, BNBETH, BNBSOL
};

const std::vector<rqs::CoinSymbol> ArbitrageCurencies {
    //"VANRYUSDT",
    //"BTCUSDT",
    //"ETHUSDT"
};

const std::vector<MarketType> ArbitrageMarkets {
    MarketType::Binance, MarketType::ByBit
};

const std::vector<rqs::MarketAccount> ArbitrageAccounts {
    BinanceAccount, ByBitAccount
};

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    auto builder = std::make_unique<rqs::Builder>();
    auto viewFactory = new ViewFactory(this);
    auto modelFactory = new ModelFactory(std::move(builder), this);

    auto appModel = modelFactory->createApplicationModel(this);
    appModel->addArbitrageNode(ArbitrageMarkets,
                               ArbitrageCurencies,
                               ArbitrageAccounts);
    //appModel->addTriangleArbitrageNode(MarketType::Binance,
    //                                   ArbitrageTrinities,
    //                                   BinanceAccount);

    auto appView = viewFactory->createApplicationView(appModel, this);

    auto mainWidget = new QWidget(this);
    setCentralWidget(mainWidget);

    auto mainLayout = new QVBoxLayout();
    mainWidget->setLayout(mainLayout);

    mainLayout->addWidget(appView);

    appModel->selectNode(0);
    setMinimumSize({1200, 800});
}

} // namespace atradus
