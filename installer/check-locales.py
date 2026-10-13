import json,re
from pathlib import Path
root=Path(__file__).resolve().parent
locales=json.loads((root/'locales.json').read_text(encoding='utf-8-sig'))
used=set(re.findall(r"L '([^']+)'",(root/'setup.ps1').read_text(encoding='utf-8-sig')))
assert len(locales)==10
base=set(locales['en-US'])
for code,values in locales.items():
    assert set(values)==base,code
    assert used<=set(values),(code,used-set(values))
    assert all(values.values()),code
    print(f'{code}: {len(values)-1} complete UI keys and native language name')
