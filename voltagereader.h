#ifndef VOLTAGEREADER_H
#define VOLTAGEREADER_H
#include <QThread>

class VoltageReader: public QThread
{
    Q_OBJECT
    public:
        explicit VoltageReader(QObject* parent=0);
    protected:
        void run() Q_DECL_OVERRIDE;
    signals:
        void new_read(float);
};

#endif // VOLTAGEREADER_H
