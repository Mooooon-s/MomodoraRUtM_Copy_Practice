#include "MnComponent.h"

namespace Mn
{
    Component::Component(eComponentType Type)
        : _Type(Type)
    {
    }
    Component::~Component()
    {
    }
    void Component::Initialize()
    {
    }
    void Component::Update()
    {
    }
    void Component::Render(HDC hdc)
    {
    }
    void Component::Release()
    {
    }
}