#include "MainWindow.h"
#include "src/view/ApplicationView.h"
#include "src/model/ApplicationModel.h"
#include "src/service/ModelFactory.h"
#include "src/service/ViewFactory.h"
#include <QVBoxLayout>

namespace atradus
{

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    auto viewFactory = new ViewFactory(this);
    auto modelFactory = new ModelFactory(this);

    auto appModel = modelFactory->createApplicationModel(this);
    auto appView = viewFactory->createApplicationView(appModel, this);

    auto mainWidget = new QWidget(this);
    setCentralWidget(mainWidget);

    auto mainLayout = new QVBoxLayout();
    mainWidget->setLayout(mainLayout);

    mainLayout->addWidget(appView);
}

} // namespace atradus
