//
// Created by lnxterry on 22/10/20.
//

#ifndef CBTENGINE_CBTPHYSICSUTIL_H
#define CBTENGINE_CBTPHYSICSUTIL_H

#include "cbtMacros.h"
#include "cbtMathUtil.h"

NS_CBT_BEGIN

    class cbtPhysicsUtil {
    public:
        // Linear Motion
        /// s = ut + 0.5at^2
        cbtF32 GetLinearDisplacement(cbtF32 _initialVelocity, cbtF32 _acceleration, cbtF32 _time);

        /// v = (u + t)/2 * t
        cbtF32 GetLinearDisplacement2(cbtF32 _initialVelocity, cbtF32 _finalVelocity, cbtF32 _time);

        /// v^2 = u^2 + 2as
        cbtF32 GetVelocitySquared(cbtF32 _initialVelocity, cbtF32 _acceleration, cbtF32 _displacement);

        /// v = u + at
        cbtF32 GetVelocity(cbtF32 _initialVelocity, cbtF32 _acceleration, cbtF32 _time);

        // Rotational Motion
        cbtF32 GetAngle(cbtF32 _radius, cbtF32 _arcLength);

        cbtF32 GetArcLength(cbtF32 _radius, cbtF32 _angle);

        cbtF32 GetRadius(cbtF32 _angle, cbtF32 _arcLength);

        cbtF32 GetAngularVelocity(cbtF32 _deltaAngularDisplacement, cbtF32 _deltaTime);

    };

NS_CBT_END

#endif //CBTENGINE_CBTPHYSICSUTIL_H