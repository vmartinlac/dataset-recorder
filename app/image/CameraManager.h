#pragma once

#include <vector>
#include <memory>

class Camera
{
public:
    virtual ~Camera();
protected:
};

class CameraManager
{
public:

    CameraManager();
    ~CameraManager();

    std::vector< std::shared_ptr<Camera> > getCameras();

protected:
    static CameraManager* _instance;
};
