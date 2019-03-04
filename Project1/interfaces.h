#ifndef _INTERFACES
#define _INTERFACES

#include <windows.h>

//IStats используется для получения имени модели чайника, а также 
//для отображения параметров состояния реализуемого объекта
DECLARE_INTERFACE_(IStats, IUnknown)
{
	STDMETHOD(DisplayStats)() PURE;
	STDMETHOD(GetKettleModel)(BSTR* kettleModel) PURE;
};

//IEngine моделирует поведение кипятильника. Можно запустить нагрев до максимальной температуры, 
//можно подогреть/остудить на некоторое значение,
//получать значения макстимальной температуры и текущей температуры
DECLARE_INTERFACE_(IEngine, IUnknown)
{
	STDMETHOD(TurnOn)() PURE;
	STDMETHOD(HeatUp)(int temp) PURE;
	STDMETHOD(HeatDown)(int temp) PURE;

	STDMETHOD(GetMaxTemperature)(int* maxTemperature) PURE;
	STDMETHOD(GetCurTemperature)(int* curTemperature) PURE;
};

//ICreateKettle используется для присвоения имени реализуемому  
//объекту и задания максимально достижимой температуры
DECLARE_INTERFACE_(ICreateKettle, IUnknown)
{
	STDMETHOD(SetKettleModel)(BSTR kettleModel) PURE;
	STDMETHOD(SetMaxTemperature)(int maxTemp) PURE;
};

#endif // _INTERFACES
