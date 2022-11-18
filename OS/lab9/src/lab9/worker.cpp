#include "worker.h"

Worker::Worker() {
    this->requests= new QQueue<Request>();
    if (pthread_create(&this->thread, NULL, &task, (void*)this->requests)) {
        qDebug() << "pthread_create error!";
        return;
    }
}

void* Worker::task(void* params) {
    /*
     * Every 5 secs writes requested data into cache
     * TODO: write into cache
     * TODO: replace QQueue with QVector (?)
     *
     * format:
     * total_size\n
     * filename1,create_date_time1\n
     * filename2,create_date_time2\n
     */

    QQueue<Request>* requests = (QQueue<Request>*)params;
    while (1) {
        while (!requests->isEmpty()) {
            QString cmd = "du -shc ";
            for (QString path : requests->head().paths)
                cmd += path + " ";
            cmd += "| grep total | cut -f 1; find ";
            for (QString path : requests->head().paths)
                cmd += path + " ";
            cmd += "-mindepth 1 -maxdepth 1 '('";
            for (QString extension : requests->head().extensions)
                cmd += " -name \"*" + extension + "\" -o";
            cmd += " -name \"\" ')'";
            cmd += " -printf \"%f,%t\n\"";

            FILE* fp = popen(cmd.toStdString().c_str(), "r");
            char buf[1024];
            QString s;
            while (fgets(buf, 1024, fp))
                s += QString::fromStdString(buf);
            std::cout << s.toStdString() << std::endl;

            requests->dequeue();
        }
        sleep(5);
    }
}
