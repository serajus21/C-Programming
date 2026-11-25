#!/usr/bin/env python3
"""Convert British spellings to American in the book's markdown sources.

Code blocks (``` fences) and inline code spans (`...`) are never touched.
Usage: american.py FILE...            (dry run: prints every change)
       american.py --write FILE...    (applies the changes)
"""
import re, sys

# Whole-word replacements (lower-case keys; capitalization is preserved).
WORDS = {
    "behaviour": "behavior", "behaviours": "behaviors", "behavioural": "behavioral",
    "colour": "color", "colours": "colors", "coloured": "colored",
    "neighbour": "neighbor", "neighbours": "neighbors", "neighbouring": "neighboring",
    "favour": "favor", "favours": "favors", "favourable": "favorable", "favourite": "favorite",
    "honour": "honor", "honours": "honors", "labour": "labor",
    "humour": "humor", "rumour": "rumor", "vapour": "vapor",
    "centre": "center", "centres": "centers", "centred": "centered",
    "metre": "meter", "metres": "meters", "kilometre": "kilometer", "kilometres": "kilometers",
    "millimetre": "millimeter", "millimetres": "millimeters", "centimetre": "centimeter",
    "centimetres": "centimeters", "fibre": "fiber", "fibres": "fibers", "litre": "liter",
    "theatre": "theater", "calibre": "caliber", "lustre": "luster",
    "defence": "defense", "defences": "defenses", "offence": "offense", "licence": "license",
    "practise": "practice", "practised": "practiced", "practising": "practicing",
    "ageing": "aging", "grey": "gray", "sceptical": "skeptical", "aluminium": "aluminum",
    "whilst": "while", "amongst": "among", "learnt": "learned", "spelt": "spelled",
    "towards": "toward", "programme": "program", "programmes": "programs",
    "catalogue": "catalog", "catalogues": "catalogs", "analogue": "analog",
    "dialogue": "dialog", "plough": "plow", "tyre": "tire", "tyres": "tires",
    "mould": "mold", "storey": "story", "cheque": "check", "kerb": "curb",
    "enrolment": "enrollment", "fulfil": "fulfill", "fulfils": "fulfills",
    "instalment": "installment", "skilful": "skillful", "wilful": "willful",
    "judgement": "judgment", "acknowledgement": "acknowledgment",
    "manoeuvre": "maneuver", "oestrogen": "estrogen",
    "sulphur": "sulfur", "artefact": "artifact", "artefacts": "artifacts",
    "travelled": "traveled", "travelling": "traveling", "traveller": "traveler",
    "labelled": "labeled", "labelling": "labeling", "modelled": "modeled", "modelling": "modeling",
    "signalled": "signaled", "signalling": "signaling", "cancelled": "canceled",
    "cancelling": "canceling", "levelled": "leveled", "fuelled": "fueled",
    "totalled": "totaled", "totalling": "totaling", "channelled": "channeled",
    "tunnelling": "tunneling", "marshalled": "marshaled", "counselling": "counseling",
    "jewellery": "jewelry", "woollen": "woolen", "dreamt": "dreamed", "burnt": "burned",
    "for ever": "forever", "maths": "math", "anticlockwise": "counterclockwise",
    "car park": "parking lot", "post code": "zip code",
}
# -ise / -isation / -yse families: convert only known stems (avoid "rise", "wise",
# "precise", "exercise", "advise", "otherwise", "promise", "noise", "concise" ...).
ISE_STEMS = ["organ", "ideal", "recogn", "real", "memor", "optim", "standard", "summar",
             "initial", "normal", "serial", "special", "emphas", "minim", "maxim",
             "util", "visual", "categor", "prior", "author", "general", "local",
             "synchron", "symbol", "stabil", "capital", "critic", "character",
             "apolog", "theor", "final", "harmon", "magnet", "itemis", "custom",
             "modern", "economis", "familiar", "national", "neutral", "polar",
             "random", "sanit", "tokenis", "parallel", "vectoris", "digit",
             "quant", "central", "equal", "personal", "formal", "patron",
             "sympath", "monopol", "legal", "civil", "fertil", "steril", "global",
             "internal", "external", "material", "hospital", "industrial", "rational",
             "fantas", "dramat", "agon", "terror", "jeopard", "computer", "linear",
             "regular", "particular", "trivial", "virtual", "tokenize", "radian"]
ISE_SUFFIX = {"ise": "ize", "ises": "izes", "ised": "ized", "ising": "izing",
              "isation": "ization", "isations": "izations", "iser": "izer", "isers": "izers",
              "isable": "izable"}
YSE = {"analyse": "analyze", "analysed": "analyzed", "analyses": "analyzes",
       "analysing": "analyzing", "paralyse": "paralyze", "catalyse": "catalyze"}

MONTHS = "January|February|March|April|May|June|July|August|September|October|November|December"

def keep_case(src, dst):
    if src.isupper():
        return dst.upper()
    if src[0].isupper():
        return dst[0].upper() + dst[1:]
    return dst

def build_patterns():
    pats = []
    for k, v in WORDS.items():
        pats.append((re.compile(r"\b" + re.escape(k).replace(r"\ ", r"\s+") + r"\b", re.I), v))
    for stem in ISE_STEMS:
        for suf, rep in ISE_SUFFIX.items():
            pats.append((re.compile(r"\b(" + stem + ")" + suf + r"\b", re.I), None, suf, rep))
    for k, v in YSE.items():
        pats.append((re.compile(r"\b" + k + r"\b", re.I), v))
    return pats

PATS = build_patterns()
DATE = re.compile(r"\b(\d{1,2}) (" + MONTHS + r") (\d{4})\b")

def convert_text(t, log):
    for p in PATS:
        if len(p) == 2:
            rx, v = p
            def f(m, v=v):
                out = keep_case(m.group(0), v)
                log.append((m.group(0), out)); return out
            t = rx.sub(f, t)
        else:
            rx, _, suf, rep = p
            def g(m, suf=suf, rep=rep):
                word = m.group(0)
                out = word[:len(m.group(1))] + keep_case(word[len(m.group(1)):], rep)
                log.append((word, out)); return out
            t = rx.sub(g, t)
    def d(m):
        out = f"{m.group(2)} {int(m.group(1))}, {m.group(3)}"
        log.append((m.group(0), out)); return out
    t = DATE.sub(d, t)
    # thousands separated by spaces (65 536) -> commas (65,536)
    def th(m):
        out = m.group(0).replace(" ", ",")
        log.append((m.group(0), out)); return out
    t = re.sub(r"(?<![\d.,])\d{1,3}(?: \d{3})+(?![\d])", th, t)
    # a space before a percent sign in prose (15 %) -> 15%
    def pc(m):
        log.append((m.group(0), m.group(1) + "%")); return m.group(1) + "%"
    t = re.sub(r"(\d) %(?!%)", pc, t)
    return t

def convert(src):
    """Convert outside code fences and inline code spans."""
    out, log, fence = [], [], False
    for line in src.split("\n"):
        if line.startswith("```"):
            fence = not fence
            out.append(line); continue
        if fence:
            out.append(line); continue
        parts = re.split(r"(`[^`]*`)", line)
        for i in range(0, len(parts), 2):
            parts[i] = convert_text(parts[i], log)
        out.append("".join(parts))
    return "\n".join(out), log

if __name__ == "__main__":
    args = sys.argv[1:]
    write = args and args[0] == "--write"
    if write:
        args = args[1:]
    for fn in args:
        s = open(fn).read()
        t, log = convert(s)
        print(f"== {fn}: {len(log)} changes")
        seen = {}
        for a, b in log:
            seen[(a, b)] = seen.get((a, b), 0) + 1
        for (a, b), n in sorted(seen.items()):
            print(f"   {a!r} -> {b!r}  x{n}")
        if write and t != s:
            open(fn, "w").write(t)
