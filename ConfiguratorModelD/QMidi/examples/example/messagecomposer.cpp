#include "messagecomposer.h"

#include <QGridLayout>
#include <QLabel>
#include <QVBoxLayout>

MessageComposer::MessageComposer(QWidget *parent) : QWidget(parent),
    _statusComboBox(new QComboBox(this)),
    _channelComboBox(new QComboBox(this)),
    _pitchSpinBox(new QSpinBox(this)),
    _velocitySpinBox(new QSpinBox(this)),
    _controlSpinBox(new QSpinBox(this)),
    _valueSpinBox(new QSpinBox(this))
{

    _statuses << "Note off" << "Note on" << "Control change" << "Program change"
             << "Pitch bend" << "Aftertouch" << "Poly Aftertouch"
             << "Sysex" << "Time code" << "Song pos pointer" << "Song select"
             << "Sysex end" << "Time clock" << "Start"
             << "Continue" << "Stop" << "Active sensing" << "System reset";
    QGridLayout *mainLayout = new QGridLayout(this);

    QLabel *heading = new QLabel("Compose Message");
    QFont headingFont = heading->font();
    headingFont.setBold(true);
    headingFont.setPointSize(14);
    heading->setFont(headingFont);
    mainLayout->addWidget(heading,0,0);

    mainLayout->addWidget(new QLabel(tr("Channel")), 1,0);
    QStringList channels;
    for(int i = 1; i <= 16; i++)
    {
        channels << QString::number(i);
    }
    _channelComboBox->addItems(channels);
    mainLayout->addWidget(_channelComboBox,1,1,1,2);

    mainLayout->addWidget(new QLabel(tr("Status")),2,0);


    _statusComboBox->addItems(_statuses);

    connect(_statusComboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(onStatusChange(QString)));
    mainLayout->addWidget(_statusComboBox, 2,1,1,2);

    mainLayout->addWidget(new QLabel(tr("Pitch")),3,0);
    _pitchSpinBox->setRange(0,127);
    mainLayout->addWidget(_pitchSpinBox, 3,1,1,2);

    mainLayout->addWidget(new QLabel(tr("Velocity")),4,0);
    _velocitySpinBox->setRange(0,127);
    mainLayout->addWidget(_velocitySpinBox, 4,1,1,2);

    mainLayout->addWidget(new QLabel(tr("Control")),5,0);
    _controlSpinBox->setRange(0,127);
    mainLayout->addWidget(_controlSpinBox, 5,1,1,2);

    mainLayout->addWidget(new QLabel(tr("Value")),6,0);
    _valueSpinBox->setRange(0,127);
    mainLayout->addWidget(_valueSpinBox, 6,1,1,2);


    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    setLayout(mainLayout);


    onStatusChange(_statusComboBox->currentText());
}

QMidiMessage *MessageComposer::getMidiMessage()
{
    QMidiMessage *message = new QMidiMessage(this);
    message->setChannel(_channelComboBox->currentText().toInt());
    QMidiStatus status;
    switch(_statusComboBox->currentIndex())
    {
    case 0: status = MIDI_NOTE_OFF; break;
    case 1: status = MIDI_NOTE_ON; break;
    case 2: status = MIDI_CONTROL_CHANGE; break;
    case 3: status = MIDI_PROGRAM_CHANGE; break;
    case 4: status = MIDI_PITCH_BEND; break;
    case 5: status = MIDI_AFTERTOUCH; break;
    case 6: status = MIDI_POLY_AFTERTOUCH; break;
    case 7: status = MIDI_SYSEX; break;
    case 8: status = MIDI_TIME_CODE; break;
    case 9: status = MIDI_SONG_POS_POINTER; break;
    case 10: status = MIDI_SONG_SELECT; break;
    case 11: status = MIDI_TUNE_REQUEST; break;
    case 12: status = MIDI_SYSEX_END; break;
    case 13: status = MIDI_TIME_CLOCK; break;
    case 14: status = MIDI_START; break;
    case 15: status = MIDI_CONTINUE; break;
    case 16: status = MIDI_STOP; break;
    case 17: status = MIDI_ACTIVE_SENSING; break;
    case 18: status = MIDI_SYSTEM_RESET; break;
    default: break;
    }

    message->setStatus(status);
    message->setPitch(_pitchSpinBox->value());
    message->setControl(_controlSpinBox->value());
    message->setValue(_valueSpinBox->value());
//    message->setDeltaTime(_delta)
    return message;
}

void MessageComposer::onStatusChange(QString status)
{
    if(status == _statuses[0] || status == _statuses[1]) //note on or note off
    {
        _pitchSpinBox->setEnabled(true);
        _velocitySpinBox->setEnabled(true);
        _controlSpinBox->setEnabled(false);
        _valueSpinBox->setEnabled(false);

    }
    if(status == _statuses[2]) //control change
    {
        _pitchSpinBox->setEnabled(false);
        _velocitySpinBox->setEnabled(false);
        _controlSpinBox->setEnabled(true);
        _valueSpinBox->setEnabled(true);
    }
    if(status == _statuses[3] || status == _statuses[5]) //program change or aftertouch
    {
        _pitchSpinBox->setEnabled(false);
        _velocitySpinBox->setEnabled(false);
        _controlSpinBox->setEnabled(true);
        _valueSpinBox->setEnabled(true);
    }

    if(status == _statuses[4]) //bend
    {
        _pitchSpinBox->setEnabled(false);
        _velocitySpinBox->setEnabled(false);
        _controlSpinBox->setEnabled(false);
        _valueSpinBox->setEnabled(true);
        //TODO: value setMax
    }
    if(status == _statuses[6]) //poly aftertouch
    {
        _pitchSpinBox->setEnabled(true);
        _velocitySpinBox->setEnabled(false);
        _controlSpinBox->setEnabled(false);
        _valueSpinBox->setEnabled(true);
    }

}

