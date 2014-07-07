##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=Liero3D
ConfigurationName      :=Debug
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "/home/xerox/.codelite/Irrlicht"
ProjectPath            := "/home/xerox/Programmierung/Projekte/Liero3D"
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Xerox
Date                   :=07/07/14
CodeLitePath           :="/home/xerox/.codelite"
LinkerName             :=g++
ArchiveTool            :=ar rcus
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
CompilerName           :=g++
C_CompilerName         :=gcc
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
MakeDirCommand         :=mkdir -p
CmpOptions             := -g -Wall -std=c++0x -DBOOST_ALL_DYN_LINK  $(Preprocessors)
LinkOptions            :=  -Wl,-rpath,/home/xerox/Programmierung/Bibliotheken/Build/lib
IncludePath            :=  "$(IncludeSwitch)." "$(IncludeSwitch)." "$(IncludeSwitch)/home/xerox/Programmierung/Bibliotheken/Build/include" 
RcIncludePath          :=
Libs                   :=$(LibrarySwitch)Irrlicht $(LibrarySwitch)GL $(LibrarySwitch)Xxf86vm $(LibrarySwitch)X11 $(LibrarySwitch)Xcursor $(LibrarySwitch)boost_thread $(LibrarySwitch)boost_filesystem $(LibrarySwitch)boost_system $(LibrarySwitch)boost_unit_test_framework $(LibrarySwitch)boost_log_setup $(LibrarySwitch)boost_log 
LibPath                := "$(LibraryPathSwitch)." "$(LibraryPathSwitch)/usr/lib" "$(LibraryPathSwitch)/home/xerox/Programmierung/Bibliotheken/Build/lib" 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects=$(IntermediateDirectory)/source_utilities$(ObjectSuffix) $(IntermediateDirectory)/source_config$(ObjectSuffix) $(IntermediateDirectory)/source_unit_test$(ObjectSuffix) $(IntermediateDirectory)/source_messagehub$(ObjectSuffix) 

##
## Main Build Targets 
##
all: $(OutputFile)

$(OutputFile): makeDirStep $(Objects)
	@$(MakeDirCommand) $(@D)
	$(LinkerName) $(OutputSwitch)$(OutputFile) $(Objects) $(LibPath) $(Libs) $(LinkOptions)

makeDirStep:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/source_utilities$(ObjectSuffix): source/utilities.cpp $(IntermediateDirectory)/source_utilities$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/xerox/Programmierung/Projekte/Liero3D/source/utilities.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/source_utilities$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/source_utilities$(DependSuffix): source/utilities.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/source_utilities$(ObjectSuffix) -MF$(IntermediateDirectory)/source_utilities$(DependSuffix) -MM "/home/xerox/Programmierung/Projekte/Liero3D/source/utilities.cpp"

$(IntermediateDirectory)/source_utilities$(PreprocessSuffix): source/utilities.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/source_utilities$(PreprocessSuffix) "/home/xerox/Programmierung/Projekte/Liero3D/source/utilities.cpp"

$(IntermediateDirectory)/source_config$(ObjectSuffix): source/config.cpp $(IntermediateDirectory)/source_config$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/xerox/Programmierung/Projekte/Liero3D/source/config.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/source_config$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/source_config$(DependSuffix): source/config.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/source_config$(ObjectSuffix) -MF$(IntermediateDirectory)/source_config$(DependSuffix) -MM "/home/xerox/Programmierung/Projekte/Liero3D/source/config.cpp"

$(IntermediateDirectory)/source_config$(PreprocessSuffix): source/config.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/source_config$(PreprocessSuffix) "/home/xerox/Programmierung/Projekte/Liero3D/source/config.cpp"

$(IntermediateDirectory)/source_unit_test$(ObjectSuffix): source/unit_test.cpp $(IntermediateDirectory)/source_unit_test$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/xerox/Programmierung/Projekte/Liero3D/source/unit_test.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/source_unit_test$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/source_unit_test$(DependSuffix): source/unit_test.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/source_unit_test$(ObjectSuffix) -MF$(IntermediateDirectory)/source_unit_test$(DependSuffix) -MM "/home/xerox/Programmierung/Projekte/Liero3D/source/unit_test.cpp"

$(IntermediateDirectory)/source_unit_test$(PreprocessSuffix): source/unit_test.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/source_unit_test$(PreprocessSuffix) "/home/xerox/Programmierung/Projekte/Liero3D/source/unit_test.cpp"

$(IntermediateDirectory)/source_messagehub$(ObjectSuffix): source/messagehub.cpp $(IntermediateDirectory)/source_messagehub$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/xerox/Programmierung/Projekte/Liero3D/source/messagehub.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/source_messagehub$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/source_messagehub$(DependSuffix): source/messagehub.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/source_messagehub$(ObjectSuffix) -MF$(IntermediateDirectory)/source_messagehub$(DependSuffix) -MM "/home/xerox/Programmierung/Projekte/Liero3D/source/messagehub.cpp"

$(IntermediateDirectory)/source_messagehub$(PreprocessSuffix): source/messagehub.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/source_messagehub$(PreprocessSuffix) "/home/xerox/Programmierung/Projekte/Liero3D/source/messagehub.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/source_utilities$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/source_utilities$(DependSuffix)
	$(RM) $(IntermediateDirectory)/source_utilities$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/source_config$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/source_config$(DependSuffix)
	$(RM) $(IntermediateDirectory)/source_config$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/source_unit_test$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/source_unit_test$(DependSuffix)
	$(RM) $(IntermediateDirectory)/source_unit_test$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/source_messagehub$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/source_messagehub$(DependSuffix)
	$(RM) $(IntermediateDirectory)/source_messagehub$(PreprocessSuffix)
	$(RM) $(OutputFile)


