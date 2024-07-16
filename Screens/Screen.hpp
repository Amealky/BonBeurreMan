//
//  Screen.hpp
//  BonBeurreMan
//
//  Copyright © 2018 Amealky. All rights reserved.
//

#ifndef Screen_hpp
#define Screen_hpp

#include <unordered_map>

#include <SFML/Graphics.hpp>

#include "../GameEngine.hpp"
#include "../Controls/IController.hpp"
#include "../Entities/Core/GameEntity.hpp"

using namespace std;
using namespace sf;

class GameEngine;

class Screen {

    public:

        Screen(string name, RenderWindow* window);
        ~Screen();

        //Core
        virtual void launchScreen(GameEngine* engine, vector<string> datas);
        virtual void setupUIView();
        virtual void setupGameView();
        virtual void updateScreen(GameEngine* engine);
        virtual void handleInput(MappedEvent inputEvent, GameEngine* engine) {};
        virtual void handleNetworkClientsData(unordered_map<string, vector<string>> datas, GameEngine* engine) {};
        virtual void handleNetworkServerData(vector<string> datas, GameEngine* engine);
        virtual void exitScreen(GameEngine* engine);


        //Getter
        string getName();
        View* getUIView();
        View* getGameView();
        vector<GameEntity*> getGameEntities();
        vector<GameEntity*> getGameEntitiesByName(string name);

        template <typename T>
        vector<T*> getGameEntitiesOfType() {
            vector<T*> result;
            for (auto* entity : gameEntities) {
                if (T* castedEntity = dynamic_cast<T*>(entity)) {
                    result.push_back(castedEntity);
                }
            }
            return result;
        };


       //Setter
        void setName(string name);
        void setUIView(View* uiView);
        void setGameView(View* gameView);
        void setGameEntities(vector<GameEntity*> gameEntities);
        void removeGameEntity(GameEntity* gameEntity);

    protected:
        //Core
        virtual GameEntity* createUITextGameEntity(string gameEntityName, string textValue, int characterSize, Color color,  string fontPath);

        string name;
        RenderWindow* window;
        View* uiView;
        View* gameView;
        vector<GameEntity*> gameEntities;
};
#endif 