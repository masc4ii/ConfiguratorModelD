#ifndef QMIDIMESSAGE_H
#define QMIDIMESSAGE_H

#include <QObject>
#include <vector>

//https://github.com/danomatika/ofxMidi/blob/master/src/ofxMidiConstants.h
enum QMidiStatus {

    MIDI_UNKNOWN            = 0x00,

    // channel voice messages
    MIDI_NOTE_OFF           = 0x80,
    MIDI_NOTE_ON            = 0x90,
    MIDI_CONTROL_CHANGE     = 0xB0,
    MIDI_PROGRAM_CHANGE     = 0xC0,
    MIDI_PITCH_BEND         = 0xE0,
    MIDI_AFTERTOUCH         = 0xD0, // aka channel pressure
    MIDI_POLY_AFTERTOUCH    = 0xA0, // aka key pressure

    // system messages
    MIDI_SYSEX              = 0xF0,
    MIDI_TIME_CODE          = 0xF1,
    MIDI_SONG_POS_POINTER   = 0xF2,
    MIDI_SONG_SELECT        = 0xF3,
    MIDI_TUNE_REQUEST       = 0xF6,
    MIDI_SYSEX_END          = 0xF7,
    MIDI_TIME_CLOCK         = 0xF8,
    MIDI_START              = 0xFA,
    MIDI_CONTINUE           = 0xFB,
    MIDI_STOP               = 0xFC,
    MIDI_ACTIVE_SENSING     = 0xFE,
    MIDI_SYSTEM_RESET       = 0xFF
};

// number range defines
// because it's sometimes hard to remember these  ...
#define MIDI_MIN_BEND       0
#define MIDI_MAX_BEND       16383

class QMidiMessage : public QObject
{
    Q_OBJECT
public:
    explicit QMidiMessage(QObject *parent = 0);
    ~QMidiMessage();
    QMidiMessage(const QMidiMessage &other);
    QMidiStatus getStatus()
    {
        return _status;
    }
    unsigned int getChannel()
    {
        return _channel;
    }
    unsigned int getPitch()
    {
        return _pitch;
    }
    unsigned int getVelocity()
    {
        return _velocity;
    }
    unsigned int getControl()
    {
        return _control;
    }
    unsigned int getValue()
    {
        return _value;
    }
    double getDeltaTime()
    {
        return _deltaTime;
    }

    QMidiMessage* setStatus(QMidiStatus status)
    {
        _status = status;
        return this;
    }
    QMidiMessage* setChannel(unsigned int channel)
    {
        _channel = channel;
        return this;
    }
    QMidiMessage* setPitch(unsigned int pitch)
    {
        _pitch = pitch;
        return this;
    }
    QMidiMessage* setVelocity(unsigned int velocity)
    {
        _velocity = velocity;
        return this;
    }
    QMidiMessage* setControl(unsigned int control)
    {
        _control = control;
        return this;
    }
    QMidiMessage* setValue(unsigned int value)
    {
        _value = value;
        return this;
    }
    QMidiMessage* setDeltaTime(double deltaTime)
    {
        _deltaTime = deltaTime;
        return this;
    }
    QMidiMessage* setRawMessage(std::vector<unsigned char> rawMessage)
    {
        _rawMessage = rawMessage;
        return this;
    }

    std::vector<unsigned char> getRawMessage()
    {
        if(_rawMessage.size() == 0)
        {
            switch(_status)
            {
            case MIDI_NOTE_ON:{
                _rawMessage.push_back(MIDI_NOTE_ON+_channel-1);
                _rawMessage.push_back(_pitch);
                _rawMessage.push_back(_velocity);
                break;
            }
            case MIDI_NOTE_OFF:{
                _rawMessage.push_back(MIDI_NOTE_OFF+_channel-1);
                _rawMessage.push_back(_pitch);
                _rawMessage.push_back(_velocity);
                break;
            }
            case MIDI_CONTROL_CHANGE:{
                _rawMessage.push_back(MIDI_CONTROL_CHANGE+_channel-1);
                _rawMessage.push_back(_control);
                _rawMessage.push_back(_value);
                break;
            }
            case MIDI_PROGRAM_CHANGE:{
                _rawMessage.push_back(MIDI_PROGRAM_CHANGE+_channel-1);
                _rawMessage.push_back(_control);
                _rawMessage.push_back(_value);
                break;
            }
                //TODO: check protocol and implement other cases
            default:{
                break;
            }
            }
        }
        return _rawMessage;
    }

public:
    QMidiStatus _status;
    unsigned int _channel;
    unsigned int _pitch;
    unsigned int _velocity;
    unsigned int _control;
    unsigned int _value;
    double _deltaTime;

    std::vector<unsigned char> _rawMessage;
signals:

public slots:
};

#endif // QMIDIMESSAGE_H
