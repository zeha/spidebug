@echo off
:
set OBJ_DMP="%ProgramFiles(x86)%\Microchip\xc32\v1.11\bin"
SET PROJECT=I:\PROJEKTE\GMBH\spi_debug\sw\SPI_Debug_1.X\dist\default
:
echo Path to Object-Dump: %OBJ_DMP%
echo path to Project....: %PROJECT%
echo.
echo Dump / Dissasemble project ....
echo.
if exist "%PROJECT%\production\SPI_Debug_1.X.production.elf" (
   %OBJ_DMP%\xc32-objdump.exe -d -l -S "%PROJECT%\production\SPI_Debug_1.X.production.elf" > "%PROJECT%\production\SPI_Debug_1.X.production.txt"
   echo Warnig: Production Build, no Source Code insterted!
   echo Dump File: "%PROJECT%\SPI_Debug_1.X.production.txt"
) else (
  %OBJ_DMP%\xc32-objdump.exe -d -l -S "%PROJECT%\debug\SPI_Debug_1.X.debug.elf" > "%PROJECT%\debug\SPI_Debug_1.X.debug.txt"
  echo Dump File: "%PROJECT%\debug\SPI_Debug_1.X.debug.txt"
)
echo.
pause