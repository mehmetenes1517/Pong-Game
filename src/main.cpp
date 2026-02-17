#include<iostream>
#include"App.hpp"
int main(){
    //for random generations
    srand(time(0));

    //calls App class and initializes the application
    App app("Pong");
    app.Init("Pong Game");


    return 0;
}