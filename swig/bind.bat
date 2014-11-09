@echo off
Setlocal EnableDelayedExpansion
set OBJS=test

set PROFILE=Release
set PLATFORM=Win32

set OPTIONS=

if "%PROFILE%"=="Debug" set OPTIONS=/MDd
if "%PROFILE%"=="Release" set OPTIONS=/MT

if exist tmp del tmp
for /f "tokens=*" %%a in ('dir /s/b ..\obj\ca2d\%PLATFORM%\%PROFILE%\*.obj') do <nul set /p =%%a >> tmp
for /f "tokens=*" %%a in ('dir /s/b ..\obj\TestProject\%PLATFORM%\%PROFILE%\*.obj') do <nul set /p =%%a >> tmp
set /p OBJS=<tmp

call glue

cl.exe lua_wrap.cxx -I..\dep\include /c /EHsc %OPTIONS%

cl.exe /D_USRDLL /D_WINDLL -I..\dep\include lua_wrap.obj %OBJS% /link /DLL /OUT:engine.dll /DYNAMICBASE "lua52.lib" "SDL.lib" "SDL_image.lib" "SDLmain.lib" "glew32.lib" "opengl32.lib" "kernel32.lib" "user32.lib" "gdi32.lib" "winspool.lib" "comdlg32.lib" "advapi32.lib" "shell32.lib" "ole32.lib" "oleaut32.lib" "uuid.lib" "odbc32.lib" "odbccp32.lib" /LIBPATH:"C:\Projects\VS\ca2d\dep/lib/%PLATFORM%" /TLBID:1 /FORCE

echo copying engine.dll to dist directory

copy engine.dll ..\dist /y

echo done!