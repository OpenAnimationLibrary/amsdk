#include "RenderPasses.h"

struct COLORSETTING
{
	// DiffuseColor
	ColorBuf diffuse;
	// diffuse Color aendern;
	bool changediffusecolor;
	// AmbienceColor V11
	ColorBuf ambience;
	// Ambience Color aendern;
	bool changeambiencecolor;
	// Ambience Intensity
	float ambienceintensity;
	// Ambience Intensity aendern;
	bool changeambienceintensity;
	// SpecularColor
	ColorBuf specular;
	// specular Color aendern;
	bool changespecularcolor;
	// Specular Intensity
	float specularintensity;
	// specular Intensity aendern;
	bool changespecularintensity;
	// Specular Size
	float specularsize;
	// Specular Size aendern;
	bool changespecularsize;
	// Reflection Intensity
	float reflectionintensity;
	// Reflection Intensity aendern;
	bool changereflectionintensity;
};

struct DECAL
{
	//Decal selbst
	HDecalClip *hdecalclip;
	//Listbox ID
	int id;
	//ausgewaehlt zum aendern
	bool tochange;
	//type des Decal
	int decaltype;
	//auf Prozent zu setzen
	float percentage;
	//Prozentproperty des Decals
    HFloatProperty *percent;
};

struct MATERIAL
{
	//Material selbst
	HMaterial *hmaterial;
	//Listbox ID
	int id;
	//Propertienode
	HAttrProperty *attrproperty;
	//Material oder clip ?
	bool isclip;
	//Prozentproperty des Decals
    HFloatProperty *percent;
	//auf Prozent zu setzen
	float percentage;
	//aenderung prozent setzen
	bool changepercentage;
	//Colorsettings
	COLORSETTING cset;
};

struct GRUPPE
{
	//Gruppe selbst
	HGroup *hgroup;
	//Listbox ID
	int id;
	//Propertienode
	HAttrProperty *attrproperty;
	//anzahl Material
	int azmat;
	//struct Material
	MATERIAL *material;
	//Colorsettings
	COLORSETTING cset;
};

struct MODEL
{
	//Model selbst
	HModel *hmodel;
	//Listbox ID
	int id;
	//Propertienode
	HAttrProperty *attrproperty;
	//anzahl Gruppen
	int azgroup;
	//struct Gruppe
	GRUPPE *gruppe;
	//anzahl Decal
	int azdecal;
	//struct Decal
	DECAL *decal;
	//anzahl Material
	int azmat;
	//struct Material
	MATERIAL *material;
	//Colorsettings
	COLORSETTING cset;
};

struct PARAMETER
{
    //anzahl Modelle
	int azmodel;
	//struct Modell
	MODEL *model;
	//welcher Pass zu setzen 0 Diffuse,1 Specular, 2 Shadow, 3 Dof, 4 user shading
	int pass;
};

