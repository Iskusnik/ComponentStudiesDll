using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace ConsoleAppForKettles
{

    // {FE14A03A-3846-4D5D-AA5E-789256FD54F8}
    //DEFINE_GUID(CLSID_CoKettle,
    //0xfe14a03a, 0x3846, 0x4d5d, 0xaa, 0x5e, 0x78, 0x92, 0x56, 0xfd, 0x54, 0xf8);

    [ComVisible(true)]
    [ComImport, Guid("FE14A03A-3846-4D5D-AA5E-789256FD54F8")]
    
    public class Kettle
    {
    }

    [ComImport, InterfaceType(ComInterfaceType.InterfaceIsIUnknown), Guid("0839A377-8B39-48F2-8EA5-155DF2291BDA")]
    public interface ICreateKettle
    {
        [PreserveSig]
        void SetKettleModel(string kettleModel);
        [PreserveSig]
        void SetMaxTemperature(int maxTemp);
    }
    
    [ComImport, InterfaceType(ComInterfaceType.InterfaceIsIUnknown), Guid("A256D4CB-6472-46D3-A16C-5684F78CFC5A")]
    public interface IStats
    {
        [PreserveSig]
        void DisplayStats();
        [PreserveSig]
        void GetKettleModel(ref string kettleModel);
    }

    [ComImport, InterfaceType(ComInterfaceType.InterfaceIsIUnknown), Guid("ACDABA6F-A9BC-423C-A41C-8065BAB787E5")]
    public interface IEngine
    {
        [PreserveSig]
        void TurnOn();
        [PreserveSig]
        void HeatUp(int temp);
        [PreserveSig]
        void HeatDown(int temp);
        [PreserveSig]
        void GetMaxTemperature(ref int maxTemperature);
        [PreserveSig]
        void GetCurTemperature(ref int curTemperature);
    }

}