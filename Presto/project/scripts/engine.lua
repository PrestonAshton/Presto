workspace(gamename)
	filename(gamename)
	location("../../")
	configurations { "Debug", "Release" }
	platforms { "x64", "x86" }

project "Engine (Engine)"
	kind "SharedLib"
	filename("engine")
	language "C"
	location("../../engine/engine/")
	dependson { "pstdlib (Engine)" }
	
	if steam then
		includedirs 
		{ 
			"../../engine/engine/include/",
			"../../engine/pstdlib/include/",
			"../../extern/steamworks/public/steam"
		}
	else
		includedirs 
		{ 
			"../../engine/engine/include/",
			"../../engine/pstdlib/include/",
		}
	end
	
	files { "../../engine/engine/src/UnityBuild.c" }
	
	filter "configurations:Debug"
		if steam then
			defines { "DEBUG", "_DEBUG", "PRESTO_EXPORTS", "PRESTO_BUILD_NUMBER=$(BuildNumber)", "PRESTO_STEAM" }
		else
			defines { "DEBUG", "_DEBUG", "PRESTO_EXPORTS", "PRESTO_BUILD_NUMBER=$(BuildNumber)" }
		end
		flags { "Symbols" }

	filter "configurations:Release"
		if steam then
			defines { "NDEBUG", "PRESTO_EXPORTS", "PRESTO_BUILD_NUMBER=$(BuildNumber)", "PRESTO_STEAM" }
		else
			defines { "NDEBUG", "PRESTO_EXPORTS", "PRESTO_BUILD_NUMBER=$(BuildNumber)" }
		end
		optimize "On"
		
	filter "platforms:x86"
		targetname "engine"
		if steam then
			links { "pstdlib" }
		else
			links { "pstdlib" }
		end
		if steam then
			libdirs   {"../../game/build/bin32", "../../extern/steamworks/redistributable_bin"}
		else
			libdirs   {"../../game/build/bin32"}
		end
		implibdir ("../../game/build/bin32")
		targetdir ("../../game/build/bin32")
		objdir     "../../engine/engine/obj32"
	filter "platforms:x64"
		targetname "engine"
		if steam then
			links { "pstdlib" }
		else
			links { "pstdlib" }
		end
		if steam then
			libdirs   {"../../game/build/bin64", "../../extern/steamworks/redistributable_bin/win64"}
		else
			libdirs   {"../../game/build/bin64"}
		end
		implibdir ("../../game/build/bin64")
		targetdir ("../../game/build/bin64")
		objdir     "../../engine/engine/obj64"
		
project "Launcher (Engine)"
	kind "WindowedApp"
	filename("launcher")
	language "C"
	location("../../engine/launcher/")
	flags { "WinMain" }
	dependson("Engine (Engine)")
	
	includedirs 
	{ 
		"../../engine/engine/include/",
		"../../engine/pstdlib/include/",
	}
	
	files { "../../engine/launcher/src/UnityBuild.c" }
	
	filter "configurations:Debug"
		defines { "DEBUG", "_DEBUG", "PRESTO_BUILD_NUMBER=$(BuildNumber)" }
		flags { "Symbols" }

	filter "configurations:Release"
		defines { "NDEBUG", "PRESTO_BUILD_NUMBER=$(BuildNumber)" }
		optimize "On"
		
	filter "platforms:x86"
		targetname("presto-x32")
		libdirs   {"../../game/build"}
		implibdir ("../../game/build")
		targetdir ("../../game/build")
		objdir     "../../engine/launcher/obj32"
	filter "platforms:x64"
		targetname("presto-x64")
		libdirs   {"../../game/build"}
		implibdir ("../../game/build")
		targetdir ("../../game/build")
		objdir     "../../engine/launcher/obj64"
		
project("Client ("..gamename..")")
	kind "SharedLib"
	filename("client_"..gamename:lower())
	language "C"
	location("../../game/src/client")
	dependson { "pstdlib (Engine)" }
	
	includedirs 
	{ 
		"../../engine/engine/include/",
		"../../engine/pstdlib/include/",
	}
	
	files { "../../game/src/client/"..gamename.."/UnityBuild.c" }
	
	filter "configurations:Debug"
		defines { "DEBUG", "_DEBUG" }
		flags { "Symbols" }

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"
		
	filter "platforms:x86"
		targetname("client")
		libdirs   {"../../game/build/"..gamename:lower().."/bin32"}
		implibdir ("../../game/build/"..gamename:lower().."/bin32")
		targetdir ("../../game/build/"..gamename:lower().."/bin32")
		objdir    ("../../game/src/client/"..gamename.."/obj32")
	filter "platforms:x64"
		targetname("client")
		libdirs   {"../../game/build/"..gamename:lower().."/bin64"}
		implibdir ("../../game/build/"..gamename:lower().."/bin64")
		targetdir ("../../game/build/"..gamename:lower().."/bin64")
		objdir    ("../../game/src/client/"..gamename.."/obj64")
		
project("pstdlib (Engine)")
	kind "SharedLib"
	filename("pstdlib")
	language "C"
	location("../../engine/pstdlib")
	
	includedirs 
	{ 
		"../../engine/pstdlib/include/",
	}
	
	files { "../../engine/pstdlib/src/UnityBuild.c" }
	
	filter "configurations:Debug"
		defines { "DEBUG", "_DEBUG", "PSTDLIB_EXPORTS", "PRESTO_BUILD_NUMBER=$(BuildNumber)" }
		flags { "Symbols" }

	filter "configurations:Release"
		defines { "NDEBUG", "PSTDLIB_EXPORTS", "PRESTO_BUILD_NUMBER=$(BuildNumber)" }
		optimize "On"
		
	filter "platforms:x86"
		targetname("pstdlib")
		libdirs   {"../../game/build/bin32"}
		implibdir ("../../game/build/bin32")
		targetdir ("../../game/build/bin32")
		objdir    ("../../engine/pstdlib/src/obj32")
	filter "platforms:x64"
		targetname("pstdlib")
		libdirs   {"../../game/build/bin64"}
		implibdir ("../../game/build/bin64")
		targetdir ("../../game/build/bin64")
		objdir    ("../../engine/pstdlib/src/bin64")
		
--[[project("Preprocessor (Engine)")
	kind "SharedLib"
	filename("client_"..gamename:lower())
	language "C"
	location("../../game/src/client")
	
	includedirs 
	{ 
		"../../engine/engine/include/",
	}
	
	files { "../../game/src/client/"..gamename.."/UnityBuild.c" }
	
	filter "configurations:Debug"
		defines { "DEBUG", "_DEBUG" }
		flags { "Symbols" }

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"
		
	filter "platforms:x86"
		targetname("client")
		libdirs   {"../../game/build/"..gamename:lower().."/bin32"}
		implibdir ("../../game/build/"..gamename:lower().."/bin32")
		targetdir ("../../game/build/"..gamename:lower().."/bin32")
		objdir    ("../../game/src/client/"..gamename.."/obj32")
	filter "platforms:x64"
		targetname("client")
		libdirs   {"../../game/build/"..gamename:lower().."/bin64"}
		implibdir ("../../game/build/"..gamename:lower().."/bin64")
		targetdir ("../../game/build/"..gamename:lower().."/bin64")
		objdir    ("../../game/src/client/"..gamename.."/obj64")]]--