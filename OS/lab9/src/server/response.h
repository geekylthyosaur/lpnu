#ifndef RESPONSE_H
#define RESPONSE_H

#include <QString>

class Response {
public:
    int receiver_id;
    QString response;
    Response(int receiver_id, QString response);
};

#endif // RESPONSE_H
