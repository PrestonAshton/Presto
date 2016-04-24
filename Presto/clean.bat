@echo off
del presto-x64*.* /s
del presto-x32*.* /s
del engine.lib /s
del engine.ilk /s
del engine.pdb /s
del engine.dll /s
del client*.* /s
del server*.* /s
del *.idb /s
del *.pdb /s
del *.obj /s
del *.vcproj /s
del *.sln /s
del *.vcxproj* /s
rmdir "game/build/bin32" /s /q
rmdir "game/build/bin64" /s /q
rmdir "game/build/template/bin32" /s /q
rmdir "game/build/template/bin64" /s /q
rmdir "engine/engine/obj32" /s /q
rmdir "engine/engine/obj64" /s /q
rmdir "engine/launcher/obj32" /s /q
rmdir "engine/launcher/obj64" /s /q
rmdir "game/src/client/Template/obj32" /s /q
rmdir "game/src/client/Template/obj64" /s /q