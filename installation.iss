;  
#define   Name       "dinosaur"
;  
#define   Version    "1.0.0"
; 
#define   Publisher  "Anastasija Balashova"
;   
#define   URL        "https://vk.com/s.sstasya"
;   
#define   ExeName    "dinosaur.exe"

;------------------------------------------------------------------------------
;    
;------------------------------------------------------------------------------
[Setup]

;   , 
;  Tools -> Generate GUID
AppId={{0E6470C7-9892-49A5-A3D9-152D9A3B162E}

;  ,   
AppName={#Name}
AppVersion={#Version}
AppPublisher={#Publisher}
AppPublisherURL={#URL}
AppSupportURL={#URL}
AppUpdatesURL={#URL}

;   -
DefaultDirName={pf}\{#Name}
;     ""
DefaultGroupName={#Name}

; ,     setup    
OutputDir=C:\Users\Balas\dinosaur-project
OutputBaseFileName=dinosaur

;  
Compression=lzma
SolidCompression=yes

;------------------------------------------------------------------------------
;       
;------------------------------------------------------------------------------
[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"; LicenseFile: "License_ENG.txt"
Name: "russian"; MessagesFile: "compiler:Languages\Russian.isl"; LicenseFile: "License_RUS.txt"

;------------------------------------------------------------------------------
;    -  ,     
;------------------------------------------------------------------------------
[Tasks]
;     
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

;------------------------------------------------------------------------------
;   ,      
;------------------------------------------------------------------------------
[Files]

;  
Source: "C:\dino build\Release\dinosaur.exe"; DestDir: "{app}"; Flags: ignoreversion

;  
Source: "C:\Users\Balas\dinosaur-project\images\*"; DestDir: "{app}\images\"; Flags: ignoreversion recursesubdirs createallsubdirs


; VS Redistributable package
Source: "C:\Users\Balas\dinosaur-project\VC_redist.x64.exe"; DestDir: "{tmp}"; Flags: deleteafterinstall
;------------------------------------------------------------------------------
;    ,     
;------------------------------------------------------------------------------ 
[Icons]

Name: "{group}\{#Name}"; Filename: "{app}\{#ExeName}"

Name: "{commondesktop}\{#Name}"; Filename: "{app}\{#ExeName}"; Tasks: desktopicon

[Run]
;------------------------------------------------------------------------------
;      VS
;------------------------------------------------------------------------------
Filename: {tmp}\VC_redist.x64.exe; Parameters: "/q:a /c:""install /l /q"""; StatusMsg: VS redistributable package is installed. Please wait...
