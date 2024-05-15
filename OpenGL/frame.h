#ifndef FRAME_H
#define FRAME_H

#include "utils.h"

class Frame {

public:
    glm::vec3 pos;
    glm::vec3 up;
    glm::vec3 forward;

    glm::mat4 matrix();
};

#endif // FRAME_H
