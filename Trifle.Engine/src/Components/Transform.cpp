#include "Transform.h"
#include <glm/glm.hpp>
#include "../Math/MatrixHelper.h"

Transform::Transform() 
    : Component()
{
    SetPosition(glm::vec3(0.0f,0.0f,0.0f));
    Scale(1.0f);
    Rotate(glm::vec3(0.0f,0.0f,0.0f));
}

Transform::Transform(const Transform &rhs)
{
    m_localPos = rhs.m_localPos;
    m_localRot = rhs.m_localRot;
    m_localScale = rhs.m_localScale;
    m_isDirty = true;
}

Transform::~Transform()
{
}


void Transform::SetPosition(const glm::vec3 &pos)
{
    bool isChanged = m_localPos.x != pos.x || m_localPos.y != pos.y || m_localPos.z != pos.z; 

    if (isChanged)
    {
        m_localPos.x = pos.x;
        m_localPos.y = pos.y;
        m_localPos.z = pos.z;
    }

    m_isDirty = m_isDirty || isChanged;
}

glm::vec3 Transform::GetPosition()
{
    return m_localPos;
}

glm::vec3 Transform::GetScale()
{
    return m_localScale;
}

glm::vec3 Transform::GetRotaion()
{
    return m_localRot;
}

void Transform::Translate(float x, float y, float z)
{
    m_localPos.x += x;
    m_localPos.y += y;
    m_localPos.z += z;

    m_isDirty = m_isDirty || (x + y + z > 0.0f);
}

void Transform::Translate(const glm::vec3 &vector)
{
    Translate(vector.x, vector.y, vector.z);
}    

void Transform::TranslateX(float x)
{    
    Translate(x, 0.0f, 0.0f);
}

void Transform::TranslateY(float y)
{    
    Translate(0.0f, y, 0.0f);
}

void Transform::TranslateZ(float z)
{
    Translate(0.0f, 0.0f, z);
}

void Transform::Rotate(float x, float y, float z)
{
    m_localRot.x += x;
    m_localRot.y += y;
    m_localRot.z += z;

    m_isDirty = m_isDirty || (x + y + z > 0);
}

void Transform::Rotate(const glm::vec3 &vector)
{
    Rotate(vector.x, vector.y, vector.z);
}

void Transform::RotateX(float x)
{
    Rotate(x, 0.0f, 0.0f);
}

void Transform::RotateY(float y)
{
    Rotate(0.0f, y, 0.0f);
}

void Transform::RotateZ(float z)
{
    Rotate(0.0f, 0.0f, z);
}

void Transform::Scale(float x, float y, float z)
{
    bool isChanged = m_localScale.x != x || m_localScale.y != y || m_localScale.z != z; 

    if (isChanged)
    {
        m_localScale.x = x;
        m_localScale.y = y;
        m_localScale.z = z;
    }

    m_isDirty = m_isDirty || isChanged;
}

void Transform::Scale(float amt)
{
    Scale(amt, amt, amt);
}

void Transform::UpdateWorldMatrix()
{
    m_mtxWorld = glm::mat4();
    m_mtxWorld *= GetScaleMatrix();
    m_mtxWorld *= GetRotaionMatrix();
    m_mtxWorld *= GetTranslationMatrix();
}

glm::mat4 Transform::GetScaleMatrix()
{
    return MatrixHelper::CreateScaleMatrix(m_localScale);
}

glm::mat4 Transform::GetRotaionMatrix()
{
    return MatrixHelper::CreateRotationMatrix(m_localRot);
}

glm::mat4 Transform::GetTranslationMatrix()
{
    return MatrixHelper::CreateTranslationMatrix(m_localPos);
}

glm::mat4 Transform::GetWorldMatrix()
{
    if (m_isDirty)
    {
        UpdateWorldMatrix();
    }

    return m_mtxWorld;
}
