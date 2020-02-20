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
		std::shared_ptr< Rectangle> GetRectangle() { return shp_collisionRect->rect; }
		bool Release()override;
		virtual void Replace() {};
	protected:
		friend class ObjectFactory;
		MapChipObject(std::shared_ptr<GameObjectManager> arg_manager) :GameObject(ObjectFactory::Create<Transform>(), arg_manager) {
			tag = ObjectTag::obstacle;
		}
		MapChipObject(std::shared_ptr<Transform> arg_transform,std::shared_ptr<GameObjectManager> arg_manager) :GameObject(arg_transform, arg_manager) {
			tag = ObjectTag::obstacle;
		}

		std::shared_ptr<Collision2D_Rectangle> shp_collisionRect;
	};

	class MapChip_Space :public MapChipObject {
	public:
		friend class ObjectFactory;
		MapChip_Space(std::shared_ptr<GameObjectManager> arg_manager);
		std::shared_ptr<MapChipObject> Clone(Vector3 position) override{ return nullptr; }
		void Initialize()override {};
		void PreInitialize()override {};
		bool OnUpdate()override { return false; }
	private:
		MapChip_Space(std::shared_ptr<Transform> arg_transform,std::shared_ptr<GameObjectManager> arg_manager);
		
	};
	class MapChip_Test :public MapChipObject {
	public:
		friend class ObjectFactory;
		MapChip_Test(int arg_mapNum,std::shared_ptr<GameObjectManager> arg_manager);
		std::shared_ptr<MapChipObject> Clone(Vector3 position)override;
		bool OnUpdate()override;
		void Initialize()override;
		void PreInitialize()override {};
	private:
		MapChip_Test(int arg_mapNum, std::shared_ptr<Transform> arg_transform, std::shared_ptr<GameObjectManager> arg_manager);
		std::shared_ptr< Resource_Texture> shp_texture;
		int mapImageHandle;
	};

	class MapChip_ChildBlock :public MapChipObject {
	public:
		friend class ObjectFactory;
		MapChip_ChildBlock(std::shared_ptr<GameObjectManager> arg_manager);
		std::shared_ptr<MapChipObject> Clone(Vector3 position)override;
		void Hit(std::shared_ptr<GameObject> other)override;
		bool OnUpdate()override;
		void Initialize()override;
		void PreInitialize()override {};
	private:
		MapChip_ChildBlock(std::shared_ptr<Transform> arg_transform, std::shared_ptr<GameObjectManager> arg_manager);
		std::shared_ptr< Resource_Texture> shp_texture;
	};

	class MapChip_CrushBlock :public MapChipObject {
	public:
		friend class ObjectFactory;
		MapChip_CrushBlock(std::shared_ptr<GameObjectManager> arg_manager);
		std::shared_ptr<MapChipObject> Clone(Vector3 position)override;
		void Hit(std::shared_ptr<GameObject> other)override;
		bool OnUpdate()override;
		void Initialize()override;
		void PreInitialize()override {};
	private:
		MapChip_CrushBlock(std::shared_ptr<Transform> arg_transform, std::shared_ptr<GameObjectManager> arg_manager);
		std::shared_ptr< Resource_Texture> shp_texture;
	};

	class MapChip_Gate :public MapChipObject {
	public:
		friend  class ObjectFactory;

		MapChip_Gate(std::string arg_changeScenesName,Vector2 arg_exitPosition,std::shared_ptr<GameObjectManager> arg_manager);
		std::shared_ptr<MapChipObject> Clone(Vector3 position)override;
		bool OnUpdate()override;
		void Hit(std::shared_ptr<GameObject> other)override;
		void Initialize()override;
		void PreInitialize()override {};
		void Replace()override;
		void SetExitPosition(Vector2 arg_exitPosition) { exitPosition = arg_exitPosition; }
	private:
		std::string changeScenesName;
		bool isGone = false;
		Vector2 exitPosition=Vector2();
		MapChip_Gate(std::string arg_changeScenesName, Vector2 arg_exitPosition, std::shared_ptr<Transform> arg_transform, std::shared_ptr<GameObjectManager> arg_manager);
		std::shared_ptr< Resource_Texture> shp_texture;
	};

	class Medal :public MapChipObject
	{
		friend class ObjectFactory;
	public:
		Medal(std::shared_ptr<GameObjectManager> arg_manager);
		~Medal();
		void Hit(std::shared_ptr<GameObject> other)override;
		void PreInitialize()override;
		std::shared_ptr<MapChipObject> Clone(Vector3 position)override;
		void Initialize()override;
		bool OnUpdate()override;

		std::shared_ptr<Resource_Sound> shp_sound_medal;
	private:
		Medal(std::shared_ptr<Transform> arg_transform, std::shared_ptr<GameObjectManager> arg_manager);
		std::shared_ptr<Resource_Texture> texture;
	};
	
	class MapChip_reset :public MapChipObject
	{
		friend class ObjectFactory;
	public:
		MapChip_reset(std::shared_ptr<GameObjectManager> arg_manager);
		~MapChip_reset();
		void Hit(std::shared_ptr<GameObject> other)override;
		void PreInitialize()override;
		std::shared_ptr<MapChipObject> Clone(Vector3 position)override;
		void Initialize()override;
		bool OnUpdate()override;
	private:
		MapChip_reset(std::shared_ptr<Transform> arg_transform, std::shared_ptr<GameObjectManager> arg_manager);
		std::shared_ptr<Resource_Texture> texture;
	};
	
	class ChildSeedSpawner :public MapChipObject
	{
		friend class ObjectFactory;
	public:
		ChildSeedSpawner(std::shared_ptr<GameObjectManager> arg_manager);
		~ChildSeedSpawner();
		void Hit(std::shared_ptr<GameObject> other)override;
		void PreInitialize()override;
		std::shared_ptr<MapChipObject> Clone(Vector3 position)override;
		void Initialize()override;
		bool OnUpdate()override;
	private:
		ChildSeedSpawner(std::shared_ptr<Transform> arg_transform, std::shared_ptr<GameObjectManager> arg_manager);
		std::shared_ptr<Resource_Texture> texture;
	};
	class MapChip_Kuribo :public MapChipObject {
	public:
		friend class ObjectFactory;
		MapChip_Kuribo(std::shared_ptr<GameObjectManager> arg_manager);
		std::shared_ptr<MapChipObject> Clone(Vector3 position)override;
		bool OnUpdate()override;
		void Initialize()override;
		void PreInitialize()override {};
		void Replace()override;
		bool isClone=false;
	private:
		MapChip_Kuribo(std::shared_ptr<Transform> arg_transform, std::shared_ptr<GameObjectManager> arg_manager);
		
	};

	class MapChip_Bat :public MapChipObject {
	public:
		friend class ObjectFactory;
		MapChip_Bat(std::shared_ptr<GameObjectManager> arg_manager);
		std::shared_ptr<MapChipObject> Clone(Vector3 position)override;
		bool OnUpdate()override;
		void Initialize()override;
		void PreInitialize()override {};
		bool isClone = false;
		void Replace()override;
	private:
		MapChip_Bat(std::shared_ptr<Transform> arg_transform, std::shared_ptr<GameObjectManager> arg_manager);

	};

	class MapChip_Teresa :public MapChipObject {
	public:
		friend class ObjectFactory;
		MapChip_Teresa(std::shared_ptr<GameObjectManager> arg_manager);
		std::shared_ptr<MapChipObject> Clone(Vector3 position)override;
		bool OnUpdate()override;
		void Initialize()override;
		void PreInitialize()override {};
		bool isClone = false;
		void Replace()override;
	private:
		MapChip_Teresa(std::shared_ptr<Transform> arg_transform, std::shared_ptr<GameObjectManager> arg_manager);

	};

}