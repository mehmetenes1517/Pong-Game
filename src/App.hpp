#pragma once 
#include<iostream>
#include<Gorgon/Main.h>
#include<Gorgon/Window.h>
#include<Gorgon/Graphics/Layer.h>
#include<Gorgon/Input/Keyboard.h>
#include"GameClasses/Ball.hpp"
#include"GameClasses/Racket.hpp"
#include"GameClasses/MainScene.hpp"
#include"GameClasses/Base/InputManager.hpp"
#include"GameClasses/Base/PhysicsCheck.hpp"
namespace Keycodes=Gorgon::Input::Keyboard::Keycodes;
class App{
    public:

        unsigned int width,height;
        std::string title;
        bool isRunning;
        App(const std::string& title="Main Window",unsigned int width=1280,unsigned int height=720): title(title),width(width),height(height),isRunning(true) {}


        void Init(const std::string& program_name){
            //Initializing gorgon and creating a window with a layer
            Gorgon::Initialize(program_name);
            Gorgon::Window win({width,height},title);
            Gorgon::Graphics::Layer main_layer;
            win.Add(main_layer);

            //Initializing InputManager singleton
            InputManager::GetInstance()->Initialize(win);

            //Our scene ( contains all game mechanics and gameobjects )
            MainScene scene(win);
            scene.Start();
            
            while (isRunning)
            {
                double delta=static_cast<double>(Gorgon::Time::DeltaTime()) / 1000;// delta with seconds

                //clearing the screen
                main_layer.Clear();
                main_layer.Draw(Gorgon::Graphics::Color::Black);

                //Input Handling
                if(InputManager::GetInstance()->GetKey(Keycodes::Escape)){isRunning=!isRunning;}

                //Rendering the scene
                scene.Update(main_layer,delta);

                Gorgon::NextFrame();
            }
        }


};