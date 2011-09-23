// -*- C++ -*-
/*!
 * @file  CoordinateMapper.cpp * @brief DataFlow Component * $Date$
 *
 * $Id$
 */
#include "CoordinateMapper.h"

// Module specification
// <rtc-template block="module_spec">
static const char* coordinatemapper_spec[] =
{
    "implementation_id", "CoordinateMapper",
    "type_name",         "CoordinateMapper",
    "description",       "DataFlow Component",
    "version",           "1.0",
    "vendor",            "General Robotix,Inc.",
    "category",          "example",
    "activity_type",     "SPORADIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    ""
};
// </rtc-template>

CoordinateMapper::CoordinateMapper(RTC::Manager* manager)
// <rtc-template block="initializer">
    : RTC::DataFlowComponentBase(manager),
    m_CoordinateMapperServicePort("CoordinateMapperService")

// </rtc-template>
{
}


CoordinateMapper::~CoordinateMapper()
{
}


RTC::ReturnCode_t CoordinateMapper::onInitialize()
{
    // Registration: InPort/OutPort/Service
    // <rtc-template block="registration">
    // Set InPort buffers

    // Set OutPort buffer

    // Set service provider to Ports
    m_CoordinateMapperServicePort.registerProvider("service0", "CoordinateMapperService", m_service0);

    // Set service consumers to Ports

    // Set CORBA Service Ports
    addPort(m_CoordinateMapperServicePort);

    // </rtc-template>

    // <rtc-template block="bind_config">
    // Bind variables and configuration variable

    // </rtc-template>
    return RTC::RTC_OK;
}


/*
   RTC::ReturnCode_t CoordinateMapper::onFinalize()
   {
   return RTC::RTC_OK;
   }
 */

RTC::ReturnCode_t CoordinateMapper::onStartup(RTC::UniqueId ec_id)
{
    std::string model = "/opt/grx/HIRO/model/main.wrl";
    m_service0.loadModel(model);
    return RTC::RTC_OK;
}


/*
   RTC::ReturnCode_t CoordinateMapper::onShutdown(RTC::UniqueId ec_id)
   {
   return RTC::RTC_OK;
   }
 */
/*
   RTC::ReturnCode_t CoordinateMapper::onActivated(RTC::UniqueId ec_id)
   {
   return RTC::RTC_OK;
   }
 */
/*
   RTC::ReturnCode_t CoordinateMapper::onDeactivated(RTC::UniqueId ec_id)
   {
   return RTC::RTC_OK;
   }
 */

RTC::ReturnCode_t CoordinateMapper::onExecute(RTC::UniqueId ec_id)
{
    return RTC::RTC_OK;
}


/*
   RTC::ReturnCode_t CoordinateMapper::onAborting(RTC::UniqueId ec_id)
   {
   return RTC::RTC_OK;
   }
 */
/*
   RTC::ReturnCode_t CoordinateMapper::onError(RTC::UniqueId ec_id)
   {
   return RTC::RTC_OK;
   }
 */
/*
   RTC::ReturnCode_t CoordinateMapper::onReset(RTC::UniqueId ec_id)
   {
   return RTC::RTC_OK;
   }
 */
/*
   RTC::ReturnCode_t CoordinateMapper::onStateUpdate(RTC::UniqueId ec_id)
   {
   return RTC::RTC_OK;
   }
 */
/*
   RTC::ReturnCode_t CoordinateMapper::onRateChanged(RTC::UniqueId ec_id)
   {
   return RTC::RTC_OK;
   }
 */

extern "C"
{

void CoordinateMapperInit(RTC::Manager* manager)
{
    coil::Properties profile(coordinatemapper_spec);
    manager->registerFactory(profile,
                             RTC::Create<CoordinateMapper>,
                             RTC::Delete<CoordinateMapper>);
}

};
