#pragma once
namespace Framework {
		class Timer {
		public:
			Timer(int max);
			inline void Start() { isActive = true; }
			inline void Stop() { isActive = false; }
			void SetCount(int arg_nowCount);
			void ChangeCountFrame(int arg_maxCount);
			void Reset();
			inline bool Update() {
				if (!isActive) {
					return false;
				}
				nowCountFrame++;
				if (nowCountFrame >= maxCountFrame) {
					nowCountFrame = 0;
					return true;
				}
				return false;
			}
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
