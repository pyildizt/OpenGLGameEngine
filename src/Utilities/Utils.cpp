#include "Utilities/Utils.h"

glm::vec4 RGBAtoVec4(int r, int g, int b, int a)
{
    return glm::vec4{r/255.0f, g/255.0f, b/255.0f, a/255.0f};
}