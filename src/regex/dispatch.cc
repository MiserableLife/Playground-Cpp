#include "lib/tuk2/oleaut32/winapi.h"
#include "dlls/include/dllcommon.h"
#include "logger/dll_logger.h"
#include <assert.h>

extern "C" {

HRESULT CreateDispTypeInfo(INTERFACEDATA* pidata,
                           LCID lcid,
                           ITypeInfo** pptinfo) {
  DLL_START(pidata, lcid, pptinfo);
  DLL_RETURN(toc::winapi::_CreateDispTypeInfo(pidata, lcid, pptinfo));
}
HRESULT TOC_ORDINAL(oleaut32,
                    CreateDispTypeInfo,
                    31,
                    INTERFACEDATA* pidata,
                    LCID lcid,
                    ITypeInfo** pptinfo);

HRESULT CreateStdDispatch(IUnknown* punkOuter,
                          void* pvThis,
                          ITypeInfo* ptinfo,
                          IUnknown** ppunkStdDisp) {
  DLL_START(punkOuter, pvThis, ptinfo, ppunkStdDisp);
  DLL_RETURN(
      toc::winapi::_CreateStdDispatch(punkOuter, pvThis, ptinfo, ppunkStdDisp));
}
HRESULT TOC_ORDINAL(oleaut32,
                    CreateStdDispatch,
                    32,
                    IUnknown* punkOuter,
                    void* pvThis,
                    ITypeInfo* ptinfo,
                    IUnknown** ppunkStdDisp);
}
