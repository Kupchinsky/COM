@echo off
regsvr32 /u "%~dp0\serverdll-extend-build\debug\serverdll-extend.dll"
"%SystemRoot%\SysWOW64\regsvr32" /u "%~dp0\serverdll-extend-build\debug\serverdll-extend.dll"
pause