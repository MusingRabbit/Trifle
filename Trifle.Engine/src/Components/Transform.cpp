#include "Transform.h"
#include "../Util/Util.h"

using namespace tfl;

Transform::Transform()
{
    SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    Scale(1.0f);
    SetRotation(0, 0, 0);
}

Transform::Transform(const Transform& rhs)
{
    m_localPos = rhs.m_localPos;
    m_localRot = rhs.m_localRot;
    m_localScale = rhs.m_localScale;
    m_isDirty = true;

/*     OnPositionChanged = rhs.OnPositionChanged;
    OnRotationChanged = rhs.OnRotationChanged;
    OnScaleChanged = rhs.OnScaleChanged; */
}

/* Transform::Transform(Transform&& rhs)
{
    m_localPos = rhs.m_localPos;
    m_localRot = rhs.m_localRot;
    m_localScale = rhs.m_localScale;
    m_isDirty = true;

    OnPositionChanged.Init();
    OnRotationChanged.Init();
    OnScaleChanged.Init();

    OnPositionChanged.SwapListeners(rhs.OnPositionChanged);
    OnRotationChanged.SwapListeners(rhs.OnRotationChanged);
    OnScaleChanged.SwapListeners(rhs.OnScaleChanged);
} */

Transform::~Transform()
{
    
}

void Transform::SetPosition(const glm::vec3& pos)
{
    SetPosition(pos.x, pos.y, pos.z);
}

void Transform::SetPosition(float x, float y, float z)
{
    glm::vec3 oldVal = m_localPos;
    bool isChanged = m_localPos.x != x || m_localPos.y != y || m_localPos.z != z;

    if (isChanged)
    {
        m_localPos.x = x;
        m_localPos.y = y;
        m_localPos.z = z;

        m_isDirty = true;

        /*TransformChangedArgs args{ TransformChangedType::Position, oldVal , m_localPos};
        OnPositionChanged.Invoke(args); */
    }
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
    glm::vec3 oldVal = m_localPos;

    m_localPos.x += x;
    m_localPos.y += y;
    m_localPos.z += z;

    m_isDirty = m_isDirty || (x + y + z > 0.0f);

    /*if (m_isDirty && OnPositionChanged.HasEventRegister())
    {
        TransformChangedArgs args{ TransformChangedType::Position, oldVal , m_localPos};
        OnPositionChanged.Invoke(args);
    } */
}

void Transform::Translate(const glm::vec3& vector)
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

void Transform::SetRotation(float x, float y, float z)
{
    bool isChanged = m_localRot.x != x || m_localRot.y != y || m_localRot.z != z;

    if (isChanged)
    {
        glm::vec3 oldVal = m_localRot;

        m_localRot.x = x;
        m_localRot.y = y;
        m_localRot.z = z;

        m_isDirty = true;
        /*if (OnRotationChanged.HasEventRegister())
        {
            TransformChangedArgs args{ TransformChangedType::Rotation, oldVal , m_localRot};
            OnRotationChanged.Invoke(args);
        } */
    }
}

void Transform::Rotate(float x, float y, float z)
{
    glm::vec3 oldVal = m_localRot;

    m_localRot.x += x;
    m_localRot.y += y;
    m_localRot.z += z;

    m_isDirty = m_isDirty || (x + y + z > 0);

    /*if (m_isDirty && OnRotationChanged.HasEventRegister())
    {
        TransformChangedArgs args{ TransformChangedType::Rotation, oldVal , m_localRot};
        OnRotationChanged.Invoke(args);
    } */
}

void Transform::Rotate(const glm::vec3& vector)
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
        glm::vec3 oldVal = m_localScale;

        m_localScale.x = x;
        m_localScale.y = y;
        m_localScale.z = z;

        m_isDirty = true;

        /*if (OnScaleChanged.HasEventRegister())
        {
            TransformChangedArgs args{ TransformChangedType::Scale, oldVal , m_localScale};
            OnScaleChanged.Invoke(args);
        } */
    }
}

void Transform::Scale(float amt)
{
    Scale(amt, amt, amt);
}

void Transform::UpdateWorldMatrix()
{
    m_mtxWorld = glm::identity<glm::mat4>();
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

/* void tfl::Transform::SetEventRegister(std::shared_ptr<IEventRegister> evtRegister)
{
    OnPositionChanged.Init(m_evtRegister);
    OnRotationChanged.Init(m_evtRegister);
    OnScaleChanged.Init(m_evtRegister);
} */

bool Transform::IsDirty()
{
    return m_isDirty;
}

void Transform::ResetIsDirtyFlag()
{
    m_isDirty = false;
}

/* void Transform::InitCallbacks()
{
    OnPositionChanged.Init();
    OnRotationChanged.Init();
    OnScaleChanged.Init();
}
 */
glm::mat4 Transform::GetWorldMatrix(bool forceRefresh)
{
    if (m_isDirty || forceRefresh)
    {
        UpdateWorldMatrix();
    }

    return m_mtxWorld;
}

bool Transform::IsEqual(const Transform& rhs)
{
    bool result = true;

    result = result && m_localPos == rhs.m_localPos;
    result = result && m_localRot == rhs.m_localRot;
    result = result && m_localScale == rhs.m_localScale;

    return result;
}