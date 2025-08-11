#ifndef APPLICATIONMODEL_H
#define APPLICATIONMODEL_H

#include "src/interface/IApplicationModel.h"

namespace atradus
{

class INodeModel;

class ApplicationModel : public IApplicationModel
{
    Q_OBJECT
public:
    ApplicationModel(QObject* parent = nullptr);

private:
    QVector<INodeModel*> m_nodes;
};

} // namespace atradus

#endif // APPLICATIONMODEL_H
