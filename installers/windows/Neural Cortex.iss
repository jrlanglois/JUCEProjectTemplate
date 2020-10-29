[Setup]
AppName=Neural Cortex
AppVersion=0.8
DefaultDirName={pf}\Neural DSP
DefaultGroupName=Neural DSP
Compression=lzma2
SolidCompression=yes
OutputDir=.\
ArchitecturesInstallIn64BitMode=x64
OutputBaseFilename=Neural Cortex v0.8
SetupLogging=yes
AppPublisher=Neural DSP
AppPublisherURL=https://www.neuraldsp.com/
DisableWelcomePage=yes
DisableDirPage=yes
DisableProgramGroupPage=yes
DirExistsWarning=no
LicenseFile=..\resources\Neural_SOFTWARE LICENSE AGREEMENT.txt
WizardSmallImageFile=..\resources\LogoSmall.bmp

[Types]
Name: "full"; Description: "Full installation"
Name: "custom"; Description: "Custom installation"; Flags: iscustom

[Components]
Name: "vst2_64"; Description: "64-bit VST2 Plugin (.dll)"; Types: full custom; Check: Is64BitInstallMode;
Name: "vst3_64"; Description: "64-bit VST3 Plugin (.vst3)"; Types: full custom; Check: Is64BitInstallMode;
Name: "standalone_64"; Description: "64-bit Standalone (.exe)"; Types: full custom; Check: Is64BitInstallMode;
Name: "aax_64"; Description: "64-bit AAX Plugin (.aaxplugin)"; Types: full custom; Check: Is64BitInstallMode;

[Files]
; VST
Source: "bin\Neural Cortex.dll"; DestDir: {code:GetVST2Dir_64}; Check: Is64BitInstallMode; Components:vst2_64; Flags: ignoreversion;
; VST3
Source: "bin\Neural Cortex.vst3"; DestDir: {code:GetVST3Dir_64}; Check: Is64BitInstallMode; Components:vst3_64; Flags: ignoreversion;
; STANDALONE
Source: "bin\Neural Cortex.exe"; DestDir: {code:GetSTANDALONEDir_64}; Check: Is64BitInstallMode; Components:standalone_64; Flags: ignoreversion;
; AAX
Source: "bin\Neural Cortex.aaxplugin\*"; DestDir: "{code:GetAAXDir_64}\Neural Cortex.aaxplugin\"; Components:aax_64; Flags:ignoreversion createallsubdirs recursesubdirs;
Source: "bin\Neural Cortex.aaxplugin\desktop.ini"; DestDir: "{code:GetAAXDir_64}\Neural Cortex.aaxplugin"; Flags:ignoreversion; Attribs: hidden system; Check: Is64BitInstallMode; Components:aax_64;

;Source: "bin\Neural Cortex v1.0.0.pdf"; DestDir: "{pf}\Neural DSP\"

; Presets Factory
Source: "..\Resources\Presets\Default.xml"; DestDir: "{commonappdata}\Neural DSP\Neural Cortex\"

;create empty directories
[Dirs]
Name: "{commonappdata}\Neural DSP\Neural Cortex\Factory\"
Name: "{commonappdata}\Neural DSP\Neural Cortex\User\"
Name: "{commonappdata}\Neural DSP\Neural Cortex\Artists\"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon} (x64)"; GroupDescription: "{cm:AdditionalIcons}"; Components: "standalone_64"

[Icons]
Name: "{commondesktop}\Neural Cortex"; Filename: "{app}\Neural Cortex.EXE"; WorkingDir: "{app}"; Components: "standalone_64"
Name: "{group}\Neural Cortex"; Filename: "{app}\Neural Cortex.EXE"; WorkingDir: "{app}"; Components: "standalone_64"
Name: "{group}\Uninstall Neural Cortex"; Filename: "{pf}\Neural DSP\unins000.exe"; WorkingDir: "{pf}\Neural DSP\"

[Code]
var
  OkToCopyLog : Boolean;
  VST2DirPage_64: TInputDirWizardPage;
  VST3DirPage_64: TInputDirWizardPage;
  STANDALONEDirPage_64: TInputDirWizardPage;
  AAXDirPage_64: TInputDirWizardPage;
  index: Integer;
  i:  Integer;
  name: String;
 
function SkipEventVST64 (Sender: TWizardPage): Boolean;
begin
    Result := not IsComponentSelected('vst2_64');
end;

function SkipEventVST364 (Sender: TWizardPage): Boolean;
begin
    Result := not IsComponentSelected('vst3_64');
end;
 
function SkipEventSTANDALONE64 (Sender: TWizardPage): Boolean;
begin
    Result := not IsComponentSelected('standalone_64');
end;

function SkipEventAAX64 (Sender: TWizardPage): Boolean;
begin
    Result := not IsComponentSelected('aax_64');
end;


procedure InitializeWizard;
begin
  if IsWin64 then begin
    AAXDirPage_64 := CreateInputDirPage(wpSelectComponents,
        'Confirm 64-Bit AAX Plugin Directory', '',
        'Select the folder in which setup should install the 64-bit AAX Plugin, then click Next.',
        False, '');
    AAXDirPage_64.OnShouldSkipPage := @SkipEventAAX64;
    AAXDirPage_64.Add('');
    AAXDirPage_64.Values[0] := ExpandConstant('{pf}\Common Files\Avid\Audio\Plug-ins\');

    STANDALONEDirPage_64 := CreateInputDirPage(wpSelectComponents,
        'Confirm 64-Bit Standalone Directory', '',
        'Select the folder in which setup should install the 64-bit Standalone, then click Next.',
        False, '');
    STANDALONEDirPage_64.OnShouldSkipPage := @SkipEventSTANDALONE64;
    STANDALONEDirPage_64.Add('');
    STANDALONEDirPage_64.Values[0] := ExpandConstant('{pf}\Neural DSP\');

    VST2DirPage_64 := CreateInputDirPage(wpSelectComponents,
          'Confirm 64-Bit VST2 Plugin Directory', '',
          'Select the folder in which setup should install the 64-bit VST2 Plugin, then click Next.',
          False, '');
    VST2DirPage_64.OnShouldSkipPage := @SkipEventVST64;
    VST2DirPage_64.Add('');
    VST2DirPage_64.Values[0] := ExpandConstant('{reg:HKLM\SOFTWARE\VST,VSTPluginsPath|{pf}\Steinberg\VSTPlugins}\');

    VST3DirPage_64 := CreateInputDirPage(wpSelectComponents,
          'Confirm 64-Bit VST3 Plugin Directory', '',
          'Select the folder in which setup should install the 64-bit VST3 Plugin, then click Next.',
          False, '');
    VST3DirPage_64.OnShouldSkipPage := @SkipEventVST364;
    VST3DirPage_64.Add('');
    VST3DirPage_64.Values[0] := ExpandConstant('{pf}\Common Files\VST3\');
  end;
end;

function GetVST2Dir_64(Param: String): String;
begin
  Result := VST2DirPage_64.Values[0]
end;

function GetVST3Dir_64(Param: String): String;
begin
  Result := VST3DirPage_64.Values[0]
end;

function GetSTANDALONEDir_64(Param: String): String;
begin
  Result := STANDALONEDirPage_64.Values[0]
end;

function GetAAXDir_64(Param: String): String;
begin
  Result := AAXDirPage_64.Values[0]
end;

procedure CurStepChanged(CurStep: TSetupStep);
begin
  if CurStep = ssDone then
    OkToCopyLog := True;
end;

procedure DeinitializeSetup();
begin
  if OkToCopyLog then
    FileCopy (ExpandConstant ('{log}'), ExpandConstant ('{app}\InstallationLogFile.log'), FALSE);
  RestartReplace (ExpandConstant ('{log}'), '');
end;

[UninstallDelete]
Type: files; Name: "{app}\InstallationLogFile.log"