#include "../main.hpp"

class Scene{
  public:
    virtual void Update(){};
    virtual void Draw(){};
 };

class SceneManager{
  protected:
    Scene* currScene;
  public:
    
    SceneManager(Scene* currScene){
      this->currScene = currScene;
    }
    int Update(){
      if(currScene){
      currScene->Update();
      }
    }

    int Draw(){
      if(currScene){
        curr->Draw();
      }
    }
};

class LoginScene:public Scene{

   int Update(){
  

}

  int Draw(){

}

}
