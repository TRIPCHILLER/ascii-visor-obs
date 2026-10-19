/* Keep README links permanent; choose the newest published installer per platform. */
(function(root){
 'use strict';
 const repository='https://github.com/TRIPCHILLER/ascii-visor-obs/';
 function matches(name,platform){
  if(platform==='windows')return /^ASCII-VISOR-(?:[0-9][A-Za-z0-9.-]*-)?Windows-x64-Setup\.exe$/i.test(name)||/^ASCII-VISOR-[0-9][A-Za-z0-9.-]*-Setup\.exe$/i.test(name);
  if(platform==='linux')return /^ASCII-VISOR-(?:[0-9][A-Za-z0-9.-]*-)?Linux-x86_64-Setup\.AppImage$/i.test(name);
  if(platform==='macos')return /^ASCII-VISOR-(?:[0-9][A-Za-z0-9.-]*-)?macOS-universal-Setup\.zip$/i.test(name);
  return false;
 }
 function selectInstaller(releases,platform){
  const ordered=releases.filter(r=>r&&!r.draft&&r.published_at&&r.html_url?.startsWith(repository+'releases/tag/'))
   .sort((a,b)=>Date.parse(b.published_at)-Date.parse(a.published_at)||Number(b.id||0)-Number(a.id||0));
  for(const release of ordered){
   const asset=(release.assets||[]).find(a=>a.state==='uploaded'&&a.size>0&&matches(a.name,platform)&&a.browser_download_url?.startsWith(repository+'releases/download/'));
   if(asset)return {release,asset};
  }
  return null;
 }
 root.VisorDownloads={matches,selectInstaller};
 if(typeof module!=='undefined')module.exports=root.VisorDownloads;
})(typeof globalThis!=='undefined'?globalThis:this);
