<span style="font-size:18px;">@echo off  
set /p projectName=请输入项目名称：  
if "%projectName%"=="" goto inputError  
set /p packageName=请输入包标示名：  
if "%packageName%"=="" goto inputError  
set /p workspacePath=请输入工作空间地址：  
if "%workspacePath=%"=="" goto inputError  
cocos new %projectName% -p %packageName% -l cpp -d %workspacePath=%
pause  
exit  
:inputError  
@echo 项目名称或者包标示名或者工作空间地址不能为空！  
pause</span>  