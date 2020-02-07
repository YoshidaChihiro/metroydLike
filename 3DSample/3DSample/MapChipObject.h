#pragma once
#include"GameObject.h"
#include "Util.h"
#include "Collision2D.h"
#include"Resource.h"
namespace Framework {
	class MapChipObject:public GameObject
	{
	public:
		virtual std::shared_ptr<MapChipObject> Clone(Vector3 position)=0;
		std::shared_ptr<Collision2D_Rectangle> GetShpCollision() { return shp_collisionRect; };
	protected:
		friend class ObjectFactory;
		MapChipObject(std::shared_ptr<GameObjectManager> arg_manager) :GameObject(ObjectFactory::Create<Transform>(), arg_manager) {}
		MapChipObject(std::shared_ptr<Transform> arg_transform,std::shared_ptr<GameObjectManager> arg_manager) :GameObject(arg_transform, arg_manager) {}

		std::shared_ptr<Collision2D_Rectangle> shp_collisionRect;
	};

	class MapChip_Space :public MapChipObject {
	public:
		friend class ObjectFactory;
		MapChip_Space(std::shared_ptr<GameObjectManager> arg_manager);
		std::shared_ptr<MapChipObject> Clone(Vector3 position) override{ return nullptr; }
		void Initialize()override {};
		void PreInitialize()override {};
	private:
		MapChip_Space(std::shared_ptr<Transform> arg_transform,std::shared_ptr<GameObjectManager> arg_manager);
		
	}; 
	class MapChip_Test :public MapChipObject {
	public:
		friend class ObjectFactory;
		MapChip_Test( std::shared_ptr<GameObjectManager> arg_manager);
		std::shared_ptr<MapChipObject> Clone (Vector3 position)override;
		bool Update()override;
		void Initialize()override ;
		void PreInitialize()override {};
	private:
		MapChip_Test(std::shared_ptr<Transform> arg_transform, std::shared_ptr<GameObjectManager> arg_manager);
		std::shared_ptr< Resource_Texture> shp_texture;
	};
}