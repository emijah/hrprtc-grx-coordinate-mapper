// -*-C++-*-
/*!
 * @file  CoordinateMapperService_impl.h
 * @brief Service implementation header of CoordinateMapperService.idl
 *
 */

#ifndef COORDINATEMAPPERSERVICE_IMPL_H
#define COORDINATEMAPPERSERVICE_IMPL_H

//#include "CoordinateMapperServiceSkel.h"
#include "CoordinateMapperService.hh"
#include "mapper.h"

/*
 * Example class implementing IDL interface CoordinateMapperService
 */
class CoordinateMapperService_impl
    : public virtual POA_OpenHRP::CoordinateMapperService,
    public virtual PortableServer::RefCountServantBase
{
public:
    // standard constructor
    CoordinateMapperService_impl();
    virtual ~CoordinateMapperService_impl();
    bool loadModel(std::string &model);

    // attributes and operations
    OpenHRP::CoordinateSystem_slice* calcLocal2Global(const OpenHRP::CoordinateSystem in_cs, const char* joint);
    OpenHRP::CoordinateSystem_slice* calcGlobal2Local(const OpenHRP::CoordinateSystem in_cs, const char* joint);

private:
    // Make sure all instances are built on the heap by making the
    // destructor non-public
    //virtual ~CoordinateMapperService_impl();
    mapper *map_mod;
};
#endif                           // COORDINATEMAPPERSERVICE_IMPL_H
