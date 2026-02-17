#pragma once

#include<Gorgon/Main.h>
#include<Gorgon/Graphics/Layer.h>
#include<Gorgon/Graphics/Bitmap.h>

using Gorgon::Graphics::Bitmap;
using Gorgon::Graphics::Layer;
using Gorgon::Geometry::Pointf;
using Gorgon::Geometry::Size;
using Gorgon::Geometry::Rectangle;
namespace Color=Gorgon::Graphics::Color;



/*
    Its a common pattern i used in my game projects , 
    like unity game engine; every single game object is having Start() which is called at startup and Update() which is called continuously

    Any other objects in the screen are derived from that class 
*/
class GameObject{

    public:
        Pointf position;
        Pointf scale;
        Bitmap texture;
        
        GameObject(const std::string& tex_file) {
            texture.Import(tex_file);
            Scale(Size(scale.X,scale.Y));
        }
        GameObject(const std::string& tex_file,const Pointf& pos,const Pointf& scl):position(pos),scale(scl) {
            texture.Import(tex_file);
            Scale(Size(scale.X,scale.Y));
        }

        void Scale(const Size& newsize){
            Bitmap new_texture=texture.Scale(newsize);
            texture.Destroy();
            texture=std::move(new_texture);
            texture.Prepare();
        }

        virtual void Start(){
            texture.Prepare();
        }
        virtual void Update(Layer& layer,double delta){
            texture.Draw(layer,position,Color::White);
        }
};