//RC  4/25/2002  \HRandy95\Include\Registra.h
// ReSharper disable CppParameterMayBeConst
#pragma once

#include "StrClass.h"

class Registration {
public:
    String m_localizedname;
    String m_classname;
    String m_filename;
    Registration *m_next{nullptr};
    HINSTANCE m_hinst{nullptr};
    HINSTANCE m_hresource{nullptr};
    HICON m_hicon{nullptr};
    UINT m_defaulthiconid{0};
    UINT m_nameid{0};
    int m_version{0};

    Registration() noexcept = default;

    Registration(HINSTANCE hinst, HINSTANCE hresource, const char *classname, const UINT nameid) noexcept : m_classname((String)classname), m_hinst(hinst), m_hresource(hresource) {
        if (hresource) {
            char buf_local[STRINGSIZE]{};
            LoadString(hresource, nameid, (LPSTR)buf_local, STRINGSIZE);
            m_localizedname = (String)buf_local;
        } else {
            //YP: This happens for statics registrations
            m_nameid = nameid; //so, localize later.
            //CString name;     // for statics registrations, the 3 following lines does not work in VS 7
            //name.LoadString( nameid );
            //m_localizedname = (LPCTSTR)name;
        }
    }

    void Localize() {
        CString name;
        [[maybe_unused]] const int rc = name.LoadString(m_nameid);
        m_localizedname = name;
    }

    virtual ~Registration() {
        if (m_hinst != m_hresource)
            FreeLibrary(m_hresource);
        if (m_hinst)
            FreeLibrary(m_hinst);
    }

    Registration(const Registration &) = delete;
    Registration(Registration &&) = delete;
    Registration &operator=(const Registration &) = delete;
    Registration &operator=(Registration &&) = delete;

#ifdef _MEMDEBUG
   void        *operator new (size_t size, char *file, const int line) {
      return ALLOCEXT(size, file, line);
   }
#else
    void *operator new(const size_t size) noexcept {
        return AllocExt(size);
    }
#endif
    void operator delete(void *ptr) noexcept {
        FreeExt(ptr);
    }
};
