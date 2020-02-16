#pragma once
#include"GameObject.h"
namespace Framework {
	class Cameraman :public GameObject
	{
	public:
		Cameraman(std::shared_ptr<Transform> shp_arg_transform, std::shared_ptr<GameObjectManager> shp_arg_manager);
		bool OnUpdate()override;
	protected:
		void SetScrollFocus();
	}; 
	class Cameraman_Chase :public Cameraman
	{
	public:
		Cameraman_Chase(std::shared_ptr<Transform> shp_target_transform, std::shared_ptr<Transform> shp_arg_transform, std::shared_ptr<GameObjectManager> shp_arg_manager);

		Cameraman_Chase( std::shared_ptr<Transform> shp_arg_transform, std::shared_ptr<GameObjectManager> shp_arg_manager);
		
		bool OnUpdate()override;

		void SetTarget(std::shared_ptr<Transform> arg_target) {
			target=arg_target->GetThis<Transform>();
		}
	private:
		std::shared_ptr<Transform> target;
	};
}

