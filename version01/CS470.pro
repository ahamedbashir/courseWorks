TEMPLATE    = app
TARGET      = CS470.skel
QT 	   += widgets printsupport opengl
RESOURCES   = CS470.qrc
CONFIG     += qt debug_and_release


Release:OBJECTS_DIR = release/.obj
Release:MOC_DIR     = release/.moc
Debug:OBJECTS_DIR   = debug/.obj
Debug:MOC_DIR       = debug/.moc

INCLUDEPATH 	+= . ./IP/header

win32-msvc2015{
	Release:DESTDIR  = release
	Debug:DESTDIR    = debug
	LIBS 		+= -L./IP/win/lib
	CONFIG(release, debug|release) {
		LIBS += -lIP
	} else {
		LIBS += -lIP_d 
	}
	LIBS 		+= -lopengl32
	QMAKE_CXXFLAGS	+= /MP /Zi
	QMAKE_LFLAGS	+= /MACHINE:X64
	RC_FILE		+= CS470.rc
}

macx{
	LIBS            += -L./IP/mac/lib
	CONFIG(release, debug|release) {
		LIBS += -lIP
	} else {
		LIBS += -lIP_d 
	}
	QMAKE_SONAME_PREFIX = @executable_path/../Frameworks
	QMAKE_LFLAGS   += -Wl,-rpath,@executable_path/../Frameworks
	QMAKE_LFLAGS   -= -mmacosx-version-min=10.8
	QMAKE_LFLAGS   += -mmacosx-version-min=10.9
	QMAKE_CXXFLAGS -= -mmacosx-version-min=10.8
	QMAKE_CXXFLAGS += -mmacosx-version-min=10.9
	QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.9
	ICON = CS470.icns
}

unix:!macx{
	CONFIG += C++11
	LIBS        += -L./IP/linux/lib
	CONFIG(release, debug|release) {
		LIBS += -lIP
	} else {
		LIBS += -lIP_d 
	}
}


# Input
HEADERS +=	MainWindow.h	\
		ImageFilter.h	\
		qcustomplot.h	\
		Dummy.h		\
		Threshold.h	\
		Clip.h		\
		Quantize.h	\
		Gamma.h		\
		Contrast.h	\
		HistoStretch.h	\
		HistoMatch.h	\
		ErrDiffusion.h	\
		Blur.h		\
		Sharpen.h	\
		Median.h	\
		GLWidget.h	\
		Convolve.h	\
		Spectrum.h	\
		Swap.h

		
SOURCES +=	main.cpp	\ 
		MainWindow.cpp 	\
		ImageFilter.cpp	\
		qcustomplot.cpp	\
		Dummy.cpp	\
		Threshold.cpp	\
		Clip.cpp	\
		Quantize.cpp	\
		Gamma.cpp	\
		Contrast.cpp	\
		HistoStretch.cpp\
		HistoMatch.cpp	\
		ErrDiffusion.cpp\
		Blur.cpp	\
		Sharpen.cpp	\
		Median.cpp	\
		GLWidget.cpp	\
		Convolve.cpp	\
		Spectrum.cpp	\
		Swap.cpp		
