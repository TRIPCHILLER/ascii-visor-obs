import re
from pathlib import Path

root=Path(__file__).resolve().parents[1]
source=(root/'src/visor.c').read_text(encoding='utf-8')
used=set(re.findall(r'obs_module_text\("([^"]+)"\)',source))
base=None
for path in sorted((root/'data/locale').glob('*.ini')):
    entries={}
    for line in path.read_text(encoding='utf-8-sig').splitlines():
        if not line.strip() or line.startswith('#'):continue
        match=re.fullmatch(r'([A-Za-z0-9_]+)="(.+)"',line)
        assert match,line
        key,value=match.groups()
        assert key not in entries,key
        entries[key]=value
    assert used<=entries.keys(),used-entries.keys()
    if base is None:base=set(entries)
    assert set(entries)==base,path
    print(f'{path.name}: {len(entries)} complete translation keys')
