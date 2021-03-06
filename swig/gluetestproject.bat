@echo off

set SWIG=..\tools\swigwin-3.0.2\swig
set OUT_INTERFACE=testproject.i

@echo %%module engine > %OUT_INTERFACE%
@echo %%{ >> %OUT_INTERFACE%

for /f "delims==" %%g in ('dir /s/b ..\coment\coment\*.h') do @echo #include "%%g" >> %OUT_INTERFACE%
for /f "delims==" %%g in ('dir /s/b ..\ca2d\*.h') do @echo #include "%%g" >> %OUT_INTERFACE%
for /f "delims==" %%g in ('dir /s/b ..\TestProject\*.h') do @echo #include "%%g" >> %OUT_INTERFACE%

@echo using namespace coment; >> %OUT_INTERFACE%
@echo using namespace ca2d; >> %OUT_INTERFACE%

@echo %%} >> %OUT_INTERFACE%

for /f "delims==" %%g in ('dir /s/b interface\*.i') do @echo %%include "%%g" >> %OUT_INTERFACE%

for /f "delims==" %%g in ('dir /s/b ..\coment\coment\*.h') do @echo %%include "%%g" >> %OUT_INTERFACE%
for /f "delims==" %%g in ('dir /s/b ..\ca2d\*.h') do @echo %%include "%%g" >> %OUT_INTERFACE%
for /f "delims==" %%g in ('dir /s/b ..\TestProject\*.h') do @echo %%include "%%g" >> %OUT_INTERFACE%

%SWIG% -c++ -lua %OUT_INTERFACE%

: hack to get lua_wrap.cxx working with lua c++ built libs
:@echo #include ^<lua.h^> >> temp.cxx
:@echo #include ^<lualib.h^> >> temp.cxx
:@echo #include ^<lauxlib.h^> >> temp.cxx

:type lua_wrap.cxx >> temp.cxx
:del lua_wrap.cxx
:ren temp.cxx lua_wrap.cxx