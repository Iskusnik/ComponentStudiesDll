#include <windows.h>
#include "CoKettle.cpp"

extern DWORD g_lockCount;
extern DWORD g_objCount;

class CoKettleFactory : public IClassFactory
{
public:
	CoKettleFactory()
	{
		m_refCount = 0;
		g_objCount++;
	}

	~CoKettleFactory()
	{
		g_objCount--;
	}


	
	// IUnknown
	STDMETHODIMP_(ULONG) AddRef()
	{
		return ++m_refCount;

	}

	STDMETHODIMP_(ULONG) Release()
	{
		if (--m_refCount == 0)
		{
			delete this;
			return 0;
		}
		return m_refCount;
	}

	STDMETHODIMP QueryInterface(REFIID riid, void** ppv)
	{
		// Which aspect of me do they want?
		if (riid == IID_IUnknown)
		{
			*ppv = (IUnknown*)this;
		}
		else if (riid == IID_IClassFactory)
		{
			*ppv = (IClassFactory*)this;
		}
		else
		{
			*ppv = NULL;
			return E_NOINTERFACE;
		}

		((IUnknown*)(*ppv))->AddRef();
		return S_OK;
	}

	// ICF

	STDMETHODIMP LockServer(BOOL fLock)
	{
		if (fLock)
			++g_lockCount;
		else
			--g_lockCount;

		return S_OK;
	}
	STDMETHODIMP CreateInstance(LPUNKNOWN pUnkOuter,
		REFIID riid, void** ppv)
	{
		if (pUnkOuter != NULL)
			return CLASS_E_NOAGGREGATION;

		CoKettle* pKettleObj = NULL;
		HRESULT hr;

		pKettleObj = new CoKettle;

		hr = pKettleObj->QueryInterface(riid, ppv);

		if (FAILED(hr))
			delete pKettleObj;

		return hr;	// S_OK or E_NOINTERFACE.

	}

private:
	DWORD	m_refCount;
};
