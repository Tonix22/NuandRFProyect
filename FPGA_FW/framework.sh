#! /bin/bash
BASEDIR=${PWD}
#Bitstream PATH
SOFT_DIR=/dupinSoC/hdl/dupin-cenzontle2.sof
#OCD USB CFG
USB_CFG=/openOCD/tcl/interface/ftdi/openocd-usb.cfg
DUPIN_CFG=/openOCD/tcl/target/dupin_s.cfg



if [ $1 == "-bitstream" ]; then #download bitstream to FPGA
    echo "bistream: ${BASEDIR}${SOFT_DIR}"
    echo "quartus_pgm -c 1 -m JTAG -o \"p;${BASEDIR}${SOFT_DIR}\""
    quartus_pgm -c 1 -m JTAG -o "p;${BASEDIR}${SOFT_DIR}"
fi

if [ $1 == "-dummy" ]; then 
    echo "bistream: ipmIPDummy-CNZTL2.sof"
    quartus_pgm -c 1 -m JTAG -o "p;SoftFiles/ipmIPDummy-CNZTL2.sof"
fi 

if [ $1 == "-ocd" ]; then #open port for debuger
    echo "Script executed from: ${BASEDIR}${USB_CFG}"
    echo "${BASEDIR}/cpu0.yaml"
    echo "${BASEDIR}${DUPIN_CFG}"
    sudo openocd -f ${BASEDIR}${USB_CFG} -c "set DUPIN_S_CFG ${BASEDIR}/cpu0.yaml" -f ${BASEDIR}${DUPIN_CFG}
fi

if [ $1 == "-all" ]; then #make generic folder project
    cd dupinSoC/fw/
    cd $2
    make
    cd ../../../
fi

if [ $1 == "-clean" ]; then #clean generci folder projectbi
    cd dupinSoC/fw/
    cd $2
    make clean
    cd ../
fi
