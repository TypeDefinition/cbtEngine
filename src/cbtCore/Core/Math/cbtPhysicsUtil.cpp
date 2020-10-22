//
// Created by lnxterry on 22/10/20.
//

#include "cbtPhysicsUtil.h"

NS_CBT_BEGIN

    cbtF32 cbtPhysicsUtil::GetLinearDisplacement(cbtF32 _initialVelocity, cbtF32 _acceleration, cbtF32 _time)
    {
        return _initialVelocity * _time + 0.5f * _acceleration * _time * _time;
    }

    cbtF32 cbtPhysicsUtil::GetLinearDisplacement2(cbtF32 _initialVelocity, cbtF32 _finalVelocity, cbtF32 _time)
    {
        return (_initialVelocity + _finalVelocity) * 0.5f * _time;
    }

    cbtF32 cbtPhysicsUtil::GetVelocitySquared(cbtF32 _initialVelocity, cbtF32 _acceleration, cbtF32 _displacement)
    {
        return _initialVelocity * _initialVelocity + 2.0f * _acceleration * _displacement;
    }

    cbtF32 cbtPhysicsUtil::GetVelocity(cbtF32 _initialVelocity, cbtF32 _acceleration, cbtF32 _time)
    {
        return _initialVelocity + _acceleration * _time;
    }

    cbtF32 cbtPhysicsUtil::GetAngle(cbtF32 _radius, cbtF32 _arcLength)
    {
        return _arcLength / _radius;
    }

    cbtF32 cbtPhysicsUtil::GetArcLength(cbtF32 _radius, cbtF32 _angle)
    {
        return _radius * _angle;
    }

    cbtF32 cbtPhysicsUtil::GetRadius(cbtF32 _angle, cbtF32 _arcLength)
    {
        return _arcLength / _angle;
    }

    cbtF32 cbtPhysicsUtil::GetAngularVelocity(cbtF32 _deltaAngularDisplacement, cbtF32 _deltaTime)
    {
        return _deltaAngularDisplacement / _deltaTime;
    }

NS_CBT_END