@echo off
if "%~1" == "" (
	start "" "%~dp0\runtime\bin\javaw" -jar "%~dp0\bspsrc.jar" %*
) else (
	"%~dp0\runtime\bin\java" -jar "%~dp0\bspsrc.jar" %*
)