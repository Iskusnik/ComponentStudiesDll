#ifndef _INTERFACES
#define _INTERFACES

#include <windows.h>

//IStats ������������ ��� ��������� ����� ������ �������, � ����� 
//��� ����������� ���������� ��������� ������������ �������
DECLARE_INTERFACE_(IStats, IUnknown)
{
	STDMETHOD(DisplayStats)() PURE;
	STDMETHOD(GetKettleModel)(BSTR* kettleModel) PURE;
};

//IEngine ���������� ��������� ������������. ����� ��������� ������ �� ������������ �����������, 
//����� ���������/�������� �� ��������� ��������,
//�������� �������� ������������� ����������� � ������� �����������
DECLARE_INTERFACE_(IEngine, IUnknown)
{
	STDMETHOD(TurnOn)() PURE;
	STDMETHOD(HeatUp)(int temp) PURE;
	STDMETHOD(HeatDown)(int temp) PURE;

	STDMETHOD(GetMaxTemperature)(int* maxTemperature) PURE;
	STDMETHOD(GetCurTemperature)(int* curTemperature) PURE;
};

//ICreateKettle ������������ ��� ���������� ����� ������������  
//������� � ������� ����������� ���������� �����������
DECLARE_INTERFACE_(ICreateKettle, IUnknown)
{
	STDMETHOD(SetKettleModel)(BSTR kettleModel) PURE;
	STDMETHOD(SetMaxTemperature)(int maxTemp) PURE;
};

#endif // _INTERFACES
