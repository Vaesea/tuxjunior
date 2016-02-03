# Nullsoft Installer file
# for Tux Junior
# 
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
# (See COPYING.txt)
# 
# with a few tiny modifications by Phil Harper(philh@theopencd.org)
#


!define PKG_VERSION "SVN Developer Preview 0.0.4"
!define PKG_PREFIX  "tuxjunior"

!define APP_PREFIX  "TuxJunior"
!define APP_EXE     "${APP_PREFIX}.exe"
!define APP_NAME    "Tux Junior"


Name        "${APP_NAME}"

OutFile "${PKG_PREFIX}-${PKG_VERSION}-win32-installer.exe"


ShowInstDetails show

!include WinMessages.nsh

Page license
Page license "" "showLicense2"
Page license "" "showLicense3"
Page components
Page directory
Page instfiles


Caption     ""
CRCCheck    on
WindowIcon  off
BGGradient  off


# Default installation dir and registry key of install directory
InstallDir  "$PROGRAMFILES\${APP_PREFIX}"
InstallDirRegKey HKLM SOFTWARE\${APP_PREFIX} "Install_Dir"


ComponentText       "This will install ${APP_NAME} on your computer. Select which optional things you want installed."
DirText             "Choose a directory to install ${APP_NAME} in to:"
AllowRootDirInstall false

# Install page stuff
InstProgressFlags   smooth


LicenseText "Tux Junior Developer Preview - SVN 0.0.4"
LicenseData "GPL_license.txt"

Function showLicense2
  FindWindow $0 "#32770" "" $HWNDPARENT
  GetDlgItem $0 $0 1000
  SendMessage $0 ${WM_SETTEXT} 0 "STR:"
FileOpen $1 "Creative_Commons_License.txt" "r"
    loop1:
      FileRead $1 $2
      SendMessage $0 0x00C2 0 "STR:$2"
      IfErrors 0 loop1
    FileClose $1
    SendMessage $0 0x00B1 0 0
    SendMessage $0 0x00B7 0 0


FunctionEnd

Function showLicense3
  FindWindow $0 "#32770" "" $HWNDPARENT
  GetDlgItem $0 $0 1000
  SendMessage $0 ${WM_SETTEXT} 0 "STR:"
FileOpen $1 "OpenAL_license.txt" "r"
    loop1:
      FileRead $1 $2
      SendMessage $0 0x00C2 0 "STR:$2"
      IfErrors 0 loop1
    FileClose $1
    SendMessage $0 0x00B1 0 0
    SendMessage $0 0x00B7 0 0
FunctionEnd

Section
  SetOutPath $INSTDIR
  File "${APP_EXE}"
  File "*.dll"
  File "*.txt"
SetOutPath $INSTDIR\data
  File /r "data\*.*"
  WriteRegStr HKLM SOFTWARE\${APP_PREFIX} "Install_Dir" "$INSTDIR"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_PREFIX}" "DisplayName" "${APP_NAME} (remove only)"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_PREFIX}" "UninstallString" '"$INSTDIR\uninstall.exe"'
  WriteUninstaller "uninstall.exe"
SectionEnd


Section "Start Menu Shortcuts"
  SetOutPath $INSTDIR
  CreateDirectory "$SMPROGRAMS\${APP_NAME}"
  #CreateShortCut  "$SMPROGRAMS\${APP_NAME}\${APP_NAME} (Full Screen).lnk" "$INSTDIR\${APP_EXE}" "-f" "$INSTDIR\${APP_EXE}" 0 "" "" "Start Tux Junior in Fullscreen mode"
  #CreateShortCut  "$SMPROGRAMS\${APP_NAME}\${APP_NAME} (Windowed).lnk" "$INSTDIR\${APP_EXE}" "" "$INSTDIR\${APP_EXE}" 0 "" "" "Start Tux Junior in a Window"
  #CreateShortCut  "$SMPROGRAMS\${APP_NAME}\Readme.lnk" "$INSTDIR\docs\html\README.html" "" "$INSTDIR\docs\html\README.html" 0 "" "" "View ReadMe"
  CreateShortCut  "$SMPROGRAMS\${APP_NAME}\${APP_NAME} (Full Screen).lnk" "$INSTDIR\${APP_EXE}" "-f" "$INSTDIR\${APP_EXE}" 0 "" "" "Start Tux Junior in Fullscreen mode"
  CreateShortCut  "$SMPROGRAMS\${APP_NAME}\Licence.lnk" "$INSTDIR\docs\copying.txt" "" "$INSTDIR\docs\copying.txt" 0 "" "" "Read License"
  CreateShortCut  "$SMPROGRAMS\${APP_NAME}\Uninstall.lnk" "$INSTDIR\uninstall.exe" "" "$INSTDIR\uninstall.exe" 0 "" "" "Remove TuxJunior"
SectionEnd


Section "Desktop Shortcut"
  SetOutPath $INSTDIR
  CreateShortCut "$DESKTOP\${APP_NAME}.lnk" "$INSTDIR\${APP_EXE}" "" "$INSTDIR\${APP_EXE}" 0  "" "" "Play TuxJunior"
SectionEnd

; uninstall stuff

UninstallText "This will uninstall ${APP_NAME}. Hit 'Uninstall' to continue."

; special uninstall section.
Section "Uninstall"
  ; remove registry keys
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_PREFIX}"
  DeleteRegKey HKLM SOFTWARE\${APP_PREFIX}

  RMDir  /r "$INSTDIR\data"
  Delete    "$INSTDIR\*.*"

  Delete "$DESKTOP\${APP_NAME}.lnk"
  Delete "$SMPROGRAMS\${APP_NAME}\*.*"
  RMDir  "$SMPROGRAMS\${APP_NAME}"
SectionEnd
