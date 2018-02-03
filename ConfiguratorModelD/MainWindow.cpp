/*!
 * \file MainWindow.cpp
 * \author masc4ii
 * \copyright 2018
 * \brief The main window
 */

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QBuffer>

#define APPNAME "Configurator Model D"
#define VERSION "0.2"

//Constructor
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setUnifiedTitleAndToolBarOnMac( true );
    adjustSize();

    m_midiOut = new QMidiOut( this );

    getPorts();
    searchModelD();
}

//Destructor
MainWindow::~MainWindow()
{
    delete m_midiOut;
    delete ui;
}

//Get Ports and write into combobox
void MainWindow::getPorts( void )
{
    ui->comboBoxPort->addItems( m_midiOut->getPorts() );
}

//Search the D and select it
void MainWindow::searchModelD( void )
{
    for( int i = 0; i < ui->comboBoxPort->count(); i++ )
    {
        if( ui->comboBoxPort->itemText( i ) == QString( "MODEL D" ) )
        {
            ui->comboBoxPort->setCurrentIndex( i );
            break;
        }
    }
}

//Build the message
std::vector<unsigned char> MainWindow::buildMessage(unsigned char parNr, unsigned char value)
{
    std::vector<unsigned char> message;
    message.clear();
    //Start
    message.push_back( 0xF0 );
    //Behringer
    message.push_back( 0x00 );
    message.push_back( 0x20 );
    message.push_back( 0x32 );
    //Reserved
    message.push_back( 0x00 );
    //Device
    message.push_back( 0x7F );
    //Global Settings
    message.push_back( 0x0A );
    //Parameter Number
    message.push_back( parNr );
    //Value
    message.push_back( 0x00 );
    //Value
    message.push_back( value );
    //End
    message.push_back( 0xF7 );

    return message;
}

//Send action
void MainWindow::on_actionSendAll_triggered()
{
    on_spinBoxMidiChannel_editingFinished();
    on_comboBoxKeyPrio_activated( 0 );
    on_comboBoxMultiTrigger_activated( 0 );
    on_spinBoxPitchBend_editingFinished();
    on_spinBoxTranspose_editingFinished();
    on_comboBoxModCurve_activated(0);
}

//MIDI channel
void MainWindow::on_spinBoxMidiChannel_editingFinished()
{
    m_midiOut->openPort( ui->comboBoxPort->currentIndex() );
    std::vector<unsigned char> message = buildMessage( 0x00, (unsigned char)(ui->spinBoxMidiChannel->value()-1) );
    m_midiOut->sendRawMessage( message );
    m_midiOut->closePort();
}

//Key Prio (parameter unused)
void MainWindow::on_comboBoxKeyPrio_activated(int index)
{
    m_midiOut->openPort( ui->comboBoxPort->currentIndex() );
    std::vector<unsigned char> message = buildMessage( 0x01, (unsigned char)ui->comboBoxKeyPrio->currentIndex() );
    m_midiOut->sendRawMessage( message );
    m_midiOut->closePort();
}

//Multi Trigger (parameter unused)
void MainWindow::on_comboBoxMultiTrigger_activated(int index)
{
    m_midiOut->openPort( ui->comboBoxPort->currentIndex() );
    std::vector<unsigned char> message = buildMessage( 0x02, (unsigned char)ui->comboBoxMultiTrigger->currentIndex() );
    m_midiOut->sendRawMessage( message );
    m_midiOut->closePort();
}

//Pitch Bend
void MainWindow::on_spinBoxPitchBend_editingFinished()
{
    m_midiOut->openPort( ui->comboBoxPort->currentIndex() );
    std::vector<unsigned char> message = buildMessage( 0x03, (unsigned char)ui->spinBoxPitchBend->value() );
    m_midiOut->sendRawMessage( message );
    m_midiOut->closePort();
}

//Transpose
void MainWindow::on_spinBoxTranspose_editingFinished()
{
    m_midiOut->openPort( ui->comboBoxPort->currentIndex() );
    std::vector<unsigned char> message = buildMessage( 0x06, (unsigned char)(ui->spinBoxTranspose->value()+12) );
    m_midiOut->sendRawMessage( message );
    m_midiOut->closePort();
}

//Modulation Curve
void MainWindow::on_comboBoxModCurve_activated(int index)
{
    m_midiOut->openPort( ui->comboBoxPort->currentIndex() );
    std::vector<unsigned char> message = buildMessage( 0x0B, (unsigned char)ui->comboBoxModCurve->currentIndex() );
    m_midiOut->sendRawMessage( message );
    m_midiOut->closePort();
}

//Qt Box
void MainWindow::on_actionAboutQt_triggered()
{
    QMessageBox::aboutQt(this);
}

//About Box
void MainWindow::on_actionAboutConfiguratorModelD_triggered()
{
    QPixmap pixmap = QPixmap( ":/IMG/IMG/ConfigModelD.png" )
                .scaled( 128 * devicePixelRatio(), 112 * devicePixelRatio(),
                         Qt::KeepAspectRatio, Qt::SmoothTransformation );
        pixmap.setDevicePixelRatio( devicePixelRatio() );
        QByteArray byteArray;
        QBuffer buffer(&byteArray);
        pixmap.save(&buffer, "PNG");
        QString pic = QString("<img width='128' height='112' align='right' src=\"data:image/png;base64,") + byteArray.toBase64() + "\"/>";

        QMessageBox::about( this, QString( "About %1" ).arg( APPNAME ),
                                QString(
                                  "<html>%1"
                                  "<body><h3>%2</h3>"
                                  " <p>%2 v%3</p>"
                                  " <p>%7</p>"
                                  " <p>See <a href='%8'>this site</a> for more information.</p>"
                                  " <p>Some icons by <a href='%9'>Double-J Design</a> under <a href='%10'>CC4.0</a></p>"
                                  " </body></html>" )
                                 .arg( pic )
                                 .arg( APPNAME )
                                 .arg( VERSION )
                                 .arg( "by masc." )
                                 .arg( "https://github.com/masc4ii/ConfiguratorModelD" )
                                 .arg( "http://www.doublejdesign.co.uk/" )
                                 .arg( "https://creativecommons.org/licenses/by/4.0/" ) );
}

//Find Model D
void MainWindow::on_actionFindModelD_triggered()
{
    ui->comboBoxPort->clear();
    getPorts();
    searchModelD();
}

//Midi channel value changed - do the same like editing finished
void MainWindow::on_spinBoxMidiChannel_valueChanged(int arg1)
{
    on_spinBoxMidiChannel_editingFinished();
}

//Pitch bend box changed - do the same like editing finished
void MainWindow::on_spinBoxPitchBend_valueChanged(int arg1)
{
    on_spinBoxPitchBend_editingFinished();
}

//Transpose box changed - do the same like editing finished
void MainWindow::on_spinBoxTranspose_valueChanged(int arg1)
{
    on_spinBoxTranspose_editingFinished();
}
