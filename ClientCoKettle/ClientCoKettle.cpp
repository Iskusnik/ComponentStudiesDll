#include "pch.h"
#include "interfaces.h"

//using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	CoInitialize(NULL); // This parameter is reserved, 
					   // and should be NULL
	
	HRESULT hr;
	IClassFactory* pCF = NULL;
	ICreateKettle* pICreateKettle = NULL;
	IStats* pStats = NULL;
	IEngine* pEngine = NULL;

	hr = CoGetClassObject(CLSID_CoKettle, CLSCTX_INPROC_SERVER,
		NULL, IID_IClassFactory, (void**)&pCF);

	// Make a CoCar & get ICreateCar.
	hr = pCF->CreateInstance(NULL, IID_ICreateKettle,
		(void**)&pICreateKettle);
	pCF->Release();

	if (SUCCEEDED(hr))
	{
		pICreateKettle->SetMaxTemperature(100);
		BSTR kettleModel = SysAllocString(L"Classic");
		pICreateKettle->SetKettleModel(kettleModel);
		SysFreeString(kettleModel);

		// Now get IStats
		hr = pICreateKettle->QueryInterface(IID_IStats,
			(void**)&pStats);
		pICreateKettle->Release();
	}

	if (SUCCEEDED(hr))
	{
		// Show my kettle!
		pStats->DisplayStats();
		hr = pStats->QueryInterface(IID_IEngine,
			(void**)&pEngine);
	}

	if (SUCCEEDED(hr))
	{
		int curT = 0;
		int maxT = 0;
		pEngine->GetMaxTemperature(&maxT);

		do	// Zoom!
		{
			pEngine->HeatUp(10);
			pEngine->GetCurTemperature(&curT);
			std::cout << "Температура: " << curT << std::endl;
		} while (curT <= maxT);

		// Gotta convert to char array.
		char buff[80];
		BSTR bstr;
		pStats->GetKettleModel(&bstr);
		WideCharToMultiByte(CP_ACP, NULL, bstr, -1, buff,
			80, NULL, NULL);
		std::cout << buff << " has blown up! Lead Foot!" << std::endl << std::endl;
		SysFreeString(bstr);

		if (pEngine) pEngine->Release();
		if (pStats) pStats->Release();
	}

	if (SUCCEEDED(hr))
	{
		int curT = 0;
		int maxT = 0;
		pEngine->GetMaxTemperature(&maxT);


		do	// Zoom!
		{
			pEngine->HeatUp(10);
			pEngine->GetCurTemperature(&curT);
			std::cout << "Температура: " << curT << std::endl;
		} while (curT <= maxT);


		pEngine->HeatDown(100);
		pEngine->TurnOn();


		// Gotta convert to char array.
		char buff[80];
		BSTR bstr;
		pStats->GetKettleModel(&bstr);
		WideCharToMultiByte(CP_ACP, NULL, bstr, -1, buff,
			80, NULL, NULL);
		std::cout << buff << " has blown up! Lead Foot!" << std::endl << std::endl;
		SysFreeString(bstr);




		if (pEngine) pEngine->Release();
		if (pStats) pStats->Release();
	}
	CoUninitialize();
	return 0;
}
