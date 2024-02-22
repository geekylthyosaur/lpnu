#ifndef VIPWHOLESALECLIENT_H
#define VIPWHOLESALECLIENT_H

#include "wholesaleclient.h"

class VIPWholeSaleClient : public WholeSaleClient {
public:
    VIPWholeSaleClient(double money);
    double summarize();
};

#endif // VIPWHOLESALECLIENT_H
