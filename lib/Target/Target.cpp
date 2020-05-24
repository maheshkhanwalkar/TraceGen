#include "Target.h"

using namespace tg;

Target::Target(TargetType type) : type(type) { }

TargetType Target::getType()
{
    return type;
}
