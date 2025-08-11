#ifndef APPLICATIONVIEW_H
#define APPLICATIONVIEW_H

#include "src/interface/IApplicationView.h"

namespace atradus
{

class ApplicationView : public IApplicationView
{
public:
    explicit ApplicationView(QObject* parent = nullptr);
};

} // namespace atradus

#endif // APPLICATIONVIEW_H
