#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>

namespace ca2d
{
    /**
    *   \brief An abstract camera class
    *   
    *   An abstract camera class that can be extended to customise camera behaviour.
    *   To extend the behaviour of this class, you can override update, and use it to
    *   set the available camera matrices and vectors.
    */
    class Camera
    {
    public:

        /** Pure virtual method that must update the camera vectors and matrices */
        virtual void update(float dt) = 0;

        /** Get the position of this camera */
        const glm::vec3& getPosition() const;

        /** Set the position of this camera */
        void setPosition(const glm::vec3& position);

        /** Get the rotation of this camera */
        const glm::quat& getRotation() const;

        /** Set the position of this camera */
        void setRotation(const glm::quat& rotation);

        /** Get a forward-facing vector for this camera */
        const glm::vec3& getForward() const;

        /** Get an up-facing vector for this camera */
        const glm::vec3& getUp() const;

        /** Get a right-facing vector for this camera */
        const glm::vec3& getRight() const;

        /** Get the projection matrix for this camera */
        const glm::mat4& getProjection() const;

        /** Get the view matrix for this camera */
        const glm::mat4& getView() const;

        /** Get a combined projection * view matrix for this camera */
        const glm::mat4& getCombined() const;

    protected:

        /** Camera forward vector */
        glm::vec3 mForward;

        /** Camera up vector */
        glm::vec3 mUp;

        /** Camera left vector */
        glm::vec3 mRight;

        /** Camera matrices */
        glm::mat4 mProjection, mView, mCombined;

        /** The position of the camera */
        glm::vec3 mPosition;

        /** The rotation of the camera */
        glm::quat mRotation;

    };
    
    /** Get the position of the camera in world space */
    inline const glm::vec3& Camera::getPosition() const
    {
        return mPosition;
    }

    /** Set the position of the camera in world space */
    inline void Camera::setPosition(const glm::vec3& position)
    {
        mPosition = position;
    }

    /** Get the rotation of the camera */
    inline const glm::quat& Camera::getRotation() const
    {
        return mRotation;
    }

    /** Set the rotation of the camera */
    inline void Camera::setRotation(const glm::quat& rotation)
    {
        mRotation = rotation;
    }

    /** Get the forward vector for the camera */
    inline const glm::vec3& Camera::getForward() const
    {
        return mForward;
    }

    /** Get the up vector for the camera */
    inline const glm::vec3& Camera::getUp() const
    {
        return mUp;
    }

    /** Get the left vector for the camera */
    inline const glm::vec3& Camera::getRight() const
    {
        return mRight;
    }

    /** Get the projection matrix of the camera */
    inline const glm::mat4& Camera::getProjection() const
    {
        return mProjection;
    }

    /** Get the view matrix of the camera */
    inline const glm::mat4& Camera::getView() const
    {
        return mView;
    }

    /** Get a combined projection-view matrix for the camera */
    inline const glm::mat4& Camera::getCombined() const
    {
        return mCombined;
    }
}