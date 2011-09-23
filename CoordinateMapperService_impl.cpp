// -*-C++-*-
/*!
 * @file  CoordinateMapperService_impl.cpp
 * @brief Service implementation code of CoordinateMapperService.idl
 *
 */

#include "CoordinateMapperService_impl.h"

/*
 * Example implementational code for IDL interface CoordinateMapperService
 */
CoordinateMapperService_impl::CoordinateMapperService_impl()
{
    map_mod = new mapper();
}


CoordinateMapperService_impl::~CoordinateMapperService_impl()
{
    // Please add extra destructor code here.
}


/*
 * Methods corresponding to IDL attributes and operations
 */
OpenHRP::CoordinateSystem_slice* CoordinateMapperService_impl::calcLocal2Global(const OpenHRP::CoordinateSystem in_cs, const char* joint)
{
    double _in_cs[6], _out_cs[6];
    for(int i=0; i<6; i++) _in_cs[i] = in_cs[i];
    map_mod->l2g(_in_cs, _out_cs, joint);

    OpenHRP::CoordinateSystem_slice *out_cs = OpenHRP::CoordinateSystem_alloc();
    for(int i=0; i<6; i++) out_cs[i] = _out_cs[i];

    return out_cs;
}


OpenHRP::CoordinateSystem_slice* CoordinateMapperService_impl::calcGlobal2Local(const OpenHRP::CoordinateSystem in_cs, const char* joint)
{
    double _in_cs[6], _out_cs[6];
    for(int i=0; i<6; i++) _in_cs[i] = in_cs[i];
    map_mod->g2l(_in_cs, _out_cs, joint);

    OpenHRP::CoordinateSystem_slice *out_cs = OpenHRP::CoordinateSystem_alloc();
    for(int i=0; i<6; i++) out_cs[i] = _out_cs[i];

    return out_cs;
}


bool
CoordinateMapperService_impl::loadModel(std::string &model)
{
    return map_mod->load(model);
}


// End of example implementational code
