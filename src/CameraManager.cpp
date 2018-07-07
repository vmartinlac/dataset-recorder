#include <VimbaCPP/Include/VimbaCPP.h>
#include "CameraManager.h"

CameraManager* CameraManager::_instance = nullptr;

CameraManager::CameraManager()
{
    if( _instance != nullptr )
    {
        abort();
    }

    _instance = this;

    AVT::VmbAPI::VimbaSystem::GetInstance().Startup();
}

CameraManager::~CameraManager()
{
    if( _instance != this )
    {
        abort();
    }

    delete _instance;

    _instance = nullptr;

    AVT::VmbAPI::VimbaSystem::GetInstance().Shutdown();
}

std::vector< std::shared_ptr<Camera> > CameraManager::getCameras()
{
    std::vector< std::shared_ptr<Camera> > ret;

    return ret;
}
