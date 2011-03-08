// -*-C++-*-
/*!
 * @file  CoordinateMapperServiceSVC_impl.cpp
 * @brief Service implementation code of CoordinateMapperService.idl
 *
 */

#include "CoordinateMapperServiceSVC_impl.h"

/*
 * Example implementational code for IDL interface CoordinateMapperService
 */
CoordinateMapperServiceSVC_impl::CoordinateMapperServiceSVC_impl()
{
	map_mod = new mapper();
}


CoordinateMapperServiceSVC_impl::~CoordinateMapperServiceSVC_impl()
{
	// Please add extra destructor code here.
}


/*
 * Methods corresponding to IDL attributes and operations
 */
CoordinateSystem_slice* CoordinateMapperServiceSVC_impl::calcLocal2Global(const CoordinateSystem in_cs, const char* joint)
{
	double _in_cs[6], _out_cs[6];
	for(int i=0; i<6; i++) _in_cs[i] = in_cs[i];
	map_mod->l2g(_in_cs, _out_cs, joint);

	CoordinateSystem_slice *out_cs = CoordinateSystem_alloc();
	for(int i=0; i<6; i++) out_cs[i] = _out_cs[i];

	return out_cs;
}


CoordinateSystem_slice* CoordinateMapperServiceSVC_impl::calcGlobal2Local(const CoordinateSystem in_cs, const char* joint)
{
	double _in_cs[6], _out_cs[6];
	for(int i=0; i<6; i++) _in_cs[i] = in_cs[i];
	map_mod->g2l(_in_cs, _out_cs, joint);

	CoordinateSystem_slice *out_cs = CoordinateSystem_alloc();
	for(int i=0; i<6; i++) out_cs[i] = _out_cs[i];

	return out_cs;
}


bool
CoordinateMapperServiceSVC_impl::loadModel(std::string &model)
{
	return map_mod->load(model);
}


// End of example implementational code
