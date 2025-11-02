// KB  6/4/01  \Ken90\Plugin\HXT\Duplicator\Evaluate.cpp

#include "StdAfx.h"
#include "Hxt.h"

BOOL CHxtApp::SpinShape(HModelCache *hmc, HGroup *gh) const {
    {
        AFX_MANAGE_STATE(AfxGetAppModuleState())
        hmc->SaveAllToUndo(); // only do this if the routines you are calling do not support step by step undo, stores entire copy of model in undo stack.
    }
    //    RotateEuler rotate;
    HGroupCP *currentgroupcp, *newgroup = nullptr, *lastgroup, *group, *accumgroup = nullptr;
    Vector groupcenter;
    Matrix34 prevmatrix;
    BOOL first = TRUE, second = FALSE;

    // The sweep rotation is taken from the group's pivot location
    const Matrix34 *groupmatrix = gh->GetMatrix();
    const Matrix34 groupinversematrix = groupmatrix->Inverse();

    prevmatrix.SetIdentity();
    int groupcount = 0;
    groupcenter.Set(0.F);
    // find the group's center location
    for (currentgroupcp = gh->GetGroupCP(); currentgroupcp; currentgroupcp = currentgroupcp->GetNext()) {
        groupcenter += *currentgroupcp->GetCP()->GetPosition();
        groupcount++;
    }
    groupcenter /= (float)groupcount; // get the average of all points in the group
    Vector delta = groupcenter - groupmatrix->GetTranslate(); // find offset translate value for making screw shape
    const float distfromcenter = delta.Norm();
    delta = delta.Normalize() * m_parameters.m_offsetdisttocenter;
    groupcenter += m_parameters.m_tumblepivotoffset; // add the tumble offset
    float i = 1.F;
    for (int ii = 0; ii < m_parameters.m_repeat; ++ii) {
        // test distance from center for screw shapes
        if (m_parameters.m_offsetdisttocenter) {
            if (m_parameters.m_offsetdisttocenter > 0.F) {
                if (distfromcenter - i * delta.Norm() < m_parameters.m_stopatdist)
                    // offset spiral towards center reached limit
                    continue;
            } else if (distfromcenter - i * delta.Norm() < m_parameters.m_stopatdist)
                // offset spiral away from center reached limit
                continue;
        }
        // factor the translate, tumblescale, and rotation of the matrix by the iteration value
        Vector accumtumblescale;
        accumtumblescale.x = hash_math::pow(m_parameters.m_tumblescale.x / 100.F, i);
        accumtumblescale.y = hash_math::pow(m_parameters.m_tumblescale.y / 100.F, i);
        accumtumblescale.z = hash_math::pow(m_parameters.m_tumblescale.z / 100.F, i);
        Matrix34 currentmatrix = *groupmatrix * TranslateV(m_parameters.m_translate * i) * // sweep translate
        Matrix34(m_parameters.m_sweeprotate * i) * // sweep rotate
        TranslateV(i * delta) * // move toward center for screw shape
        groupinversematrix * TranslateV(groupcenter) * Matrix34(m_parameters.m_tumblerotate * i) * ScaleV(accumtumblescale) * // tumble scale
        TranslateV(-groupcenter); // tumble translate
        const Matrix34 matrix = currentmatrix * prevmatrix.Inverse();
        prevmatrix = currentmatrix;
        // copy or extrude the selected group
        if (first)
            lastgroup = gh->GetGroupCP(); // extrude or copy from original group
        else
            lastgroup = newgroup; // extrude or copy from the last created group
        newgroup = nullptr;
        hmc->CopyExtrude(m_parameters.m_isextrude, lastgroup, &newgroup);
        if (!first) {
            // add to group after used by CopyExtrude() so group flags don't interfere
            if (second && m_parameters.m_isextrude) {
                second = FALSE;
                for (group = lastgroup; group; group = group->GetNext())
                    group->GetCP()->AddToGroup(&accumgroup); // add all attached cps to group
            } else
                for (group = lastgroup; group; group = group->GetNext())
                    group->GetCP()->AddStackToGroup(&accumgroup); // add all attached cps to group
            lastgroup->Delete();
        } else {
            first = FALSE;
            second = TRUE;
        }

        // apply matrix to group
        currentgroupcp = newgroup;
        while (currentgroupcp) {
            HCP *cp = currentgroupcp->GetCP();
            Vector pos = *cp->GetPosition();
            // creates new matrix and multiplies by pos
            pos *= matrix;
            cp->SetPosition(&pos);
            currentgroupcp = currentgroupcp->GetNext();
        }
        i++;
    }
    if (newgroup) {
        // add the last group
        for (group = newgroup; group; group = group->GetNext()) {
            group->GetCP()->AddStackToGroup(&accumgroup); // add all attached cps to group
        }
        newgroup->Delete();
    }
    hmc->AddToTemporaryGroup(accumgroup);

    return TRUE;
}
