#pragma once
#include<memory>
#include<string>
#include<stdexcept>
#include<random>
#include<time.h>
namespace Framework {
	class Util
	{
		public:
			static void WStringtoMultiByte(const std::wstring& src, std::string& dest);
			static void MultiBytetoWString(const std::string& src, std::wstring& dest) {
				size_t i;
				wchar_t* WCstr = new wchar_t[src.length() + 1];
				mbstowcs_s(
					&i,
					WCstr,
					src.length() + 1,
					src.c_str(),
					_TRUNCATE //Ç∑Ç◊Çƒïœä∑Ç≈Ç´Ç»Ç©Ç¡ÇΩÇÁêÿÇËéÃÇƒ
				);
				dest = WCstr;
				delete[] WCstr;
			}
			template<typename T>
			static std::wstring GetWStringTypeName() {
				std::wstring outputClassName;
				MultiBytetoWString(typeid(T).name(), outputClassName);
				return outputClassName;
			}
	};
	class ButiException :public std::exception {

		std::wstring wstr_errorMessage;
	public:
		ButiException(std::wstring const message1, std::wstring const message2,std:: wstring const message3) {
			wstr_errorMessage = message1;
			wstr_errorMessage += L"\n" + message2 + L"\n" + message3;
		}
		const std::wstring& what_w() const throw() {
			return wstr_errorMessage;
		}
	};
	namespace ButiTime {
		inline timespec *timespecSubstruction(const struct timespec *A, const struct timespec *B, struct timespec *C)
		{
			C->tv_sec = A->tv_sec - B->tv_sec;
			C->tv_nsec = A->tv_nsec - B->tv_nsec;
			if (C->tv_nsec < 0) {
				C->tv_sec--;
				C->tv_nsec += 1000000000;
			}

			return C;
		}
	}

	void ThrowButiException_Runtime(const std::wstring& message1, const std::wstring& message2, const std::wstring& message3);
		//throw runtime_error function
	void ThrowButiException_Runtime(const std::string& meesage1, const std::string& message2, const std::string& message3);

	template<typename T>
	std::shared_ptr<void> SharedPtrToVoid(const std::shared_ptr<T>& SrcPtr);
	template<typename T>
	std::shared_ptr<T> VoidToShared(const std::shared_ptr<void>& SrcPtr);

	class ObjectFactory {
	public:
		template<typename T, typename... Ts>
		static inline std::shared_ptr<T> Create(Ts&&... params) {
			std::shared_ptr<T> Ptr = std::shared_ptr<T>(new T(params...));
			//âºëzä÷êîåƒÇ—èoÇµ
			Ptr->PreInitialize();
			Ptr->Initialize();
			Ptr->SetCreated(true);
			return Ptr;
		};
	};

	class IObject :public std::enable_shared_from_this<IObject>
	{
		friend class ObjectFactory;
		bool isCreated = false;
		void SetCreated(bool b);
	protected:
		IObject() {}
		virtual ~IObject() {}

	public:
		template<typename T>
		inline std::shared_ptr<T> GetThis() {
			auto Ptr = std::dynamic_pointer_cast<T>(shared_from_this());
			if (Ptr) {
				return Ptr;
			}
			else {
				std::wstring str(L"Can't cast this to");
				str += Util::GetWStringTypeName<T>();
				str += L" type.";
				throw ButiException(
					str,
					L"if( ! dynamic_pointer_cast<T>(shared_from_this()) )",
					L"ObjectInterface::GetThis()"
				);
			}
			return nullptr;

		}
		template<typename T>
			inline bool IsThis() {
			auto Ptr = std::dynamic_pointer_cast<T>(shared_from_this());
			if (Ptr) {
				return true;
			}
			else {
				return false;
			}
			//return nullptr;

		}
		bool IsCreated() { return isCreated; }
		virtual void PreInitialize() = 0;
		virtual void Initialize() = 0;

	};
	class ButiRandom {
	public:

		static void Initialize();


		template<class T>
		inline static T GetRandom(T min,T max,int pase) {
			if (min == max) {
				return min;
			}
			if (min > max) {
				auto b = min;
				min = max;
				max = min;
			}

			shp_randRange = std::make_shared< std::uniform_int_distribution<>>(min*pase, max*pase);
			return (T)(*shp_randRange)(*shp_mt) / pase;

		};

		
		

	private:
		static std::shared_ptr< std::random_device> shp_rnd_device;// = std::make_shared<std::random_device>();
		static std::shared_ptr<std::mt19937>shp_mt;// = std::make_shared<std::mt19937>((*shp_rnd_device)());
		static std::shared_ptr< std::uniform_int_distribution<>> shp_randRange;// = std::make_shared< std::uniform_int_distribution<>>(0, 1);

		ButiRandom() {};
		~ButiRandom() {};
	};
	template<typename T>
	std::shared_ptr<void> SharedPtrToVoid(const std::shared_ptr<T>& SrcPtr);
	template<typename T>
	std::shared_ptr<T> VoidToShared(const std::shared_ptr<void>& SrcPtr);

}
