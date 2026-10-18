#include <QtWidgets>
#include <QCryptographicHash>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QProcess>
#include <QTemporaryDir>
#include <stdexcept>

static QByteArray readFile(const QString &path) {
 QFile f(path);if(!f.open(QIODevice::ReadOnly))throw std::runtime_error(("Cannot read: "+path).toStdString());return f.readAll();
}
static void fail(const QString &message){throw std::runtime_error(message.toStdString());}
static bool copyTree(const QString &from,const QString &to) {
 if(QFileInfo(from).isSymLink())return false;
 if(QFileInfo(from).isDir()){
  if(!QDir().mkpath(to))return false;
  for(const QFileInfo &f:QDir(from).entryInfoList(QDir::AllEntries|QDir::NoDotAndDotDot|QDir::Hidden))
   if(!copyTree(f.absoluteFilePath(),to+"/"+f.fileName()))return false;
  return true;
 }
 return QFile::copy(from,to);
}
static void verifyPayload(const QString &root){
 QJsonParseError err;auto document=QJsonDocument::fromJson(readFile(root+"/manifest.json"),&err);
 if(err.error!=QJsonParseError::NoError||!document.isArray()||document.array().isEmpty())fail("Invalid payload manifest");
 QSet<QString> listed;
 for(const auto &entry:document.array()){
  auto o=entry.toObject();auto path=o["path"].toString();
  if(path.isEmpty()||QDir::isAbsolutePath(path)||path.contains('\\')||path.split('/').contains("..")||listed.contains(path))fail("Unsafe payload path");
  auto bytes=readFile(root+"/"+path);
  if(QFileInfo(root+"/"+path).isSymLink()||QCryptographicHash::hash(bytes,QCryptographicHash::Sha256).toHex()!=o["sha256"].toString().toLatin1())fail("Payload checksum mismatch: "+path);
  listed.insert(path);
 }
 QDirIterator it(root,QDir::Files|QDir::Hidden|QDir::NoDotAndDotDot,QDirIterator::Subdirectories);
 while(it.hasNext()){
  QString rel=QDir(root).relativeFilePath(it.next());
  if(rel!="manifest.json"&&!listed.contains(rel))fail("Unlisted payload file: "+rel);
 }
}
static QString deployPlugin(const QString &payload,const QString &plugin,const QString &root){
 verifyPayload(payload);
   if(!QDir().mkpath(root)||QFileInfo(root).isSymLink())fail("Cannot use destination directory");
   const QString destination=root+"/"+plugin;
   if(QFileInfo(destination).isSymLink())fail("Destination is a symbolic link");

   QTemporaryDir staging(root+"/.visor-stage-XXXXXX");if(!staging.isValid())fail("Cannot create staging directory");
   const QString staged=staging.path()+"/"+plugin;
   if(!copyTree(payload+"/"+plugin,staged))fail("Cannot stage plugin files");
#ifdef Q_OS_MACOS
   QProcess signing;signing.start("/usr/bin/codesign",{"--force","--sign","-",staged});
   if(!signing.waitForFinished(30000)||signing.exitCode()!=0)fail("Local plugin signing failed");
#endif
   QString backup;
   if(QFileInfo::exists(destination)){
    backup=root+"/.visor-backup-"+QUuid::createUuid().toString(QUuid::WithoutBraces);
    if(!QDir().rename(destination,backup))fail("Cannot back up previous plugin");
   }
   if(!QDir().rename(staged,destination)){
    if(!backup.isEmpty()&&!QDir().rename(backup,destination))fail("Install and rollback failed. Backup: "+backup);
    fail("Install failed; previous plugin restored.");
   }
 return backup;
}
class Setup:public QWidget {
 QJsonObject all;QString resources,code,backup,selectedOBS;
 QLabel *heading,*intro,*detail,*license,*credits,*logo;
 QComboBox *languages,*mode,*launchMode;QLineEdit *custom,*obsPath;QPushButton *browse,*install,*cancel,*chooseOBS;
 QCheckBox *launch;bool complete=false;
 QString l(const char *key)const{return all[code].toObject()[key].toString();}
 QString targetRoot()const {
#ifdef Q_OS_MACOS
  const QString native=QDir::homePath()+"/Library/Application Support/obs-studio/plugins";
#else
  const QString config=qEnvironmentVariable("XDG_CONFIG_HOME",QDir::homePath()+"/.config");
  const QString native=config+"/obs-studio/plugins";
  if(mode->currentIndex()==1)return QDir::homePath()+"/.var/app/com.obsproject.Studio/config/obs-studio/plugins";
#endif
  return mode->currentData().toString()=="custom"?custom->text():native;
 }
 void updateText(){
  heading->setText(l(complete?"DoneHeading":"Heading"));
  QString text=l("Intro");text.replace("Windows x64",
#ifdef Q_OS_MACOS
  "macOS · Intel / Apple Silicon"
#else
  "Linux x86_64"
#endif
  );text.replace("32.2.2","31+ · PREVIEW");intro->setText(text);
  install->setText(l("Install"));cancel->setText(l(complete?"Finish":"Cancel"));
  license->setText(l("License"));QString credit=l("Credits");credit.replace(QString::fromUtf8("⛶ "),QString());credits->setText(credit);launch->setText(l("Launch"));
  int previous=launchMode->currentIndex();launchMode->clear();launchMode->addItem(l("DirectOBS"),"direct");
#ifndef Q_OS_MACOS
  if(mode->currentData().toString()!="flatpak"&&!QStandardPaths::findExecutable("steam").isEmpty())launchMode->addItem(l("SteamOBS"),"steam");
#endif
  launchMode->setCurrentIndex(qMax(0,qMin(previous,launchMode->count()-1)));
  if(complete)detail->setText(l("DoneInfo")+"\n"+l("Backup")+" "+backup);
  else detail->setText(l("Destination")+"\n"+targetRoot()+"\n\n"+l("BackupNotice"));
 }
 void doInstall(){
  try{
   for(const QString &name:{QString("obs"),QString("OBS")}){
    QProcess p;p.start("pgrep",{"-x",name});p.waitForFinished();if(p.exitCode()==0)fail(l("CloseOBS"));
   }
   QProcess version;
#ifdef Q_OS_MACOS
   const QString app=obsPath->text();
   version.start("/usr/libexec/PlistBuddy",{"-c","Print:CFBundleIdentifier",app+"/Contents/Info.plist"});version.waitForFinished();
   if(version.readAllStandardOutput().trimmed()!="com.obsproject.obs-studio")fail("Select the OBS Studio application.");
   version.start("/usr/libexec/PlistBuddy",{"-c","Print:CFBundleShortVersionString",app+"/Contents/Info.plist"});
#else
   if(mode->currentData().toString()=="flatpak")version.start("flatpak",{"run","com.obsproject.Studio","--version"});
   else version.start(obsPath->text(),{"--version"});
#endif
   if(!version.waitForFinished(15000)||version.exitCode()!=0)fail("Cannot identify OBS. Select your OBS installation.");
   QString output=QString::fromUtf8(version.readAllStandardOutput()+version.readAllStandardError());
   auto match=QRegularExpression("(\\d+)\\.\\d+").match(output);
   if(!match.hasMatch()||match.captured(1).toInt()<31)fail("OBS Studio 31 or newer is required for this preview.");
   selectedOBS=obsPath->text();
   const QString root=QDir::cleanPath(targetRoot());
   if(!QDir::isAbsolutePath(root)||root=="/"||root==QDir::homePath())fail("Choose an OBS plugins directory.");
   const QString payload=resources+"/payload";verifyPayload(payload);
#ifdef Q_OS_MACOS
   const QString plugin="ascii-visor.plugin";
   if(!QFileInfo::exists(payload+"/"+plugin+"/Contents/MacOS/ascii-visor"))fail("Missing macOS plugin");
#else
   const QString plugin="ascii-visor";
   if(!QFileInfo::exists(payload+"/"+plugin+"/bin/64bit/ascii-visor.so"))fail("Missing Linux plugin");
#endif
   const QString destination=root+"/"+plugin;
   if(QMessageBox::question(this,"ASCII VISOR",l("Destination")+"\n"+destination+"\n\n"+l("BackupNotice"))!=QMessageBox::Yes)return;
   backup=deployPlugin(payload,plugin,root);
   complete=true;mode->hide();custom->hide();browse->hide();obsPath->hide();chooseOBS->hide();install->hide();launch->show();launchMode->show();updateText();
  }catch(const std::exception &e){QMessageBox::critical(this,"ASCII VISOR",l("InstallerError")+"\n"+QString::fromUtf8(e.what()));}
 }
public:
 void preview(const QString &directory){
  QDir().mkpath(directory);
  for(int i=0;i<languages->count();i++){
   languages->setCurrentIndex(i);QApplication::processEvents();
   grab().save(directory+"/"+languages->currentData().toString()+".png");
  }
 }
 explicit Setup(const QString &res):resources(res){
  all=QJsonDocument::fromJson(readFile(resources+"/locales.json")).object();
  setWindowTitle("ASCII VISOR · OBS Edition · Setup Preview");resize(720,500);
  setWindowIcon(QIcon(resources+"/installer-icon.png"));
  auto *layout=new QVBoxLayout(this);layout->setContentsMargins(26,24,26,20);layout->setSpacing(14);
  auto *top=new QHBoxLayout;heading=new QLabel;QFont font=heading->font();font.setPointSize(19);font.setBold(true);heading->setFont(font);heading->setWordWrap(true);top->addWidget(heading,1);
  logo=new QLabel;logo->setPixmap(QPixmap(resources+"/installer-icon.png").scaled(48,48,Qt::KeepAspectRatio,Qt::SmoothTransformation));top->addWidget(logo);
  languages=new QComboBox;const QStringList codes={"ru-RU","en-US","es-ES","pt-BR","de-DE","fr-FR","ja-JP","ko-KR","zh-CN","zh-TW"};
  for(const auto &c:codes)languages->addItem(QIcon(resources+"/flags/"+c+".png"),all[c].toObject()["Name"].toString(),c);
  QString system=QLocale::system().name();system.replace('_','-');
  if(system.startsWith("zh"))system=QLocale::system().script()==QLocale::TraditionalHanScript?"zh-TW":"zh-CN";
  int index=codes.indexOf(system);
  if(index<0)for(int i=0;i<codes.size();i++)if(codes[i].left(2)==system.left(2)){index=i;break;}
  if(index<0)index=1;
  languages->setCurrentIndex(index);code=codes[index];top->addWidget(languages);layout->addLayout(top);
  intro=new QLabel;intro->setWordWrap(true);layout->addWidget(intro);
  mode=new QComboBox;
#ifdef Q_OS_MACOS
  mode->addItem("OBS Studio · ~/Library","native");
#else
  mode->addItem("OBS Studio · Native / Steam","native");mode->addItem("OBS Studio · Flatpak","flatpak");
#endif
  mode->addItem("OBS Studio · …","custom");layout->addWidget(mode);
  auto *obsPick=new QHBoxLayout;obsPath=new QLineEdit;
#ifdef Q_OS_MACOS
  obsPath->setText(QFileInfo::exists("/Applications/OBS.app")?"/Applications/OBS.app":QDir::homePath()+"/Applications/OBS.app");
#else
  obsPath->setText(QStandardPaths::findExecutable("obs"));
#endif
  chooseOBS=new QPushButton("OBS…");obsPick->addWidget(obsPath);obsPick->addWidget(chooseOBS);layout->addLayout(obsPick);
  auto *pick=new QHBoxLayout;custom=new QLineEdit;custom->setPlaceholderText("OBS plugins directory");custom->setVisible(false);browse=new QPushButton("…");browse->setVisible(false);pick->addWidget(custom);pick->addWidget(browse);layout->addLayout(pick);
  detail=new QLabel;detail->setWordWrap(true);layout->addWidget(detail,1);license=new QLabel;license->setWordWrap(true);layout->addWidget(license);
  launch=new QCheckBox;launch->hide();layout->addWidget(launch);launchMode=new QComboBox;launchMode->hide();layout->addWidget(launchMode);
  auto *bottom=new QHBoxLayout;credits=new QLabel;credits->setWordWrap(true);credits->setStyleSheet("color:#777;font-size:11px");bottom->addWidget(credits,1);
  install=new QPushButton;cancel=new QPushButton;bottom->addWidget(install);bottom->addWidget(cancel);layout->addLayout(bottom);
  connect(languages,&QComboBox::currentIndexChanged,this,[this]{code=languages->currentData().toString();updateText();});
  connect(mode,&QComboBox::currentIndexChanged,this,[this]{bool c=mode->currentData().toString()=="custom";custom->setVisible(c);browse->setVisible(c);obsPath->setEnabled(mode->currentData().toString()!="flatpak");chooseOBS->setEnabled(obsPath->isEnabled());updateText();});
  connect(chooseOBS,&QPushButton::clicked,this,[this]{
#ifdef Q_OS_MACOS
   QString path=QFileDialog::getExistingDirectory(this,"OBS Studio","/Applications");
#else
   QString path=QFileDialog::getOpenFileName(this,"OBS Studio",QFileInfo(obsPath->text()).absolutePath());
#endif
   if(!path.isEmpty())obsPath->setText(path);
  });
  connect(custom,&QLineEdit::textChanged,this,[this]{updateText();});
  connect(browse,&QPushButton::clicked,this,[this]{auto p=QFileDialog::getExistingDirectory(this,l("Destination"),QDir::homePath());if(!p.isEmpty())custom->setText(p);});
  connect(install,&QPushButton::clicked,this,[this]{doInstall();});
  connect(cancel,&QPushButton::clicked,this,[this]{
   if(complete&&launch->isChecked()){
    bool started=false;
#ifdef Q_OS_MACOS
    started=QProcess::startDetached("/usr/bin/open",{"-a",selectedOBS});
#else
    if(mode->currentData().toString()=="flatpak")started=QProcess::startDetached("flatpak",{"run","com.obsproject.Studio"});
    else if(launchMode->currentData().toString()=="steam")started=QProcess::startDetached("steam",{"steam://run/1905180"});
    else started=QProcess::startDetached(selectedOBS,{});
#endif
    if(!started){QMessageBox::warning(this,"ASCII VISOR",l("LaunchError"));return;}
   }close();
  });updateText();
 }
};
static void testInstall(const QString &resources){
 QTemporaryDir sandbox;if(!sandbox.isValid())fail("Self-test cannot create temporary directory");
 const QString plugin=
#ifdef Q_OS_MACOS
 "ascii-visor.plugin";
#else
 "ascii-visor";
#endif
 const QString payload=resources+"/payload",root=sandbox.path()+"/plugins";
 if(!deployPlugin(payload,plugin,root).isEmpty())fail("Unexpected backup on first install");
 QFile sentinel(root+"/"+plugin+"/previous-version.txt");
 if(!sentinel.open(QIODevice::WriteOnly))fail("Cannot prepare upgrade fixture");sentinel.write("old version");sentinel.close();
 const QString backup=deployPlugin(payload,plugin,root);
 if(backup.isEmpty()||!QFileInfo::exists(backup+"/previous-version.txt")||QFileInfo::exists(root+"/"+plugin+"/previous-version.txt"))fail("Upgrade backup failed");
 const QString broken=sandbox.path()+"/broken-payload";
 if(!copyTree(payload,broken))fail("Cannot prepare checksum fixture");
 auto manifest=QJsonDocument::fromJson(readFile(broken+"/manifest.json")).array();
 QFile corrupt(broken+"/"+manifest.first().toObject()["path"].toString());
 if(!corrupt.open(QIODevice::Append))fail("Cannot modify checksum fixture");corrupt.write("tampered");corrupt.close();
 bool rejected=false;try{verifyPayload(broken);}catch(const std::exception &){rejected=true;}
 if(!rejected)fail("Corrupt payload was accepted");
 qInfo("Installer self-test: fresh install, upgrade backup and corrupt payload rejection PASS");
}
int main(int argc,char **argv){
 QApplication app(argc,argv);app.setStyle("Fusion");
 QString root=QCoreApplication::applicationDirPath();
#ifdef Q_OS_MACOS
 root=QDir(root+"/../Resources").absolutePath();
#endif
 const QString fontRoot=root+"/payload/"+
#ifdef Q_OS_MACOS
 "ascii-visor.plugin/Contents/Resources/fonts/";
#else
 "ascii-visor/data/fonts/";
#endif
 QFontDatabase::addApplicationFont(fontRoot+"NotoSansMonoCJKjp-Regular.otf");
 try{
  if(argc==2&&QString::fromLocal8Bit(argv[1])=="--self-test"){testInstall(root);return 0;}
  Setup window(root);window.show();
  if(argc==3&&QString::fromLocal8Bit(argv[1])=="--preview"){
   QTimer::singleShot(200,&app,[&]{window.preview(QString::fromLocal8Bit(argv[2]));app.quit();});
  }
  return app.exec();}
 catch(const std::exception &e){
  if(argc>1){qCritical("%s",e.what());return 1;}
  QMessageBox::critical(nullptr,"ASCII VISOR",QString::fromUtf8(e.what()));return 1;
 }
}
