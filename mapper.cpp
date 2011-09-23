#include <hrpUtil/Tvmet3d.h>
#include <hrpModel/Link.h>
#include <hrpModel/LinkTraverse.h>
#include <hrpModel/JointPath.h>

#include "mapper.h"

bool
mapper::load(std::string &model)
{
    std::string url = "file://" + model;

    // load the model
    int argc = 1;
    char* argv[] = {" "};
    body = new hrp::Body();
    if(!hrp::loadBodyFromModelLoader(body, url.c_str(), argc, argv))
    {
        std::cerr << "ModelLoader: " << url << " cannot be loaded" << std::endl;
        return 0;
    }

    #ifdef ONLINE_VIEW
    // OnlineViewer settings  //
    try
    {
        olv = hrp::getOnlineViewer(argc, argv);
        olv->load(body->modelName().c_str(), url.c_str());
        olv->clearLog();
    }
    catch (CORBA::SystemException& ex)
    {
        std::cerr << "Failed to connect GrxUI." << std::endl;
        return 1;
    }
    // create WorldState
    world = new OpenHRP::WorldState();
    world->characterPositions.length(1);
    //world->characterPositions.length(2); // if use dice
    world->collisions.length(0);
    world->time=0;
    robot = &(world->characterPositions[0]);
    robot->characterName = CORBA::string_dup("HIRO");
    //dice = &(world->characterPositions[1]);
    //dice->characterName = CORBA::string_dup("dice");
    #endif
    std::cerr << "robot loaded." << std::endl;
    body->calcForwardKinematics();
}


bool
mapper::l2g(const double in_cs[6], double out_cs[6], const char *joint)
{
    /*
       // to debug, set arbitrary angles
       std::cerr << "in_cs: " << in_cs[0]<<","<<in_cs[1]<<","<<in_cs[2] << std::endl;
       hrp::Link* root  = body->link("WAIST");
       root->p[2] = 0.89;
       root->q = 90*M_PI/180.0;
       hrp::Link* lj2  = body->link("LARM_JOINT2");
       lj2->q = -90*M_PI/180.0;
       //lj2->q -= 0.1;
       hrp::Link* lj3  = body->link("LARM_JOINT3");
       lj3->q = -15*M_PI/180.0;
       //lj3->q -= 0.05;
       body->calcForwardKinematics();
     */

    // *************************************************
    //
    // ex.) hrp::Link* lj2  = body->link("LARM_JOINT2");
    //      lj2->q = -90*M_PI/180.0;
    // *************************************************

    //local
    hrp::Link* local  = body->link(joint);
    hrp::Vector3 t = local->p;
    hrp::Matrix33 at = local->attitude();

    // in_cs[:3] are positions, in_cs[3:] are rotations
    hrp::Vector3 p_in;
    for(int i=0; i<3; i++) p_in[i] = in_cs[i];
    hrp::Matrix33 R1;
    hrp::calcRotFromRpy(R1, in_cs[3], in_cs[4], in_cs[5]);
    hrp::Vector3 rpy = hrp::rpyFromRot(hrp::Matrix33(at * R1));
    hrp::Vector3 _tmp = hrp::Vector3(hrp::Vector3(at * p_in) + t);

    // out_cs[:3] are positions, out_cs[3:] are rotations
    for(int i=0; i<3; i++)
    {
        out_cs[i] = _tmp[i];
        out_cs[i+3] = rpy[i];
    }

    #ifdef ONLINE_VIEW
    std::cerr << "online" << std::endl;
    world->time+=0.01;           //
    // copy Links to WorldState
    int n = body->numLinks();
    robot->linkPositions.length(n);
    for (int i=0; i<n; i++)
    {
        hrp::Link* link = body->link(i);
        hrp::setVector3(link->p, robot->linkPositions[i].p);
        hrp::setMatrix33ToRowMajorArray(link->attitude(), robot->linkPositions[i].R);
    }
    /*
       n = 1;
       dice->linkPositions.length(n);
       for (int i=0; i<n; i++) {
        hrp::setVector3(hrp::Vector3(0,0,2.0), dice->linkPositions[i].p);
        hrp::Matrix33 identity;
        hrp::calcRotFromRpy(identity, 0, 0, 0);
        hrp::setMatrix33ToRowMajorArray(identity, dice->linkPositions[i].R);
       }
     */
    // update OnlineViewer
    try
    {
        olv->update(*world);
    }
    catch (CORBA::SystemException& ex)
    {
        std::cerr << "OnlineViewer could not be updated." << std::endl;
        return 1;
    }
    #endif

    return true;
}


bool
mapper::g2l(const double in_cs[6], double out_cs[6], const char *joint)
{
    // *************************************************
    //
    // ex.) hrp::Link* lj2  = body->link("LARM_JOINT2");
    //      lj2->q = -90*M_PI/180.0;
    // *************************************************

    hrp::Link* local  = body->link(joint);
    hrp::Vector3 t = local->p;
    hrp::Matrix33 at = local->attitude();

    hrp::Vector3 p_in;
    for(int i=0; i<3; i++) p_in[i] = in_cs[i];
    hrp::Matrix33 R1;
    hrp::calcRotFromRpy(R1, in_cs[3], in_cs[4], in_cs[5]);
    hrp::Matrix33 at_t;
    // inverse matrix
    hrp::setTransMatrix33(at, at_t);
    hrp::Vector3 rpy = hrp::rpyFromRot(hrp::Matrix33(at_t * R1));
    hrp::Vector3 _tmp = hrp::Vector3(hrp::Vector3(at_t * p_in) - t);

    for(int i=0; i<3; i++)
    {
        out_cs[i] = _tmp[i];
        out_cs[i+3] = rpy[i];
    }

    return true;
}
