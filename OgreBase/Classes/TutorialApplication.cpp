/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.cpp
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _ 
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/                              
      Tutorial Framework
      http://www.ogre3d.org/tikiwiki/
-----------------------------------------------------------------------------
*/
#include "TutorialApplication.h"

//-------------------------------------------------------------------------------------
TutorialApplication::TutorialApplication(void)
{
}
//-------------------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{
}


bool TutorialApplication::frameStarted(const Ogre::FrameEvent& evt)
{
	baseAnim->addTime(evt.timeSinceLastFrame);
	topAnim->addTime(evt.timeSinceLastFrame);	

    return true;
}

//-------------------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{
    // Set the scene's ambient light
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));
	
    // Create a Light and set its position
    Ogre::Light* light = mSceneMgr->createLight("MainLight");
    light->setPosition(20.0f, 80.0f, 50.0f);
	
	
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	
    Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
												  plane, 1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
	
    Ogre::Entity* entGround = mSceneMgr->createEntity("GroundEntity", "ground");
    mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entGround);
	
    entGround->setMaterialName("Examples/Rockwall");
    entGround->setCastShadows(false);
	
	mSceneMgr->setSkyDome(true, "Examples/CloudySky", 5, 8);
	
	Ogre::Entity* entSinbad = mSceneMgr->createEntity("Ninja", "Sinbad.mesh");
	
	entSinbad->setCastShadows(true);
	entSinbad->getSkeleton()->setBlendMode(Ogre::ANIMBLEND_CUMULATIVE);
	
	Ogre::SceneNode* nodeSinbad = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	nodeSinbad->setPosition(0, 74, 0);
	nodeSinbad->scale(15,15,15);
	nodeSinbad->attachObject(entSinbad);

	//Get the two halves of the idle animation.
	baseAnim = entSinbad->getAnimationState("IdleBase");
	topAnim = entSinbad->getAnimationState("IdleTop");

	//Enable both of them and set them to loop.
	baseAnim->setLoop(true);
	topAnim->setLoop(true);
	baseAnim->setEnabled(true);
	topAnim->setEnabled(true);	
}



#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        TutorialApplication app;

        try {
            app.go();
        } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            Ogre::String workingDir = Ogre::macBundlePath()+"/Contents/Resources";
            chdir(workingDir.c_str());
            std::cout << "working directory: "+workingDir+"\n";
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif
