#pragma once 
#include<Gorgon/Main.h>
#include<Gorgon/Geometry/Rectangle.h>

using Gorgon::Geometry::Rectangle;

namespace Physics {

    inline float min(float val1,float val2){
        return (val1>=val2) ? val2 : val1;
    }

    /*
        Kinda complicated AABB test 
        This function Just checks , which way the ball is collided to racket and sets the ball's position and movement direction with respect to that.
    */
    inline bool CheckCollision(const Racket& racket,Ball& ball){
        if(ball.position.Y+ball.scale.Y>racket.position.Y 
            &&racket.position.Y+racket.scale.Y>ball.position.Y
            &&racket.position.X+racket.scale.X>ball.position.X
            &&ball.position.X+ball.scale.X>racket.position.X){

                float topDif=ball.position.Y+ball.scale.Y-racket.position.Y;
                float bottomDif=racket.position.Y+racket.scale.Y-ball.position.Y;
                float rightDif=racket.position.X+racket.scale.X-ball.position.X;
                float leftDif=ball.position.X+ball.scale.X-racket.position.X;
                
                bool top=min(min(topDif,bottomDif),min(rightDif,leftDif))==topDif;
                bool bottom=min(min(topDif,bottomDif),min(rightDif,leftDif))==bottomDif;
                
                bool right=min(min(topDif,bottomDif),min(rightDif,leftDif))==rightDif;
                bool left=min(min(topDif,bottomDif),min(rightDif,leftDif))==leftDif;
                
                
                if(top){
                    ball.position.Y=racket.position.Y-ball.scale.Y;
                    ball.direction.Y*=-1;
                }else if(bottom){
                    ball.position.Y=racket.position.Y+racket.scale.Y;
                    ball.direction.Y*=-1;
                }else if(right){
                    ball.position.X=racket.position.X+racket.scale.X;
                    ball.direction.X*=-1;
                }else if(left){
                    ball.position.X=racket.position.X-ball.scale.X;
                    ball.direction.X*=-1;    
                }
                return true;
            }return false;
    }
}
