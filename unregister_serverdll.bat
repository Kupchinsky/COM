@echo off
regsvr32 /u "%~dp0\serverdll-build\debug\serverdll.dll"
"%SystemRoot%\SysWOW64\regsvr32" /u "%~dp0\serverdll-build\debug\serverdll.dll"
pause