#include "StdAfx.h"
#include "StringLi.h"
#include "Hxt.h"
#include "HashFile.h"
#include "F_Protos.h"
#include "ImportModelDialog.h"

#include "SDK/Misc.h"
#include "SDK/HModel.h"
#include "SDK/HProgres.h"

BOOL CHxtApp::OnImportModelCache(HModelCache *hmc) {
    CString caption, filter;
    caption.LoadString(IDS_IMPORTTITLE);
    filter.LoadString(IDS_FILEFILTERS);
    String defdir; //not used for multiselect dlg
    const String ext("LWO");
    StringList *namelist;

    {
        AFX_MANAGE_STATE(AfxGetAppModuleState())
        if (!OpenRequest(caption, filter, defdir, ext.Get(), ext.Get(), nullptr, nullptr, &namelist))
            return TRUE;
    }

    if (namelist == nullptr) {
        CString caption1;
        caption1.LoadString(IDS_IMPORTTITLE);
        CString text;
        text.LoadString(IDS_ERRORIMPORTING);
        MessageBox(GetMainApplicationWnd(), text, caption1, MB_OK);
        return TRUE;
    }

    CImportModelDialog cdlg;
    if (cdlg.DoModal() != IDOK) {
        DeleteStringList(namelist);
        return TRUE;
    }

    CWaitCursor wait;
    for (POSITION namepos = namelist->GetHeadPosition(); namepos;) {
        String filename = namelist->GetNext(namepos);
//        String nameonly = filename.GetNameOnly();
        IEPolyModel *patchmodel = ImportLWO(filename);
        if (patchmodel == nullptr) {
            ReportImportError(filename);
            continue;
        }
        if (!hmc->MergeIEModel(patchmodel, filename.Get(), cdlg.m_peaktolerance, TRUE, TRUE))
            ReportImportError(filename);

        delete patchmodel;
    }
    DeleteStringList(namelist);

    return TRUE;
}

BOOL CHxtApp::OnImportObjectCacheContainer(HObjectCacheContainer *hocc) {
    CString caption, filter;
    caption.LoadString(IDS_IMPORTTITLE);
    filter.LoadString(IDS_FILEFILTERS);
    String defdir; //not used for multiselect dlg
    const String ext("LWO");
    StringList *namelist;

    {
        AFX_MANAGE_STATE(AfxGetAppModuleState())
        if (!OpenRequest(caption, filter, defdir, ext.Get(), ext.Get(), nullptr, nullptr, &namelist))
            return TRUE;
    }

    if (namelist == nullptr) {
        CString caption1;
        caption1.LoadString(IDS_IMPORTTITLE);
        CString text;
        text.LoadString(IDS_ERRORIMPORTING);
        MessageBox(GetMainApplicationWnd(), text, caption1, MB_OK);
        return TRUE;
    }

    CImportModelDialog cdlg;
    if (cdlg.DoModal() != IDOK) {
        DeleteStringList(namelist);
        return TRUE;
    }

    CWaitCursor wait;
    for (POSITION namepos = namelist->GetHeadPosition(); namepos;) {
        String filename = namelist->GetNext(namepos);
        String nameonly = filename.GetNameOnly();
        HModelCache *hmc = HModelCache::New(nameonly.Get());
        if (hmc == nullptr) {
            ReportImportError(filename);
            DeleteStringList(namelist);
            return TRUE;
        }
        IEPolyModel *patchmodel = ImportLWO(filename);
        if (patchmodel == nullptr) {
            ReportImportError(filename);
            continue;
        }
        if (!hmc->MergeIEModel(patchmodel, filename.Get(), cdlg.m_peaktolerance, FALSE, TRUE))
            ReportImportError(filename);

        delete patchmodel;
    }

    DeleteStringList(namelist);
    return TRUE;
}

void CHxtApp::ReportImportError(const String &filename) {
    CString caption;
    caption.LoadString(IDS_IMPORTTITLE);
    CString text;
    text.LoadString(IDS_ERRORIMPORTINGMODEL);
    String temp = text;
    temp.Replace("%1", filename);
    text = temp.Get();
    MessageBox(GetMainApplicationWnd(), text, caption, MB_OK);
}

#define MAKE_ID(a,b,c,d)	\
	((unsigned long) (a)<<24 | (unsigned long) (b)<<16 | (unsigned long) (c)<<8 | (unsigned long) (d))

/* Universal IFF identifiers */

#define ID_FORM		MAKE_ID('F','O','R','M')
#define ID_LWOB		MAKE_ID('L','W','O','B')

#define ID_PNTS		MAKE_ID('P','N','T','S')
#define ID_POLS		MAKE_ID('P','O','L','S')
#define ID_SRFS		MAKE_ID('S','R','F','S')
#define ID_SURF		MAKE_ID('S','U','R','F')
#define ID_CRVS		MAKE_ID('C','R','V','S')
#define ID_PCHS		MAKE_ID('P','C','H','S')

#define ID_COLR		MAKE_ID('C','O','L','R')
#define ID_TCLR		MAKE_ID('T','C','L','R')
#define ID_FLAG		MAKE_ID('F','L','A','G')
#define ID_TFLG		MAKE_ID('T','F','L','G')
#define ID_LUMI		MAKE_ID('L','U','M','I')
#define ID_DIFF		MAKE_ID('D','I','F','F')
#define ID_SPEC		MAKE_ID('S','P','E','C')
#define ID_REFL		MAKE_ID('R','E','F','L')
#define ID_TRAN		MAKE_ID('T','R','A','N')
#define ID_GLOS		MAKE_ID('G','L','O','S')
#define ID_TVAL		MAKE_ID('T','V','A','L')
#define ID_CTEX		MAKE_ID('C','T','E','X')
#define ID_DTEX		MAKE_ID('D','T','E','X')
#define ID_STEX		MAKE_ID('S','T','E','X')
#define ID_RTEX		MAKE_ID('R','T','E','X')
#define ID_TTEX		MAKE_ID('T','T','E','X')
#define ID_BTEX		MAKE_ID('B','T','E','X')
#define ID_TIMG		MAKE_ID('T','I','M','G')
#define ID_TSIZ		MAKE_ID('T','S','I','Z')
#define ID_TCTR		MAKE_ID('T','C','T','R')
#define ID_TFAL		MAKE_ID('T','F','A','L')
#define ID_TVEL		MAKE_ID('T','V','E','L')
#define ID_SMAN		MAKE_ID('S','M','A','N')
#define ID_TAMP		MAKE_ID('T','A','M','P')
#define ID_EDGE		MAKE_ID('E','D','G','E')
#define ID_TFRQ		MAKE_ID('T','F','R','Q')
#define ID_TOPC		MAKE_ID('T','O','P','C')
#define ID_TWRP		MAKE_ID('T','W','R','P')
#define ID_TALP		MAKE_ID('T','A','L','P')
#define ID_TAAS		MAKE_ID('T','A','A','S')
#define ID_RIND		MAKE_ID('R','I','N','D')
#define ID_RSAN		MAKE_ID('R','S','A','N')
#define ID_RFLT		MAKE_ID('R','F','L','T')
#define ID_SHDR		MAKE_ID('S','H','D','R')
#define ID_VLUM		MAKE_ID('V','L','U','M')
#define ID_VDIF		MAKE_ID('V','D','I','F')
#define ID_VSPC		MAKE_ID('V','S','P','C')
#define ID_VRFL		MAKE_ID('V','R','F','L')
#define ID_VTRN		MAKE_ID('V','T','R','N')
#define ID_TFP0		MAKE_ID('T','F','P','0')
#define ID_TFP1		MAKE_ID('T','F','P','1')
#define ID_TIP0		MAKE_ID('T','I','P','0')
#define ID_TIP1		MAKE_ID('T','I','P','1')
#define ID_TSP0		MAKE_ID('T','S','P','0')
#define ID_TSP1		MAKE_ID('T','S','P','1')
#define ID_TSP2		MAKE_ID('T','S','P','2')

#ifdef _WIN32
#define MSB2			_SwapTwoBytes
#define MSB4			_SwapFourBytes
#define LSB2(w)			(w)
#define LSB4(w)			(w)
#else
#define MSB2(w)			(w)
#define MSB4(w)			(w)
#define LSB2			_SwapTwoBytes
#define LSB4			_SwapFourBytes 
#endif

IEPolyModel *CHxtApp::Escape(FILE *fp, IEPolyModel *model, const char *message) {
    if (fp)
        fclose(fp);
    if (message) {
        AfxMessageBox(message, MB_ICONEXCLAMATION);
        if (model) {
            delete model;
            model = nullptr;
        }
    }
    return model;
}

IEPolyModel *CHxtApp::ImportLWO(const String &pfilename, const BOOL isnewimport) {
    unsigned int nSfs = 0;
    IEPolyModel *model = nullptr;
//    char *message = nullptr;

    FILE *fp;
    if (fopen_s(&fp, pfilename.Get(), "rb") != 0)
        return nullptr;

    /* Make sure the Lightwave file is an IFF file. */
    unsigned long type;
    fread(&type, sizeof(unsigned long), 1, fp);
    if (MSB4(type) != ID_FORM) {
        if (isnewimport)
            return Escape(fp, model, "Not an IFF file (Missing FORM tag)");
        return Escape(fp, model, nullptr);
    }

    unsigned long datasize;
    fread(&datasize, sizeof(unsigned long), 1, fp);
    datasize = MSB4(datasize);
    //printf("FORM [%d]\n", datasize);

    /* Make sure the IFF file has a LWOB form type. */
    fread(&type, sizeof(unsigned long), 1, fp);
    if (MSB4(type) != ID_LWOB) {
        if (isnewimport)
            return Escape(fp, model, "Not a lightwave object (Missing LWOB tag)");
        return Escape(fp, model, nullptr);
    }
    //printf("LWOB\n");

    model = new IEPolyModel;

    int attrID = 0;
    /* Read all Lightwave chunks. */
    unsigned long bytesread = 4;
    while (bytesread < datasize) {
        unsigned long size;
        fread(&type, sizeof(unsigned long), 1, fp);
        fread(&size, sizeof(unsigned long), 1, fp);

        type = MSB4(type);
        size = MSB4(size);

        switch (type) {
            case ID_PNTS:
                read_pnts(model, size, fp);
                break;
            case ID_POLS:
                read_pols(model, size, fp, nSfs);
                break;
            case ID_SRFS:
                nSfs = read_srfs(size, fp);
                model->m_attrlist.SetSize(nSfs);
                break;
            case ID_SURF:
                read_surf(model, attrID++, size, fp);
                break;
                //case ID_CRVS:	read_crvs(model, size, fp); break;
            default:
                fseek(fp, (long)size, SEEK_CUR);
        }

        bytesread += size + 8;
    }

    return Escape(fp, model, nullptr);
}

/*
 *  Swap byte order for WIN32
 */
unsigned short CHxtApp::_SwapTwoBytes(const unsigned short w) {
    unsigned short tmp = w & 0x00ff;
    tmp = (w & 0xff00) >> 0x08 | tmp << 0x08;
    return tmp;
}

unsigned long CHxtApp::_SwapFourBytes(const unsigned long w) {
    unsigned long tmp = w & 0x000000ff;
    tmp = (w & 0x0000ff00) >> 0x08 | tmp << 0x08;
    tmp = (w & 0x00ff0000) >> 0x10 | tmp << 0x08;
    tmp = (w & 0xff000000) >> 0x18 | tmp << 0x08;
    return tmp;
}

/*
 * Reads vertices.
 * Returns the number of vertices read.
 */

int CHxtApp::read_pnts(IEPolyModel *model, const unsigned long nbytes, FILE *file) {
    const unsigned long nPts = nbytes / sizeof(float[3]);
    //printf("PNTS [%d] nPts [%d]\n", nbytes, nPts);

    model->m_vertexlist.SetSize(nPts);
    for (unsigned int i = 0; i < nPts; ++i) {
        unsigned long lv[3];
        fread(lv, sizeof(float), 3, file);
        lv[0] = MSB4(lv[0]);
        lv[1] = MSB4(lv[1]);
        lv[2] = MSB4(lv[2]);
        float v[3];
        memcpy(v, lv, sizeof(float) * 3);
        Vector &vec = model->m_vertexlist[i];
        vec.x = v[0];
        vec.y = v[1];
        vec.z = v[2];
    }

    return nPts;
}

/*
 * Reads polygons.
 * Returns the number of indexes (vertex and surface) read.
 */

char *CHxtApp::read_pols(IEPolyModel *model, const unsigned long nbytes, FILE *file, const unsigned int nSfs) {
    //printf("POLS [%d]\n", nbytes);
    /* The Lightwave file specification states that the POLS chunk must be  */
    /* preceded by the SRFS chunk.  If not, nSrfs will be 0. 		    */
#if 0
    if (nSrfs == 0)
        return "No SRFS chunk in this Lightwave file";
#endif

    /* Not really the number of polygons.  Actually the total number of  */
    /* shorts in this chunk. 						 */
    const unsigned long nPols = nbytes / sizeof(short);
    auto *polys = (short *)malloc(sizeof(short) * nPols);
    auto *upols = (unsigned short *)polys;
    fread(upols, sizeof(short), nPols, file);

    for (int i = 0; i < (int)nPols; ++i) {
        upols[i] = MSB2(upols[i]);
    }

    int totalPoly = 0;
    int i = 0;
    while (i < (int)nPols) {
        int cnt = polys[i++]; //controlPoint Number
        //printf("\t[%d] ",  cnt);

        /* Surface index is found here. */
        int sc = i + cnt;

        [[maybe_unused]] int snum;
        /* Look for negative surface value (detail polygons follow). */
        if (polys[sc] < 0) {
            /* Absolute value of the surface index.  Advance the pointer to    */
            /* skip over the short specifying how many detail polygons follow. */
            /* (I don't think I should care, since detail polygons look like   */
            /* all other polygons as far as I'm concerned).                    */
            //printf(" S(%d)",  polys[sc]);
            snum = -polys[sc++] - 1;
        } else {
            /* Surface indexes are numbered starting at 1. */
            while (polys[sc] > (int)nSfs) {
                sc++;
                cnt++;
            }
            //printf(" S(%d)",  polys[sc]);
            snum = polys[sc] - 1;
        }

        /* If polygons have repeated vertices or have less than 3 vertices, */
        /* add them to an SoIndexedLineSet for that surface. Otherwise add  */
        /* them to an SoIndexedFaceSet for that surface.                    */
#if 0
        for (j = 0; j < cnt; ++j)
            printf(" <%d>", polys[i++]);
        printf("\n");
#endif

        /* Go on to the next polygon. */
        i = sc + 1;
        totalPoly++;
    }

    model->m_polyarray.SetSize(totalPoly);
    int currentPoly = 0;
    i = 0;
    while (i < (int)nPols) {
        int cnt = polys[i++]; //controlPoint Number
        //printf("\t[%d] ",  cnt);

        /* Surface index is found here. */
        int sc = i + cnt;

        int snum;

        /* Look for negative surface value (detail polygons follow). */
        if (polys[sc] < 0) {
            /* Absolute value of the surface index.  Advance the pointer to    */
            /* skip over the short specifying how many detail polygons follow. */
            /* (I don't think I should care, since detail polygons look like   */
            /* all other polygons as far as I'm concerned).                    */
            //printf(" S(%d)",  polys[sc]);
            snum = -polys[sc++] - 1;
        } else {
            /* Surface indexes are numbered starting at 1. */
            while (polys[sc] > (int)nSfs) {
                sc++;
                cnt++;
            }
            //printf(" S(%d)",  polys[sc]);
            snum = polys[sc] - 1;
        }

        /* If polygons have repeated vertices or have less than 3 vertices, */
        /* add them to an SoIndexedLineSet for that surface. Otherwise add  */
        /* them to an SoIndexedFaceSet for that surface.                    */
#if 0
        for (j = 0; j < cnt; ++j)
            printf(" <%d>", polys[i++]);
        printf("\n");
#endif

        auto *polygon = new IEPoly(nullptr);
        model->m_polyarray.SetAt(currentPoly, polygon);
        polygon->m_attrid = snum;

        for (int j = 0; j < cnt; ++j) {
            if (j >= 4)
                break;
            polygon->m_vertexid[j] = polys[i++];
        }
        for (int j = cnt; j < 4; ++j) {
            polygon->m_vertexid[j] = polys[i - 1];
        }

        /* Go on to the next polygon. */
        i = sc + 1;
        currentPoly++;
    }

    free(polys);

    return nullptr;
}

/*
 * Reads the SRFS chunk to determine how many surfaces are used by this
 * object.  Returns the number of surfaces.
 */

int CHxtApp::read_srfs(const unsigned long nbytes, FILE *file) {
    //printf("SRFS [%d]\n", nbytes);
    char *names = (char *)malloc(nbytes);
    fread(names, 1, nbytes, file);

    int count = 0;
    unsigned long i = 0;
    while (i < nbytes) {
        //printf("[%s]\n", &names[i]);
        i += strlen(&names[i]);
        count++;
        /* Skip any extra nulls at the end of the surface name. */
        while (names[i] == '\0' && i < nbytes)
            i++;
    }

    free(names);
    return count;
}

/*
 * Reads a SURF chunk, and returns the surface number.
 */

void CHxtApp::read_surf(IEPolyModel *model, const int attrid, const unsigned long nbytes, FILE *file) {
    unsigned long ncnt = 0, bytesRead = 0;
    unsigned short size;
    char name[255];
    char ctype[4];

    //printf("SURF [%d]\n", nbytes);

//    unsigned short *idats = (unsigned short *)cdats;
//    unsigned long *ldats = (unsigned long *)cdats;
    auto *ltype = (unsigned long *)ctype;

    char ch = fgetc(file);
    bytesRead++;
    if (ch)
        name[ncnt++] = ch;
    while (ch != 0) {
        ch = fgetc(file);
        bytesRead++;
        if (ch)
            name[ncnt++] = ch;
    }
    name[ncnt] = 0;
    //printf("[%s]\n", name);

    /* If the length of the surface name is odd, skip another byte. */
    if (bytesRead % 2 > 0) {
        ch = fgetc(file);
        bytesRead++;
    }

    Attr &attr = model->m_attrlist.ElementAt(attrid);

    while (bytesRead < nbytes) {
        unsigned char cdats[256]{};
        /* Handle the various sub-chunks. */
        fread(ltype, sizeof(unsigned long), 1, file);
        fread(&size, sizeof(unsigned short), 1, file);
        ltype[0] = MSB4(ltype[0]);
        size = MSB2(size);

        //printf("\t[%c%c%c%c] (%d) ", ctype[3], ctype[2], ctype[1], ctype[0], size);
        fread(cdats, sizeof(unsigned char), size, file);

        switch (ltype[0]) {
            case ID_COLR:
                attr.m_diffusecolor.m_red = (float)cdats[0] / 255.0F;
                attr.m_diffusecolor.m_green = (float)cdats[1] / 255.0F;
                attr.m_diffusecolor.m_blue = (float)cdats[2] / 255.0F;
                //printf("<%d,%d,%d>\n", cdats[0], cdats[1], cdats[2]);
                break;
            case ID_TCLR:
                //printf("<%d,%d,%d,%d>\n", cdats[0], cdats[1], cdats[2], cdats[3]);
                break;
            case ID_FLAG:
            case ID_TFLG:
                //printf("<%04x>\n", MSB2(idats[0]));
                break;
            case ID_LUMI:
            case ID_DIFF:
            case ID_SPEC:
            case ID_REFL:
            case ID_TRAN:
            case ID_GLOS:
            case ID_TVAL:
            case ID_RFLT:
            case ID_TFRQ:
                //printf("<%d>\n", MSB2(idats[0]));
                break;
            case ID_TWRP:
                //printf("<%d, %d>\n", MSB2(idats[0]), MSB2(idats[1]));
                break;
            case ID_CTEX:
            case ID_DTEX:
            case ID_STEX:
            case ID_RTEX:
            case ID_TTEX:
            case ID_BTEX:
            case ID_TIMG:
            case ID_TALP:
            case ID_SHDR:
                //printf("<%s>\n", cdats);
                break;
            case ID_TSIZ:
            case ID_TCTR:
            case ID_TFAL:
            case ID_TVEL:
                //ldats[0] = MSB4 (ldats[0]);
                //ldats[1] = MSB4 (ldats[1]);
                //ldats[2] = MSB4 (ldats[2]);
                //memcpy (fdats, ldats, size);
                //printf("<%f,%f,%f>\n", fdats[0], fdats[1], fdats[2]);
                break;
            case ID_VLUM:
            case ID_VDIF:
            case ID_VSPC:
            case ID_VRFL:
            case ID_VTRN:
            case ID_SMAN:
            case ID_TAMP:
            case ID_RSAN:
            case ID_RIND:
            case ID_EDGE:
            case ID_TAAS:
            case ID_TOPC:
            case ID_TFP0:
            case ID_TFP1:
            case ID_TSP0:
            case ID_TSP1:
            case ID_TSP2:
                //ldats[0] = MSB4 (ldats[0]);
                //memcpy (fdats, ldats, size);
                //printf("<%f>\n", fdats[0]);
                break;
            default:
                //printf("(%d bytes)\n", size);
                break;
        }

        bytesRead += sizeof(unsigned long) + sizeof(unsigned short) + size;
    }
}
