#!/bin/sh
export RTM_PATH=/opt/grx
export PATH=$RTM_PATH/bin/:$PATH
export LD_LIBRARY_PATH=$RTM_PATH/lib:$RTM_PATH/lib/OpenRTM-aist:$LD_LIBRARY_PATH

/opt/grx/bin/rtc-template -bcxx \
    --module-name=CoordinateMapper \
	--module-type='DataFlowComponent' \
    --module-desc='DataFlow Component' \
    --module-version=1.0 \
	--module-vendor='General Robotix,Inc.' \
    --module-category=example \
    --module-comp-type=DataFlowComponent \
	--module-act-type=SPORADIC \
    --module-max-inst=1 \
    --service=CoordinateMapperService:service0:CoordinateMapperService \
    --service-idl=CoordinateMapperService.idl


