#ifndef OCTOON_PHYSICS_SCENE_H_
#define OCTOON_PHYSICS_SCENE_H_

#include <memory>

#include <octoon/runtime/platform.h>
#include <octoon/math/math.h>

#include <octoon/physics/physics_type.h>
#include <octoon/physics/physics_rigidbody.h>

namespace octoon
{
    namespace physics
    {
		struct OCTOON_EXPORT PhysicsSceneDesc
		{
			math::float3 gravity;
		};

        class OCTOON_EXPORT PhysicsScene
        {
        public:
			PhysicsScene() noexcept;
			~PhysicsScene() noexcept;

			virtual void addRigidbody(std::shared_ptr<PhysicsRigidbody> rigidbody) = 0;

		private:
			PhysicsScene(const PhysicsScene&) = delete;
			PhysicsScene& operator=(const PhysicsScene&) = delete;
        };
    }
}

#endif