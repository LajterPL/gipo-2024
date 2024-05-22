#ifndef CAMERA_H
#define CAMERA_H

#include <frame.h>

class Camera : public Frame {

public:
    virtual glm::vec3 s() {
        return glm::cross(this->forward, this->up);
    }

    virtual glm::mat4 matrix() {

        glm::mat4 M = glm::mat4(1.0f);

        glm::vec3 norm_s = glm::normalize(this->s());
        glm::vec3 norm_forward = glm::normalize(this->forward);
        glm::vec3 norm_up = glm::normalize(this->up);


        M[0][0] = norm_s.x;
        M[1][0] = norm_s.y;
        M[2][0] = norm_s.z;

        M[0][1] = norm_up.x;
        M[1][1] = norm_up.y;
        M[2][1] = norm_up.z;

        M[0][2] = -norm_forward.x;
        M[1][2] = -norm_forward.y;
        M[2][2] = -norm_forward.z;

        M[3] = glm::vec4(-this->pos, 1.0f);

        return M;
    }

};

#endif // CAMERA_H
