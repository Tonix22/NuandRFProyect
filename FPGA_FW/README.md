#TOLTECA FPGA FIRMWARE
## DEPENDENCIES 
* [Quartus Prime Programmer Version 20.1.1](https://fpgasoftware.intel.com/?edition=lite)(linux)
    * Download bistream
* RISCV GCC
    * Compiler of softcore
* openocd 0.10.0+dev-g1e85cf0-dirty
    * Debugger interconnect

## Obtain RISCV GCC
```bash
#!/bin/bash
sudo apt-get install wget
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

## SPI pins

| pins    | signal    |
| ---     | ---       |
| GP2_2   | SPI_MISO  |
| GP2_4   | SPI_MOSI  |
| GP2_6   | SPI_SCLK  |
| GP2_8   | SPI_SS    |
| GP2_10  | GND       |

## STM32F4-based Logic Analyser
As an option of Logic Analyser, we could use a STM32F432 Discovery 

In ‘Acquisition’ sampling rate cannot exceed 20MHz. 
Setting it higher will sample at 20MHz anyway, 
but will report all the times wrong.
Channel Groups, set to “0” for PD0–PD7; or “0” and “1” for PD0–PD15.

1. For develop with this logic analyser we recomend you to review this 
[blog](https://www.fussylogic.co.uk/blog/?p=1226)

2. Get [stm32f4discovery.cfg](https://github.com/arduino/OpenOCD/blob/master/tcl/board/stm32f4discovery.cfg), is a cfg to call board from OpenOCD.

3. [LogicDiscovery-r12.bin](https://storage.googleapis.com/google-code-archive-downloads/v2/code.google.com/logicdiscovery/LogicDiscovery-r12.bin) Binary file of the Logic Analyser

4. [Logic analyser software](https://www.lxtreme.nl/ols/ols-0.9.7.2-full.zip)


To power the board from the same port, we jumper pins PA9 and 5V

openocd \
   -f /OpenOCD/tcl/board/stm32f4discovery.cfg \
   -c "init" \
   -c "reset halt" \
   -c "sleep 100" \
   -c "wait_halt 2" \
   -c "echo \"--- Writing LogicDiscovery-r12.bin\"" \
   -c "flash write_image erase LogicDiscovery-r12.bin 0x08000000" \
   -c "sleep 100" \
   -c "echo \"--- Verifying\"" \
   -c "verify_image LogicDiscovery-r12.bin 0x08000000" \
   -c "sleep 100" \
   -c "echo \"--- Done\"" \
   -c "resume" \
   -c "shutdown"
   

## Known Issue in STM32F4-based Logic Analyser 2021
OS: Linux
Software: Open Logic Sniffer (or OLS) -> ols-0.9.7.2-full.tar.gz 

OLS works with java 8. The java 11 is not supported, 
finding the fix could be frustrating due to the bunch of errors show in terminal,
There is not so obvious another that  another java version is required. 

To fix this error you could downgrade java version. 
https://askubuntu.com/questions/1133216/downgrading-java-11-to-java-8

1. $sudo apt-get install openjdk-8-jre
2. $sudo update-alternatives --config java # chose the java 8 option 

To test new java version 
$java -version 
    openjdk version "1.8.0_151"
    
After fixing the error I can open the OLS normally. 
