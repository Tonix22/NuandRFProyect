#TOLTECA FPGA FIRMWARE
## DEPENDENCIES 
* Quartus Prime Programmer Version 20.1.1(linux)
    * Download bistream
* RISCV GCC
    * Compiler of softcore
* openocd 0.10.0+dev-g1e85cf0-dirty
    * Debugger interconnect

## Obtain RISCV GCC
```bash
#!/bin/bash
wget https://static.dev.sifive.com/dev-tools/riscv64-unknown-elf-gcc-20171231-x86_64-linux-centos6.tar.gz
tar -xzvf riscv64-unknown-elf-gcc-20171231-x86_64-linux-centos6.tar.gz
sudo mv riscv64-unknown-elf-gcc-20171231-x86_64-linux-centos6 /opt/riscv64-unknown-elf-gcc-20171231-x86_64-linux-centos6
sudo mv /opt/riscv64-unknown-elf-gcc-20171231-x86_64-linux-centos6 /opt/riscv
echo 'export PATH=/opt/riscv/bin:$PATH' >> ~/.bashrc
```
## hands on download
We will use a bash script **framwork.sh** to make easier manage with developing.


1. Download the bistream. Check that **SOFT_DIR** is correct. 
```console
foo@bar:~$ ./framework.sh -bitstream
```
2. Open OCD, connect to the FPGA and core to debug.  Check that **USB_CFG** and **DUPIN_CFG** are correct.
```console
foo@bar:~$ ./framework.sh -ocd
```
3. Compile Firmware. You could also compile firmware direcly on dev folder, [ad9361_project](FPGA_FW/dupinSoC/fw/ad9361_project).
```console
foo@bar:~$ ./framework.sh -all ad9361_project
foo@bar:~$ ./framework.sh -all <project_folder_name>
```

If the compilation exits successfully, an **elf** file will be generated under **debug/** folder. This elf file has to be downloaded by the JTAG to the main memory.

4. Download elf file generate by the compiler.
```console
foo@bar:~$ ./opt/riscv/bin/riscv64-unknown-elf-gdb
(gdb) target remote :3333
(gdb) set remotetimeout 60
(gdb) set arch riscv:rsv32
(gdb) monito reset halt
(gdb) load
```
## How to Debug on VScode Linux
1. Download Vscode extension Native Debug.
![Alt text](VScodeApplet.jpeg?raw=true "VScodeApplet")

2. Open Proyect in vscode, and go to the left menu and click
on the debug symbol, add configuration.
![Alt text](debugsymbol.png?raw=true "debugsymbol")

3. Vscode will open a .vscode/task.json file which will be configure as the image below. Check elf path and riscv-gdb path. 
![Alt text](DebugCFG.jpeg?raw=true "DebugCFG")

4. Debug elf clicking on debug menu on the green triangle. 
Debug may start in a .S file and the will go to the main.c file
![Alt text](Result.jpeg?raw=true "Result")


## Known Issues, USB blaster, Linux 
Permisions problems on JTAG port
https://rocketboards.org/foswiki/Documentation/UsingUSBBlasterUnderLinux

## STM32F4-based Logic Analyser
<https://www.fussylogic.co.uk/blog/?p=1226>
