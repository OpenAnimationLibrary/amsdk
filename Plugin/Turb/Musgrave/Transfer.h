// Yves 04/11/01  \Plugins\Turb\Musgrave\Transfer.h
#pragma once

class TransfererUI {
public:
    TypeInfoArray m_WaveTypeInfoArray;
    HPropertyInfo *m_OptionsInfo;
    HTypePropertyInfo *m_WaveTypeInfo;
    HIntPropertyInfo *m_CyclesInfo;
    HPercentPropertyInfo *m_TiltInfo;
    HPercentPropertyInfo *m_ShapeInfo;
    HPercentPropertyInfo *m_GainInfo;
    HPercentPropertyInfo *m_BiasInfo;
    HPercentPropertyInfo *m_HiCutoffInfo;
    HPercentPropertyInfo *m_LoCutoffInfo;
    HBoolPropertyInfo *m_SmoothInfo;

    TransfererUI() noexcept = default;
    ~TransfererUI();

    TransfererUI(const TransfererUI &) = delete;
    TransfererUI &operator=(const TransfererUI &) = delete;
    TransfererUI(TransfererUI &&) = delete;
    TransfererUI &operator=(TransfererUI &&) = delete;

    void InitProperties();
};

class Transferer {
public:
    HCategoryProperty *m_Options{nullptr};
    HTypeProperty *m_WaveType{nullptr};
    HIntProperty *m_Cycles{nullptr};
    HPercentProperty *m_Tilt{nullptr};
    HPercentProperty *m_Shape{nullptr};
    HPercentProperty *m_Gain{nullptr};
    HPercentProperty *m_Bias{nullptr};
    HPercentProperty *m_HiCutoff{nullptr};
    HPercentProperty *m_LoCutoff{nullptr};
    HBoolProperty *m_Smooth{nullptr};

    Transferer() noexcept = default;
    ~Transferer();

    Transferer(const Transferer &) = delete;
    Transferer &operator=(const Transferer &) = delete;
    Transferer(Transferer &&) = delete;
    Transferer &operator=(Transferer &&) = delete;

    void LinkProperties(const TransfererUI &UI);
    HProperty *GetPropertyAt(int &i);
    bool ParseArg(const char *label, const char *value);
    [[nodiscard]] float Transfer(float Value) const;
    [[nodiscard]] float TriangularWave(float Value) const;
    [[nodiscard]] float RectangularWave(float Value) const;
    [[nodiscard]] float SinusoidalWave(float Value) const;
};
