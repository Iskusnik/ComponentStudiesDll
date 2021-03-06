#pragma once
#ifndef _INTERFACES
#define _INTERFACES

#include <windows.h>

//IStats ������������ ��� ��������� ����� ������ �������, � ����� 
//��� ����������� ���������� ��������� ������������ �������
DECLARE_INTERFACE_(IStats, IDispatch)
{
	STDMETHOD(DisplayStats)() PURE;
	STDMETHOD(GetKettleModel)(BSTR* kettleModel) PURE;
};

//IEngine ���������� ��������� ������������. ����� ��������� ������ �� ������������ �����������, 
//����� ���������/�������� �� ��������� ��������,
//�������� �������� ������������� ����������� � ������� �����������
DECLARE_INTERFACE_(IEngine, IDispatch)
{
	STDMETHOD(TurnOn)() PURE;
	STDMETHOD(HeatUp)(int temp) PURE;
	STDMETHOD(HeatDown)(int temp) PURE;

	STDMETHOD(GetMaxTemperature)(int* maxTemperature) PURE;
	STDMETHOD(GetCurTemperature)(int* curTemperature) PURE;
};

//ICreateKettle ������������ ��� ���������� ����� ������������  
//������� � ������� ����������� ���������� �����������
DECLARE_INTERFACE_(ICreateKettle, IDispatch)
{
	STDMETHOD(SetKettleModel)(BSTR kettleModel) PURE;
	STDMETHOD(SetMaxTemperature)(int maxTemp) PURE;
};

#endif // _INTERFACES
