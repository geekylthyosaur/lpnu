#include "worker.h"

struct WorkerParams {
    QQueue<Request>* requests;
    QQueue<Response>* responses;
};

Worker::Worker() {
    this->requests = new QQueue<Request>();
    this->responses = new QQueue<Response>();
    WorkerParams* params = new WorkerParams {
        this->requests,
        this->responses,
    };
    if (pthread_create(&this->thread, NULL, &task, (void*)params)) {
        qDebug() << "pthread_create error!";
        return;
    }
}

void* Worker::task(void* p) {
    /*
     * Every 5 secs writes requested data into cache
     *
     * format:
     * total_size\n
     * filename1,create_date_time1\n
     * filename2,create_date_time2\n
     */

    WorkerParams* params = (WorkerParams*)p;
    QQueue<Request>* requests = params->requests;
    QQueue<Response>* responses = params->responses;
    while (1) {
        while (!requests->isEmpty()) {
            Request request = requests->head();
            QString cmd = "du -shc ";
            for (QString path : *request.paths)
                cmd += path + " ";
            cmd += "| grep total | cut -f 1; find ";
            for (QString path : *request.paths)
                cmd += path + " ";
            cmd += "-mindepth 1 -maxdepth 1 '('";
            for (QString extension : *request.extensions)
                cmd += " -name \"*" + extension + "\" -o";
            cmd += " -name \"\" ')'";
            cmd += " -printf \"%f,%Td-%Tm-%TY %TH:%TM:%.2TS\n\"";

            qDebug() << cmd;
            FILE* fp = popen(cmd.toStdString().c_str(), "r");
            char buf[1024];
            QString response;
            while (fgets(buf, 1024, fp))
                response += QString::fromStdString(buf);

            qDebug() << response;

            responses->enqueue(Response(request.receiver_id, response));
            requests->dequeue();
        }
        sleep(5);
    }
}
