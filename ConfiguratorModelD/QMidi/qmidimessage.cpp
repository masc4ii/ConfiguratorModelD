#include "qmidimessage.h"

QMidiMessage::QMidiMessage(QObject *parent) : QObject(parent)
{

}

QMidiMessage::~QMidiMessage()
{

}

QMidiMessage::QMidiMessage(const QMidiMessage &other)
{
    (void)other;
}

