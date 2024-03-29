
#pragma once 

#include "collider.h"

#include <Jolt/Jolt.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>
#include <Jolt/Physics/Collision/Shape/CapsuleShape.h>
#include <Jolt/Physics/Collision/Shape/CylinderShape.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/Shape.h>
#include <Jolt/Geometry/ConvexSupport.h>

using compare::Base::Collider;
using compare::Base::ColliderType;
using compare::Base::Case;

using JPH::SphereShape;
using JPH::CapsuleShape;
using JPH::CylinderShape;
using JPH::BoxShape;
using JPH::Shape;
using JPH::ConvexShapeSettings;
using JPH::TransformedConvexObject;

using JPH::Mat44;

namespace compare::Jolt {

    struct JoltCollider {
        JPH::ConvexShape::SupportBuffer supportBuffer;
        JPH::VertexList vertexList;
        const JPH::Shape* shape;
    };

    struct JoltCase {
        Mat44 transform0;
        Mat44 transform1;

        JoltCollider collider0;
        JoltCollider collider1;
    };

    void init();
    void get_cases(Case* base_cases, JoltCase* jolt_cases, int length);
    bool get_intersection(JoltCase& jolt_case);
}







