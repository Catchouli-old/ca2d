@echo off

set SWIG=..\tools\swigwin-3.0.2\swig
set OUT_INTERFACE=sceneedit.i

@echo %%module engine > %OUT_INTERFACE%
@echo %%{ >> %OUT_INTERFACE%

for /f "delims==" %%g in ('dir /s/b ..\coment\coment\*.h') do @echo #include "%%g" >> %OUT_INTERFACE%
for /f "delims==" %%g in ('dir /s/b ..\ca2d\*.h') do @echo #include "%%g" >> %OUT_INTERFACE%
for /f "delims==" %%g in ('dir /s/b ..\SceneEdit\*.h') do @echo #include "%%g" >> %OUT_INTERFACE%

@echo using namespace coment; >> %OUT_INTERFACE%
@echo using namespace ca2d; >> %OUT_INTERFACE%

@echo %%} >> %OUT_INTERFACE%

for /f "delims==" %%g in ('dir /s/b interface\*.i') do @echo %%include "%%g" >> %OUT_INTERFACE%

for /f "delims==" %%g in ('dir /s/b ..\coment\coment\*.h') do @echo %%include "%%g" >> %OUT_INTERFACE%
for /f "delims==" %%g in ('dir /s/b ..\ca2d\*.h') do @echo %%include "%%g" >> %OUT_INTERFACE%
for /f "delims==" %%g in ('dir /s/b ..\SceneEdit\*.h') do @echo %%include "%%g" >> %OUT_INTERFACE%

%SWIG% -c++ -lua %OUT_INTERFACE%