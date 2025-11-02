//Dan  1/13/2004  \DanLP110\Include\PtrMessa.h
#pragma once

enum PtrMessage {
    PTM_DELETED = 0,
    PTM_RENAMED = 1,
    PTM_VALUECHANGED = 2,
    PTM_VALUESTORED = 3,
    PTM_MARKDEPENDENT = 4,
    PTM_GETPOINTERLIST = 5,
    PTM_NULLCHANGED = 6,
    PTM_SELECTIONCHANGED = 7,
    PTM_FPSCHANGED = 8,
    //fps =*((float*)lparam)
    PTM_WORLDSTORED = 9,
    PTM_ENDLOAD = 10,
    //productversion = *((float *)lparam)
    PTM_FORCEDESCRIPTION = 11,
    PTM_BUTTONPRESSED = 12,
    PTM_DRAW = 13,
    PTM_OFFINTERPOLATE = 14,
    //almost as strong as PTM_VALUESTORED, but may have been caused by frame change, like OffInterpolatePropertiesContainingAction().  We specifically do not want Constraint::OnPtrMessage to force keys in this case.
    PTM_PROJECTCLOSE = 15,
    //send , when Project is closed
};
