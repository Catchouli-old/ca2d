#ifndef RENDER_UTILS_CAMERA_H
#define RENDER_UTILS_CAMERA_H

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>

namespace rend
{
    class Camera
    {
    public:
        virtual void update(float dt) = 0;

        /* Accessors and mutators for the position and rotation of the camera */
        const glm::vec3& getPosition() const;
        void setPosition(const glm::vec3& position);

        const glm::quat& getRotation() const;
        void setRotation(const glm::quat& rotation);

        /* Accessors for the vectors that define this camera */
        const glm::vec3& getForward() const;
        const glm::vec3& getUp() const;
        const glm::vec3& getLeft() const;

        /* Accessors for the matrices that define this camera */
        const glm::mat4& getProjection() const;
        const glm::mat4& getView() const;
        const glm::mat4& getCombined() const;

    protected:

        /* Camera vectors */
        glm::vec3 mForward, mUp, mLeft;

        /* Camera matrices */
        glm::mat4 mProjection, mView, mCombined;

        /* The position of the camera */
        glm::vec3 mPosition;

        /* The rotation of the camera */
        glm::quat mRotation;
    };

    inline const glm::vec3& Camera::getPosition() const
    {
        return mPosition;
    }

    inline void Camera::setPosition(const glm::vec3& position)
    {
        mPosition = position;
    }

    inline const glm::quat& Camera::getRotation() const
    {
        return mRotation;
    }

    inline void Camera::setRotation(const glm::quat& rotation)
    {
        mRotation = rotation;
    }

    inline const glm::vec3& Camera::getForward() const
    {
        return mForward;
    }

    inline const glm::vec3& Camera::getUp() const
    {
        return mUp;
    }

    inline const glm::vec3& Camera::getLeft() const
    {
        return mLeft;
    }

    inline const glm::mat4& Camera::getProjection() const
    {
        return mProjection;
    }

    inline const glm::mat4& Camera::getView() const
    {
        return mView;
    }

    inline const glm::mat4& Camera::getCombined() const
    {
        return mCombined;
    }
}

#endif /* RENDER_UTILS_CAMERA_H */