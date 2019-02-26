// ======================================================================
// IMPROC: Image Processing Software Package
// Copyright (C) 2017 by George Wolberg
//
// Dummy.h - Header for dummy control panel
//
// Written by: George Wolberg, 2017
// ======================================================================

#ifndef DUMMY_H
#define DUMMY_H

#include "ImageFilter.h"


//////////////////////////////////////////////////////////////////////////
///
/// \class Dummy
/// \brief Blank Panel widget .
///
//////////////////////////////////////////////////////////////////////////

class Dummy : public ImageFilter {
	Q_OBJECT

public:
	Dummy		(QWidget *parent = 0);		// constructor
	QGroupBox*	controlPanel();			// create control panel
	void		initShader();
	void		gpuProgram(int pass);		// use GPU program to apply filter

private:
	// widgets and groupbox
	QGroupBox*	m_ctrlGrp;			// groupbox for panel
};


#endif	// DUMMY_H
