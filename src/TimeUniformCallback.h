/* 
 * File:   TimeUniformCallback.h
 * Author: allan
 *
 * Created on September 26, 2015, 3:10 PM
 */

#ifndef TIMEUNIFORMCALLBACK_H
#define	TIMEUNIFORMCALLBACK_H

#include <osg/Uniform>
#include <osg/NodeVisitor>


class TimeUniformCallback : public osg::Uniform::Callback
{
public:
    
    TimeUniformCallback() {};
    
    ~TimeUniformCallback() {};
    
    virtual void operator()( osg::Uniform* u, osg::NodeVisitor* nv )
    {
        float t = (float)nv->getFrameStamp()->getReferenceTime();
        u->set( t );
    }
};

#endif	/* TIMEUNIFORMCALLBACK_H */

