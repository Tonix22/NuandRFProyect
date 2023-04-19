# Tolteca Project Development based on Blade RF 
This repository contains all the source code required to program and interact with a bladeRF platform, including firmware for the Cypress FX3 USB controller, HDL for the Altera Cyclone IV FPGA, and C code for the host-side libraries, drivers, and utilities

| Directory         | Description                                                                                       |
| ----------------- |:--------------------------------------------------------------------------------------------------|
| [Installers](Installers) | Dependencies and software required                                |
| [GUITEST](GUITEST) | Interactive QT GUI to control the ad3261 drivers                           |
| [host](Nuand_Blade_Base/host)  | PC host, to control de bladeRF project                     |
| [Documentation](Documentation/Documentation.pdf)  | Project Explanation PDF File                   |

## AD9361 Conection Firmware
| File              | Short Description                               | Link                                            |
|-------------------|-------------------------------------------------|-------------------------------------------------|
| `main.c`          | Main firmware code                              | [MAIN](FirmwareDev/src/main.c)                  |
| `parser.c`        | Memory broker parser code                       | [Parser](FirmwareDev/src/memory_broker/parser.c) |
| `ad9361_api.c`    | AD9361 library API code                          | [Ad9361_lib](FirmwareDev/src/ad9361_lib/ad9361_api.c) |

## SIMILAR PROJECT

[LSM7002M_RISC-V_driver](https://github.com/Tonix22/LSM7002M_RISC-V_driver)
Also this project documents how to install QUartus and USB blaster rules.
[Install.md]https://github.com/Tonix22/LSM7002M_RISC-V_driver/blob/main/Installers/Install.md


## FPGA Setup
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