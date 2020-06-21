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
		links { "m" }
		targetdir "build"

		configuration "Debug"
			defines { "DEBUG" }
			symbols "On"

		configuration "Release"
			defines { "NDEBUG" }
			optimize "On"

		configuration { "linux", "gmake" }
			buildoptions { "-pedantic" }

	project "benchmark"
		location "build"
		kind "ConsoleApp"
		language "C"
		files
		{
			"main.c",
			"sorting_algs.h"
		}
--		excludes { "" }
--		libdirs { "/usr/lib64/" }
--		includedirs { "./inc" }
		links { "m" }
		targetdir "build"

		configuration "Debug"
			defines { "DEBUG" }
			symbols "On"

		configuration "Release"
			defines { "NDEBUG" }
			optimize "On"

		configuration { "linux", "gmake" }
			buildoptions { "-std=c99", "-pedantic" }

