@echo off
call Dependencies\premake\bin\premake5.exe vs2022
if %ERRORLEVEL% NEQ 0 (
	PAUSE
)