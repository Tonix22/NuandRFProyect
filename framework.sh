#! /bin/bash
BASEDIR=${PWD}
#Bitstream PATH
#SOFT_DIR=/dupinSoC/hdl/dupin-cenzontle2.sof
SOFT_DIR=FPGA_images/hdl/dupinCoprocessor-CNZTL2.sof
DUMMY_DIR=FPGA_images/hdl/ipmIPDummy-CNZTL2.sof
#OCD USB CFG
if [ $1 == "-bitstream" ]; then #download bitstream to FPGA
    echo "bistream: ${BASEDIR}${SOFT_DIR}"
    echo "quartus_pgm -c 1 -m JTAG -o \"p;${BASEDIR}${SOFT_DIR}\""
    quartus_pgm -c 1 -m JTAG -o "p;${BASEDIR}${SOFT_DIR}"
fi

if [ $1 == "-dummy" ]; then 
    echo "bistream: ipmIPDummy-CNZTL2.sof"
    quartus_pgm -c 1 -m JTAG -o "p;${BASEDIR}${DUMMY_DIR}"
fi