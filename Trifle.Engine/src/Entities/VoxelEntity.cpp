#include "VoxelEntity.h"
#include "../Components/Components.h"
#include "../Util/Util.h"
#include "../Entities/VoxelEntity.h"

using namespace tfl;

VoxelEntity::VoxelEntity()
{
}

VoxelEntity::VoxelEntity(const VoxelEntity& rhs) : Entity(rhs)
{
/*     OnPositionChanged = EventHandler(rhs.OnPositionChanged.GetEventId());
    OnRotationChanged = EventHandler(rhs.OnRotationChanged.GetEventId());
    OnSizeChanged = EventHandler(rhs.OnSizeChanged.GetEventId()); */
}

VoxelEntity::~VoxelEntity()
{
}

void VoxelEntity::Init()
{
    this->Register();

    AddComponent<Transform>();
    AddComponent<ColourComponent>();

    Transform& trans = GetComponent<Transform>();

    //std::function<void(EventArgs&)> func = [this](EventArgs& e) { this->OnTransformChangedCallback(e); };

    //trans.OnPositionChanged.Subscribe(func);
}

void VoxelEntity::SetPosition(glm::vec3 position)
{
    Transform& transform = GetComponent<Transform>();
    glm::vec3 oldRot = transform.GetPosition();

    transform.SetPosition(position);
    //NotifyPositionChanged(oldRot, position);
}

Point3 VoxelEntity::GetPoint()
{
    Transform& transform = GetComponent<Transform>();
    glm::vec3 pos = transform.GetPosition();
    return {(int)pos.x, (int)pos.y, (int)pos.z};
}

void VoxelEntity::SetPoint(Point3 point)
{
    Transform& transform = GetComponent<Transform>();
    glm::vec3 pos = {point.x, point.y, point.z};
    transform.SetPosition(pos);
}

void VoxelEntity::Move(const glm::vec3& moveVector)
{
    Transform& transform = GetComponent<Transform>();
    glm::vec3 oldRot = transform.GetPosition();
   
    transform.Translate(moveVector);

    //NotifyPositionChanged(oldRot, transform.GetPosition());
}

void VoxelEntity::Rotate(const glm::vec3& rotationVector)
{
    Transform& transform = GetComponent<Transform>();
    transform.Rotate(rotationVector);
}


void VoxelEntity::SetColour(const Colour& colour)
{
    ColourComponent& clr = GetComponent<ColourComponent>();
    clr.colour.r = colour.r;
    clr.colour.g = colour.g;
    clr.colour.b = colour.b;
    clr.colour.a = colour.a;
}

Colour VoxelEntity::GetColour()
{
    return GetComponent<ColourComponent>().colour;
}

unsigned int tfl::VoxelEntity::GetSize()
{
    Transform& transform = GetComponent<Transform>();
    glm::vec3 scale = transform.GetScale();
    return (scale.x + scale.y + scale.z) / 3.0f;
}

/* void VoxelEntity::OnTransformChangedCallback(EventArgs& e)
{
    TransformChangedArgs& args = e.GetData<TransformChangedArgs>();

    switch (args.type)
    {
        case TransformChangedType::Position :
            NotifyPositionChanged(args.oldValue, args.newValue);
        break;

        case TransformChangedType::Rotation : 
            NotifyPositionChanged(args.oldValue, args.newValue);
        break;

        case TransformChangedType::Scale : 
            NotifyScaleChanged(args.oldValue, args.newValue);
        break;
    }
} */


/* void VoxelEntity::NotifyPositionChanged(const glm::vec3& oldVal, const glm::vec3& newVal)
{
    OnPositionChangedArgs evtArgs;
    evtArgs.entityId = GetId();
    evtArgs.oldPos = {oldVal.x, oldVal.y, oldVal.z};
    evtArgs.newPos = {newVal.x, newVal.y, newVal.z};

    OnPositionChanged.Invoke<OnPositionChangedArgs>(evtArgs);
}

void VoxelEntity::NotifyRotationChanged(const glm::vec3& oldVal, const glm::vec3& newVal)
{
    OnRotationChangedArgs evtArgs;
    evtArgs.entityId = GetId();
    evtArgs.oldRot = {oldVal.x, oldVal.y, oldVal.z};
    evtArgs.newRot = {newVal.x, newVal.y, newVal.z};

    OnRotationChanged.Invoke<OnRotationChangedArgs>(evtArgs);
}

void VoxelEntity::NotifyScaleChanged(const glm::vec3& oldSize, const glm::vec3& newSize)
{
    OnSizeChangedArgs evtArgs;
    evtArgs.entityId = GetId();
    evtArgs.oldSize = oldSize;
    evtArgs.newSize = newSize;
    OnSizeChanged.Invoke<OnSizeChangedArgs>(evtArgs);
} */