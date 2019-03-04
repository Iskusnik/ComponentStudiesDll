// Приведенный ниже блок ifdef — это стандартный метод создания макросов, упрощающий процедуру
// экспорта из библиотек DLL. Все файлы данной DLL скомпилированы с использованием символа IDISPATCHKETTLE_EXPORTS
// Символ, определенный в командной строке. Этот символ не должен быть определен в каком-либо проекте,
// использующем данную DLL. Благодаря этому любой другой проект, исходные файлы которого включают данный файл, видит
// функции IDISPATCHKETTLE_API как импортированные из DLL, тогда как данная DLL видит символы,
// определяемые данным макросом, как экспортированные.
#ifdef IDISPATCHKETTLE_EXPORTS
#define IDISPATCHKETTLE_API __declspec(dllexport)
#else
#define IDISPATCHKETTLE_API __declspec(dllimport)
#endif

// Этот класс экспортирован из библиотеки DLL
class IDISPATCHKETTLE_API CIDispatchKettle {
public:
	CIDispatchKettle(void);
	// TODO: добавьте сюда свои методы.
};

extern IDISPATCHKETTLE_API int nIDispatchKettle;

IDISPATCHKETTLE_API int fnIDispatchKettle(void);
