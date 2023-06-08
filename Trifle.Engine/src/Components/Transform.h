#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Component.h"
#include <glm/glm.hpp>

class Transform : Component
{
private:
    glm::mat4 m_mtxWorld;

    glm::vec3 m_localRot;
    glm::vec3 m_localPos;
    glm::vec3 m_localScale;

    bool m_isDirty;     // Determines whether the world matrix needs to be updated/recalculated on GetWorldMatrix

    void UpdateWorldMatrix();

    glm::mat4 GetScaleMatrix();
    glm::mat4 GetRotaionMatrix();
    glm::mat4 GetTranslationMatrix();
    
public:
    /// @brief Constructor.
    Transform();

    /// @brief Copy Constructor.
    /// @param rhs Source Transform.
    Transform(const Transform& rhs);
    
    /// Destructor
    ~Transform();

    /// @brief Sets the world position of the transform.
    /// @param pos Position.
    void SetPosition(const glm::vec3& pos);

    /// @brief Gets the tranforms current position vector.
    /// @return Position vector.
    glm::vec3 GetPosition();
    
    /// @brief Gets the transforms current scale vector.
    /// @return Scale vector.
    glm::vec3 GetScale();

    /// @brief Gets the transforms current rotation vector.
    /// @return Rotation vector.
    glm::vec3 GetRotaion();
    
    /// @brief Translates the transforms position by the specified x, y and z magnitude
    /// @param x Amount to transform position on the x axis by.
    /// @param y Amount to transform position on the y axis by.
    /// @param z Amount to transform position on the z axis by.
    void Translate(float x, float y, float z);

    /// @brief Translates the transforms position by the specified vector.
    /// @param vector Vector by which to perform the transform.
    void Translate(const glm::vec3& vector);
    
    /// @brief Translates the transform on the x axis.
    /// @param x Amount to update the transform position by.
    void TranslateX(float x);

    /// @brief Translates the transform on the y axis.
    /// @param y Amount to update the transform position by.
    void TranslateY(float y);

    /// @brief Translates the transform on the z axis.
    /// @param z Amount to update the transform position by.
    void TranslateZ(float z);

    /// @brief Rotates the transform by the specied x, y and z values.
    /// @param x Amount to rotate the transform on the x axis by.
    /// @param y Amount to rotate the transform on the y axis by.
    /// @param z Amount to rotate the transform on the z axis by.
    void Rotate(float x, float y, float z);

    /// @brief Rotates the transform by the specied vector.
    /// @param vector Vector to rotate the transform by.
    void Rotate(const glm::vec3& vector);

    /// @brief Rotates the transform on the x axis.
    /// @param x Amopunt to update the transform rotation by.
    void RotateX(float x);

    /// @brief Rotates the transform on the y axis.
    /// @param y Amopunt to update the transform rotation by.
    void RotateY(float y);
    
    /// @brief Rotates the transform on the z axis.
    /// @param z Amopunt to update the transform rotation by.
    void RotateZ(float z);

    /// @brief Scales the transform by specified x, y and z values.
    /// @param x Amount to scale the transform on the x axis by.
    /// @param y Amount to scale the transform on the y axis by.
    /// @param z Amount to scale the transform on the z axis by.
    void Scale(float x, float y, float z);

    /// @brief Scales the transform uniformly by specified value on all axis'.
    /// @param amt Amount to scale the transform by.
    void Scale(float amt);

    /// @brief Gets the transforms' current world matrix, which is an aggregate of the transforms' Scale, Rotation and Translation matrices.
    /// @return World Matrix
    glm::mat4 GetWorldMatrix();
};




#endif // !TRANSFORM_H
