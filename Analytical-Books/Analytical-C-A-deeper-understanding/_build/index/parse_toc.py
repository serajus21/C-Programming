import re, json, sys
t = open('toc-draft-v1.md').read()
chap_short = {
'00':'Before-the-Journey','01':'What-a-Computer-Physically-Is','02':'Why-C-Exists',
'03':'From-Source-to-Running-Program','04':'Numbers-as-Bit-Patterns','05':'Integer-Types',
'06':'Objects-Variables-and-Memory','07':'Floating-Point-Numbers','08':'Characters-and-Text-Encoding',
'09':'Expressions-and-Evaluation','10':'Arithmetic-and-Conversions','11':'Assignment-and-Increment',
'12':'Truth-and-Logic','13':'Bitwise-Operators','14':'Flow-of-Control','15':'Selection','16':'Iteration',
'17':'break-continue-and-goto','18':'Functions','19':'The-Call-Stack','20':'Scope-Lifetime-and-Linkage',
'21':'Multi-File-Programs-and-Linker','22':'The-Preprocessor','23':'Arrays','24':'Pointers','25':'Strings',
'26':'Dynamic-Memory','27':'Memory-Map-of-a-Program','28':'Structures','29':'Unions-Bit-Fields-and-Enums',
'30':'Data-Structures','31':'Streams-and-Formatted-IO','32':'Files','33':'Termination-Signals-and-Time',
'34':'Writing-Correct-C','35':'C-for-Critical-Systems','36':'Bare-Metal-ATmega328P',
'37':'Interrupts-Timers-Peripherals','38':'Concurrency-and-Memory-Model','39':'Toward-the-Machine-Designer',
'40':'Reference-Appendices'}
override = json.load(open('overrides.json')) if len(sys.argv)>1 else {}
def san(s):
    s = s.replace('&',' and ').replace('…',' ').replace('→',' to ')
    s = re.sub(r'[^A-Za-z0-9 +-]',' ',s).replace('+','p')
    w = s.split()
    out=[]
    for x in w:
        if len('-'.join(out+[x]))>40: break
        out.append(x)
    return '-'.join(out)
book={'front':[], 'parts':[]}
lines=t.split('\n')
cur_part=None; cur_ch=None; cur_sec=None
for ln in lines:
    m=re.match(r'^# (PART [IVX]+) — (.*)$',ln)
    if m:
        cur_part={'id':m.group(1),'title':m.group(2),'chapters':[]}; book['parts'].append(cur_part); continue
    m=re.match(r'^# Chapter (\d\d) — (.*)$',ln)
    if m:
        cur_ch={'num':m.group(1),'title':m.group(2),'short':chap_short[m.group(1)],'sections':[]}
        if cur_part is None or m.group(1) in ('00',):
            book['front'].append(cur_ch)
        elif m.group(1)=='40':
            book.setdefault('back',[]).append(cur_ch)
        else: cur_part['chapters'].append(cur_ch)
        continue
    if ln.startswith('# Summary'): cur_ch=None; continue
    m=re.match(r'^### §(\d\d)\.(\d\d) (.*)$',ln)
    if m and cur_ch:
        ref=f'{m.group(1)}.{m.group(2)}'
        sec={'ref':ref,'title':m.group(3),'builds':'','bullets':[]}
        sname=override.get(ref, san(m.group(3)))
        sec['file']=f"{m.group(1)}-{cur_ch['short']}-{m.group(2)}-{sname}.docx"
        cur_ch['sections'].append(sec); cur_sec=sec; continue
    if ln.startswith('Builds on:') and cur_sec: cur_sec['builds']=ln[len('Builds on:'):].strip(); continue
    m=re.match(r'^(\s*)- (.*)$',ln)
    if m and cur_sec and cur_ch:
        cur_sec['bullets'].append({'lvl':len(m.group(1))//2,'text':m.group(2)})
json.dump(book,open('toc.json','w'),indent=1,ensure_ascii=False)
for grp in [book['front']]+[p['chapters'] for p in book['parts']]+[book['back']]:
    for c in grp:
        for s in c['sections']:
            print(s['ref'], s['file'].split('-',)[0], s['file'][len(c['num'])+len(c['short'])+5:])
