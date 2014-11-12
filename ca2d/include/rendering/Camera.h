#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>

namespace ca2d
{
    /* A camera class */
    class Camera
    {
    public:

        /* Pure virtual method that must update the camera vectors */
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
    
    /* Get the position of the camera in world space */
    inline const glm::vec3& Camera::getPosition() const
    {
        return mPosition;
    }

    /* Set the position of the camera in world space */
    inline void Camera::setPosition(const glm::vec3& position)
    {
        mPosition = position;
    }

    /* Get the rotation of the camera */
    inline const glm::quat& Camera::getRotation() const
    {
        return mRotation;
    }

    /* Set the rotation of the camera */
    inline void Camera::setRotation(const glm::quat& rotation)
    {
        mRotation = rotation;
    }

    /* Get the forward vector for the camera */
    inline const glm::vec3& Camera::getForward() const
    {
        return mForward;
    }

    /* Get the up vector for the camera */
    inline const glm::vec3& Camera::getUp() const
    {
        return mUp;
    }

    /* Get the left vector for the camera */
    inline const glm::vec3& Camera::getLeft() const
    {
        return mLeft;
    }

    /* Get the projection matrix of the camera */
    inline const glm::mat4& Camera::getProjection() const
    {
        return mProjection;
    }

    /* Get the view matrix of the camera */
    inline const glm::mat4& Camera::getView() const
    {
        return mView;
    }

    /* Get a combined projection-view matrix for the camera */
    inline const glm::mat4& Camera::getCombined() const
    {
        return mCombined;
    }
}