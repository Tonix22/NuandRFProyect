# Tolteca Project Development based on Blade RF#
This repository contains all the source code required to program and interact with a bladeRF platform, including firmware for the Cypress FX3 USB controller, HDL for the Altera Cyclone IV FPGA, and C code for the host side libraries, drivers, and utilities.

| Directory         | Description                                                                                       |
| ----------------- |:--------------------------------------------------------------------------------------------------|
| [FPGA_FW](FPGA_FW) | Custom softcore firmware to migrate ad9361 library                                |
| [GUITEST](GUITEST) | Interactive GUI to control the ad3261 drivers                           |
| [host](Nuand_Blade_Base/host/)  | PC host, to control de bladeRF project                     |

![Alt text](General_spec.jpg?raw=true "General Spec")