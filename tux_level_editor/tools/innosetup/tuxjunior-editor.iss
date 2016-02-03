; $Id: tuxjunior-editor.iss 4825 2007-02-08 23:17:42Z anmaster $
;
; Before running this setup:
;  * Copy *.dll and *.pdb and *.exe from the Release bin dir (except Dock.dll and Dock.pdb) to the setup dir.
;      (Make sure to include SDL.dll and SDL_image.dll too!)
;  * Use svn export to create the data dir
;  * Create a file called COPYING.txt that contains the GPL2


#define MyAppName "TuxJunior Editor"
#define MyAppVer "0.4.0"
#define MyAppVerName "TuxJunior Editor 0.4.0"
#define MyAppMajVerName "TuxJunior Editor 0.4"
#define MyAppPublisher "TuxJunior Development Team"
#define MyAppURL "http://tuxjunior.lethargik.org"
#define MyAppBaseName "tuxjunior-editor"

[Setup]
AppName={#MyAppName}
AppVerName={#MyAppVerName}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={pf}\{#MyAppMajVerName}
DefaultGroupName={#MyAppMajVerName}
AllowNoIcons=true
VersionInfoVersion={#MyAppVer}
AppVersion={#MyAppVer}
LicenseFile=COPYING.txt
OutputBaseFilename={#MyAppBaseName}-{#MyAppVer}-win32-setup
Compression=lzma/ultra
SolidCompression=true
AppID={{5D880A65-B01D-4BE4-AC53-A2D21FE4BEF2}
ShowLanguageDialog=yes
DisableStartupPrompt=true
SetupIconFile={#MyAppBaseName}.ico
UninstallDisplayName={#MyAppVerName}

[Languages]
Name: english; MessagesFile: compiler:Default.isl

[Tasks]
Name: desktopicon; Description: {cm:CreateDesktopIcon}; GroupDescription: {cm:AdditionalIcons}; Flags: unchecked

[Files]
Source: {#MyAppBaseName}.exe; DestDir: {app}; Flags: ignoreversion
Source: *.dll; DestDir: {app}; Flags: ignoreversion
Source: data\*.*; DestDir: {app}\data\; Flags: ignoreversion recursesubdirs
Source: {#MyAppBaseName}.ico; DestDir: {app}; Flags: ignoreversion
Source: COPYING.txt; DestDir: {app}; Flags: ignoreversion
Source: *.pdb; DestDir: {app}; Flags: ignoreversion

[Icons]
Name: {group}\{#MyAppMajVerName}; Filename: {app}\{#MyAppBaseName}.exe
Name: {userdesktop}\{#MyAppMajVerName}; Filename: {app}\{#MyAppBaseName}.exe; Tasks: desktopicon

[Run]
Filename: {app}\{#MyAppBaseName}.exe; Description: {cm:LaunchProgram,{#MyAppName}}; Flags: nowait postinstall skipifsilent

[Code]
// This checks if another app that installed using Inno Setup is already installed.
function GetPathInstalled( AppID: String ): String;
var
	sPrevPath: String;
begin
	sPrevPath := '';
	if not RegQueryStringValue(HKLM,
	                           'Software\Microsoft\Windows\CurrentVersion\Uninstall\'+AppID+'_is1',
	                           'Inno Setup: App Path', sPrevpath) then
		RegQueryStringValue(HKCU, 'Software\Microsoft\Windows\CurrentVersion\Uninstall\'+AppID+'_is1' ,
		                    'Inno Setup: App Path', sPrevpath);

  Result := sPrevPath;
end;

const
	// AppID for TuxJunior, if you change it in the .iss for tuxjunior change here too!
	TuxJuniorID = '{4BEF4147-E17A-4848-BDC4-60A0AAC70F2A}';

// Global variable that will contain path to tuxjunior if tuxjunior was installed using Inno Setup
var
	TuxJuniorPath: String;

function InitializeSetup(): Boolean;
var
	ErrorCode: Integer;
	NetFrameWorkInstalled: Boolean;
	ResultNET: Boolean;
	ResultTuxJunior: Boolean;
begin
	// Check that .NET 2.0 is installed
	NetFrameWorkInstalled := RegKeyExists(HKLM,'SOFTWARE\Microsoft\.NETFramework\policy\v2.0');
	if NetFrameWorkInstalled = true then
	begin
		Result := true;
	end;
	if NetFrameWorkInstalled = false then
	begin
		ResultNET := MsgBox('{#MyAppVerName} requires the .NET 2.0 Framework. Please download and install the .NET 2.0 Framework and run this setup again. Do you want to download the framwork now?',
		                    mbConfirmation, MB_YESNO) = idYes;
		if ResultNET = false then
		begin
			Result := false;
		end
		else
		begin
			Result := false;
			ShellExec('open', 'http://download.microsoft.com/download/5/6/7/567758a3-759e-473e-bf8f-52154438565a/dotnetfx.exe','','',SW_SHOWNORMAL,ewNoWait,ErrorCode);
		end;
	end;
	//TODO: Check for GTK#

	// Check that TuxJunior is installed
	TuxJuniorPath := GetPathInstalled(TuxJuniorID);
	if (Length(TuxJuniorPath) = 0) then
	begin
		ResultTuxJunior := MsgBox('{#MyAppVerName} requires TuxJunior 0.4 to be installed. Are you sure you want to continue without installing TuxJunior-0.3?',
		                         mbConfirmation, MB_YESNO) = idYes;
		if ResultTuxJunior = false then
			Result := false;
	end;

end;
