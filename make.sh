#!/bin/sh
RTM_PATH=/opt/grx/
export PATH=$RTM_PATH/bin/:$PATH
export LD_LIBRARY_PATH=$RTM_PATH/lib:$RTM_PATH/lib/OpenRTM-aist:$LD_LIBRARY_PATH
PKG_CONFIG_PATH=/opt/grx/lib/pkgconfig make -f Makefile 
#make -f Makefile CoordinateMapperService.jar
omniidl -bpython -I/opt/grx/include/rtm/idl/ CoordinateMapperService.idl
