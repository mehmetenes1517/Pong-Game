#pragma once 

#include<Gorgon/Main.h>
#include<Gorgon/Window.h>
#include<Gorgon/Input/Layer.h>

#include<map>
class InputManager{
    private:
        Gorgon::Input::Layer input_layer;
        std::map<Gorgon::Input::Key,bool> key_states;
    public:
        static InputManager* instance;
        
    static InputManager* GetInstance(){
        if (instance==nullptr){
            instance=new InputManager();
        }
        return instance;
    }
    Gorgon::Input::Layer& GetLayer(){
        return input_layer;
    }
    void Initialize(Gorgon::Window& win){
        win.Add(input_layer);
            
        
        win.KeyEvent.Register([&](Gorgon::Input::Key key,float state){
            key_states[key] = state!=0;
            return false;
        });
    }
    bool GetKey(Gorgon::Input::Key key){
        return key_states.find(key) != key_states.end() && key_states[key]; 
    }
};
InputManager* InputManager::instance =nullptr;