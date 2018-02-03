# ConfiguratorModelD
A easy configurator for Behringer Model D.

This little app helps to configure the Behringer Model D. This synth can be setup by some MIDI sysex messages, which are more or less hard to create. So I started to implement this little GUI, which uses QMidi (and this uses rtMidi). So everybody can setup the Model D by some simple clicks...

![pic](https://image.ibb.co/dYa6dm/Bildschirmfoto.png)

## Usage
Open the program, make sure the Port is "MODEL D", change the values as you like. Note: the values can only be written and not loaded from the Model D. So the initial setup shown by the app might not be the one in your synth!

## Download
Download a release [here](https://github.com/masc4ii/ConfiguratorModelD/releases).

## Compile
The app can be compiled for Windows, Linux and macOS. You just need Qt5.6 or newer. Open the ConfiguratorModelD.pro file in QtCreator, press the Run button and have fun!
