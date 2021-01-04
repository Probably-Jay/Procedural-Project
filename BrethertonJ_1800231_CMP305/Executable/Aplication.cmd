@echo off
REM
REM Launch both the main application thread and the audio thread, kill the audio thread after the main application quits
REM

REM Begin audio thread
start "audio" src\Audio.exe

REM Launch main application, suspend here 
src\Graphics.exe src\Graphics.exe

REM Main aplication quit, now kill audio thread
taskkill /IM Audio.exe /T /F


