#include "regularwholesaleclient.h"

double RegularWholeSaleClient::summarize() {
    double sum = 0;
    for (double i : getCheck()) sum += i;
    if (sum >= 1000) return sum * 0.98;
    else return sum;
}
