#pragma once

#include<iostream>
#include<array>
#include<cmath>
#include<cstdint>
#include<Gorgon/Main.h>
#include<Gorgon/Window.h>
#include<Gorgon/Graphics/Layer.h>
#include<Gorgon/Graphics/FreeType.h>
#include<Gorgon/Graphics/Font.h>
#include<Gorgon/Input/Keyboard.h>
#include"./Base/PhysicsCheck.hpp"


class MainScene{


    private:
        //reference to gorgon window
        Gorgon::Window& win;
        // player1 and 2
        std::vector<Racket> players;
        //ball
        Ball ball;
        //screen borders
        Pointf bounds{1280.0f,720.0f};
        //the font type we will use
        Gorgon::Graphics::FreeType font;
        //game over check 
        bool GameOver=false;


        // Resetting position of the ball and generating new direction for it
        void ResetBall(){
            ball.position.X=bounds.X/2 - ball.scale.X/2;
            ball.position.Y=bounds.Y/2 - ball.scale.Y/2;
            ball.direction.X=static_cast<float>((rand()%1000)-500.0f)/1000.0f;
            ball.direction.Y=static_cast<float>((rand()%200)-50.0f)/1000.0f;
            if(ball.direction.Distance()==0.0f){
                ball.direction={1.0f,1.0f};
            }
            ball.direction=ball.direction.Normalize();
        }

        // it does what it says
        void IncreasePoint(Racket& r){
            r.point+=1.0f;
        }


        // resets the ball and players positions
        void ResetGame(){
            ResetBall();
            for(auto&p : players){
                p.Reset();
            }
        }


    public:
    
        MainScene(Gorgon::Window& win):win(win),ball(Ball("./Resource/ball.png",{150.0f,50.0f},{50,50})) {
            //Loads the font we will be using
            font.LoadFile("./Resource/font.ttf",36);
        }



        void Start(){

            //Initializing players assigning control keys and calling Start() functions of all objects
            players.push_back(Racket("./Resource/racket.png"));
            players[0].up=Keycodes::W;
            players[0].down=Keycodes::S;
            players.push_back(Racket("./Resource/racket.png",{1210,50}));
            players[1].up=Keycodes::Up;
            players[1].down=Keycodes::Down;

            //Start functions
            ball.Start();
            for(auto& p:players){
                p.Start();
            }
        }



        void Update(Layer& layer,double delta){
            if(!GameOver){
                
                //Updating Objects (Game Mechanics)
                ball.Update(layer,delta);
                for(auto& p:players){
                    p.Update(layer,delta);
                }
                
                //Collision checking
                for(auto& p:players){
                    Physics::CheckCollision(p,ball);
                }

                //checking ball is out of bounds 
                /*
                 * if ball is gonna be outside in left side -> add score to player1
                 * vice versa -> add score to player2   
                 */
                //player1 scoring
                if(ball.position.X+ball.scale.X<0){
                    IncreasePoint(players[1]);
                    ResetBall();
                }
                //player2 scoring
                if(ball.position.X>bounds.X){
                    IncreasePoint(players[0]);
                    ResetBall();
                }


                //check one of the players has 5 score
                for (auto& p:players){
                    if(p.point>=5){
                        GameOver=true;
                    }
                }
                //rendering the score texts
                font.Print(layer, Gorgon::String::Concat("Player 1 Score: ",players[0].point), 11, 11,800,Gorgon::Graphics::Color::Blue);
                font.Print(layer, Gorgon::String::Concat("Player 2 Score: ",players[1].point), 1000, 11,800,Gorgon::Graphics::Color::Yellow);

            }else{
                //if we press R game will start again
                if(InputManager::GetInstance()->GetKey(Keycodes::R)){
                    GameOver=false;
                    ResetGame();
                }

                //Rendering game over text 
                font.Print(layer, 
                    Gorgon::String::Concat(players[0].point>players[1].point ? "Player 1 Won !" : "Player 2 Won !" ,
                         "\n Score : " ,players[0].point," - ", players[1].point)  , 230,300,800,Gorgon::Graphics::TextAlignment::Center,Gorgon::Graphics::Color::Green);
                font.Print(layer, Gorgon::String::Concat("Press [R] for replay!")  , 230,380,800,Gorgon::Graphics::TextAlignment::Center,Gorgon::Graphics::Color::Green);
            }
        }







};