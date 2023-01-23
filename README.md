# ModularAmpToolKit.lv2
set of LV2 plugs to simulate valve amplifiers 


## Features

Each plug have a input/output control and a mode selector.
They could all be used as seperate plugs, together they should emulate a full amplifier stack.

- PreAmps

Select the valve type to use in the Pre Amp section and adjust the input/output controls to match the sweep point of your guitar

- PreAmpImpulses

Select the Pre Amp type to use and adjust the input/output controls for the module.

- PowerAmps

Select the valve type to use in the Power Amp section and adjust the input/output controls to match the sweep point of your guitar

- PowerAmpImpulses

Select the POwer Amp type to use and adjust the input/output controls for the module.


## Dependencys

- libcairo2-dev
- libx11-dev
- lv2-dev

## Build

- git submodule init
- git submodule update
- make
- make install # will install into ~/.lv2 ... AND/OR....
- sudo make install # will install into /usr/lib/lv2
