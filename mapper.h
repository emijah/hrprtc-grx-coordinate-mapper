#ifndef __COORDINATEMAPPER_H__
#define __COORDINATEMAPPER_H__

#include <hrpModel/ModelLoaderUtil.h>
#define ONLINE_VIEW
#ifdef ONLINE_VIEW
#include <hrpUtil/OnlineViewerUtil.h>
#endif

class mapper
{
public:
    mapper() : olv(NULL) {
    };
    ~mapper() {
    };
    bool load(std::string &model);
    bool l2g(const double in_cs[6], double out_cs[6], const char* joint);
    bool g2l(const double in_cs[6], double out_cs[6], const char* joint);

private:
    hrp::BodyPtr body;
    #ifdef ONLINE_VIEW
    OpenHRP::OnlineViewer_var olv;
    OpenHRP::WorldState *world;
    OpenHRP::CharacterPosition *robot;
    OpenHRP::CharacterPosition *dice;
    #endif
};
#endif                           /*  __COORDINATEMAPPER_H__ */
