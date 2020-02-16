#pragma once
#include"Util.h"
#include "GameObjectManager.h"
namespace Framework {
	class SceneOverObjects:public IObject {
	public:
		SceneOverObjects(){}
		SceneOverObjects(std::vector<std::shared_ptr< GameObject>> vec_arg_shp_gameObjects) :vec_shp_gameObjects(vec_arg_shp_gameObjects){}
		void Initialize()override{}
		void PreInitialize()override{}
		std::vector<std::shared_ptr< GameObject>> GetSceneOverGameObjects();
		void AddSceneOverGameObject(std::shared_ptr< GameObject> arg_gameObject);
		Vector3 playerPos = Vector3();
	private:
		std::vector<std::shared_ptr< GameObject>> vec_shp_gameObjects;
	};
	class IScene:public IObject
	{
	public:
		virtual void Release() =0;
		virtual bool Update() =0;
		virtual void OnSet() {};
		virtual void SetSceneOverObjects(std::shared_ptr<SceneOverObjects> shp_arg_sceneOverObjects);
		std::string GetSceneName() const{
			return sceneName;
		}
		void SetSceneName(std::string arg_sceneName) {
			sceneName = arg_sceneName;
		}
	protected:
		std::shared_ptr<GameObjectManager> shp_gameObjectManager;
		std::string sceneName;
	};
}
