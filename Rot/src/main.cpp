#include <Anxiety.h>
#include <AnxietyMain.h>

#include "Rot.h"

Anx::Application* Anx::CreateApplication()
{
    return new Rot::Rot();
}
