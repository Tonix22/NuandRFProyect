# Tolteca Project Development based on Blade RF#
This repository contains all the source code required to program and interact with a bladeRF platform, including firmware for the Cypress FX3 USB controller, HDL for the Altera Cyclone IV FPGA, and C code for the host side libraries, drivers, and utilities.

| Directory         | Description                                                                                       |
| ----------------- |:--------------------------------------------------------------------------------------------------|
| [Installers](Installers) | Dependencies and software required                                |
| [GUITEST](GUITEST) | Interactive GUI to control the ad3261 drivers                           |
| [host](Nuand_Blade_Base/host)  | PC host, to control de bladeRF project                     |
| [Documentation](Documentation/Documentation.pdf)  | Project Explanation                   |


To download FPGA bitstream run the following code

RISCV

```bash
./framework.sh -bitstream
```
Memory only IP dummy

```bash
./framework.sh -dummy
```

![Alt text](GUIoverwiew.jpg?raw=true "General Spec")