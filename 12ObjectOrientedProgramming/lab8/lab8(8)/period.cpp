#include "period.h"

double Period::asHours() {
    return startDateTime.secsTo(endDateTime) / (60*60);
};
