#ifndef FRAME_H
#define FRAME_H

#include "utils.h"

class Frame {

public:
    glm::vec3 pos;
    glm::vec3 up;
    glm::vec3 forward;

    virtual glm::vec3 s() {
        return glm::cross(this->forward, this->up);
    }

    virtual glm::mat4 matrix() {

        glm::mat4 M = glm::mat4(1.0f);


        glm::vec4 norm_s = glm::vec4(glm::normalize(this->s()), 0.0f);
        glm::vec4 norm_forward = glm::vec4(glm::normalize(this->forward), 0.0f);
        glm::vec4 norm_up = glm::vec4(glm::normalize(this->up), 0.0f);

        M = glm::translate(M, this->pos);

        M[0] = norm_s;
        M[1] = norm_up;
        M[2] = norm_forward;

        return M;
    }
};

#endif // FRAME_H
