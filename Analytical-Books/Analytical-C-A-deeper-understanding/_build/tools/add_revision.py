# Append one revision-log row to _index.docx by cloning the last row, and bump the title-page version.
import sys, zipfile, re, html
src, dst, old, new, date, text = sys.argv[1:7]
z = zipfile.ZipFile(src)
x = z.read('word/document.xml').decode()
j = x.find('>' + old + '<'); s = x.rfind('<w:tr', 0, j); s = x.rfind('<w:tr>', 0, j+1) if x.rfind('<w:tr>',0,j+1) > x.rfind('<w:tr ',0,j+1) else x.rfind('<w:tr ',0,j+1)
e = x.find('</w:tr>', j) + 7
row = x[s:e]
cells = re.findall(r'<w:tc>.*?</w:tc>', row, re.S)
assert len(cells) == 3, len(cells)
def set_cell(cell, value):
    paras = re.findall(r'<w:p[ >].*?</w:p>', cell, re.S)
    p = paras[0]
    runs = re.findall(r'<w:r>.*?</w:r>|<w:r .*?</w:r>', p, re.S)
    rpr = re.search(r'<w:rPr>.*?</w:rPr>', runs[0], re.S)
    rpr = rpr.group(0) if rpr else ''
    ppr = re.search(r'<w:pPr>.*?</w:pPr>', p, re.S); ppr = ppr.group(0) if ppr else ''
    newp = '<w:p>' + ppr + '<w:r>' + rpr + '<w:t xml:space="preserve">' + html.escape(value, quote=False) + '</w:t></w:r></w:p>'
    start = cell.find(paras[0]); end = cell.find(paras[-1]) + len(paras[-1])
    return cell[:start] + newp + cell[end:]
newcells = [set_cell(cells[0], new), set_cell(cells[1], date), set_cell(cells[2], text)]
newrow = row
for a, b in zip(cells, newcells): newrow = newrow.replace(a, b, 1)
x = x[:e] + newrow + x[e:]
assert x.count('Version ' + old + ' ·') == 1
x = x.replace('Version ' + old + ' ·', 'Version ' + new + ' ·')
out = zipfile.ZipFile(dst, 'w', zipfile.ZIP_DEFLATED)
for it in z.infolist():
    out.writestr(it, x if it.filename == 'word/document.xml' else z.read(it.filename))
out.close()
print('ok', len(x))
