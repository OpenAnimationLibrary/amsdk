#pragma once

// token kinds
enum AITokenKind {
    AIKComment,
    AIKReal,
    AIKInteger,
    AIKUnsigned,
    AIKString,
    AIKName
};

// object kinds
enum AIObjectKind {
    AIOCompoundPath,
    AIOPath,
    AIOPathOp
};

// pathop kinds
enum AIPathOpKind {
    AIPMoveto,
    AIPLineto,
    AIPCurveto
};

class AIToken {
    friend class AITokenList;
private:
    // prev, next used when token is part of a list
    AIToken *prev;
    AIToken *next;
public:
    AITokenKind kind;

    explicit AIToken(const AITokenKind k) : prev{nullptr}, next{nullptr}, kind(k) { }
    virtual ~AIToken() = default;

    virtual BOOL MatchesComment(LPCTSTR prefix) {
        return FALSE;
    }

    virtual BOOL IsNonlitName() {
        return FALSE;
    }

    virtual BOOL MatchesName(LPCTSTR name) {
        return FALSE;
    }

    virtual BOOL IsNumber() {
        return FALSE;
    }

    virtual double NumberVal() {
        return 0.0;
    }
};

class AITokenList {
    AIToken *head;
    AIToken *tail;
public:
    AITokenList() : head(nullptr), tail(nullptr) { }
    ~AITokenList();

    [[nodiscard]] AIToken *Head() const {
        return head;
    }

    [[nodiscard]] AIToken *Tail() const {
        return tail;
    }

    static AIToken *Next(const AIToken *tok) {
        return tok ? tok->next : nullptr;
    }

    static AIToken *Prev(const AIToken *tok) {
        return tok ? tok->prev : nullptr;
    }

    void AddFront(AIToken *tok);
    void AddBack(AIToken *tok);
    void Remove(AIToken *tok);
};

class AIComment final : public AIToken {
public:
    CString text{};

    AIComment(const LPCTSTR s) : AIToken(AIKComment), text(s) { }
    BOOL MatchesComment(LPCTSTR prefix) override;
};

class AIReal final : public AIToken {
public:
    double val;

    explicit AIReal(const double v) : AIToken(AIKReal), val(v) { }

    BOOL IsNumber() override {
        return TRUE;
    }

    double NumberVal() override {
        return val;
    }
};

class AIInteger final : public AIToken {
public:
    long val;

    explicit AIInteger(const long v) : AIToken(AIKInteger), val(v) { }

    BOOL IsNumber() override {
        return TRUE;
    }

    double NumberVal() override {
        return val;
    }
};

class AIUnsigned final : public AIToken {
public:
    unsigned long val;

    explicit AIUnsigned(const unsigned long v) : AIToken(AIKUnsigned), val(v) { }

    BOOL IsNumber() override {
        return TRUE;
    }

    double NumberVal() override {
        return val;
    }
};

class AIString final : public AIToken {
public:
    CString text{};

    explicit AIString(const LPCTSTR s) : AIToken(AIKString), text(s) { }
};

class AIName final : public AIToken {
public:
    CString text{};
    BOOL isliteral;

    AIName(const LPCTSTR s, const BOOL islit = FALSE) : AIToken(AIKName), text(s), isliteral(islit) { }
    BOOL MatchesName(LPCTSTR name) override;

    BOOL IsNonlitName() override {
        return !isliteral;
    }
};

class AIObject {
    friend class AIObjectList;
private:
    // prev, next used when token is part of a list
    AIObject *prev;
    AIObject *next;
public:
    AIObjectKind kind;

    explicit AIObject(const AIObjectKind k) : prev{nullptr}, next{nullptr}, kind(k) { }
    virtual ~AIObject() = default;
};

class AIObjectList {
    AIObject *head;
    AIObject *tail;
public:
    AIObjectList() : head(nullptr), tail(nullptr) { }
    ~AIObjectList();

    [[nodiscard]] AIObject *Head() const {
        return head;
    }

    [[nodiscard]] AIObject *Tail() const {
        return tail;
    }

    static AIObject *Next(const AIObject *obj) {
        return obj ? obj->next : nullptr;
    }

    static AIObject *Prev(const AIObject *obj) {
        return obj ? obj->prev : nullptr;
    }

    void AddFront(AIObject *obj);
    void AddBack(AIObject *obj);
    void Remove(AIObject *obj);
    [[nodiscard]] int Count() const;
};

class AICompoundPath final : public AIObject {
public:
    AIObjectList members; // should all be AIPath objects

    AICompoundPath() : AIObject(AIOCompoundPath) { }
    ~AICompoundPath() override = default;
};

class AIPath final : public AIObject {
public:
    BOOL fill;
    BOOL stroke;
    BOOL close;
    BOOL clockwise;
    BOOL nonzerowinding;

    AIObjectList pathops; // should all be AIPathOp objects

    AIPath() : AIObject(AIOPath), fill(FALSE), stroke(FALSE), close(FALSE), clockwise(TRUE), nonzerowinding(TRUE) { }
    ~AIPath() override = default;
};

class AIPathOp final : public AIObject {
public:
    AIPathOpKind opkind;
    BOOL iscorner;
    double x1;
    double y1;
    double x2;
    double y2;
    double x3;
    double y3;

    AIPathOp() : AIObject(AIOPathOp), opkind(AIPMoveto), iscorner(FALSE), x1(0.0), y1(0.0), x2(0.0), y2(0.0), x3(0.0), y3(0.0) { }

    AIPathOp(const AIPathOpKind k, const BOOL corn, const double X1, const double Y1, const double X2 = 0.0, const double Y2 = 0.0, const double X3 = 0.0, const double Y3 = 0.0) : AIObject(AIOPathOp), opkind(k), iscorner(corn), x1(X1), y1(Y1), x2(X2), y2(Y2), x3(X3), y3(Y3) { }

    ~AIPathOp() override = default;
};

class AIParser {
    AITokenList tokens;
    AIToken *curtok;
    AIPath *curpath;
    AICompoundPath *curcpath;
    BOOL instring;
    BOOL inhexstring;
    TCHAR *holdstring;
    int holdlen;
    int holdmax;
    void TokenizeBuf(const char *buf);
    BOOL CheckForPathOp();
    BOOL CheckForRenderOp();
    BOOL CheckForCompoundPathOp();
    BOOL GetRealArgs(int n, double *argbuf) const;
public:
    AIObjectList objects;

    AIParser();
    ~AIParser();
    BOOL TokenizeFile(LPCTSTR filename);
    void ParseTokens();
    void DumpTokens(LPCTSTR filename) const;
    void DumpObjects(LPCTSTR filename) const;
};
