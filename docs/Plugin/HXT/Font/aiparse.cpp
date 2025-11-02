#include "StdAfx.h"
#include "aiformat.h"

BOOL AIComment::MatchesComment(const LPCTSTR prefix) {
    const size_t n = _tcslen(prefix);
    return _tcsncmp(text, prefix, n) == 0;
}

BOOL AIName::MatchesName(const LPCTSTR name) {
    return _tcscmp(text, name) == 0;
}

AITokenList::~AITokenList() {
    const AIToken *p = head;
    while (p) {
        const AIToken *pnext = p->next;
        delete p;
        p = pnext;
    }
}

// assume tok not 0 and not part of any other list
void AITokenList::AddFront(AIToken *tok) {
    if (head) {
        head->prev = tok;
        tok->prev = nullptr;
        tok->next = head;
        head = tok;
    } else {
        head = tail = tok;
        tok->next = nullptr;
        tok->prev = nullptr;
    }
}

// assume tok not 0 and not part of any other list
void AITokenList::AddBack(AIToken *tok) {
    if (tail) {
        tail->next = tok;
        tok->prev = tail;
        tok->next = nullptr;
        tail = tok;
    } else {
        tail = head = tok;
        tok->next = nullptr;
        tok->prev = nullptr;
    }
}

// assume tok != 0 and part of this list (don't free tok)
void AITokenList::Remove(AIToken *tok) {
    AIToken *tprev = tok->prev;
    AIToken *tnext = tok->next;
    if (tprev)
        tprev->next = tnext;
    if (tnext)
        tnext->prev = tprev;
    tok->next = nullptr;
    tok->prev = nullptr;
    if (head == tok)
        head = tnext;
    if (tail == tok)
        tail = tprev;
}

AIObjectList::~AIObjectList() {
    const AIObject *p = head;
    while (p) {
        const AIObject *pnext = p->next;
        delete p;
        p = pnext;
    }
}

// assume obj not 0 and not part of any other list
void AIObjectList::AddFront(AIObject *obj) {
    if (head) {
        head->prev = obj;
        obj->prev = nullptr;
        obj->next = head;
        head = obj;
    } else {
        head = tail = obj;
        obj->next = nullptr;
        obj->prev = nullptr;
    }
}

// assume obj not 0 and not part of any other list
void AIObjectList::AddBack(AIObject *obj) {
    if (tail) {
        tail->next = obj;
        obj->prev = tail;
        obj->next = nullptr;
        tail = obj;
    } else {
        tail = head = obj;
        obj->next = nullptr;
        obj->prev = nullptr;
    }
}

// assume obj != 0 and part of this list (don't free obj)
void AIObjectList::Remove(AIObject *obj) {
    AIObject *tprev = obj->prev;
    AIObject *tnext = obj->next;
    if (tprev)
        tprev->next = tnext;
    if (tnext)
        tnext->prev = tprev;
    obj->next = nullptr;
    obj->prev = nullptr;
    if (head == obj)
        head = tnext;
    if (tail == obj)
        tail = tprev;
}

int AIObjectList::Count() const {
    int cnt = 0;
    for (const AIObject *p = head; p != nullptr; p = p->next) {
        cnt++;
    }
    return cnt;
}

AIParser::AIParser() : instring(FALSE), inhexstring(FALSE) {
    holdmax = 2000;
    holdstring = new TCHAR[holdmax];
    holdlen = 0;
    curtok = nullptr;
    curpath = nullptr;
    curcpath = nullptr;
}

AIParser::~AIParser() {
    delete [] holdstring;

    delete curpath;

    delete curcpath;
}

// Return FALSE if it seems the file is not an Illustrator (Version 8 or less) file.
// Also, skip over all lines until past %%EndSetup line, as we do not currently use
// any of the information before that.
BOOL AIParser::TokenizeFile(const LPCTSTR filename) {
    char *buf = nullptr;
    try {
        CFile f(filename, CFile::modeRead);
        const DWORD flen = f.GetLength();
        buf = new char[flen + 1];
        const UINT nread = f.Read(buf, flen);
        const char *psheader = "%!PS-Adobe";
        if (nread < 10 || strncmp(buf, psheader, strlen(psheader)) != 0) {
            delete [] buf;
            return FALSE;
        }
        buf[nread] = '\0';
        const char *skipto = "%%EndSetup";
        const char *es = strstr(buf, skipto);
        if (es == nullptr) {
            delete [] buf;
            return FALSE;
        }
        TokenizeBuf(es + strlen(skipto));
    }
    catch (CFileException &e) {
        TRACE("TokenizeFile caught file exception\n");
        e.Delete();
        delete [] buf;
        return FALSE;
    }
    delete [] buf;
    return TRUE;
}

static int fromhex(const char c) {
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;
    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    return 0;
}

static char fromhex(const char c1, const char c2) {
    return 16 * fromhex(c1) + fromhex(c2);
}

// Examine null-terminated buf for tokens, adding them to end of this->tokens.
// Assume buffer ends between lines or at end of file.
void AIParser::TokenizeBuf(const char *buf) {
    const char *numstartchars = "0123456789-+.";
    const int n = (int)strlen(buf);
    if (n == 0)
        return;
    const char *lbuf = buf;
    char *p;
    char *q;
    CString s;
    for (int i = 0; i <= n; ++i) {
        char c;
        if (i == n) {
            // put in explicit newline if in a string
            if (instring && !inhexstring)
                c = '\n';
            else
                break;
        } else
            c = lbuf[i];
        if (instring) {
            if (holdlen == holdmax) {
                holdmax *= 2;
                char *newhold = new char[holdmax];
                memmove(newhold, holdstring, holdlen * sizeof(char));
                delete [] holdstring;
                holdstring = newhold;
            }
            ASSERT(holdlen < holdmax);
            if (inhexstring) {
                if (c == '>') {
                    tokens.AddBack(new AIString(CString(holdstring, holdlen)));
                    holdlen = 0;
                    instring = FALSE;
                    inhexstring = FALSE;
                    continue;
                }
                // consume c and next char (if any, else 0)
                c = fromhex(c, i + 1 < n ? lbuf[i + 1] : '0');
                i++;
            } else {
                if (c == ')') {
                    tokens.AddBack(new AIString(CString(holdstring, holdlen)));
                    holdlen = 0;
                    instring = FALSE;
                    continue;
                }
            }
            if (!inhexstring && c == '\\') {
                if (i == n - 1) {
                    // means don't put newline in; finished with this line
                    return;
                }
                c = lbuf[++i];
                switch (c) {
                    case 'n':
                        c = '\n';
                        break;
                    case 'r':
                        c = '\r';
                        break;
                    case 't':
                        c = '\t';
                        break;
                    case 'b':
                        c = '\b';
                        break;
                    case '\\':
                        c = '\\';
                        break;
                    case '(':
                    case ')':
                        break; // c is the paren
                    default:
                        if (c >= '0' && c <= '7') {
                            c = c - '0';
                            if (i < n - 1) {
                                const char d = lbuf[++i];
                                if (d >= '0' && d <= '7') {
                                    c = 8 * c + d - '0';
                                    if (i < n - 1) {
                                        const char e = lbuf[++i];
                                        if (e >= '0' && e <= '7')
                                            c = 8 * c + e - '0';
                                        else
                                            i--;
                                    }
                                } else
                                    i--;
                            }
                        } else
                            continue; // unknown escape: ignored
                }
            }
            holdstring[holdlen++] = c;
        } else {
            const char *tokbreak = " \t\r\n()<>[]{}/%";
            // not in string (or hexstring)
            switch (c) {
                case ' ':
                case '\r':
                case '\t':
                case '\n':
                    continue;
                case '%':
                {
                    const char *cp = strpbrk(lbuf + i, "\r\n"); //was p but vs8.0 didn't like converting const char * to char *. As near as I can tell buf isn't going to be modified here.
                    if (cp != nullptr) {
                        tokens.AddBack(new AIComment(CString(lbuf + i, cp - (lbuf + i))));
                        i = cp - lbuf; // ok to skip over '\r' with loop i++
                        if (lbuf[i + 1] == '\n')
                            i++; // ok to skip over '\n' with loop i++
                    } else {
                        tokens.AddBack(new AIComment(CString(lbuf + i)));
                        return;
                    }
                    break;
                }
                case '(':
                    instring = TRUE;
                    holdlen = 0;
                    break;
                case ')':
                    // not in string: shouldn't happen
                    break;
                case '<':
                    instring = TRUE;
                    inhexstring = TRUE;
                    holdlen = 0;
                    break;
                case '>':
                    // not in hex string: shouldn't happen
                    break;
                case '[':
                case ']':
                case '{':
                case '}':
                    tokens.AddBack(new AIName(CString(c)));
                    break;
                case '/':
                {
                    const char *cp = strpbrk(lbuf + i + 1, tokbreak); //was p but vs8.0 didn't like converting const char * to char *. As near as I can tell buf isn't going to be modified here.
                    if (cp == nullptr) {
                        s = CString(lbuf + i + 1);
                        i = n - 1;
                    } else {
                        s = CString(lbuf + i + 1, cp - (lbuf + i + 1));
                        i = cp - lbuf - 1;
                    }
                    tokens.AddBack(new AIName(s, TRUE));
                    break;
                }
                default:
                    if (strchr(numstartchars, c)) {
                        // see if it's an int
                        const long lval = strtol(lbuf + i, &p, 10);
                        c = *p;
                        if (p > lbuf + i && (c == 0 || strchr(tokbreak, c))) {
                            tokens.AddBack(new AIInteger(lval));
                            i = p - lbuf - 1; // -1 to compensate for loop i++
                            continue;
                        }
                        // see if it's a radix number: base#val
                        if (p > lbuf + i && c == '#' && lval >= 2 && lval <= 36) {
                            const unsigned long ulval = strtoul(p + 1, &q, lval);
                            c = *q;
                            if (q > p + 1 && (c == 0 || strchr(tokbreak, c))) {
                                // got a radix val
                                tokens.AddBack(new AIUnsigned(ulval));
                                i = q - lbuf - 1; // -1 to compensate for loop i++
                                continue;
                            }
                        }
                        // see if it's a real
                        const double dval = strtod(lbuf + i, &p);
                        c = *p;
                        if (p > lbuf + i && (c == 0 || strchr(tokbreak, c))) {
                            tokens.AddBack(new AIReal(dval));
                            i = p - lbuf - 1; // -1 to compensate for loop i++
                            continue;
                        }
                    }
                    // must be a name
                    const char *cp = strpbrk(lbuf + i, tokbreak); //was p but vs8.0 didn't like converting const char * to char *. As near as I can tell buf isn't going to be modified here.
                    if (cp == nullptr) {
                        s = CString(lbuf + i);
                        i = n - 1; //  -1 to compensate for loop i++
                    } else {
                        s = CString(lbuf + i, cp - (lbuf + i));
                        i = cp - lbuf - 1; //  -1 to compensate for loop i++
                    }
                    tokens.AddBack(new AIName(s, FALSE));
            }
        }
    }
}

// Write readable representation of this->tokens to file with given name.
// (For debugging)
void AIParser::DumpTokens(const LPCTSTR filename) const {
    try {
        CStdioFile f(filename, CFile::modeWrite | CFile::modeCreate | CFile::typeText);
        CString line;
        AIToken *tok = tokens.Head();
        while (tok != nullptr) {
            const AITokenKind kind = tok->kind;
            if (kind == AIKComment) {
                auto *tcom = (AIComment *)tok;
                line.Format("Comment %s\n", tcom->text.GetBuffer());
            } else if (kind == AIKReal) {
                const AIReal *tr = (AIReal *)tok;
                line.Format("Real %g\n", tr->val);
            } else if (kind == AIKInteger) {
                const AIInteger *ti = (AIInteger *)tok;
                line.Format("Int %d\n", ti->val);
            } else if (kind == AIKUnsigned) {
                const AIUnsigned *tu = (AIUnsigned *)tok;
                line.Format("Unsigned %ud\n", tu->val);
            } else if (kind == AIKString) {
                auto *ts = (AIString *)tok;
                line.Format("String %s\n", ts->text.GetBuffer());
            } else if (kind == AIKName) {
                auto *tn = (AIName *)tok;
                if (tn->isliteral)
                    line.Format("Literal Name %s\n", tn->text.GetBuffer());
                else
                    line.Format("Name %s\n", tn->text.GetBuffer());
            }
            f.WriteString(line);
            tok = AITokenList::Next(tok);
        }
    }
    catch (CFileException &e) {
        TRACE("DumpTokens caught file exception\n");
        e.Delete();
    }
}

// Call this after this->tokens has been filled.
// Parse that list AIObjects, putting them in this->objects.
// Assume we have skipped to just past %%EndSetup line before
// token array starts.
void AIParser::ParseTokens() {
    curtok = tokens.Head();
    curpath = nullptr;
    curcpath = nullptr;
    for (; curtok != nullptr; curtok = AITokenList::Next(curtok)) {
        if (curtok->IsNonlitName()) {
            if (CheckForPathOp())
                continue;
            if (curpath != nullptr && CheckForRenderOp())
                continue;
            if (CheckForCompoundPathOp())
                continue;
        }
    }
}

// See if curtok is a path operator, and that it has acceptable args.
// If so, add to curpath (or start curpath, if a Moveto).
// Assume curtok is a non-literal name token.
// Return TRUE if found and handled a pathop, else FALSE.
BOOL AIParser::CheckForPathOp() {
    ASSERT(curtok != nullptr && curtok->kind == AIKName);
    const AIName *nametok = (AIName *)curtok;
    const LPCTSTR name = nametok->text;
    // all pathop names are one letter
    const char c = name[0];
    if (c == 0 || name[1] != 0)
        return FALSE;
    AIPathOp *pop = nullptr;
    double a[6];
    switch (c) {
        case 'm':
            if (GetRealArgs(2, a))
                pop = new AIPathOp(AIPMoveto, FALSE, a[0], a[1]);
            break;
        case 'l':
        case 'L':
            if (GetRealArgs(2, a))
                pop = new AIPathOp(AIPLineto, c == 'L', a[0], a[1]);
            break;
        case 'c':
        case 'C':
            if (GetRealArgs(6, a))
                pop = new AIPathOp(AIPCurveto, c == 'C', a[0], a[1], a[2], a[3], a[4], a[5]);
            break;
        case 'v':
        case 'V':
            // start point and next bezier control point coincide
            if (GetRealArgs(4, a)) {
                pop = new AIPathOp(AIPCurveto, c == 'V', 0.0, 0.0, a[0], a[1], a[2], a[3]);
                // x1 and y1 are previous point ... hope curpath has a val!
                if (curpath != nullptr) {
                    AIObject *prevobj = curpath->pathops.Tail();
                    BOOL ok = FALSE;
                    if (prevobj != nullptr) {
                        if (prevobj->kind == AIOPathOp) {
                            const AIPathOp *prevpop = (AIPathOp *)prevobj;
                            if (prevpop->opkind == AIPMoveto || prevpop->opkind == AIPLineto) {
                                pop->x1 = prevpop->x1;
                                pop->y1 = prevpop->y1;
                                ok = TRUE;
                            } else if (prevpop->opkind == AIPCurveto) {
                                pop->x1 = prevpop->x3;
                                pop->y1 = prevpop->y3;
                                ok = TRUE;
                            }
                        }
                    }
                    if (!ok) {
                        delete pop;
                        pop = nullptr;
                    }
                }
            }
            break;
        case 'y':
        case 'Y':
            // end point and previous bezier control point coincide
            if (GetRealArgs(4, a))
                pop = new AIPathOp(AIPCurveto, c == 'Y', a[0], a[1], a[2], a[3], a[2], a[3]);
            break;
        case 'h':
        case 'H':
            // close
            if (curpath != nullptr)
                curpath->close = TRUE;
            return TRUE;
        default:
   break;
    }
    if (pop == nullptr)
        return FALSE;
    if (curpath == nullptr) {
        if (pop->opkind == AIPMoveto) {
            curpath = new AIPath();
            curpath->pathops.AddBack(pop);
        } else {
            // bad syntax: paths need to start with moveto
            TRACE("ignoring pathop not part of path\n");
            delete pop;
        }
    } else
        curpath->pathops.AddBack(pop);
    return TRUE;
}

// We need n real args preceding current token.
// If they are there, copy them into argbuf[0], ..., argbuf[n-1],
// (with earliest in list in argbuf[0])
// and return TRUE, else return FALSE.
// Allow embedded comments, and convert any integers to reals
BOOL AIParser::GetRealArgs(const int n, double *argbuf) const {
    int nsofar = 0;
    AIToken *tok = AITokenList::Prev(curtok);
    for (; tok != nullptr && nsofar < n; tok = AITokenList::Prev(tok)) {
        if (tok->IsNumber()) {
            argbuf[n - 1 - nsofar] = tok->NumberVal();
            nsofar++;
        } else if (tok->kind != AIKComment)
            break;
    }
    return n == nsofar;
}

// See if curtok is a renderop, and if so, finish off curpath
// and add the path the the end of the current compound path, if any,
// else to the end of the parser's objects list.
// Return TRUE if it was one, else FALSE.
// Assume curtok is a nonliteral name token, and curpath != 0.
BOOL AIParser::CheckForRenderOp() {
    ASSERT(curtok != nullptr && curtok->kind == AIKName && curpath != nullptr);
    const AIName *nametok = (AIName *)curtok;
    const LPCTSTR name = nametok->text;
    // all renderop names are one or two letters
    const char c1 = name[0];
    if (c1 == 0)
        return FALSE;
    const char c2 = name[1];
    BOOL ans = TRUE;
    BOOL dofill = FALSE;
    BOOL dostroke = FALSE;
    BOOL doclose = FALSE;
    switch (c1) {
        case 'n':
        case 'N':
            if (c2 == 0) {
                doclose = c1 == 'n';
                // doc disagrees with itself about n vs N, but this matches pattern
            }
            break;
        case 'f':
        case 'F':
            if (c2 == 0) {
                dofill = TRUE;
                doclose = c1 == 'f';
            }
            break;
        case 's':
        case 'S':
            if (c2 == 0) {
                dostroke = TRUE;
                doclose = c1 == 's';
            }
            break;
        case 'b':
            if (c2 == 0) {
                dofill = TRUE;
                dostroke = TRUE;
                doclose = TRUE;
            }
            break;
        case 'B':
            if (c2 == 0 || c2 == 'b' || c2 == 'g' || c2 == 'm' || c2 == 'c' || c2 == 'B') {
                dofill = TRUE;
                dostroke = TRUE;
                doclose = FALSE;
            }
            break;
        default:
            ans = FALSE;
    }
    if (ans) {
        curpath->close = curpath->close || doclose;
        curpath->stroke = dostroke;
        curpath->fill = dofill;
        if (curcpath != nullptr)
            curcpath->members.AddBack(curpath);
        else
            objects.AddBack(curpath);
        curpath = nullptr;
    }
    return ans;
}

// Check for beginning or end of compound path (*u ... *U).
// The paths in such a group are to be regarded as Postcript "subpaths",
// filled at one go, with the possibility of making holes.
// Compound paths are not supposed to nest, so there should be at most
// one active compound path.
// If this is the start of a compound group, make sure we are not already
// in one and then set curcpath to a new compound path object.
// If this is the end of a compound group, make sure that we are in one,
// and finish it off, adding it to the parser's objects list.
// Assume the current token is a nonliteral name token
BOOL AIParser::CheckForCompoundPathOp() {
    ASSERT(curtok != nullptr && curtok->kind == AIKName);
    const AIName *nametok = (AIName *)curtok;
    const LPCTSTR name = nametok->text;
    const char c1 = name[0];
    if (c1 != '*')
        return FALSE;
    const char c2 = name[1];
    if (c2 == 'u') {
        if (curcpath == nullptr)
            curcpath = new AICompoundPath;
        else
            TRACE("unexpected start of compound path\n");
        return TRUE;
    }
    if (c2 == 'U') {
        if (curcpath != nullptr) {
            objects.AddBack(curcpath);
            curcpath = nullptr;
        } else
            TRACE("unexpected end of compound path\n");
        return TRUE;
    }
    return FALSE;
}

// Write a readable representation of obj to file f.
// Use indent to say how much to indent.
static void DumpObject(CStdioFile &f, AIObject *obj, const int indent) {
    const CString indstr = CString(' ', 3 * indent);
    CString line;
    AICompoundPath *cpath;
    AIPath *path;
    AIPathOp *op;
    AIObject *p;
    switch (obj->kind) {
        case AIOCompoundPath:
            cpath = (AICompoundPath *)obj;
            line = indstr + "Compound Path\n";
            f.WriteString(line);
            for (p = cpath->members.Head(); p != nullptr; p = AIObjectList::Next(p))
                DumpObject(f, p, indent + 1);
            break;
        case AIOPath:
            path = (AIPath *)obj;
            line = indstr + "Path ";
            if (path->fill)
                line += "filled ";
            if (path->stroke)
                line += "stroked ";
            if (path->close)
                line += "closed ";
            if (!path->clockwise)
                line += "ccw ";
            if (!path->nonzerowinding)
                line += "odd/even ";
            line += "\n";
            f.WriteString(line);
            for (p = path->pathops.Head(); p != nullptr; p = AIObjectList::Next(p))
                DumpObject(f, p, indent + 1);
            break;
        case AIOPathOp:
            op = (AIPathOp *)obj;
            if (op->opkind == AIPMoveto)
                line.Format("Moveto (%g,%g)", op->x1, op->y1);
            else if (op->opkind == AIPLineto)
                line.Format("Lineto (%g,%g)", op->x1, op->y1);
            else if (op->opkind == AIPCurveto)
                line.Format("Curveto (%g,%g)(%g,%g)(%g,%g)", op->x1, op->y1, op->x2, op->y2, op->x3, op->y3);
            else
                line = "????";
            line = indstr + line;
            if (op->iscorner)
                line += " ^";
            line += "\n";
            f.WriteString(line);
            break;
//        default:
//            line = indstr + "???\n";
//            f.WriteString(line);
    }
}

void AIParser::DumpObjects(const LPCTSTR filename) const {
    try {
        CStdioFile f(filename, CFile::modeWrite | CFile::modeCreate | CFile::typeText);
//        CString line;
        AIObject *obj = objects.Head();
        while (obj != nullptr) {
            DumpObject(f, obj, 0);
            obj = AIObjectList::Next(obj);
        }
    }
    catch (CFileException &e) {
        TRACE("DumpTokens caught file exception\n");
        e.Delete();
    }
}
