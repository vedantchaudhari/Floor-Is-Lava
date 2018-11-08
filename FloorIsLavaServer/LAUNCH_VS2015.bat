@echo off
set EGP_NET_FW=%~dp0
call "%EGP_NET_FW%\utility\win\dev\egp_win_launch.bat" "%VS140COMNTOOLS%..\IDE\" "%EGP_NET_FW%" VS2015 _SLN "EGP Networking Base FW"