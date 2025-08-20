#include "MainWindow.h"
#include "../RequesterLib/src/Builder.h"
#include "src/view/ApplicationView.h"
#include "src/model/ApplicationModel.h"
#include "src/service/ModelFactory.h"
#include "src/service/ViewFactory.h"
#include <QVBoxLayout>

namespace atradus
{

const rqs::CurrencyTrinity SOLBTC{{rqs::CurrencyType::SOL, rqs::CurrencyType::USDT},
                                  {rqs::CurrencyType::BTC, rqs::CurrencyType::USDT},
                                  {rqs::CurrencyType::SOL, rqs::CurrencyType::BTC}};

const rqs::CurrencyTrinity ETHBTC{{rqs::CurrencyType::ETH, rqs::CurrencyType::USDT},
                                  {rqs::CurrencyType::BTC, rqs::CurrencyType::USDT},
                                  {rqs::CurrencyType::ETH, rqs::CurrencyType::BTC}};

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    auto builder = std::make_unique<rqs::Builder>();
    auto viewFactory = new ViewFactory(this);
    auto modelFactory = new ModelFactory(std::move(builder), this);

    auto appModel = modelFactory->createApplicationModel(this);
    appModel->addArbitrageNode(MarketType::Binance, {SOLBTC, ETHBTC});

    auto appView = viewFactory->createApplicationView(appModel, this);

    auto mainWidget = new QWidget(this);
    setCentralWidget(mainWidget);

    auto mainLayout = new QVBoxLayout();
    mainWidget->setLayout(mainLayout);

    mainLayout->addWidget(appView);

    appModel->selectNode(0);
}

} // namespace atradus
