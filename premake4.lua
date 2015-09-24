-- A solution contains projects, and defines the available configurations
solution "Sorting"
	configurations { "Debug", "Release" }
	location "build"
 

	-- A project defines one build target
	project "cppbenchmark"
		location "build"
		kind "ConsoleApp"
		language "C++"
		files
		{
			"main.cpp",
			"sorting_algs.h"
		}
--		excludes { "" }
--		libdirs { "/usr/lib64/" }
--		includedirs { "./inc" }
		--links { "cunit" } 
		targetdir "build"

		configuration "Debug"
			defines { "DEBUG" }
			flags { "Symbols" }

		configuration "Release"
			defines { "NDEBUG" }
			flags { "Optimize" }

		configuration { "linux", "gmake" }
			buildoptions { "-pedantic" }

