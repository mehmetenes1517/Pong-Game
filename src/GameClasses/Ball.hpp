#pragma once

#include<iostream>
#include"Base/GameObject.hpp"
using Gorgon::Geometry::Pointf;
class Ball:public GameObject{
    public:


        //movement speed
        float speed=1000.0f;
        //screen border
        float boundsY=720;
        //initial movement direction
        Pointf direction={0.5f,0.5f};

        Ball(const std::string& tex_file,const Pointf& pos=Pointf(150.0f,0.0f),const Pointf& scl=Pointf(50.0f,50.0f)):GameObject::GameObject(tex_file,pos,scl){}
        
        void Start(){
            GameObject::Start();
            direction=direction.Normalize();
        }
        void Update(Layer& layer,double delta){
            GameObject::Update(layer,delta);
            

            //moving the object to movement direction we want
            position+=direction*speed*delta;


            //border checking
            if(position.Y+scale.Y > boundsY){
                direction.Y=-direction.Y;
                position.Y=boundsY-scale.Y;
            }
            if(position.Y<0){
                direction.Y=-direction.Y;
                position.Y=0;
            }
                       

        }

};