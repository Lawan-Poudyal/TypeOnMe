#pragma once
#include <string>
#include <unordered_map>
#include<iostream>
class Scene {
public:
    virtual void on_entry() {
        throw std::runtime_error("on_entry hasn't been implemented yet.");
    }//When a scene is started,this method is called.

    virtual void on_event() {
        throw std::runtime_error("on_event hasn't been implemented yet.");
    }
    //When an event related functionality is to be implemented.

    virtual void on_update() {
        throw std::runtime_error("on_update hasn't been implemented yet.");
    }
    //The things to update on the screen on each frame.
    virtual void on_exit() {
        throw std::runtime_error("on_exit hasn't been implemented yet.");
    }
    //When the function is to be exited
};

class SceneManager {
public:
    SceneManager() : curr_scene(nullptr) {}

    void add(const std::string& name, Scene* scene) {
        scenes[name] = scene;
    }

    void switch_to(const std::string& name) {
        if (scenes.find(name) == scenes.end()) {
            std::cerr << "Scene '" << name << "' doesn't exist." << std::endl;
            return;
        }

        if (curr_scene) {
            curr_scene->on_exit();
        }

        curr_scene = scenes[name];
        curr_scene->on_entry();
    }

    void update() {
        if (!curr_scene) {
            std::cerr << "Current scene not set. Use switch_to method to switch to a scene." << std::endl;
            return;
        }

        curr_scene->on_update();
    }

    void poll_event() {
        if (!curr_scene) {
            std::cerr << "Current scene not set. Use switch_to method to switch to a scene." << std::endl;
            return;
        }

        curr_scene->on_event();
    }

    void quit() {
        if (curr_scene) {
            curr_scene->on_exit();
        }
    }

private:
    Scene* curr_scene;
    std::unordered_map<std::string, Scene*> scenes;
};
