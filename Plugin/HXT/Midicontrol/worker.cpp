#include "StdAfx.h"
#include "Midicontrol.h"

HStringProperty *CheckEmbed(HCategoryProperty *hcatp, const String &matchname) {
    HProperty *prop;
    for (int i = 0; (prop = hcatp->GetPropertyAt(i)); ++i) {
        if (!prop)
            break;
        HPropertyInfo *hpi = prop->GetPropertyInfo();
        if (hpi->GetLocalizedName() == "MC" && hpi->GetMatchName() == matchname)
            return (HStringProperty *)prop;
    }
    return nullptr;
}

void CMidicontrolApp::LoadEmbed() const {
    String temp3[6];
    char *stopstring;

    for (int i = 0; i < para->azobject; ++i) {
        const HStringProperty *hsp = nullptr;
        //		hcatmodel = para->obj[i].hobj->GetUserProperties();
        HUserCategoryProperty *hcatmodel = para->obj[i].hobj->GetUserCategoryProperty();
        HAnimObject *hao = para->obj[i].hobj;
        HAnimObject *haoc = hao->GetCache();
        //		hcatcache = ((HHashObject *)haoc)->GetUserProperties();
        HUserCategoryProperty *hcatcache = ((HHashObject *)haoc)->GetUserCategoryProperty();
        for (int j = 0; j < para->obj[i].azprop; ++j) {
            if (hcatmodel) {
                // ChorModel hat Userproperties
                hsp = CheckEmbed(hcatmodel, para->obj[i].prop[j].name);
            } else {
                // Check ob Modelcache Userproperties hat 
                if (hcatcache) {
                    // Modelcache hat Userproperties
                    hsp = CheckEmbed(hcatcache, para->obj[i].prop[j].name);
                }
            }
            if (hsp) {
                // Eintrag gefunden
                CString temp = para->obj[i].prop[j].name;
/*
                HStringPropertyInfo *hspi = (HStringPropertyInfo *)hsp->GetPropertyInfo(); //ueberhaupt noetig ??
                if (hspi)
                    [[maybe_unused]] String defaultvalue = hspi->GetDefaultValue();
*/
                String value = hsp->GetValue();
                if (value.GetLength() > 1) {
                    for (int k = 0; k < 5; ++k) {
                        temp3[k] = value.StrTok(" ");
                    }
                    if (para->obj[i].prop[j].objt == HOT_COLOR) {
                        temp.Format("%s", temp3[0].Get());
                        para->obj[i].prop[j].min_value_color = strtoul(temp, &stopstring, 10);
                        temp.Format("%s", temp3[1].Get());
                        para->obj[i].prop[j].max_value_color = strtoul(temp, &stopstring, 10);
                    } else {
                        temp.Format("%s", temp3[0].Get());
                        para->obj[i].prop[j].min_value = strtod(temp, &stopstring);
                        temp.Format("%s", temp3[1].Get());
                        para->obj[i].prop[j].max_value = strtod(temp, &stopstring);
                    }
                    temp.Format("%s", temp3[2].Get());
                    para->obj[i].prop[j].driven_value[0] = atoi_replace(temp);
                    temp.Format("%s", temp3[3].Get());
                    para->obj[i].prop[j].driven_value[1] = atoi_replace(temp);
                    temp.Format("%s", temp3[4].Get());
                    para->obj[i].prop[j].driven_value[2] = atoi_replace(temp);
                    para->obj[i].prop[j].driven = 1;
                }
            }
        }
    }
}

void CMidicontrolApp::SaveEmbed() const {
    int j;
    HStringPropertyInfo *hspimodel;
    HStringProperty *hspcache, *hspmodel;
    CString temp;

    for (int i = 0; i < para->azobject; ++i) {
        if (para->obj[i].azprop > 0) {
            bool assigned = false;
            for (j = 0; j < para->obj[i].azprop; ++j) {
                if (para->obj[i].prop[j].driven) {
                    assigned = true;
                    break;
                }
            }
            if (assigned) {
                HAnimObject *hao = para->obj[i].hobj;
                HAnimObject *haoc = hao->GetCache();
                for (j = 0; j < para->obj[i].azprop; ++j) {
                    if (para->obj[i].prop[j].driven) {
                        // Eintrag erzeugen
                        if (para->obj[i].prop[j].objt == HOT_COLOR) {
                            //						    _ultoa(para->obj[i].prop[j].min_value_color, buf1, 10 ); 
                            //						    _ultoa(para->obj[i].prop[j].max_value_color, buf2, 10 ); 
                            //						   temp.Format("%s %s %d %d %d",
                            //							   buf1,
                            //							   buf2,
                            //						       para->obj[i].prop[j].driven_value[0],
                            //						       para->obj[i].prop[j].driven_value[1],
                            //						       para->obj[i].prop[j].driven_value[2]);
                            temp.Format("%d %d %d %d %d", para->obj[i].prop[j].min_value_color, para->obj[i].prop[j].max_value_color, para->obj[i].prop[j].driven_value[0], para->obj[i].prop[j].driven_value[1], para->obj[i].prop[j].driven_value[2]);
                        } else {
                            temp.Format("%.3f %.3f %d %d %d", para->obj[i].prop[j].min_value, para->obj[i].prop[j].max_value, para->obj[i].prop[j].driven_value[0], para->obj[i].prop[j].driven_value[1], para->obj[i].prop[j].driven_value[2]);
                        }

                        // Userproperties ModelCache
                        HUserCategoryProperty *hcatcache = ((HHashObject *)haoc)->GetUserCategoryProperty();
                        //						hcatcache = ((HHashObject *)haoc)->GetUserProperties();
                        if (hcatcache) {
                            //Userproperties vorhanden
                            hspcache = CheckEmbed(hcatcache, para->obj[i].prop[j].name);
                        } else {
                            //Userproperties kreieren
                            hcatcache = ((HHashObject *)haoc)->CreateUserCategoryProperty();
                            hspcache = nullptr;
                        }
                        if (hspcache == nullptr) {
                            hspcache = HStringProperty::New();
                            hcatcache->AddUserProperty(hspcache, "MC", TRUE);
                            auto *hspicache = (HStringPropertyInfo *)hspcache->GetPropertyInfo();
                            if (hspicache) {
                                hspicache->SetReadOnly(TRUE);
                                hspicache->SetAdvanced(TRUE);
                                hspicache->SetConstant(TRUE);
                                hspicache->SetLocalizedName("MC");
                                hspicache->SetMatchName(para->obj[i].prop[j].name.GetBuffer());
                                hspicache->SetDefaultValue(temp);
                                hspcache->StoreValue(temp,TRUE);
                            }
                            /* old v11 alpha
                                                        hspicache = HStringPropertyInfo::New("MC",para->obj[i].prop[j].name); 
                                                        hspcache = HStringProperty::New(hspicache);
                                                        k = hcatcache->AddProperty(hspcache);
                                                        hspicache->SetReadOnly(TRUE);
                                                        hspicache->SetAdvanced(TRUE);
                                                        hspicache->SetConstant(TRUE);
                                                        hspicache->SetDefaultValue(temp);
                                                        hspcache->StoreValue(temp,TRUE);
                                                        */
                        }
                        // Userproperties ChorModel
                        //						hcatmodel = para->obj[i].hobj->GetUserProperties();
                        HUserCategoryProperty *hcatmodel = para->obj[i].hobj->GetUserCategoryProperty();
                        if (hcatmodel) {
                            //Userproperties vorhanden
                            hspmodel = CheckEmbed(hcatmodel, para->obj[i].prop[j].name);
                        } else {
                            //Userproperties kreieren
                            hcatmodel = para->obj[i].hobj->CreateUserCategoryProperty();
                            hspmodel = nullptr;
                        }
                        if (hspmodel) {
                            hspmodel->StoreValue(temp,TRUE);
                            hspimodel = (HStringPropertyInfo *)hspmodel->GetPropertyInfo();
                            hspimodel->SetReadOnly(TRUE);
                            hspimodel->SetAdvanced(TRUE);
                            hspimodel->SetConstant(TRUE);
                        } else {
                            hspmodel = HStringProperty::New();
                            hcatmodel->AddUserProperty(hspmodel, "MC", TRUE);
                            hspimodel = (HStringPropertyInfo *)hspmodel->GetPropertyInfo();
                            if (hspimodel) {
                                hspimodel->SetReadOnly(TRUE);
                                hspimodel->SetAdvanced(TRUE);
                                hspimodel->SetConstant(TRUE);
                                hspimodel->SetMatchName(para->obj[i].prop[j].name.GetBuffer());
                                hspimodel->SetLocalizedName("MC");
                                hspimodel->SetDefaultValue(temp);
                                hspmodel->StoreValue(temp,TRUE);
                            }
                            /* old V11 alpha
                                                        hspimodel = HStringPropertyInfo::New("MC",para->obj[i].prop[j].name); 
                                                        hspmodel = HStringProperty::New(hspimodel);
                                                        k = hcatmodel->AddProperty(hspmodel);
                                                        hspimodel->SetReadOnly(TRUE);
                                                        hspimodel->SetAdvanced(TRUE);
                                                        hspimodel->SetConstant(TRUE);
                                                        hspimodel->SetDefaultValue(temp);
                                                        hspmodel->StoreValue(temp,TRUE);
                                                        */
                        }
                    }
                }
            }
        }
    }
}

BOOL CMidicontrolApp::GetAzPropRecurse(HProperty *akt_prop, int &azprop) {
    HProperty *prop;

    for (int i = 0; (prop = akt_prop->GetPropertyAt(i)); ++i) {
        if (!prop)
            return TRUE;
        if (!GetAzPropRecurse(prop, azprop)) {
            const ObjectType objt = prop->GetObjectType();
            if (objt == HOT_FLOAT || objt == HOT_PERCENT || objt == HOT_EULERFLOAT || objt == HOT_COLOR) {
                String temp = prop->GetFullName();
                if (temp.Find("FallOff") == -1 && temp.Find("NormalWeight") == -1 && temp.Find(".BlendMethod.") == -1 && temp.Find("Pivot.") == -1 && temp.Find("NoLabel.") == -1 && temp.Find("BonePos.") == -1 && temp.Find("Options.") == -1 && temp.Find("|Relationships|") == -1) {
                    azprop++;
                }
            }
        }
    }
    return FALSE;
}

BOOL CMidicontrolApp::GetAzObjRecurse(HHashObject *obj, int &azprop) {
    HProperty *prop;

    for (HHashObject *hobj = obj->GetChild(); hobj; hobj = hobj->GetSibling()) {
        if (!GetAzObjRecurse(hobj, azprop)) {
            for (int i = 0; (prop = hobj->GetPropertyAt(i)); ++i) {
                if (prop) {
                    if (!GetAzPropRecurse(prop, azprop)) {
                        const ObjectType objt = prop->GetObjectType();
                        if (objt == HOT_FLOAT || objt == HOT_PERCENT || objt == HOT_EULERFLOAT || objt == HOT_COLOR) {
                            String temp = prop->GetFullName();
                            if (temp.Find("FallOff") == -1 && temp.Find("NormalWeight") == -1 && temp.Find(".BlendMethod.") == -1 && temp.Find("Pivot.") == -1 && temp.Find("NoLabel.") == -1 && temp.Find("BonePos.") == -1 && temp.Find("Options.") == -1 && temp.Find("|Relationships|") == -1) {
                                azprop++;
                            }
                        }
                    }
                }
            }
        }
    }
    return FALSE;
}

int CMidicontrolApp::GetAzProp(HHashObject *obj) {
    int azprop = 0;
    HProperty *prop;

    //properties
    for (int i = 0; (prop = obj->GetPropertyAt(i)); ++i) {
        if (prop) {
            if (!GetAzPropRecurse(prop, azprop)) {
                const ObjectType objt = prop->GetObjectType();
                if (objt == HOT_FLOAT || objt == HOT_PERCENT || objt == HOT_EULERFLOAT || objt == HOT_COLOR) {
                    String temp = prop->GetFullName();
                    if (temp.Find("FallOff") == -1 && temp.Find("NormalWeight") == -1 && temp.Find(".BlendMethod.") == -1 && temp.Find("Pivot.") == -1 && temp.Find("NoLabel.") == -1 && temp.Find("BonePos.") == -1 && temp.Find("Options.") == -1 &&
                        temp.Find("|Relationships|") == -1) {
                        azprop++;
                    }
                }
            }
        }
    }
    //underlaying properties (material,group)
    GetAzObjRecurse(obj, azprop);
    return azprop;
}

BOOL CMidicontrolApp::GetPropertiesRecurse(HProperty *akt_prop, const int nummer, int &azprop) const {
    HProperty *prop;
    String temp1;

    for (int i = 0; (prop = akt_prop->GetPropertyAt(i)); ++i) {
        if (!prop)
            return TRUE;
        if (!GetPropertiesRecurse(prop, nummer, azprop)) {
            ObjectType objt = prop->GetObjectType();
            if (objt == HOT_FLOAT || objt == HOT_PERCENT || objt == HOT_EULERFLOAT || objt == HOT_COLOR) {
                String temp = prop->GetFullName();
                if (temp.Find("FallOff") == -1 && temp.Find("NormalWeight") == -1 && temp.Find(".BlendMethod.") == -1 && temp.Find("Pivot.") == -1 && temp.Find("NoLabel.") == -1 && temp.Find("BonePos.") == -1 && temp.Find("Options.") == -1 && temp.Find("|Relationships|") == -1) {
                    para->obj[nummer].prop[azprop].prop = prop;
                    para->obj[nummer].prop[azprop].objt = objt;
                    para->obj[nummer].prop[azprop].matchtype = 0;
                    para->obj[nummer].prop[azprop].Fullname = temp;
                    para->obj[nummer].prop[azprop].driven = 0;
                    para->obj[nummer].prop[azprop].driven_value[0] = 0;
                    para->obj[nummer].prop[azprop].driven_value[1] = 0;
                    para->obj[nummer].prop[azprop].driven_value[2] = 0;
                    para->obj[nummer].prop[azprop].min_value = 0;
                    para->obj[nummer].prop[azprop].max_value = 100;
                    para->obj[nummer].prop[azprop].min_value_color = RGB(0, 0, 0);
                    para->obj[nummer].prop[azprop].max_value_color = RGB(255, 255, 255);
                    switch (objt) {
                        case HOT_COLOR:
                            para->obj[nummer].prop[azprop].min_value_color = para->obj[nummer].prop[azprop].org_value_color = ((HColorProperty *)prop)->GetCOLORREF();
                            para->obj[nummer].prop[azprop].org_value = 0;
                            break;
                        case HOT_PERCENT:
                            para->obj[nummer].prop[azprop].org_value_color = RGB(0, 0, 0);
                            para->obj[nummer].prop[azprop].org_value = ((HFloatProperty *)prop)->GetValue(Time()) * 100;
                            break;
                        default:
                            para->obj[nummer].prop[azprop].org_value_color = RGB(0, 0, 0);
                            para->obj[nummer].prop[azprop].org_value = ((HFloatProperty *)prop)->GetValue(Time());
                            break;
                    }
                    const int index = temp.Find(para->obj[nummer].matchname);
                    if (index != -1) {
                        int index1 = temp.Find(index, '|');
                        if (index1 == -1)
                            index1 = temp.Find(index, '.');
                        index1++;
                        temp1 = temp.Right(temp.GetLength() - index1);
                    } else {
                        temp1 = temp;
                    }
                    if (temp1.Find("Transform") != -1)
                        para->obj[nummer].prop[azprop].matchtype = 1;
                    if (temp1.Find("Surface") != -1)
                        para->obj[nummer].prop[azprop].matchtype = 3;
                    if (temp1.Find("Color") != -1)
                        para->obj[nummer].prop[azprop].matchtype = 2;
                    if (temp1.Find("User Properties") != -1) {
                        para->obj[nummer].prop[azprop].matchtype = 4;
                        para->obj[nummer].prop[azprop].ispose = 1;
                        objt = para->obj[nummer].prop[azprop].prop->GetObjectType();
                        switch (objt) {
                            case HOT_FLOAT:
                                para->obj[nummer].prop[azprop].min_value = ((HFloatPropertyInfo *)para->obj[nummer].prop[azprop].prop->GetPropertyInfo())->GetMinValue() * ((HFloatPropertyInfo *)para->obj[nummer].prop[azprop].prop->GetPropertyInfo())->
                                                                           GetFactorValue();
                                para->obj[nummer].prop[azprop].max_value = ((HFloatPropertyInfo *)para->obj[nummer].prop[azprop].prop->GetPropertyInfo())->GetMaxValue() * ((HFloatPropertyInfo *)para->obj[nummer].prop[azprop].prop->GetPropertyInfo())->
                                                                           GetFactorValue();
                                break;
                            case HOT_PERCENT:
                                para->obj[nummer].prop[azprop].min_value = ((HPercentPropertyInfo *)para->obj[nummer].prop[azprop].prop->GetPropertyInfo())->GetMinValue() * ((HPercentPropertyInfo *)para->obj[nummer].prop[azprop].prop->GetPropertyInfo())->
                                                                           GetFactorValue();
                                para->obj[nummer].prop[azprop].max_value = ((HPercentPropertyInfo *)para->obj[nummer].prop[azprop].prop->GetPropertyInfo())->GetMaxValue() * ((HPercentPropertyInfo *)para->obj[nummer].prop[azprop].prop->GetPropertyInfo())->
                                                                           GetFactorValue();
                                break;
                            default:
                                break;
                        }
                    } else {
                        para->obj[nummer].prop[azprop].ispose = 0;
                    }
                    para->obj[nummer].prop[azprop].name.Format("%s", temp1.Get());
                    azprop++;
                }
            }
        }
    }
    return FALSE;
}

BOOL CMidicontrolApp::GetObjRecurse(HHashObject *obj, const int nummer, int &azprop) const {
    HProperty *prop;
    String temp1;

    for (HHashObject *hobj = obj->GetChild(); hobj; hobj = hobj->GetSibling()) {
        if (!GetObjRecurse(hobj, nummer, azprop)) {
            for (int i = 0; (prop = hobj->GetPropertyAt(i)); ++i) {
                if (prop) {
                    if (!GetPropertiesRecurse(prop, nummer, azprop)) {
                        ObjectType objt = prop->GetObjectType();
                        if (objt == HOT_FLOAT || objt == HOT_PERCENT || objt == HOT_EULERFLOAT || objt == HOT_COLOR) {
                            String temp = prop->GetFullName();
                            if (temp.Find("FallOff") == -1 && temp.Find("NormalWeight") == -1 && temp.Find(".BlendMethod.") == -1 && temp.Find("Pivot.") == -1 && temp.Find("NoLabel.") == -1 && temp.Find("BonePos.") == -1 && temp.Find("Options.") == -1 && temp.Find("|Relationships|") == -1) {
                                para->obj[nummer].prop[azprop].prop = prop;
                                para->obj[nummer].prop[azprop].objt = objt;
                                para->obj[nummer].prop[azprop].matchtype = 0;
                                para->obj[nummer].prop[azprop].driven = 0;
                                para->obj[nummer].prop[azprop].driven_value[0] = 0;
                                para->obj[nummer].prop[azprop].driven_value[1] = 0;
                                para->obj[nummer].prop[azprop].driven_value[2] = 0;
                                para->obj[nummer].prop[azprop].min_value = 0;
                                para->obj[nummer].prop[azprop].max_value = 100;
                                para->obj[nummer].prop[azprop].min_value_color = RGB(0, 0, 0);
                                para->obj[nummer].prop[azprop].max_value_color = RGB(255, 255, 255);
                                switch (objt) {
                                    case HOT_COLOR:
                                        para->obj[nummer].prop[azprop].org_value_color = ((HColorProperty *)prop)->GetCOLORREF();
                                        para->obj[nummer].prop[azprop].org_value = 0;
                                        break;
                                    case HOT_PERCENT:
                                        para->obj[nummer].prop[azprop].org_value_color = RGB(0, 0, 0);
                                        para->obj[nummer].prop[azprop].org_value = ((HFloatProperty *)prop)->GetValue(Time()) * 100;
                                        break;
                                    default:
                                        para->obj[nummer].prop[azprop].org_value_color = RGB(0, 0, 0);
                                        para->obj[nummer].prop[azprop].org_value = ((HFloatProperty *)prop)->GetValue(Time());
                                        break;
                                }
                                para->obj[nummer].prop[azprop].Fullname = temp;
                                const int index = temp.Find(para->obj[nummer].matchname);
                                if (index != -1) {
                                    int index1 = temp.Find(index, '|');
                                    if (index1 == -1)
                                        index1 = temp.Find(index, '.');
                                    index1++;
                                    temp1 = temp.Right(temp.GetLength() - index1);
                                } else {
                                    temp1 = temp;
                                }
                                if (temp1.Find("Transform") != -1)
                                    para->obj[nummer].prop[azprop].matchtype = 1;
                                if (temp1.Find("Surface") != -1)
                                    para->obj[nummer].prop[azprop].matchtype = 3;
                                if (temp1.Find("Color") != -1)
                                    para->obj[nummer].prop[azprop].matchtype = 2;
                                if (temp1.Find("User Properties") != -1) {
                                    para->obj[nummer].prop[azprop].matchtype = 4;
                                    para->obj[nummer].prop[azprop].ispose = 1;
                                    objt = para->obj[nummer].prop[azprop].prop->GetObjectType();
                                    switch (objt) {
                                        case HOT_FLOAT:
                                            para->obj[nummer].prop[azprop].min_value = ((HFloatPropertyInfo *)para->obj[nummer].prop[azprop].prop->GetPropertyInfo())->GetMinValue() * ((HFloatPropertyInfo *)para->obj[nummer].prop[azprop].prop->
                                                                                           GetPropertyInfo())->GetFactorValue();
                                            para->obj[nummer].prop[azprop].max_value = ((HFloatPropertyInfo *)para->obj[nummer].prop[azprop].prop->GetPropertyInfo())->GetMaxValue() * ((HFloatPropertyInfo *)para->obj[nummer].prop[azprop].prop->
                                                                                           GetPropertyInfo())->GetFactorValue();
                                            break;
                                        case HOT_PERCENT:
                                            para->obj[nummer].prop[azprop].min_value = ((HPercentPropertyInfo *)para->obj[nummer].prop[azprop].prop->GetPropertyInfo())->GetMinValue() * ((HPercentPropertyInfo *)para->obj[nummer].prop[azprop].prop->
                                                                                           GetPropertyInfo())->GetFactorValue();
                                            para->obj[nummer].prop[azprop].max_value = ((HPercentPropertyInfo *)para->obj[nummer].prop[azprop].prop->GetPropertyInfo())->GetMaxValue() * ((HPercentPropertyInfo *)para->obj[nummer].prop[azprop].prop->
                                                                                           GetPropertyInfo())->GetFactorValue();
                                            break;
                                        default:
                                            break;
                                    }
                                } else {
                                    para->obj[nummer].prop[azprop].ispose = 0;
                                }
                                para->obj[nummer].prop[azprop].name.Format("%s", temp1.Get());
                                azprop++;
                            }
                        }
                    }
                }
            }
        }
    }
    return FALSE;
}

void CMidicontrolApp::GetProperties(const int nummer) const {
    int azprop = 0;
    HProperty *prop;
    String temp1;

    //allgemeine Properties
    for (int i = 0; (prop = para->obj[nummer].hobj->GetPropertyAt(i)); ++i) {
        if (prop) {
            if (!GetPropertiesRecurse(prop, nummer, azprop)) {
                ObjectType objt = prop->GetObjectType();
                if (objt == HOT_FLOAT || objt == HOT_PERCENT || objt == HOT_EULERFLOAT || objt == HOT_COLOR) {
                    String temp = prop->GetFullName();
                    if (temp.Find("FallOff") == -1 && temp.Find("NormalWeight") == -1 && temp.Find(".BlendMethod.") == -1 && temp.Find("Pivot.") == -1 && temp.Find("NoLabel.") == -1 && temp.Find("BonePos.") == -1 && temp.Find("Options.") == -1 &&
                        temp.Find("|Relationships|") == -1) {
                        para->obj[nummer].prop[azprop].prop = prop;
                        para->obj[nummer].prop[azprop].objt = objt;
                        para->obj[nummer].prop[azprop].matchtype = 0;
                        para->obj[nummer].prop[azprop].driven = 0;
                        para->obj[nummer].prop[azprop].driven_value[0] = 0;
                        para->obj[nummer].prop[azprop].driven_value[1] = 0;
                        para->obj[nummer].prop[azprop].driven_value[2] = 0;
                        para->obj[nummer].prop[azprop].min_value = 0;
                        para->obj[nummer].prop[azprop].max_value = 100;
                        para->obj[nummer].prop[azprop].min_value_color = RGB(0, 0, 0);
                        para->obj[nummer].prop[azprop].max_value_color = RGB(255, 255, 255);
                        switch (objt) {
                            case HOT_COLOR:
                                para->obj[nummer].prop[azprop].org_value_color = ((HColorProperty *)prop)->GetCOLORREF();
                                para->obj[nummer].prop[azprop].org_value = 0;
                                break;
                            case HOT_PERCENT:
                                para->obj[nummer].prop[azprop].org_value_color = RGB(0, 0, 0);
                                para->obj[nummer].prop[azprop].org_value = ((HFloatProperty *)prop)->GetValue(Time()) * 100;
                                break;
                            default:
                                para->obj[nummer].prop[azprop].org_value = ((HFloatProperty *)prop)->GetValue(Time());
                                para->obj[nummer].prop[azprop].org_value_color = RGB(0, 0, 0);
                                break;
                        }
                        para->obj[nummer].prop[azprop].Fullname = temp;
                        const int index = temp.Find(para->obj[nummer].matchname);
                        if (index != -1) {
                            int index1 = temp.Find(index, '|');
                            if (index1 == -1)
                                index1 = temp.Find(index, '.');
                            index1++;
                            temp1 = temp.Right(temp.GetLength() - index1);
                        } else {
                            temp1 = temp;
                        }
                        if (temp1.Find("Transform") != -1)
                            para->obj[nummer].prop[azprop].matchtype = 1;
                        if (temp1.Find("Surface") != -1)
                            para->obj[nummer].prop[azprop].matchtype = 3;
                        if (temp1.Find("Color") != -1)
                            para->obj[nummer].prop[azprop].matchtype = 2;
                        if (temp1.Find("User Properties") != -1) {
                            para->obj[nummer].prop[azprop].matchtype = 4;
                            para->obj[nummer].prop[azprop].ispose = 1;
                            objt = para->obj[nummer].prop[azprop].prop->GetObjectType();
                            switch (objt) {
                                case HOT_FLOAT:
                                    para->obj[nummer].prop[azprop].min_value = ((HFloatPropertyInfo *)para->obj[nummer].prop[azprop].prop->GetPropertyInfo())->GetMinValue() * ((HFloatPropertyInfo *)para->obj[nummer].prop[azprop].prop->GetPropertyInfo())->
                                                                               GetFactorValue();
                                    para->obj[nummer].prop[azprop].max_value = ((HFloatPropertyInfo *)para->obj[nummer].prop[azprop].prop->GetPropertyInfo())->GetMaxValue() * ((HFloatPropertyInfo *)para->obj[nummer].prop[azprop].prop->GetPropertyInfo())->
                                                                               GetFactorValue();
                                    break;
                                case HOT_PERCENT:
                                    para->obj[nummer].prop[azprop].min_value = ((HPercentPropertyInfo *)para->obj[nummer].prop[azprop].prop->GetPropertyInfo())->GetMinValue() * ((HPercentPropertyInfo *)para->obj[nummer].prop[azprop].prop->GetPropertyInfo())->
                                                                               GetFactorValue();
                                    para->obj[nummer].prop[azprop].max_value = ((HPercentPropertyInfo *)para->obj[nummer].prop[azprop].prop->GetPropertyInfo())->GetMaxValue() * ((HPercentPropertyInfo *)para->obj[nummer].prop[azprop].prop->GetPropertyInfo())->
                                                                               GetFactorValue();
                                    break;
                                default:
                                    break;
                            }
                        } else {
                            para->obj[nummer].prop[azprop].ispose = 0;
                        }
                        para->obj[nummer].prop[azprop].name.Format("%s", temp1.Get());
                        azprop++;
                    }
                }
            }
        }
    }

    //underlaying properties (material,group)
    GetObjRecurse(para->obj[nummer].hobj, nummer, azprop);
}

BOOL CMidicontrolApp::Chorworking(HChor *hchor) const {
    int azchild = 0;
    HHashObject *obj;

    for (obj = hchor->GetChild(); obj; obj = obj->GetSibling()) {
        azchild++;
    }

    //allocate objects
    para->azobject = azchild;
    para->obj = new OBJECT[azchild];

    azchild = 0;
    for (obj = hchor->GetChild(); obj; obj = obj->GetSibling()) {
        para->obj[azchild].hobj = obj;
        para->obj[azchild].name = obj->GetName();
        para->obj[azchild].matchname = obj->GetMatchName();
        para->obj[azchild].Filter = 0;
        azchild++;
    }

    for (azchild = 0; azchild < para->azobject; azchild++) {
        para->obj[azchild].azprop = GetAzProp(para->obj[azchild].hobj);
        //allocate properties
        para->obj[azchild].prop = new PROPERTIE[para->obj[azchild].azprop];
        GetProperties(azchild);
    }

    return TRUE;
}

void CMidicontrolApp::DeleteKeys() const {
    Time time, time_end;
    TimeRange time_range;
    int i;

    time.SetFrame(0, para->fps);
    time_end.SetFrame(para->end_frame, para->fps);
    time_range.Set(time, time_end);

    for (i = 0; i < para->az_control; ++i) {
        para->p_control[i].prop->DeleteKeys(time_range);
        if (para->p_control[i].First_is) {
            if (para->p_control[i].objt == HOT_COLOR) {
                para->p_control[i].hcp->StoreValue(Time(), para->p_control[i].First_value_c,FALSE);
            } else {
                para->p_control[i].hfp->StoreValue(Time(), para->p_control[i].First_value,FALSE);
            }
        }
    }
    for (i = 0; i < para->az_key; ++i) {
        para->p_key[i].prop->DeleteKeys(time_range);
        if (para->p_key[i].First_is) {
            if (para->p_key[i].objt == HOT_COLOR) {
                para->p_key[i].hcp->StoreValue(Time(), para->p_key[i].First_value_c,FALSE);
            } else {
                para->p_key[i].hfp->StoreValue(Time(), para->p_key[i].First_value,FALSE);
            }
        }
    }
    for (i = 0; i < para->az_note; ++i) {
        para->p_note[i].prop->DeleteKeys(time_range);
        if (para->p_note[i].First_is) {
            if (para->p_note[i].objt == HOT_COLOR) {
                para->p_note[i].hcp->StoreValue(Time(), para->p_note[i].First_value_c,FALSE);
            } else {
                para->p_note[i].hfp->StoreValue(Time(), para->p_note[i].First_value,FALSE);
            }
        }
    }
}
