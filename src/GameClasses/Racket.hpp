#pragma once

#include"Base/GameObject.hpp"
#include"Base/InputManager.hpp"

using Gorgon::Input::Keyboard::Key;
namespace Keycodes=Gorgon::Input::Keyboard::Keycodes;

class Racket: public GameObject{

    public:
        //movement speed
        float speed=800.0f;
        //screen border
        float boundY=720.0f;
        
        // controlling keys
        Key up=Keycodes::W;
        Key down=Keycodes::S;
        
        //score
        float point=0.0f;

        Racket(const std::string& tex_file,Pointf pos={50.0f,50.0f},Pointf scl={20.0f,80.0f}):GameObject::GameObject(tex_file,pos,scl){}
        //Resets the points
        void Reset(){
            point=0.0f;
        }
        void Start(){
            GameObject::Start();

            //initial position
            position.Y=boundY/2-scale.Y/2;
        }

        void Update(Layer& layer,double delta){
            GameObject::Update(layer,delta);


            //Character movement
            if(InputManager::GetInstance()->GetKey(up)){position.Y-=delta*speed;}
            if(InputManager::GetInstance()->GetKey(down)){position.Y+=delta*speed;}

            //Border checking
            if(position.Y<0){position.Y=0;}
            if(position.Y+scale.Y>boundY){position.Y=boundY-scale.Y;}

        }
        



};