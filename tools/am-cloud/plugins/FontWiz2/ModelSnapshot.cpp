#include "FontWiz2.h"
#include "Inspector.h"
#include "SDK/HModel.h"
#include "SDK/HCP.h"
#include "SDK/HPatch.h"
#include "SDK/HPropert.h"
#include "HashFile.h"
#include <iomanip>
#include <locale>
#include <sstream>
#include <stdexcept>

namespace fw2 {
namespace {
void color(std::ostream &out, HAttrProperty *attributes) {
    if (!attributes) { out << "attributes=absent"; return; }
    auto *diffuse = attributes->GetDiffuseColor();
    if (!diffuse) { out << "diffuse=absent"; return; }
    out << "attr_null=" << attributes->IsNull() << " diffuse_null=" << diffuse->IsNull();
    if (!diffuse->IsNull()) {
        // Read only the stored group/model vector. Patch surface handles and
        // driver/default/normalized-value queries are deliberately excluded.
        const Vector raw = static_cast<const HVectorProperty *>(diffuse)->GetValue();
        out << " stored_rgb=" << raw.x << ',' << raw.y << ',' << raw.z;
    }
}
unsigned id(HCP *cp) { return cp ? cp->GetID() : 0; }
}
std::wstring ModelSnapshot(HModelCache *model, bool serialize) {
    if (serialize) {
        MemoryStream stream(FileMode::HS_ASCII | FileMode::HS_DONTPROGRESS);
        stream.m_productversion = 19.5F;
        if (!model->ExportModel(stream) || stream.IsFailed())
            throw std::runtime_error("A:M could not serialize the model into memory.");
        if (stream.GetLength() > 16 * 1024 * 1024)
            throw std::runtime_error("The serialized model exceeds 16 MiB.");
        return DiagnosticText(std::string(stream.m_buf ? stream.m_buf : "", stream.GetLength()));
    }
    // Getter-only report precedes the optional SDK serializer. No Save, Update,
    // FindPatches, MakeCurrent, interpolation, property writes or redraw here.
    std::ostringstream out; out.imbue(std::locale::classic()); out << std::setprecision(9);
    out << "FontWiz2 live model snapshot v2\r\nA:M " << GetAMVersion().Get_const_char()
        << "\r\nModel: " << model->GetName() << "\r\nModified: " << model->IsModified()
        << "\r\nModel surface: "; color(out, model->GetAttr()); out << "\r\n";
    if (auto *container = model->GetChildGroupContainer()) {
        unsigned groups = 0;
        for (auto *group = container->GetChildGroup(); group; group = static_cast<HGroup *>(group->GetSiblingSame())) {
            if (++groups > 10000) throw std::runtime_error("Too many groups for a diagnostic snapshot.");
            out << "\r\nGroup: " << group->GetName() << " temp=" << group->IsTempGroup() << "\r\nSurface: ";
            color(out, group->GetAttr()); out << "\r\nCP IDs:";
            unsigned points = 0;
            for (auto *item = group->GetGroupCP(); item; item = item->GetNext()) {
                if (++points > 200000) throw std::runtime_error("Too many group points for a diagnostic snapshot.");
                out << ' ' << id(item->GetCP());
            }
            out << "\r\nCP count=" << points << "\r\n";
        }
    }
    const int patches = model->GetPatchCount();
    if (patches < 0 || patches > 200000) throw std::runtime_error("Too many patches for a diagnostic snapshot.");
    out << "\r\nPatch count=" << patches << "\r\n";
    for (int i = 0; i < patches; ++i) {
        auto *patch = model->GetPatch(i);
        if (!patch) { out << "Patch " << i << " absent\r\n"; continue; }
        out << "Patch " << i << " CPs=" << id(patch->GetCP1()) << ',' << id(patch->GetCP2())
            << ',' << id(patch->GetCP3()) << ',' << id(patch->GetCP4()) << "\r\n";
        if (out.tellp() > 16 * 1024 * 1024) throw std::runtime_error("The live report exceeds 16 MiB.");
    }
    out << "\r\nPatch surface values omitted: these SDK reads are suspected in the colored-model inspector crash.\r\n";
    out << "\r\nThe getter report is not a .mdl file. Capture model code separately to invoke\r\n"
        "the SDK serializer in memory. Serialization may normalize data; no claim\r\n"
        "is made that it reproduces every pre-save cache. No model file is written.\r\n";
    return DiagnosticText(out.str());
}
}
