@echo off
set launchpath=%~1
set launchroot=%~2
set version=%3
set slndir=%4
set sln=%~5
start "%launchpath%devenv" "%launchroot%project\%version%\%slndir%\%sln%\%sln%.sln"