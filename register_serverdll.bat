@echo off
regsvr32 "%~dp0\serverdll-build\debug\serverdll.dll"
"%SystemRoot%\SysWOW64\regsvr32" "%~dp0\serverdll-build\debug\serverdll.dll"
pause