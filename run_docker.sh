#! /bin/bash
sudo docker run -it --mount src="$(pwd)",target=/root/external,type=bind --device=/dev/bus/usb tonix22/ubuntu_lime_dev