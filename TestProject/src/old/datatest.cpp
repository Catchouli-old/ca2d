#include <iostream>
#include <map>
#include <string>
#include <memory>
#include <functional>

#include "luafuncs.h"
#include "Component.h"

int main(int argc, char** argv)
{
    test();

    TransformComponent comp;

    DEFINE_COMPONENT("Transform", TransformComponent);
    DEFINE_COMPONENT("Colour", ColourComponent);

    std::shared_ptr<Component> weakTransform = addComponent("Transform");
    std::shared_ptr<Component> weakColour = addComponent("Colour");

    std::shared_ptr<TransformComponent> transform =
        std::dynamic_pointer_cast<TransformComponent>(weakTransform);
    std::shared_ptr<ColourComponent> colour =
        std::dynamic_pointer_cast<ColourComponent>(weakColour);

    transform->x = 0.0f;

    colour->r = 0.5f;

    std::cout << "Transform component type: " << componentTypeName(weakTransform.get()) << std::endl;

    system("pause");
}