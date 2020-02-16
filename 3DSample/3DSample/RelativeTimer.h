#pragma once
namespace Framework {
		class RelativeTimer {
		public:
			RelativeTimer(int max);
			inline void Start() { isActive = true; }
			inline void Stop() { isActive = false; }
			void SetCount(int arg_nowCount);
			void ChangeCountFrame(int arg_maxCount);
			void Reset();
			bool Update();
			inline float GetPercent() const {
				if (maxCountFrame == 0)return 0;
				return (float)nowCountFrame / (float)maxCountFrame;
			}
			inline int GetRemainFrame()const {
				return maxCountFrame - nowCountFrame;
			}
		private:
			float maxCountFrame, nowCountFrame;
			bool isActive = false;
		};
}
