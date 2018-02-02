#ifndef MESSAGECOMPOSER_H
#define MESSAGECOMPOSER_H

#include <QComboBox>
#include <QSpinBox>
#include <QWidget>

#include "qmidimessage.h"

class MessageComposer : public QWidget
{
    Q_OBJECT
public:
    explicit MessageComposer(QWidget *parent = 0);

    QMidiMessage* getMidiMessage();
    QStringList _statuses;
private:
    QComboBox *_statusComboBox;
    QComboBox *_channelComboBox;
    QSpinBox *_pitchSpinBox;
    QSpinBox *_velocitySpinBox;
    QSpinBox *_controlSpinBox;
    QSpinBox *_valueSpinBox;


signals:

public slots:
private slots:
    void onStatusChange(QString status);
};

#endif // MESSAGECOMPOSER_H
