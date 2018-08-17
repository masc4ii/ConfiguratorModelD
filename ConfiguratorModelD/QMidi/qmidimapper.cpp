#include "qmidimapper.h"

QMidiMapper::QMidiMapper(QObject *parent) : QObject(parent)
{

}

void QMidiMapper::setMappingState(bool value)
{
    (void)value;
}

void QMidiMapper::setWidget(QWidget *widget)
{
    (void)widget;
}

void QMidiMapper::onMidiMessageReceive(QMidiMessage *message)
{
    (void)message;
}

