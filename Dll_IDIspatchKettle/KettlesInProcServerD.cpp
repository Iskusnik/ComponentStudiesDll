#include <windows.h>
#include "CoKettleFactoryD.cpp"

ULONG g_lockCount = 0; // ���������� ���������� �������
ULONG g_objCount = 0; // ���������� "�����" �������� � �������

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv)
{
	HRESULT hr;
	CoKettleFactory *pCFact = NULL;

	if (rclsid != CLSID_CoKettle)
		return CLASS_E_CLASSNOTAVAILABLE;

	pCFact = new CoKettleFactory;

	hr = pCFact->QueryInterface(riid, ppv);

	if (FAILED(hr))
		delete pCFact;

	return hr;
}
STDAPI DllCanUnloadNow()
{
	if (g_lockCount == 0 && g_objCount == 0)
	{
		return S_OK;
	}
	else
		return S_FALSE;
}
