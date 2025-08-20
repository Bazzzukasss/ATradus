#ifndef TRADINGTERMINAL_UTILS_H
#define TRADINGTERMINAL_UTILS_H


#include "src/common/Common.h"

#include <string>

namespace atradus
{
namespace utils
{

std::string toString(const NodeType& nodeType);
double calculateCurrencyVolume(double price_usdt, double volume_usdt, double commision_prs);

} //namspace utils
} //namspace atradus

#endif // TRADINGTERMINAL_UTILS_H
