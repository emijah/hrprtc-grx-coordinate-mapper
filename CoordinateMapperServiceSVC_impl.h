// -*-C++-*-
/*!
 * @file  CoordinateMapperServiceSVC_impl.h
 * @brief Service implementation header of CoordinateMapperService.idl
 *
 */

#include "CoordinateMapperServiceSkel.h"
#include "mapper.h"

#ifndef COORDINATEMAPPERSERVICESVC_IMPL_H
#define COORDINATEMAPPERSERVICESVC_IMPL_H

/*
 * Example class implementing IDL interface CoordinateMapperService
 */
class CoordinateMapperServiceSVC_impl
: public virtual POA_CoordinateMapperService,
public virtual PortableServer::RefCountServantBase
{
	public:
		// standard constructor
		CoordinateMapperServiceSVC_impl();
		virtual ~CoordinateMapperServiceSVC_impl();
		bool loadModel(std::string &model);

		// attributes and operations
		CoordinateSystem_slice* calcLocal2Global(const CoordinateSystem in_cs, const char* joint);
		CoordinateSystem_slice* calcGlobal2Local(const CoordinateSystem in_cs, const char* joint);

	private:
		// Make sure all instances are built on the heap by making the
		// destructor non-public
		//virtual ~CoordinateMapperServiceSVC_impl();
		mapper *map_mod;
};
#endif							 // COORDINATEMAPPERSERVICESVC_IMPL_H
