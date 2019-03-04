#include "interfaces.h"
#include "iid.h"
#include <iostream>

#include <windows.h>
#include "iid.h"
//#define _CRT_SECURE_NO_WARNINGS

extern DWORD g_objCount;

class CoKettle : public IEngine, public ICreateKettle, public IStats
{
private:
	unsigned long m_refCount;
	static const long MAX_TEMP = 1000, MAX_NAME_LENGTH = 100;

public:
	BSTR	m_kettleModel; // Инициализация через SysAllocString(), 
						 // удаление — через вызов SysFreeString()
	int		m_maxTemperature; // Максимальная температура
	int		m_currTemperature; // Текущая температура чайника







// Конструктор и деструктор CoKettle
	CoKettle() : m_refCount(0), m_currTemperature(0), m_maxTemperature(0)
	{

		setlocale(LC_ALL, "Russian");
		m_kettleModel = SysAllocString(L"Default kettle model");

		++g_objCount;
	}

	~CoKettle()
	{

		if (m_kettleModel)
			SysFreeString(m_kettleModel);
		MessageBox(NULL, L"CoKettle is dead", L"Destructor", MB_OK |
			MB_SETFOREGROUND);

		--g_objCount;
	}






	// IUnknown
	STDMETHODIMP QueryInterface(REFIID riid, void** pIFace)
	{
		// Which aspect of me do they want?
		if (riid == IID_IUnknown)
		{
			*pIFace = (IUnknown*)(IEngine*)this;
			MessageBox(NULL, L"Handed out IUnknown", L"QI", MB_OK |
				MB_SETFOREGROUND);
		}

		else if (riid == IID_IEngine)
		{
			*pIFace = (IEngine*)this;
			MessageBox(NULL, L"Handed out IEngine", L"QI", MB_OK |
				MB_SETFOREGROUND);
		}

		else if (riid == IID_IStats)
		{
			*pIFace = (IStats*)this;
			MessageBox(NULL, L"Handed out IStats", L"QI", MB_OK |
				MB_SETFOREGROUND);
		}

		else if (riid == IID_ICreateKettle)
		{
			*pIFace = (ICreateKettle*)this;
			MessageBox(NULL, L"Handed out ICreateKettle", L"QI", MB_OK |
				MB_SETFOREGROUND);
		}
		else
		{
			*pIFace = NULL;
			return E_NOINTERFACE;
		}

		((IUnknown*)(*pIFace))->AddRef();
		return S_OK;
	}

	STDMETHODIMP_(DWORD) AddRef()
	{
		++m_refCount;
		return m_refCount;
	}

	STDMETHODIMP_(DWORD) Release()
	{
		if (--m_refCount == 0)
		{
			delete this;
			return 0;
		}
		else
			return m_refCount;
	}

	// Реализация IEngine
	STDMETHODIMP TurnOn()
	{

		std::printf("\nКипятильник включился\n");
		while (m_currTemperature < m_maxTemperature)
		{
			m_currTemperature += m_currTemperature * 0.5;
			m_currTemperature = min(m_maxTemperature, m_currTemperature);
			std::printf("Температура kипятильника: %d °C \n", m_currTemperature);
		}

		std::printf("Кипятильник нагрелся до максимума\nКипятильник выключился\n\n");
		return S_OK;
	}

	STDMETHODIMP HeatUp(int temp)
	{
		m_currTemperature += temp;
		return S_OK;
	}

	STDMETHODIMP HeatDown(int temp)
	{
		m_currTemperature -= temp;
		return S_OK;
	}

	STDMETHODIMP GetMaxTemperature(int* maxTemperature)
	{
		*maxTemperature = m_maxTemperature;
		return S_OK;
	}

	STDMETHODIMP GetCurTemperature(int* curTemperature)
	{
		*curTemperature = m_currTemperature;
		return S_OK;
	}


	// IStats
	// Информация помещается в блоки сообщений
	STDMETHODIMP DisplayStats()
	{
		// Need to transfer a BSTR to a char array.

		wchar_t buff[MAX_NAME_LENGTH];
		wsprintf(buff, L"%s", m_kettleModel);
		//WideCharToMultiByte(CP_ACP, NULL, m_kettleModel, -1, buff,
		//	MAX_NAME_LENGTH, NULL, NULL);

		MessageBox(NULL, (LPCWSTR)buff, L"Имя чайника", MB_OK | MB_SETFOREGROUND);
		//MessageBox(NULL, (LPCWSTR)m_kettleModel, L"Имя чайника", MB_OK | MB_SETFOREGROUND);
		//memset(buff, 0, sizeof(buff));
		//sprintf_s(buff, "%d", m_maxTemperature);

		wsprintf(buff, L"%d", m_maxTemperature);
		MessageBox(NULL, (LPCWSTR)buff, L"Максимальная температура", MB_OK | MB_SETFOREGROUND);
		//MessageBox(NULL, (LPCWSTR)m_maxTemperature, L"Максимальная температура", MB_OK | MB_SETFOREGROUND);
		return S_OK;
	}

	// Возвращает клиенту копию внутреннего буфера
	STDMETHODIMP GetKettleModel(BSTR* kettleModel)
	{
		*kettleModel = SysAllocString(m_kettleModel);
		return S_OK;
	}




	// Реализация ICreateKettle
	STDMETHODIMP SetKettleModel(BSTR kettleModel)
	{
		SysReAllocString(&m_kettleModel, kettleModel);
		return S_OK;
	}

	STDMETHODIMP SetMaxTemperature(int maxTemp)
	{
		if (maxTemp < MAX_TEMP)
			m_maxTemperature = maxTemp;
		return S_OK;

	}

};

