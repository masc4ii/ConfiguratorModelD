# ConfiguratorModelD
A easy configurator for Behringer Model D.

This little app helps to configure the Behringer Model D. This synth can be setup by some MIDI sysex messages, which are more or less hard to create. So I started to implement this little GUI, which uses QMidi (and this uses rtMidi). So everybody can setup the Model D by some simple clicks...

![pic](https://image.ibb.co/dYa6dm/Bildschirmfoto.png)

## Usage
Open the program, make sure the Port is "MODEL D", change the values as you like.

## Compile
The app can be compiled for Windows, Linux and macOS. You just need Qt5.6 or newer. Open the ConfiguratorModelD.pro file in QtCreator, press the Run button and have fun!
