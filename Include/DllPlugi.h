//BC  12/2/2004  \BobL120\Include\DLLPlugi.h
// ReSharper disable CppJoinDeclarationAndAssignment
#pragma once
#include "HashTime.h"
#include "SDK/HHashobj.h"
#include "PtrMessa.h"

class HProperty;
class HTreeObject;
//needed for shaders
#define PLUGINVERSION ((int)(PRODUCTVERSION * 10.))  // NOLINT(cppcoreguidelines-macro-usage)

class DLLPlugin {
public:
    HINSTANCE m_hresource{nullptr};
    HTreeObject *m_treeobject{nullptr}; //for ReassignPtr and so plugin knows owner
    //passed to CreatePLUGINTYPE
    //so CreatePLUGINTYPE knows plugins owner
    //currently CreatePLUGINTYPE must pass this through constructor to set this
    //grep for GetProcAddress and set this after creation to take burden off plugin writer
    //also expose GetOwner() that returns this
    //CONSTRUCTION/DESTRUCTION
    DLLPlugin() {
        InitSimple();
    }

    explicit DLLPlugin(HTreeObject *treeobject) : m_treeobject(treeobject) {
        Init();
    }

    virtual ~DLLPlugin() = default;

    DLLPlugin(const DLLPlugin &) = default;
    DLLPlugin(DLLPlugin &&) = delete;
    DLLPlugin &operator=(const DLLPlugin &) = delete;
    DLLPlugin &operator=(DLLPlugin &&) = delete;

    HASH_INLINE void Init();
    HASH_INLINE void InitSimple();
    virtual void Init(Time) {}
    virtual void Copy(const DLLPlugin &) {}

    [[nodiscard]] HTreeObject *GetOwner() const noexcept {
        return m_treeobject;
    }

    //INTERFACE
    virtual UINT GetIconID() noexcept {
        return 0;
    }

    virtual UINT GetNameID() noexcept {
        return 0;
    }

    virtual const char *GetClassName() {
        return nullptr;
    }

    virtual HProperty *GetPropertyAt(int ) {
        return nullptr;
    }

    virtual int GetNumProperties() {
        int c;
        for (c = 0; GetPropertyAt(c); ++c) { }
        return c;
    }

    //SERIALIZATION
    virtual bool Save(char * &, char * &, int ) {
        return false;
    }

    virtual bool ParseArg(const char *, const char *) {
        return false;
    }

    virtual bool OnNotifyEndProjectLoad(float ) {
        return true;
    }

    //POINTER MESSAGES
    virtual HTreeObject **GetPtrAt(int ) {
        return nullptr;
    }

    void ReassignPtr(void *ptruplink, HTreeObject *newvalue) const {
        if (m_treeobject)
            m_treeobject->ReassignPtr(ptruplink, newvalue);
    }

    virtual bool OnPtrMessage(PtrMessage , HTreeObject **, LONG_PTR , Time time = Time()) {
        return false;
    }
};

HASH_INLINE void DLLPlugin::Init() {
    constexpr char exename[512]{};
    GetModuleFileName(AfxGetInstanceHandle(), (LPSTR)exename, 512);
    // ReSharper disable once CppTooWideScope
    char *ptr = strrchr((char *)exename, '.');
    if (ptr)
        *ptr = '\0';
    CString dllname;
    dllname.Format(_T("%s.lng"), (char *)exename);

    // ReSharper disable once CppLocalVariableMayBeConst
    if (HINSTANCE hlangdll = LoadLibrary(dllname); hlangdll) {
        AfxSetResourceHandle(hlangdll);
        m_hresource = hlangdll;
    } else {
        m_hresource = AfxGetInstanceHandle();
    }
}

HASH_INLINE void DLLPlugin::InitSimple() {
    //doesn't come from a plugin , instance is always master.exe
    m_hresource = AfxGetInstanceHandle();
}
