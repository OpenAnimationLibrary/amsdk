#include "StdAfx.h"
#include "RenderPasses.h"

#ifdef _DEBUG
void dbgout(PARAMETER *pa) {
    FileStream fs;
    int j;
    fs.Open("d:\\RenderPasses.txt", FileMode::HS_ASCII);
    for (int i = 0; i < pa->azmodel; ++i) {
        fs << pa->model[i].hmodel->GetName() << nl;
        for (j = 0; j < pa->model[i].azgroup; ++j) {
            fs << "  Group    " << pa->model[i].gruppe[j].hgroup->GetName() << nl;
            for (int k = 0; k < pa->model[i].gruppe[j].azmat; ++k) {
                fs << "       Material   " << pa->model[i].gruppe[j].material[k].hmaterial->GetName() << nl;
            }
        }
        for (j = 0; j < pa->model[i].azdecal; ++j) {
            fs << "  Decal    " << pa->model[i].decal[j].hdecalclip->GetName() << nl;
        }
        for (j = 0; j < pa->model[i].azmat; ++j) {
            fs << "  Material " << pa->model[i].material[j].hmaterial->GetName() << nl;
        }
    }
    fs.Close();
}
#endif

void CPassesApp::FreeStruct() const {
    for (int i = 0; i < para->azmodel; ++i) {
        for (int j = 0; j < para->model[i].azgroup; ++j) {
            if (para->model[i].gruppe[j].azmat > 0)
                delete [] para->model[i].gruppe[j].material;
        }
        if (para->model[i].azgroup > 0)
            delete [] para->model[i].gruppe;
        if (para->model[i].azdecal > 0)
            delete [] para->model[i].decal;
        if (para->model[i].azmat > 0)
            delete [] para->model[i].material;
    }
    if (para->azmodel > 0)
        delete [] para->model;
}

void CPassesApp::ChangeChorName(HChor *hchor, const String &newname) {
    HFileInfoProperty *hfip = hchor->GetFileInfo();
    const String cname_o = hchor->GetName();
    if (cname_o.Find(0, newname) == -1) {
        CString cname;
        cname.Format("%s%s", cname_o.Get(), newname.Get());
        if (hfip->GetEmbedded()->GetValue()) {
            hchor->SetName(cname);
        } else {
            CString fname;
            const String fname_o = hfip->GetFileName()->GetValue();
            fname.Format("%s%s%s", fname_o.Left(fname_o.Find(".cho")).Get(), newname.Get(), ".cho");
            hfip->GetFileName()->SetValue(fname);
            hchor->SetName(cname);
        }
    }
}

void CPassesApp::Usershading(HChor *hchor) const {
    int j;
    int ck;
    HColorProperty *hcolor;
    HFloatProperty *hfloat;
    TimeRange time_range;

    time_range.Set(Time(), hchor->GetTotalTime()->GetValue());

    for (int i = 0; i < para->azmodel; ++i) {
        // model
        if (para->model[i].cset.changediffusecolor) {
            hcolor = para->model[i].attrproperty->GetDiffuseColor();
            ck = hcolor->CountKeys();
            if (ck > 1)
                hcolor->DeleteKeys(time_range);
            hcolor->StoreValue(Time(), para->model[i].cset.diffuse,TRUE);
        }
        if (para->model[i].cset.changeambiencecolor) {
            hcolor = para->model[i].attrproperty->GetAmbianceColor();
            ck = hcolor->CountKeys();
            if (ck > 1)
                hcolor->DeleteKeys(time_range);
            hcolor->StoreValue(Time(), para->model[i].cset.ambience,TRUE);
        }
        if (para->model[i].cset.changespecularcolor) {
            hcolor = para->model[i].attrproperty->GetSpecularColor();
            ck = hcolor->CountKeys();
            if (ck > 1)
                hcolor->DeleteKeys(time_range);
            hcolor->StoreValue(Time(), para->model[i].cset.specular,TRUE);
        }
        if (para->model[i].cset.changeambienceintensity) {
            hfloat = para->model[i].attrproperty->GetAmbiance();
            ck = hfloat->CountKeys();
            if (ck > 1)
                hfloat->DeleteKeys(time_range);
            hfloat->StoreValue(Time(), para->model[i].cset.ambienceintensity,TRUE);
        }
        if (para->model[i].cset.changespecularintensity) {
            hfloat = para->model[i].attrproperty->GetSpecularIntensity();
            ck = hfloat->CountKeys();
            if (ck > 1)
                hfloat->DeleteKeys(time_range);
            hfloat->StoreValue(Time(), para->model[i].cset.specularintensity,TRUE);
        }
        if (para->model[i].cset.changespecularsize) {
            hfloat = para->model[i].attrproperty->GetSpecularSize();
            ck = hfloat->CountKeys();
            if (ck > 1)
                hfloat->DeleteKeys(time_range);
            hfloat->StoreValue(Time(), para->model[i].cset.specularsize,TRUE);
        }
        if (para->model[i].cset.changereflectionintensity) {
            hfloat = para->model[i].attrproperty->GetReflectivity();
            ck = hfloat->CountKeys();
            if (ck > 1)
                hfloat->DeleteKeys(time_range);
            hfloat->StoreValue(Time(), para->model[i].cset.reflectionintensity,TRUE);
        }

        //Decal
        for (j = 0; j < para->model[i].azdecal; ++j) {
            if (para->model[i].decal[j].tochange) {
                ck = para->model[i].decal[j].percent->CountKeys();
                if (ck > 1)
                    para->model[i].decal[j].percent->DeleteKeys(time_range);
                para->model[i].decal[j].percent->StoreValue(Time(), para->model[i].decal[j].percentage,TRUE);
            }
        }
        // Material
        for (j = 0; j < para->model[i].azmat; ++j) {
            if (para->model[i].material[j].isclip) {
                if (para->model[i].material[j].changepercentage) {
                    ck = para->model[i].material[j].percent->CountKeys();
                    if (ck > 1)
                        para->model[i].material[j].percent->DeleteKeys(time_range);
                    para->model[i].material[j].percent->StoreValue(Time(), para->model[i].material[j].percentage,TRUE);
                }
            } else {
                if (para->model[i].material[j].cset.changediffusecolor) {
                    hcolor = para->model[i].material[j].attrproperty->GetDiffuseColor();
                    ck = hcolor->CountKeys();
                    if (ck > 1)
                        hcolor->DeleteKeys(time_range);
                    hcolor->StoreValue(Time(), para->model[i].material[j].cset.diffuse,TRUE);
                }
                if (para->model[i].material[j].cset.changeambiencecolor) {
                    hcolor = para->model[i].material[j].attrproperty->GetAmbianceColor();
                    ck = hcolor->CountKeys();
                    if (ck > 1)
                        hcolor->DeleteKeys(time_range);
                    hcolor->StoreValue(Time(), para->model[i].material[j].cset.ambience,TRUE);
                }
                if (para->model[i].material[j].cset.changespecularcolor) {
                    hcolor = para->model[i].material[j].attrproperty->GetSpecularColor();
                    ck = hcolor->CountKeys();
                    if (ck > 1)
                        hcolor->DeleteKeys(time_range);
                    hcolor->StoreValue(Time(), para->model[i].material[j].cset.specular,TRUE);
                }
                if (para->model[i].material[j].cset.changeambienceintensity) {
                    hfloat = para->model[i].material[j].attrproperty->GetAmbiance();
                    ck = hfloat->CountKeys();
                    if (ck > 1)
                        hfloat->DeleteKeys(time_range);
                    hfloat->StoreValue(Time(), para->model[i].material[j].cset.ambienceintensity,TRUE);
                }
                if (para->model[i].material[j].cset.changespecularintensity) {
                    hfloat = para->model[i].material[j].attrproperty->GetSpecularIntensity();
                    ck = hfloat->CountKeys();
                    if (ck > 1)
                        hfloat->DeleteKeys(time_range);
                    hfloat->StoreValue(Time(), para->model[i].material[j].cset.specularintensity,TRUE);
                }
                if (para->model[i].material[j].cset.changespecularsize) {
                    hfloat = para->model[i].material[j].attrproperty->GetSpecularSize();
                    ck = hfloat->CountKeys();
                    if (ck > 1)
                        hfloat->DeleteKeys(time_range);
                    hfloat->StoreValue(Time(), para->model[i].material[j].cset.specularsize,TRUE);
                }
                if (para->model[i].material[j].cset.changereflectionintensity) {
                    hfloat = para->model[i].material[j].attrproperty->GetReflectivity();
                    ck = hfloat->CountKeys();
                    if (ck > 1)
                        hfloat->DeleteKeys(time_range);
                    hfloat->StoreValue(Time(), para->model[i].material[j].cset.reflectionintensity,TRUE);
                }
            }
        }
        //Gruppe
        for (j = 0; j < para->model[i].azgroup; ++j) {
            if (para->model[i].gruppe[j].cset.changediffusecolor) {
                hcolor = para->model[i].gruppe[j].attrproperty->GetDiffuseColor();
                ck = hcolor->CountKeys();
                if (ck > 1)
                    hcolor->DeleteKeys(time_range);
                hcolor->StoreValue(Time(), para->model[i].gruppe[j].cset.diffuse,TRUE);
            }
            if (para->model[i].gruppe[j].cset.changeambiencecolor) {
                hcolor = para->model[i].gruppe[j].attrproperty->GetAmbianceColor();
                ck = hcolor->CountKeys();
                if (ck > 1)
                    hcolor->DeleteKeys(time_range);
                hcolor->StoreValue(Time(), para->model[i].gruppe[j].cset.ambience,TRUE);
            }
            if (para->model[i].gruppe[j].cset.changespecularcolor) {
                hcolor = para->model[i].gruppe[j].attrproperty->GetSpecularColor();
                ck = hcolor->CountKeys();
                if (ck > 1)
                    hcolor->DeleteKeys(time_range);
                hcolor->StoreValue(Time(), para->model[i].gruppe[j].cset.specular,TRUE);
            }
            if (para->model[i].gruppe[j].cset.changeambienceintensity) {
                hfloat = para->model[i].gruppe[j].attrproperty->GetAmbiance();
                ck = hfloat->CountKeys();
                if (ck > 1)
                    hfloat->DeleteKeys(time_range);
                hfloat->StoreValue(Time(), para->model[i].gruppe[j].cset.ambienceintensity,TRUE);
            }
            if (para->model[i].gruppe[j].cset.changespecularintensity) {
                hfloat = para->model[i].gruppe[j].attrproperty->GetSpecularIntensity();
                ck = hfloat->CountKeys();
                if (ck > 1)
                    hfloat->DeleteKeys(time_range);
                hfloat->StoreValue(Time(), para->model[i].gruppe[j].cset.specularintensity,TRUE);
            }
            if (para->model[i].gruppe[j].cset.changespecularsize) {
                hfloat = para->model[i].gruppe[j].attrproperty->GetSpecularSize();
                ck = hfloat->CountKeys();
                if (ck > 1)
                    hfloat->DeleteKeys(time_range);
                hfloat->StoreValue(Time(), para->model[i].gruppe[j].cset.specularsize,TRUE);
            }
            if (para->model[i].gruppe[j].cset.changereflectionintensity) {
                hfloat = para->model[i].gruppe[j].attrproperty->GetReflectivity();
                ck = hfloat->CountKeys();
                if (ck > 1)
                    hfloat->DeleteKeys(time_range);
                hfloat->StoreValue(Time(), para->model[i].gruppe[j].cset.reflectionintensity,TRUE);
            }
            for (int k = 0; k < para->model[i].gruppe[j].azmat; ++k) {
                if (para->model[i].gruppe[j].material[k].isclip) {
                    // Decal
                    if (para->model[i].gruppe[j].material[k].changepercentage) {
                        ck = para->model[i].gruppe[j].material[k].percent->CountKeys();
                        if (ck > 1)
                            para->model[i].gruppe[j].material[k].percent->DeleteKeys(time_range);
                        para->model[i].gruppe[j].material[k].percent->StoreValue(Time(), para->model[i].gruppe[j].material[k].percentage,TRUE);
                    }
                } else {
                    // Material
                    if (para->model[i].gruppe[j].material[k].cset.changediffusecolor) {
                        hcolor = para->model[i].gruppe[j].material[k].attrproperty->GetDiffuseColor();
                        ck = hcolor->CountKeys();
                        if (ck > 1)
                            hcolor->DeleteKeys(time_range);
                        hcolor->StoreValue(Time(), para->model[i].gruppe[j].material[k].cset.diffuse,TRUE);
                    }
                    if (para->model[i].gruppe[j].material[k].cset.changeambiencecolor) {
                        hcolor = para->model[i].gruppe[j].material[k].attrproperty->GetAmbianceColor();
                        ck = hcolor->CountKeys();
                        if (ck > 1)
                            hcolor->DeleteKeys(time_range);
                        hcolor->StoreValue(Time(), para->model[i].gruppe[j].material[k].cset.ambience,TRUE);
                    }
                    if (para->model[i].gruppe[j].material[k].cset.changespecularcolor) {
                        hcolor = para->model[i].gruppe[j].material[k].attrproperty->GetSpecularColor();
                        ck = hcolor->CountKeys();
                        if (ck > 1)
                            hcolor->DeleteKeys(time_range);
                        hcolor->StoreValue(Time(), para->model[i].gruppe[j].material[k].cset.specular,TRUE);
                    }
                    if (para->model[i].gruppe[j].material[k].cset.changeambienceintensity) {
                        hfloat = para->model[i].gruppe[j].material[k].attrproperty->GetAmbiance();
                        ck = hfloat->CountKeys();
                        if (ck > 1)
                            hfloat->DeleteKeys(time_range);
                        hfloat->StoreValue(Time(), para->model[i].gruppe[j].material[k].cset.ambienceintensity,TRUE);
                    }
                    if (para->model[i].gruppe[j].material[k].cset.changespecularintensity) {
                        hfloat = para->model[i].gruppe[j].material[k].attrproperty->GetSpecularIntensity();
                        ck = hfloat->CountKeys();
                        if (ck > 1)
                            hfloat->DeleteKeys(time_range);
                        hfloat->StoreValue(Time(), para->model[i].gruppe[j].material[k].cset.specularintensity,TRUE);
                    }
                    if (para->model[i].gruppe[j].material[k].cset.changespecularsize) {
                        hfloat = para->model[i].gruppe[j].material[k].attrproperty->GetSpecularSize();
                        ck = hfloat->CountKeys();
                        if (ck > 1)
                            hfloat->DeleteKeys(time_range);
                        hfloat->StoreValue(Time(), para->model[i].gruppe[j].material[k].cset.specularsize,TRUE);
                    }
                    if (para->model[i].gruppe[j].material[k].cset.changereflectionintensity) {
                        hfloat = para->model[i].gruppe[j].material[k].attrproperty->GetReflectivity();
                        ck = hfloat->CountKeys();
                        if (ck > 1)
                            hfloat->DeleteKeys(time_range);
                        hfloat->StoreValue(Time(), para->model[i].gruppe[j].material[k].cset.reflectionintensity,TRUE);
                    }
                }
            }
        }
    }
}

BOOL RecurseMaterial_check(HHashObject *hobj1, int &k) {

    HProperty *prop;

    bool isclip = FALSE;
    for (int u = 0; (prop = hobj1->GetPropertyAt(u)); u++) {
        if (prop->GetObjectType() == HOT_CLIPPROPERTY)
            isclip = true;
        if (prop->GetObjectType() == HOT_FLOAT && isclip)
            k++;
        if (prop->GetObjectType() == HOT_ATTR)
            k++;
    }
    if (hobj1->GetChild())
        RecurseMaterial_check(hobj1->GetChild(), k);
    if (hobj1->GetSibling())
        RecurseMaterial_check(hobj1->GetSibling(), k);
    return true;
}

BOOL CPassesApp::RecurseMaterial_add(HHashObject *hobj, HHashObject *hobj1, const int j, int &i) const {

    HProperty *prop;

    bool isclip = FALSE;
    for (int u = 0; (prop = hobj1->GetPropertyAt(u)); u++) {
        if (prop->GetObjectType() == HOT_CLIPPROPERTY)
            isclip = true;
        if (prop->GetObjectType() == HOT_FLOAT && isclip) {
            para->model[j].material[i].hmaterial = (HMaterial *)hobj;
            para->model[j].material[i].isclip = TRUE;
            para->model[j].material[i].percentage = 0;
            para->model[j].material[i].changepercentage = FALSE;
            para->model[j].material[i].percent = (HFloatProperty *)prop;
            i++;
        }
        if (prop->GetObjectType() == HOT_ATTR) {
            para->model[j].material[i].hmaterial = (HMaterial *)hobj;
            para->model[j].material[i].isclip = FALSE;
            para->model[j].material[i].attrproperty = (HAttrProperty *)prop;
            para->model[j].material[i].cset.changeambiencecolor = FALSE;
            para->model[j].material[i].cset.changeambienceintensity = FALSE;
            para->model[j].material[i].cset.changediffusecolor = FALSE;
            para->model[j].material[i].cset.changereflectionintensity = FALSE;
            para->model[j].material[i].cset.changespecularcolor = FALSE;
            para->model[j].material[i].cset.changespecularintensity = FALSE;
            para->model[j].material[i].cset.changespecularsize = FALSE;
            i++;
        }
    }
    if (hobj1->GetChild())
        RecurseMaterial_add(hobj, hobj1->GetChild(), j, i);
    if (hobj1->GetSibling())
        RecurseMaterial_add(hobj, hobj1->GetSibling(), j, i);
    return true;
}

BOOL CPassesApp::RecurseMaterial_add_group(HHashObject *hobj, HHashObject *hobj1, const int j, const int i, int &k) const {

    HProperty *prop;

    bool isclip = FALSE;
    for (int u = 0; (prop = hobj1->GetPropertyAt(u)); u++) {
        if (prop->GetObjectType() == HOT_CLIPPROPERTY)
            isclip = true;
        if (prop->GetObjectType() == HOT_FLOAT && isclip) {
            para->model[j].gruppe[i].material[k].hmaterial = (HMaterial *)hobj;
            para->model[j].gruppe[i].material[k].isclip = TRUE;
            para->model[j].gruppe[i].material[k].changepercentage = FALSE;
            para->model[j].gruppe[i].material[k].percentage = 0;
            para->model[j].gruppe[i].material[k].percent = (HFloatProperty *)prop;
            k++;
        }
        if (prop->GetObjectType() == HOT_ATTR) {
            para->model[j].gruppe[i].material[k].hmaterial = (HMaterial *)hobj;
            para->model[j].gruppe[i].material[k].isclip = FALSE;
            para->model[j].gruppe[i].material[k].attrproperty = (HAttrProperty *)prop;
            para->model[j].gruppe[i].material[k].cset.changeambiencecolor = FALSE;
            para->model[j].gruppe[i].material[k].cset.changeambienceintensity = FALSE;
            para->model[j].gruppe[i].material[k].cset.changediffusecolor = FALSE;
            para->model[j].gruppe[i].material[k].cset.changereflectionintensity = FALSE;
            para->model[j].gruppe[i].material[k].cset.changespecularcolor = FALSE;
            para->model[j].gruppe[i].material[k].cset.changespecularintensity = FALSE;
            para->model[j].gruppe[i].material[k].cset.changespecularsize = FALSE;
            k++;
        }
    }
    if (hobj1->GetChild())
        RecurseMaterial_add_group(hobj, hobj1->GetChild(), j, i, k);
    if (hobj1->GetSibling())
        RecurseMaterial_add_group(hobj, hobj1->GetSibling(), j, i, k);
    return true;
}

BOOL CPassesApp::ReadChor(HChor *hchor) const {
    HModel *hm;
    HDecalClipContainer *clipcontainer;
    HHashObject *hobj, *hobj1, *hobj2;
    int i, k;
    //   int u;
    //   HProperty *prop;
    //   bool isclip;

    for (hm = hchor->GetChildModel(); hm; hm = hm->GetNextModelInChor(), para->azmodel++)
        para->model = new MODEL[para->azmodel];

    int j = 0;
    for (hm = hchor->GetChildModel(); hm; hm = hm->GetNextModelInChor(), ++j) {
        para->model[j].hmodel = hm;
        para->model[j].attrproperty = hm->GetAttr();
        para->model[j].azdecal = 0;
        para->model[j].azmat = 0;
        para->model[j].azgroup = 0;
        para->model[j].cset.changeambiencecolor = FALSE;
        para->model[j].cset.changeambienceintensity = FALSE;
        para->model[j].cset.changediffusecolor = FALSE;
        para->model[j].cset.changereflectionintensity = FALSE;
        para->model[j].cset.changespecularcolor = FALSE;
        para->model[j].cset.changespecularsize = FALSE;
        para->model[j].cset.changespecularintensity = FALSE;

        //Decal
        HDecalContainer *decalcontainer = hm->GetChildDecalContainer();
        if (decalcontainer) {
            i = 0;
            for (hobj = decalcontainer->GetChildDecal(); hobj; hobj = hobj->GetSibling()) {
                clipcontainer = ((HDecal *)hobj)->GetChildDecalClipContainer();
                if (clipcontainer) {
                    for (hobj1 = clipcontainer->GetChildDecalClip(); hobj1; hobj1 = hobj1->GetSibling()) {
                        i++;
                    }
                }
            }
            para->model[j].azdecal = i;
            para->model[j].decal = new DECAL[para->model[j].azdecal];
            i = 0;
            for (hobj = decalcontainer->GetChildDecal(); hobj; hobj = hobj->GetSibling()) {
                clipcontainer = ((HDecal *)hobj)->GetChildDecalClipContainer();
                if (clipcontainer) {
                    for (hobj1 = clipcontainer->GetChildDecalClip(); hobj1; hobj1 = hobj1->GetSibling()) {
                        para->model[j].decal[i].hdecalclip = (HDecalClip *)hobj1;
                        para->model[j].decal[i].decaltype = para->model[j].decal[i].hdecalclip->GetKind()->GetValue();
                        para->model[j].decal[i].percent = para->model[j].decal[i].hdecalclip->GetPercent();
                        para->model[j].decal[i].percentage = 0.F;
                        para->model[j].decal[i].tochange = false;
                        i++;
                    }
                }
            }
        } else {
            para->model[j].azdecal = 0;
        }

        //Gruppen
        HGroupContainer *groupcontainer = hm->GetChildGroupContainer();
        if (groupcontainer) {
            i = 0;
            for (hobj = groupcontainer->GetChildGroup(); hobj; hobj = hobj->GetSibling(), ++i)
                para->model[j].azgroup = i;
            para->model[j].gruppe = new GRUPPE[para->model[j].azgroup];
            i = 0;
            for (hobj = groupcontainer->GetChildGroup(); hobj; hobj = hobj->GetSibling(), ++i) {
                para->model[j].gruppe[i].hgroup = (HGroup *)hobj;
                para->model[j].gruppe[i].attrproperty = para->model[j].gruppe[i].hgroup->GetAttr();
                para->model[j].gruppe[i].cset.changeambiencecolor = FALSE;
                para->model[j].gruppe[i].cset.changeambienceintensity = FALSE;
                para->model[j].gruppe[i].cset.changediffusecolor = FALSE;
                para->model[j].gruppe[i].cset.changereflectionintensity = FALSE;
                para->model[j].gruppe[i].cset.changespecularcolor = FALSE;
                para->model[j].gruppe[i].cset.changespecularintensity = FALSE;
                para->model[j].gruppe[i].cset.changespecularsize = FALSE;
                //extra Material fuer Gruppen checken
                k = 0;
                for (hobj1 = hobj->GetChild(); hobj1; hobj1 = hobj1->GetSibling()) {
                    if (hobj1->GetObjectType() == HOT_MATERIAL) {
                        hobj2 = hobj1->GetChild();
                        if (hobj2)
                            RecurseMaterial_check(hobj2, k);
                        /*					   while (hobj2) {
                                                   isclip = FALSE;
                                                   for (u=0; property=hobj2->GetPropertyAt(u); u++) {
                                                        if (property->GetObjectType() == HOT_CLIPPROPERTY) isclip = true;
                                                        if ((property->GetObjectType() == HOT_FLOAT) && (isclip)) k++;
                                                        if (property->GetObjectType() == HOT_ATTR) k++;
                                                    }
                                                   if (hobj2->GetSibling()) {
                                                       hobj2 = hobj2->GetSibling();
                                                   } else {
                                                         hobj2 = hobj2->GetChild();
                                                   }
                                               } */
                    }
                }
                if (k == 0) {
                    para->model[j].gruppe[i].azmat = 0;
                } else {
                    para->model[j].gruppe[i].azmat = k;
                    para->model[j].gruppe[i].material = new MATERIAL[k];
                    k = 0;
                    for (hobj1 = hobj->GetChild(); hobj1; hobj1 = hobj1->GetSibling()) {
                        if (hobj1->GetObjectType() == HOT_MATERIAL) {
                            hobj2 = hobj1->GetChild();
                            if (hobj2)
                                RecurseMaterial_add_group(hobj1, hobj2, j, i, k);
                            /*						   while (hobj2) {
                                                           isclip = FALSE;
                                                           for (u=0; property=hobj2->GetPropertyAt(u); u++) {
                                                                if (property->GetObjectType() == HOT_CLIPPROPERTY) isclip = true;
                                                                if ((property->GetObjectType() == HOT_FLOAT) && (isclip)) {
                                                                    para->model[j].gruppe[i].material[k].hmaterial = (HMaterial *)hobj1;
                                                                    para->model[j].gruppe[i].material[k].isclip = TRUE;
                                                                    para->model[j].gruppe[i].material[k].changepercentage = FALSE;
                                                                    para->model[j].gruppe[i].material[k].percentage = 0;
                                                                    para->model[j].gruppe[i].material[k].percent = (HFloatProperty *)property;
                                                                    k++;
                                                                }
                                                                if (property->GetObjectType() == HOT_ATTR) {
                                                                    para->model[j].gruppe[i].material[k].hmaterial = (HMaterial *)hobj1;
                                                                    para->model[j].gruppe[i].material[k].isclip = FALSE;
                                                                    para->model[j].gruppe[i].material[k].attrproperty = (HAttrProperty *)property;
                                                                    para->model[j].gruppe[i].material[k].cset.changeambiencecolor = FALSE;
                                                                    para->model[j].gruppe[i].material[k].cset.changeambienceintensity = FALSE;
                                                                    para->model[j].gruppe[i].material[k].cset.changediffusecolor = FALSE;
                                                                    para->model[j].gruppe[i].material[k].cset.changereflectionintensity = FALSE;
                                                                    para->model[j].gruppe[i].material[k].cset.changespecularcolor = FALSE;
                                                                    para->model[j].gruppe[i].material[k].cset.changespecularintensity = FALSE;
                                                                    para->model[j].gruppe[i].material[k].cset.changespecularsize = FALSE;
                                                                    k++;
                                                                }
                                                            }
                                                           if (hobj2->GetSibling()) {
                                                               hobj2 = hobj2->GetSibling();
                                                           } else {
                                                                 hobj2 = hobj2->GetChild();
                                                           }
                                                       } */
                        }
                    }
                }
            }
        } else {
            para->model[j].azgroup = 0;
        }

        //Material
        k = 0;
        for (hobj = hm->GetChild(); hobj; hobj = hobj->GetSibling()) {
            if (hobj->GetObjectType() == HOT_MATERIAL) {
                hobj1 = hobj->GetChild();
                if (hobj1)
                    RecurseMaterial_check(hobj1, k);
                /*			   while (hobj1) {
                                   isclip = FALSE;
                                   for (u=0; property=hobj1->GetPropertyAt(u); u++) {
                                        if (property->GetObjectType() == HOT_CLIPPROPERTY) isclip = true;
                                        if ((property->GetObjectType() == HOT_FLOAT) && (isclip)) k++;
                                        if (property->GetObjectType() == HOT_ATTR) k++;
                                    }
                                   if (hobj1->GetSibling()) {
                                       hobj1 = hobj1->GetSibling();
                                   } else {
                                         hobj1 = hobj1->GetChild();
                                   }
                               }*/
            }
        }
        para->model[j].azmat = k;
        para->model[j].material = new MATERIAL[k];
        i = 0;
        for (hobj = hm->GetChild(); hobj; hobj = hobj->GetSibling()) {
            if (hobj->GetObjectType() == HOT_MATERIAL) {
                hobj1 = hobj->GetChild();
                if (hobj1)
                    RecurseMaterial_add(hobj, hobj1, j, i);
                /*			   while (hobj1) {
                                   isclip = FALSE;
                                   for (u=0; property=hobj1->GetPropertyAt(u); u++) {
                                        if (property->GetObjectType() == HOT_CLIPPROPERTY) isclip = true;
                                        if ((property->GetObjectType() == HOT_FLOAT) && (isclip)) {
                                            para->model[j].material[i].hmaterial = (HMaterial *)hobj;
                                            para->model[j].material[i].isclip = TRUE;
                                            para->model[j].material[i].percentage = 0;
                                            para->model[j].material[i].changepercentage = FALSE;
                                            para->model[j].material[i].percent = (HFloatProperty *)property;
                                            i++;
                                        }
                                        if (property->GetObjectType() == HOT_ATTR) {
                                            para->model[j].material[i].hmaterial = (HMaterial *)hobj;
                                            para->model[j].material[i].isclip = FALSE;
                                            para->model[j].material[i].attrproperty = (HAttrProperty *)property;
                                            para->model[j].material[i].cset.changeambiencecolor = FALSE;
                                            para->model[j].material[i].cset.changeambienceintensity = FALSE;
                                            para->model[j].material[i].cset.changediffusecolor = FALSE;
                                            para->model[j].material[i].cset.changereflectionintensity = FALSE;
                                            para->model[j].material[i].cset.changespecularcolor = FALSE;
                                            para->model[j].material[i].cset.changespecularintensity = FALSE;
                                            para->model[j].material[i].cset.changespecularsize = FALSE;
                                            i++;
                                        }
                                    }
                                   if (hobj1->GetSibling()) {
                                       hobj1 = hobj1->GetSibling();
                                   } else {
                                         hobj1 = hobj1->GetChild();
                                   }
                               }*/
            }
        }
    }

#ifdef _DEBUG
    dbgout(para);
#endif
    return TRUE;
}

BOOL MaterialDofPass(HHashObject *akt_prop, HChor *hchor) {
    int ck;
    HProperty *prop;
    bool isclip = FALSE;
    HFloatProperty *hfloat;
    ColorBuf cvector;

    TimeRange time_range;
    time_range.Set(Time(), hchor->GetTotalTime()->GetValue());
    cvector.Set(255, 255, 255, 0);

    for (int i = 0; (prop = akt_prop->GetPropertyAt(i)); ++i) {
        if (prop->GetObjectType() == HOT_CATEGORYPROPERTY) {
            MaterialDofPass(prop, hchor);
        }
        if (prop->GetObjectType() == HOT_CLIPPROPERTY)
            isclip = true;
        if (prop->GetObjectType() == HOT_FLOAT && isclip) {
            hfloat = (HFloatProperty *)prop;
            ck = hfloat->CountKeys();
            if (ck > 1)
                hfloat->DeleteKeys(time_range);
            hfloat->StoreValue(Time(), 0,TRUE);
        }
        if (prop->GetObjectType() == HOT_ATTR) {
            HColorProperty *hcolor = ((HAttrProperty *)prop)->GetDiffuseColor();
            ck = hcolor->CountKeys();
            if (ck > 1)
                hcolor->DeleteKeys(time_range);
            hcolor->StoreValue(Time(), cvector,TRUE);
            hfloat = ((HAttrProperty *)prop)->GetDiffuseFallOff();
            ck = hfloat->CountKeys();
            if (ck > 1)
                hfloat->DeleteKeys(time_range);
            hfloat->StoreValue(Time(), 0,TRUE);
            hcolor = ((HAttrProperty *)prop)->GetAmbianceColor();
            ck = hcolor->CountKeys();
            if (ck > 1)
                hcolor->DeleteKeys(time_range);
            hcolor->StoreValue(Time(), cvector,TRUE);
            hfloat = ((HAttrProperty *)prop)->GetAmbiance();
            ck = hfloat->CountKeys();
            if (ck > 1)
                hfloat->DeleteKeys(time_range);
            hfloat->StoreValue(Time(), 0,TRUE);
            hcolor = ((HAttrProperty *)prop)->GetSpecularColor();
            ck = hcolor->CountKeys();
            if (ck > 1)
                hcolor->DeleteKeys(time_range);
            hcolor->StoreValue(Time(), cvector,TRUE);
            hfloat = ((HAttrProperty *)prop)->GetSpecularSize();
            ck = hfloat->CountKeys();
            if (ck > 1)
                hfloat->DeleteKeys(time_range);
            hfloat->StoreValue(Time(), 0,TRUE);
            hfloat = ((HAttrProperty *)prop)->GetSpecularIntensity();
            ck = hfloat->CountKeys();
            if (ck > 1)
                hfloat->DeleteKeys(time_range);
            hfloat->StoreValue(Time(), 0,TRUE);
            hfloat = ((HAttrProperty *)prop)->GetRoughness();
            ck = hfloat->CountKeys();
            if (ck > 1)
                hfloat->DeleteKeys(time_range);
            hfloat->StoreValue(Time(), 0,TRUE);
            hfloat = ((HAttrProperty *)prop)->GetRoughnessScale();
            ck = hfloat->CountKeys();
            if (ck > 1)
                hfloat->DeleteKeys(time_range);
            hfloat->StoreValue(Time(), 0,TRUE);
            hfloat = ((HAttrProperty *)prop)->GetTransparency();
            ck = hfloat->CountKeys();
            if (ck > 1)
                hfloat->DeleteKeys(time_range);
            hfloat->StoreValue(Time(), 0,TRUE);
            hfloat = ((HAttrProperty *)prop)->GetDensity();
            ck = hfloat->CountKeys();
            if (ck > 1)
                hfloat->DeleteKeys(time_range);
            hfloat->StoreValue(Time(), 0,TRUE);
            hfloat = ((HAttrProperty *)prop)->GetRefraction();
            ck = hfloat->CountKeys();
            if (ck > 1)
                hfloat->DeleteKeys(time_range);
            hfloat->StoreValue(Time(), 0,TRUE);
            hfloat = ((HAttrProperty *)prop)->GetTranslucency();
            ck = hfloat->CountKeys();
            if (ck > 1)
                hfloat->DeleteKeys(time_range);
            hfloat->StoreValue(Time(), 0,TRUE);
            hfloat = ((HAttrProperty *)prop)->GetReflectivity();
            ck = hfloat->CountKeys();
            if (ck > 1)
                hfloat->DeleteKeys(time_range);
            hfloat->StoreValue(Time(), 0,TRUE);
            hfloat = ((HAttrProperty *)prop)->GetReflectivityFallOff();
            ck = hfloat->CountKeys();
            if (ck > 1)
                hfloat->DeleteKeys(time_range);
            hfloat->StoreValue(Time(), 0,TRUE);
            hfloat = ((HAttrProperty *)prop)->GetRadiance();
            ck = hfloat->CountKeys();
            if (ck > 1)
                hfloat->DeleteKeys(time_range);
            hfloat->StoreValue(Time(), 0,TRUE);
            HBoolProperty *hbool = ((HAttrProperty *)prop)->GetGlow();
            ck = hbool->CountKeys();
            if (ck > 1)
                hbool->DeleteKeys(time_range);
            hbool->StoreValue(Time(), 0,TRUE);
        }
    }
    return TRUE;
}

BOOL RecurseDof(HHashObject *obj, HChor *hchor) {
    MaterialDofPass(obj, hchor);
    if (obj->GetChild())
        RecurseDof(obj->GetChild(), hchor);
    if (obj->GetSibling())
        RecurseDof(obj->GetSibling(), hchor);
    return TRUE;
}

BOOL FindLightDof(HHashObject *obj, HChor *hchor) {

    TimeRange time_range;
    time_range.Set(Time(), hchor->GetTotalTime()->GetValue());

    if (!obj->GetChild() && !obj->GetSibling()) {
        if (obj->GetObjectType() == HOT_LIGHT) {
            auto *hlight = (HLight *)obj;
            HBoolCategoryProperty *hbc = hlight->GetCastShadows();
            const int ck = hbc->CountKeys();
            if (ck > 1)
                hbc->DeleteKeys(time_range);
            hbc->StoreValue(Time(),FALSE,TRUE); //Specularity off
        }
        return FALSE;
    }
    if (obj->GetSibling()) {
        FindLightDof(obj->GetSibling(), hchor);
    }
    if (obj->GetChild()) {
        FindLightDof(obj->GetChild(), hchor);
    }
    return TRUE;
}

BOOL CPassesApp::DofPass(HChor *hchor) {

    HHashObject *obj1;
    HCamera *hcam;
    HLight *hlight;
    HHashObject *hobj, *hobj1;
    HColorProperty *hcolor;
    ColorBuf cvector;
    HProperty *prop, *property1;
    int i, ck;
    HBoolCategoryProperty *hbc;

    TimeRange time_range;
    time_range.Set(Time(), hchor->GetTotalTime()->GetValue());
    cvector.Set(255, 255, 255, 0);

    for (HModel *hm = hchor->GetChildModel(); hm; hm = hm->GetNextModelInChor()) {
        //HauptSurface 
        hcolor = hm->GetAttr()->GetDiffuseColor();
        ck = hcolor->CountKeys();
        if (ck > 1)
            hcolor->DeleteKeys(time_range);
        hcolor->StoreValue(Time(), cvector,TRUE);
        HFloatProperty *hfloat = hm->GetAttr()->GetDiffuseFallOff();
        ck = hfloat->CountKeys();
        if (ck > 1)
            hfloat->DeleteKeys(time_range);
        hfloat->StoreValue(Time(), 0,TRUE);
        hcolor = hm->GetAttr()->GetAmbianceColor();
        ck = hcolor->CountKeys();
        if (ck > 1)
            hcolor->DeleteKeys(time_range);
        hcolor->StoreValue(Time(), cvector,TRUE);
        hfloat = hm->GetAttr()->GetAmbiance();
        ck = hfloat->CountKeys();
        if (ck > 1)
            hfloat->DeleteKeys(time_range);
        hfloat->StoreValue(Time(), 0,TRUE);
        hcolor = hm->GetAttr()->GetSpecularColor();
        ck = hcolor->CountKeys();
        if (ck > 1)
            hcolor->DeleteKeys(time_range);
        hcolor->StoreValue(Time(), cvector,TRUE);
        hfloat = hm->GetAttr()->GetSpecularSize();
        ck = hfloat->CountKeys();
        if (ck > 1)
            hfloat->DeleteKeys(time_range);
        hfloat->StoreValue(Time(), 0,TRUE);
        hfloat = hm->GetAttr()->GetSpecularIntensity();
        ck = hfloat->CountKeys();
        if (ck > 1)
            hfloat->DeleteKeys(time_range);
        hfloat->StoreValue(Time(), 0,TRUE);
        hfloat = hm->GetAttr()->GetRoughness();
        ck = hfloat->CountKeys();
        if (ck > 1)
            hfloat->DeleteKeys(time_range);
        hfloat->StoreValue(Time(), 0,TRUE);
        hfloat = hm->GetAttr()->GetRoughnessScale();
        ck = hfloat->CountKeys();
        if (ck > 1)
            hfloat->DeleteKeys(time_range);
        hfloat->StoreValue(Time(), 0,TRUE);
        hfloat = hm->GetAttr()->GetTransparency();
        ck = hfloat->CountKeys();
        if (ck > 1)
            hfloat->DeleteKeys(time_range);
        hfloat->StoreValue(Time(), 0,TRUE);
        hfloat = hm->GetAttr()->GetDensity();
        ck = hfloat->CountKeys();
        if (ck > 1)
            hfloat->DeleteKeys(time_range);
        hfloat->StoreValue(Time(), 0,TRUE);
        hfloat = hm->GetAttr()->GetRefraction();
        ck = hfloat->CountKeys();
        if (ck > 1)
            hfloat->DeleteKeys(time_range);
        hfloat->StoreValue(Time(), 0,TRUE);
        hfloat = hm->GetAttr()->GetTranslucency();
        ck = hfloat->CountKeys();
        if (ck > 1)
            hfloat->DeleteKeys(time_range);
        hfloat->StoreValue(Time(), 0,TRUE);
        hfloat = hm->GetAttr()->GetReflectivity();
        ck = hfloat->CountKeys();
        if (ck > 1)
            hfloat->DeleteKeys(time_range);
        hfloat->StoreValue(Time(), 0,TRUE);
        hfloat = hm->GetAttr()->GetReflectivityFallOff();
        ck = hfloat->CountKeys();
        if (ck > 1)
            hfloat->DeleteKeys(time_range);
        hfloat->StoreValue(Time(), 0,TRUE);
        hfloat = hm->GetAttr()->GetRadiance();
        ck = hfloat->CountKeys();
        if (ck > 1)
            hfloat->DeleteKeys(time_range);
        hfloat->StoreValue(Time(), 0,TRUE);
        HBoolProperty *hbool = hm->GetAttr()->GetGlow();
        ck = hbool->CountKeys();
        if (ck > 1)
            hbool->DeleteKeys(time_range);
        hbool->StoreValue(Time(), 0,TRUE);

        //Decal
        HDecalContainer *decalcontainer = hm->GetChildDecalContainer();
        if (decalcontainer) {
            for (hobj = decalcontainer->GetChildDecal(); hobj; hobj = hobj->GetSibling()) {
                HDecalClipContainer *clipcontainer = ((HDecal *)hobj)->GetChildDecalClipContainer();
                if (clipcontainer) {
                    for (hobj1 = clipcontainer->GetChildDecalClip(); hobj1; hobj1 = hobj1->GetSibling()) {
                        auto *clip = (HDecalClip *)hobj1;
                        hfloat = clip->GetPercent();
                        ck = hfloat->CountKeys();
                        if (ck > 1)
                            hfloat->DeleteKeys(time_range);
                        hfloat->StoreValue(Time(), 0,TRUE);
                    }
                }
            }
        }

        //Group
        HGroupContainer *groupcontainer = hm->GetChildGroupContainer();
        if (groupcontainer) {
            for (hobj = groupcontainer->GetChildGroup(); hobj; hobj = hobj->GetSibling()) {
                //Hauptsurface
                hcolor = ((HGroup *)hobj)->GetAttr()->GetDiffuseColor();
                ck = hcolor->CountKeys();
                if (ck > 1)
                    hcolor->DeleteKeys(time_range);
                hcolor->StoreValue(Time(), cvector,TRUE);
                hfloat = ((HGroup *)hobj)->GetAttr()->GetDiffuseFallOff();
                ck = hfloat->CountKeys();
                if (ck > 1)
                    hfloat->DeleteKeys(time_range);
                hfloat->StoreValue(Time(), 0,TRUE);
                hcolor = ((HGroup *)hobj)->GetAttr()->GetAmbianceColor();
                ck = hcolor->CountKeys();
                if (ck > 1)
                    hcolor->DeleteKeys(time_range);
                hcolor->StoreValue(Time(), cvector,TRUE);
                hfloat = ((HGroup *)hobj)->GetAttr()->GetAmbiance();
                ck = hfloat->CountKeys();
                if (ck > 1)
                    hfloat->DeleteKeys(time_range);
                hfloat->StoreValue(Time(), 0,TRUE);
                hcolor = ((HGroup *)hobj)->GetAttr()->GetSpecularColor();
                ck = hcolor->CountKeys();
                if (ck > 1)
                    hcolor->DeleteKeys(time_range);
                hcolor->StoreValue(Time(), cvector,TRUE);
                hfloat = ((HGroup *)hobj)->GetAttr()->GetSpecularSize();
                ck = hfloat->CountKeys();
                if (ck > 1)
                    hfloat->DeleteKeys(time_range);
                hfloat->StoreValue(Time(), 0,TRUE);
                hfloat = ((HGroup *)hobj)->GetAttr()->GetSpecularIntensity();
                ck = hfloat->CountKeys();
                if (ck > 1)
                    hfloat->DeleteKeys(time_range);
                hfloat->StoreValue(Time(), 0,TRUE);
                hfloat = ((HGroup *)hobj)->GetAttr()->GetRoughness();
                ck = hfloat->CountKeys();
                if (ck > 1)
                    hfloat->DeleteKeys(time_range);
                hfloat->StoreValue(Time(), 0,TRUE);
                hfloat = ((HGroup *)hobj)->GetAttr()->GetRoughnessScale();
                ck = hfloat->CountKeys();
                if (ck > 1)
                    hfloat->DeleteKeys(time_range);
                hfloat->StoreValue(Time(), 0,TRUE);
                hfloat = ((HGroup *)hobj)->GetAttr()->GetTransparency();
                ck = hfloat->CountKeys();
                if (ck > 1)
                    hfloat->DeleteKeys(time_range);
                hfloat->StoreValue(Time(), 0,TRUE);
                hfloat = ((HGroup *)hobj)->GetAttr()->GetDensity();
                ck = hfloat->CountKeys();
                if (ck > 1)
                    hfloat->DeleteKeys(time_range);
                hfloat->StoreValue(Time(), 0,TRUE);
                hfloat = ((HGroup *)hobj)->GetAttr()->GetRefraction();
                ck = hfloat->CountKeys();
                if (ck > 1)
                    hfloat->DeleteKeys(time_range);
                hfloat->StoreValue(Time(), 0,TRUE);
                hfloat = ((HGroup *)hobj)->GetAttr()->GetTranslucency();
                ck = hfloat->CountKeys();
                if (ck > 1)
                    hfloat->DeleteKeys(time_range);
                hfloat->StoreValue(Time(), 0,TRUE);
                hfloat = ((HGroup *)hobj)->GetAttr()->GetReflectivity();
                ck = hfloat->CountKeys();
                if (ck > 1)
                    hfloat->DeleteKeys(time_range);
                hfloat->StoreValue(Time(), 0,TRUE);
                hfloat = ((HGroup *)hobj)->GetAttr()->GetReflectivityFallOff();
                ck = hfloat->CountKeys();
                if (ck > 1)
                    hfloat->DeleteKeys(time_range);
                hfloat->StoreValue(Time(), 0,TRUE);
                hfloat = ((HGroup *)hobj)->GetAttr()->GetRadiance();
                ck = hfloat->CountKeys();
                if (ck > 1)
                    hfloat->DeleteKeys(time_range);
                hfloat->StoreValue(Time(), 0,TRUE);
                hbool = ((HGroup *)hobj)->GetAttr()->GetGlow();
                ck = hbool->CountKeys();
                if (ck > 1)
                    hbool->DeleteKeys(time_range);
                hbool->StoreValue(Time(), 0,TRUE);
                //extra Material fuer Grupp checken
                for (hobj1 = hobj->GetChild(); hobj1; hobj1 = hobj1->GetSibling()) {
                    if (hobj1->GetObjectType() == HOT_MATERIAL) {
                        //objt 24 (Material) abfangen
                        HHashObject *hobj2 = hobj->GetChild();
                        if (hobj2)
                            RecurseDof(hobj2, hchor);
                        /*					  while (hobj2) {
                                                 MaterialDofPass(hobj2,hchor);
                                                 if (hobj2->GetSibling()) {
                                                      hobj2 = hobj2->GetSibling();
                                                 } else {
                                                        hobj2 = hobj2->GetChild();
                                                 }
                                              } */
                    }
                }
            }
        }

        for (hobj = hm->GetChild(); hobj; hobj = hobj->GetSibling()) {
            if (hobj->GetObjectType() == HOT_MATERIAL) {
                //objt 24 (Material) abfangen
                hobj1 = hobj->GetChild();
                if (hobj1)
                    RecurseDof(hobj1, hchor);
                /*			   while (hobj1) {
                                   MaterialDofPass(hobj1,hchor);
                                   if (hobj1->GetSibling()) {
                                       hobj1 = hobj1->GetSibling();
                                   } else {
                                         hobj1 = hobj1->GetChild();
                                   }
                               } */
            }
        }
    }

    cvector.Set(0, 0, 0, 0);
    for (HHashObject *obj = hchor->GetChild(); obj; obj = obj->GetSibling()) {
        switch (obj->GetObjectType()) {
            case HOT_CAMERA:
                hcam = (HCamera *)obj;
                hcolor = hcam->GetBackGroundColor();
                ck = hcolor->CountKeys();
                if (ck > 1)
                    hcolor->DeleteKeys(time_range);
                hcolor->StoreValue(Time(), cvector,TRUE);
                for (i = 0; (prop = hcam->GetPropertyAt(i)); ++i) {
                    String name = prop->GetFullName();
                    ObjectType objt = prop->GetObjectType();
                    if (name.Find(".RenderOptions") > 0 && objt == HOT_CONTAINERPROPERTY) {
                        for (int j = 0; (property1 = prop->GetPropertyAt(j)); ++j) {
                            name = property1->GetFullName();
                            objt = property1->GetObjectType();
                            if (name.Find(".ShowShadows") > 0 && objt == HOT_BOOL) {
                                auto *hbp = (HBoolProperty *)property1;
                                ck = hbp->CountKeys();
                                if (ck > 1)
                                    hbp->DeleteKeys(time_range);
                                hbp->StoreValue(Time(),FALSE,TRUE); //Shadow off
                            }
                            if (name.Find(".Dof") > 0 && objt == HOT_CATEGORYPROPERTY) {
                                hbc = (HBoolCategoryProperty *)property1;
                                ck = hbc->CountKeys();
                                if (ck > 1)
                                    hbc->DeleteKeys(time_range);
                                hbc->StoreValue(Time(),TRUE,TRUE); //Dof on
                            }
                        }
                    }
                }
                break;
            case HOT_LIGHT:
                hlight = (HLight *)obj;
                hbc = hlight->GetCastShadows();
                ck = hbc->CountKeys();
                if (ck > 1)
                    hbc->DeleteKeys(time_range);
                hbc->StoreValue(Time(),FALSE,TRUE); //Shadow off
                break;
            case HOT_MODEL:
                obj1 = obj->GetChild();
                if (obj1) {
                    if (obj1->GetObjectType() == HOT_LIGHT) {
                        hlight = (HLight *)obj1;
                        hbc = hlight->GetCastShadows();
                        ck = hbc->CountKeys();
                        if (ck > 1)
                            hbc->DeleteKeys(time_range);
                        hbc->StoreValue(Time(),FALSE,TRUE); //Specularity off
                    }
                    FindLightDof(obj1, hchor);
                }
                break;
            default:
                break;
        }
    }

    return TRUE;
}

BOOL MaterialShadowPass(HHashObject *akt_prop, HChor *hchor) {
    int ck;
    HProperty *prop;
    bool isclip = FALSE;
    HFloatProperty *hfloat;
    ColorBuf cvector;
    TimeRange time_range;
    time_range.Set(Time(), hchor->GetTotalTime()->GetValue());

    cvector.Set(255, 255, 255, 0);

    for (int i = 0; (prop = akt_prop->GetPropertyAt(i)); ++i) {
        if (prop->GetObjectType() == HOT_CATEGORYPROPERTY) {
            MaterialShadowPass(prop, hchor);
        }
        if (prop->GetObjectType() == HOT_CLIPPROPERTY)
            isclip = true;
        if (prop->GetObjectType() == HOT_FLOAT && isclip) {
            hfloat = (HFloatProperty *)prop;
            ck = hfloat->CountKeys();
            if (ck > 1)
                hfloat->DeleteKeys(time_range);
            hfloat->StoreValue(Time(), 0,TRUE);
        }
        if (prop->GetObjectType() == HOT_ATTR) {
            HColorProperty *hcolor = ((HAttrProperty *)prop)->GetDiffuseColor();
            ck = hcolor->CountKeys();
            if (ck > 1)
                hcolor->DeleteKeys(time_range);
            hcolor->StoreValue(Time(), cvector,TRUE);
            hfloat = ((HAttrProperty *)prop)->GetDiffuseFallOff();
            ck = hfloat->CountKeys();
            if (ck > 1)
                hfloat->DeleteKeys(time_range);
            hfloat->StoreValue(Time(), 0,TRUE);
            hcolor = ((HAttrProperty *)prop)->GetAmbianceColor();
            ck = hcolor->CountKeys();
            if (ck > 1)
                hcolor->DeleteKeys(time_range);
            hcolor->StoreValue(Time(), cvector,TRUE);
            hfloat = ((HAttrProperty *)prop)->GetAmbiance();
            ck = hfloat->CountKeys();
            if (ck > 1)
                hfloat->DeleteKeys(time_range);
            hfloat->StoreValue(Time(), 0,TRUE);
            hcolor = ((HAttrProperty *)prop)->GetSpecularColor();
            ck = hcolor->CountKeys();
            if (ck > 1)
                hcolor->DeleteKeys(time_range);
            hcolor->StoreValue(Time(), cvector,TRUE);
            hfloat = ((HAttrProperty *)prop)->GetSpecularSize();
            ck = hfloat->CountKeys();
            if (ck > 1)
                hfloat->DeleteKeys(time_range);
            hfloat->StoreValue(Time(), 0,TRUE);
            hfloat = ((HAttrProperty *)prop)->GetSpecularIntensity();
            ck = hfloat->CountKeys();
            if (ck > 1)
                hfloat->DeleteKeys(time_range);
            hfloat->StoreValue(Time(), 0,TRUE);
            hfloat = ((HAttrProperty *)prop)->GetRoughness();
            ck = hfloat->CountKeys();
            if (ck > 1)
                hfloat->DeleteKeys(time_range);
            hfloat->StoreValue(Time(), 0,TRUE);
            hfloat = ((HAttrProperty *)prop)->GetRoughnessScale();
            ck = hfloat->CountKeys();
            if (ck > 1)
                hfloat->DeleteKeys(time_range);
            hfloat->StoreValue(Time(), 0,TRUE);
            hfloat = ((HAttrProperty *)prop)->GetTransparency();
            ck = hfloat->CountKeys();
            if (ck > 1)
                hfloat->DeleteKeys(time_range);
            hfloat->StoreValue(Time(), 0,TRUE);
            hfloat = ((HAttrProperty *)prop)->GetDensity();
            ck = hfloat->CountKeys();
            if (ck > 1)
                hfloat->DeleteKeys(time_range);
            hfloat->StoreValue(Time(), 0,TRUE);
            hfloat = ((HAttrProperty *)prop)->GetRefraction();
            ck = hfloat->CountKeys();
            if (ck > 1)
                hfloat->DeleteKeys(time_range);
            hfloat->StoreValue(Time(), 0,TRUE);
            hfloat = ((HAttrProperty *)prop)->GetTranslucency();
            ck = hfloat->CountKeys();
            if (ck > 1)
                hfloat->DeleteKeys(time_range);
            hfloat->StoreValue(Time(), 0,TRUE);
            hfloat = ((HAttrProperty *)prop)->GetReflectivity();
            ck = hfloat->CountKeys();
            if (ck > 1)
                hfloat->DeleteKeys(time_range);
            hfloat->StoreValue(Time(), 0,TRUE);
            hfloat = ((HAttrProperty *)prop)->GetReflectivityFallOff();
            ck = hfloat->CountKeys();
            if (ck > 1)
                hfloat->DeleteKeys(time_range);
            hfloat->StoreValue(Time(), 0,TRUE);
            hfloat = ((HAttrProperty *)prop)->GetRadiance();
            ck = hfloat->CountKeys();
            if (ck > 1)
                hfloat->DeleteKeys(time_range);
            hfloat->StoreValue(Time(), 0,TRUE);
            HBoolProperty *hbool = ((HAttrProperty *)prop)->GetGlow();
            ck = hbool->CountKeys();
            if (ck > 1)
                hbool->DeleteKeys(time_range);
            hbool->StoreValue(Time(), 0,TRUE);
        }
    }
    return TRUE;
}

BOOL RecurseShadow(HHashObject *obj, HChor *hchor) {

    MaterialShadowPass(obj, hchor);
    if (obj->GetChild())
        RecurseShadow(obj->GetChild(), hchor);
    if (obj->GetSibling())
        RecurseShadow(obj->GetSibling(), hchor);
    return TRUE;
}

BOOL CPassesApp::ShadowPass(HChor *hchor) {

    HHashObject *hobj, *hobj1;
    ColorBuf cvector;
    TimeRange time_range;
    time_range.Set(Time(), hchor->GetTotalTime()->GetValue());

    cvector.Set(255, 255, 255, 0);

    for (HModel *hm = hchor->GetChildModel(); hm; hm = hm->GetNextModelInChor()) {
        //HauptSurface 
        HColorProperty *hcolor = hm->GetAttr()->GetDiffuseColor();
        int ck = hcolor->CountKeys();
        if (ck > 1)
            hcolor->DeleteKeys(time_range);
        hcolor->StoreValue(Time(), cvector,TRUE);
        HFloatProperty *hfloat = hm->GetAttr()->GetDiffuseFallOff();
        ck = hfloat->CountKeys();
        if (ck > 1)
            hfloat->DeleteKeys(time_range);
        hfloat->StoreValue(Time(), 0,TRUE);
        hcolor = hm->GetAttr()->GetAmbianceColor();
        ck = hcolor->CountKeys();
        if (ck > 1)
            hcolor->DeleteKeys(time_range);
        hcolor->StoreValue(Time(), cvector,TRUE);
        hfloat = hm->GetAttr()->GetAmbiance();
        ck = hfloat->CountKeys();
        if (ck > 1)
            hfloat->DeleteKeys(time_range);
        hfloat->StoreValue(Time(), 0,TRUE);
        hcolor = hm->GetAttr()->GetSpecularColor();
        ck = hcolor->CountKeys();
        if (ck > 1)
            hcolor->DeleteKeys(time_range);
        hcolor->StoreValue(Time(), cvector,TRUE);
        hfloat = hm->GetAttr()->GetSpecularSize();
        ck = hfloat->CountKeys();
        if (ck > 1)
            hfloat->DeleteKeys(time_range);
        hfloat->StoreValue(Time(), 0,TRUE);
        hfloat = hm->GetAttr()->GetSpecularIntensity();
        ck = hfloat->CountKeys();
        if (ck > 1)
            hfloat->DeleteKeys(time_range);
        hfloat->StoreValue(Time(), 0,TRUE);
        hfloat = hm->GetAttr()->GetRoughness();
        ck = hfloat->CountKeys();
        if (ck > 1)
            hfloat->DeleteKeys(time_range);
        hfloat->StoreValue(Time(), 0,TRUE);
        hfloat = hm->GetAttr()->GetRoughnessScale();
        ck = hfloat->CountKeys();
        if (ck > 1)
            hfloat->DeleteKeys(time_range);
        hfloat->StoreValue(Time(), 0,TRUE);
        hfloat = hm->GetAttr()->GetTransparency();
        ck = hfloat->CountKeys();
        if (ck > 1)
            hfloat->DeleteKeys(time_range);
        hfloat->StoreValue(Time(), 0,TRUE);
        hfloat = hm->GetAttr()->GetDensity();
        ck = hfloat->CountKeys();
        if (ck > 1)
            hfloat->DeleteKeys(time_range);
        hfloat->StoreValue(Time(), 0,TRUE);
        hfloat = hm->GetAttr()->GetRefraction();
        ck = hfloat->CountKeys();
        if (ck > 1)
            hfloat->DeleteKeys(time_range);
        hfloat->StoreValue(Time(), 0,TRUE);
        hfloat = hm->GetAttr()->GetTranslucency();
        ck = hfloat->CountKeys();
        if (ck > 1)
            hfloat->DeleteKeys(time_range);
        hfloat->StoreValue(Time(), 0,TRUE);
        hfloat = hm->GetAttr()->GetReflectivity();
        ck = hfloat->CountKeys();
        if (ck > 1)
            hfloat->DeleteKeys(time_range);
        hfloat->StoreValue(Time(), 0,TRUE);
        hfloat = hm->GetAttr()->GetReflectivityFallOff();
        ck = hfloat->CountKeys();
        if (ck > 1)
            hfloat->DeleteKeys(time_range);
        hfloat->StoreValue(Time(), 0,TRUE);
        hfloat = hm->GetAttr()->GetRadiance();
        ck = hfloat->CountKeys();
        if (ck > 1)
            hfloat->DeleteKeys(time_range);
        hfloat->StoreValue(Time(), 0,TRUE);
        HBoolProperty *hbool = hm->GetAttr()->GetGlow();
        ck = hbool->CountKeys();
        if (ck > 1)
            hbool->DeleteKeys(time_range);
        hbool->StoreValue(Time(), 0,TRUE);

        //Decal
        HDecalContainer *decalcontainer = hm->GetChildDecalContainer();
        if (decalcontainer) {
            for (hobj = decalcontainer->GetChildDecal(); hobj; hobj = hobj->GetSibling()) {
                HDecalClipContainer *clipcontainer = ((HDecal *)hobj)->GetChildDecalClipContainer();
                if (clipcontainer) {
                    for (hobj1 = clipcontainer->GetChildDecalClip(); hobj1; hobj1 = hobj1->GetSibling()) {
                        auto *clip = (HDecalClip *)hobj1;
                        hfloat = clip->GetPercent();
                        ck = hfloat->CountKeys();
                        if (ck > 1)
                            hfloat->DeleteKeys(time_range);
                        hfloat->StoreValue(Time(), 0,TRUE);
                    }
                }
            }
        }

        //Group
        HGroupContainer *groupcontainer = hm->GetChildGroupContainer();
        if (groupcontainer) {
            for (hobj = groupcontainer->GetChildGroup(); hobj; hobj = hobj->GetSibling()) {
                //Hauptsurface
                hcolor = ((HGroup *)hobj)->GetAttr()->GetDiffuseColor();
                ck = hcolor->CountKeys();
                if (ck > 1)
                    hcolor->DeleteKeys(time_range);
                hcolor->StoreValue(Time(), cvector,TRUE);
                hfloat = ((HGroup *)hobj)->GetAttr()->GetDiffuseFallOff();
                ck = hfloat->CountKeys();
                if (ck > 1)
                    hfloat->DeleteKeys(time_range);
                hfloat->StoreValue(Time(), 0,TRUE);
                hcolor = ((HGroup *)hobj)->GetAttr()->GetAmbianceColor();
                ck = hcolor->CountKeys();
                if (ck > 1)
                    hcolor->DeleteKeys(time_range);
                hcolor->StoreValue(Time(), cvector,TRUE);
                hfloat = ((HGroup *)hobj)->GetAttr()->GetAmbiance();
                ck = hfloat->CountKeys();
                if (ck > 1)
                    hfloat->DeleteKeys(time_range);
                hfloat->StoreValue(Time(), 0,TRUE);
                hcolor = ((HGroup *)hobj)->GetAttr()->GetSpecularColor();
                ck = hcolor->CountKeys();
                if (ck > 1)
                    hcolor->DeleteKeys(time_range);
                hcolor->StoreValue(Time(), cvector,TRUE);
                hfloat = ((HGroup *)hobj)->GetAttr()->GetSpecularSize();
                ck = hfloat->CountKeys();
                if (ck > 1)
                    hfloat->DeleteKeys(time_range);
                hfloat->StoreValue(Time(), 0,TRUE);
                hfloat = ((HGroup *)hobj)->GetAttr()->GetSpecularIntensity();
                ck = hfloat->CountKeys();
                if (ck > 1)
                    hfloat->DeleteKeys(time_range);
                hfloat->StoreValue(Time(), 0,TRUE);
                hfloat = ((HGroup *)hobj)->GetAttr()->GetRoughness();
                ck = hfloat->CountKeys();
                if (ck > 1)
                    hfloat->DeleteKeys(time_range);
                hfloat->StoreValue(Time(), 0,TRUE);
                hfloat = ((HGroup *)hobj)->GetAttr()->GetRoughnessScale();
                ck = hfloat->CountKeys();
                if (ck > 1)
                    hfloat->DeleteKeys(time_range);
                hfloat->StoreValue(Time(), 0,TRUE);
                hfloat = ((HGroup *)hobj)->GetAttr()->GetTransparency();
                ck = hfloat->CountKeys();
                if (ck > 1)
                    hfloat->DeleteKeys(time_range);
                hfloat->StoreValue(Time(), 0,TRUE);
                hfloat = ((HGroup *)hobj)->GetAttr()->GetDensity();
                ck = hfloat->CountKeys();
                if (ck > 1)
                    hfloat->DeleteKeys(time_range);
                hfloat->StoreValue(Time(), 0,TRUE);
                hfloat = ((HGroup *)hobj)->GetAttr()->GetRefraction();
                ck = hfloat->CountKeys();
                if (ck > 1)
                    hfloat->DeleteKeys(time_range);
                hfloat->StoreValue(Time(), 0,TRUE);
                hfloat = ((HGroup *)hobj)->GetAttr()->GetTranslucency();
                ck = hfloat->CountKeys();
                if (ck > 1)
                    hfloat->DeleteKeys(time_range);
                hfloat->StoreValue(Time(), 0,TRUE);
                hfloat = ((HGroup *)hobj)->GetAttr()->GetReflectivity();
                ck = hfloat->CountKeys();
                if (ck > 1)
                    hfloat->DeleteKeys(time_range);
                hfloat->StoreValue(Time(), 0,TRUE);
                hfloat = ((HGroup *)hobj)->GetAttr()->GetReflectivityFallOff();
                ck = hfloat->CountKeys();
                if (ck > 1)
                    hfloat->DeleteKeys(time_range);
                hfloat->StoreValue(Time(), 0,TRUE);
                hfloat = ((HGroup *)hobj)->GetAttr()->GetRadiance();
                ck = hfloat->CountKeys();
                if (ck > 1)
                    hfloat->DeleteKeys(time_range);
                hfloat->StoreValue(Time(), 0,TRUE);
                hbool = ((HGroup *)hobj)->GetAttr()->GetGlow();
                ck = hbool->CountKeys();
                if (ck > 1)
                    hbool->DeleteKeys(time_range);
                hbool->StoreValue(Time(), 0,TRUE);
                //extra Material fuer Grupp checken
                for (hobj1 = hobj->GetChild(); hobj1; hobj1 = hobj1->GetSibling()) {
                    if (hobj1->GetObjectType() == HOT_MATERIAL) {
                        //objt 24 (Material) abfangen
                        HHashObject *hobj2 = hobj->GetChild();
                        if (hobj2)
                            RecurseShadow(hobj2, hchor);
                        /*					  while (hobj2) {
                                                 MaterialShadowPass(hobj2,hchor);
                                                 if (hobj2->GetSibling()) {
                                                      hobj2 = hobj2->GetSibling();
                                                 } else {
                                                        hobj2 = hobj2->GetChild();
                                                 }
                                              } */
                    }
                }
            }
        }

        for (hobj = hm->GetChild(); hobj; hobj = hobj->GetSibling()) {
            if (hobj->GetObjectType() == HOT_MATERIAL) {
                //objt 24 (Material) abfangen
                hobj1 = hobj->GetChild();
                if (hobj1)
                    RecurseShadow(hobj1, hchor);
                /*			   while (hobj1) {
                                   MaterialShadowPass(hobj1,hchor);
                                   if (hobj1->GetSibling()) {
                                       hobj1 = hobj1->GetSibling();
                                   } else {
                                         hobj1 = hobj1->GetChild();
                                   }
                               } */
            }
        }
    }
    return TRUE;
}

BOOL MaterialSpecularityPass(HHashObject *akt_prop, HChor *hchor) {
    int ck;
    HProperty *prop;
    bool isclip = FALSE;
    TimeRange time_range;
    const RGBFloat rgbfloat;
    time_range.Set(Time(), hchor->GetTotalTime()->GetValue());

    for (int i = 0; (prop = akt_prop->GetPropertyAt(i)); ++i) {
        if (prop->GetObjectType() == HOT_CATEGORYPROPERTY) {
            MaterialSpecularityPass(prop, hchor);
        }
        if (prop->GetObjectType() == HOT_CLIPPROPERTY)
            isclip = true;
        if (prop->GetObjectType() == HOT_FLOAT && isclip) {
            auto *hfloat = (HFloatProperty *)prop;
            ck = hfloat->CountKeys();
            if (ck > 1)
                hfloat->DeleteKeys(time_range);
            hfloat->StoreValue(Time(), 0,TRUE);
        }
        if (prop->GetObjectType() == HOT_ATTR) {
            HColorProperty *hcolor = ((HAttrProperty *)prop)->GetDiffuseColor();
            ck = hcolor->CountKeys();
            if (ck > 1)
                hcolor->DeleteKeys(time_range);
            hcolor->StoreValue(Time(), rgbfloat, TRUE);
        }
    }
    return TRUE;
}

BOOL RecurseSpecularity(HHashObject *obj, HChor *hchor) {

    MaterialSpecularityPass(obj, hchor);
    if (obj->GetChild())
        RecurseSpecularity(obj->GetChild(), hchor);
    if (obj->GetSibling())
        RecurseSpecularity(obj->GetSibling(), hchor);
    return TRUE;
}

BOOL CPassesApp::SpecularityPass(HChor *hchor) {

    HHashObject *hobj, *hobj1;
    const RGBFloat rgbfloat;
    TimeRange time_range;
    time_range.Set(Time(), hchor->GetTotalTime()->GetValue());

    for (HModel *hm = hchor->GetChildModel(); hm; hm = hm->GetNextModelInChor()) {
        //HauptSurface 
        HColorProperty *hcolor = hm->GetAttr()->GetDiffuseColor();
        int ck = hcolor->CountKeys();
        if (ck > 1)
            hcolor->DeleteKeys(time_range);
        hcolor->StoreValue(Time(), rgbfloat,TRUE);

        //Decal
        HDecalContainer *decalcontainer = hm->GetChildDecalContainer();
        if (decalcontainer) {
            for (hobj = decalcontainer->GetChildDecal(); hobj; hobj = hobj->GetSibling()) {
                HDecalClipContainer *clipcontainer = ((HDecal *)hobj)->GetChildDecalClipContainer();
                if (clipcontainer) {
                    for (hobj1 = clipcontainer->GetChildDecalClip(); hobj1; hobj1 = hobj1->GetSibling()) {
                        auto *clip = (HDecalClip *)hobj1;
                        if (clip->GetKind()->GetValue() == 0) {
                            HFloatProperty *hfloat = clip->GetPercent();
                            ck = hfloat->CountKeys();
                            if (ck > 1)
                                hfloat->DeleteKeys(time_range);
                            hfloat->StoreValue(Time(), 0,TRUE);
                        }
                    }
                }
            }
        }

        //Group
        HGroupContainer *groupcontainer = hm->GetChildGroupContainer();
        if (groupcontainer) {
            RGBFloat rgb_float;
            for (hobj = groupcontainer->GetChildGroup(); hobj; hobj = hobj->GetSibling()) {
                //Hauptsurface
                hcolor = ((HGroup *)hobj)->GetAttr()->GetDiffuseColor();
                ck = hcolor->CountKeys();
                if (ck > 1)
                    hcolor->DeleteKeys(time_range);
                hcolor->StoreValue(Time(), rgb_float,TRUE);
                //extra Material fuer Grupp checken
                for (hobj1 = hobj->GetChild(); hobj1; hobj1 = hobj1->GetSibling()) {
                    if (hobj1->GetObjectType() == HOT_MATERIAL) {
                        //objt 24 (Material) abfangen
                        HHashObject *hobj2 = hobj->GetChild();
                        if (hobj2)
                            RecurseSpecularity(hobj2, hchor);
                        /*					  while (hobj2) {
                                                 MaterialSpecularityPass(hobj2,hchor);
                                                 if (hobj2->GetSibling()) {
                                                      hobj2 = hobj2->GetSibling();
                                                 } else {
                                                        hobj2 = hobj2->GetChild();
                                                 }
                                              }*/
                    }
                }
            }
        }

        for (hobj = hm->GetChild(); hobj; hobj = hobj->GetSibling()) {
            if (hobj->GetObjectType() == HOT_MATERIAL) {
                //objt 24 (Material) abfangen
                hobj1 = hobj->GetChild();
                if (hobj1)
                    RecurseSpecularity(hobj1, hchor);
                /*			   while (hobj1) {
                                   MaterialSpecularityPass(hobj1,hchor);
                                   if (hobj1->GetSibling()) {
                                       hobj1 = hobj1->GetSibling();
                                   } else {
                                         hobj1 = hobj1->GetChild();
                                   }
                               } */
            }
        }
    }
    return TRUE;
}

BOOL FindLightDiffuse(HHashObject *obj, HChor *hchor) {

    TimeRange time_range;
    time_range.Set(Time(), hchor->GetTotalTime()->GetValue());

    if (!obj->GetChild() && !obj->GetSibling()) {
        if (obj->GetObjectType() == HOT_LIGHT) {
            auto *hlight = (HLight *)obj;
            HBoolProperty *hbc = hlight->GetSpecular();
            int ck = hbc->CountKeys();
            if (ck > 1)
                hbc->DeleteKeys(time_range);
            hbc->StoreValue(Time(),FALSE,TRUE); //Specularity off
            HBoolCategoryProperty *hbcp = hlight->GetCastShadows();
            ck = hbcp->CountKeys();
            if (ck > 1)
                hbcp->DeleteKeys(time_range);
            hbcp->StoreValue(Time(),FALSE,TRUE); //Shadow off
        }
        return FALSE;
    }
    if (obj->GetSibling()) {
        FindLightDiffuse(obj->GetSibling(), hchor);
    }
    if (obj->GetChild()) {
        FindLightDiffuse(obj->GetChild(), hchor);
    }
    return TRUE;
}

BOOL CPassesApp::DiffuseShadingPass(HChor *hchor) {

    HHashObject *obj1;
    HCamera *hcam;
    HLight *hlight;

    int i, ck;
    HProperty *prop, *property1;
    HBoolProperty *hbc;
    HBoolCategoryProperty *hbcp;
    TimeRange time_range;
    time_range.Set(Time(), hchor->GetTotalTime()->GetValue());

    for (HHashObject *obj = hchor->GetChild(); obj; obj = obj->GetSibling()) {
        switch (obj->GetObjectType()) {
            case HOT_CAMERA:
                hcam = (HCamera *)obj;
                for (i = 0; (prop = hcam->GetPropertyAt(i)); ++i) {
                    String name = prop->GetFullName();
                    ObjectType objt = prop->GetObjectType();
                    if (name.Find(".RenderOptions") > 0 && objt == HOT_CONTAINERPROPERTY) {
                        for (int j = 0; (property1 = prop->GetPropertyAt(j)); ++j) {
                            name = property1->GetFullName();
                            objt = property1->GetObjectType();
                            if (name.Find(".ShowShadows") > 0 && objt == HOT_BOOL) {
                                auto *hbp = (HBoolProperty *)property1;
                                ck = hbp->CountKeys();
                                if (ck > 1)
                                    hbp->DeleteKeys(time_range);
                                hbp->StoreValue(Time(),FALSE,TRUE); //Shadow off
                            }
                        }
                    }
                }
                break;
            case HOT_LIGHT:
                hlight = (HLight *)obj;
                hbc = hlight->GetSpecular();
                ck = hbc->CountKeys();
                if (ck > 1)
                    hbc->DeleteKeys(time_range);
                hbc->StoreValue(Time(),FALSE,TRUE); //Specularity off
                hbcp = hlight->GetCastShadows();
                ck = hbcp->CountKeys();
                if (ck > 1)
                    hbcp->DeleteKeys(time_range);
                hbcp->StoreValue(Time(),FALSE,TRUE); //Shadow off
                break;
            case HOT_MODEL:
                obj1 = obj->GetChild();
                if (obj1) {
                    if (obj1->GetObjectType() == HOT_LIGHT) {
                        hlight = (HLight *)obj1;
                        hbc = hlight->GetSpecular();
                        ck = hbc->CountKeys();
                        if (ck > 1)
                            hbc->DeleteKeys(time_range);
                        hbc->StoreValue(Time(),FALSE,TRUE); //Specularity off
                        hbcp = hlight->GetCastShadows();
                        ck = hbcp->CountKeys();
                        if (ck > 1)
                            hbcp->DeleteKeys(time_range);
                        hbcp->StoreValue(Time(),FALSE,TRUE); //Shadow off
                    }
                    FindLightDiffuse(obj1, hchor);
                }
                break;
            default:
                break;
        }
    }
    return TRUE;
}
