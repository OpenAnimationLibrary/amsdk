#include "StdAfx.h"
#include "GrowSelection.h"

BOOL CGrowSelectionApp::Work(HGroup *hg, HModelCache *hmc) const {

    HPatch5 *hp5;
    int azpatch;
    int i;
    CArrayEx<int, int> patch_start;
    HGroupCP *accumgroup = nullptr;
    BOOL changed = false;

    int azep = azpatch = hmc->GetPatchCount();
    for (hp5 = hmc->GetHeadPatch5(); hp5; hp5 = hp5->GetNextPatch5()) {
        azep++;
    }
    auto *ep = new EPatch[azep + 1];
    for (i = 0; i < azpatch; ++i) {
        ep[i].Init(hmc->GetPatch(i), screen);
    }
    for (hp5 = hmc->GetHeadPatch5(); hp5; hp5 = hp5->GetNextPatch5()) {
        ep[i].Init(hp5, screen);
        i++;
    }
    azep = i;

    for (i = 0; i < azep; ++i) {
        if (ep[i].numpoint == 5) {
            if (hg->IsPatchInGroup(ep[i].opatch5))
                patch_start.Add(i);
        } else {
            if (hg->IsPatchInGroup(ep[i].opatch))
                patch_start.Add(i);
        }
    }

    if (patch_start.GetSize() == 0) {
        delete [] ep;
        return false;
    }

    CWnd *cwnd = CWnd::FromHandle(GetMainApplicationWnd());
    cwnd->UpdateWindow();
    GetHProject()->DeselectAll(); //Crash , when the window is not updatet before

    for (i = 0; i < patch_start.GetSize(); ++i) {
        for (int j = 0; j < azep; ++j) {
            if (ep[j].IsNeighbor(&ep[patch_start[i]], true)) {
                changed = true;
                switch (ep[j].numpoint) {
                    case 3:
                        ep[j].opatch->GetCP1()->AddStackToGroup(&accumgroup);
                        ep[j].opatch->GetCP2()->AddStackToGroup(&accumgroup);
                        ep[j].opatch->GetCP3()->AddStackToGroup(&accumgroup);
                        break;
                    case 4:
                        ep[j].opatch->GetCP1()->AddStackToGroup(&accumgroup);
                        ep[j].opatch->GetCP2()->AddStackToGroup(&accumgroup);
                        ep[j].opatch->GetCP3()->AddStackToGroup(&accumgroup);
                        ep[j].opatch->GetCP4()->AddStackToGroup(&accumgroup);
                        break;
                    case 5:
                        ep[j].opatch5->GetCP1()->AddStackToGroup(&accumgroup);
                        ep[j].opatch5->GetCP2()->AddStackToGroup(&accumgroup);
                        ep[j].opatch5->GetCP3()->AddStackToGroup(&accumgroup);
                        ep[j].opatch5->GetCP4()->AddStackToGroup(&accumgroup);
                        ep[j].opatch5->GetCP5()->AddStackToGroup(&accumgroup);
                        break;
                }
            }
        }
    }

    patch_start.RemoveAll();
    delete [] ep;
    if (changed) {
        hmc->AddToTemporaryGroup(accumgroup);
        GetHProject()->UpdateAllViews(TRUE);
        RefreshAllTrees();
        return true;
    }
    GetHProject()->UpdateAllViews(TRUE);
    RefreshAllTrees();
    return true;
}
