// ======================================================================
// IMPROC: Image Processing Software Package
// Copyright (C) 2017 by George Wolberg
//
// Swap.h - Swap widget
//
// Written by: George Wolberg, 2017
// ======================================================================

#ifndef SWAP_H
#define SWAP_H

#include "ImageFilter.h"

class Swap : public ImageFilter {
	Q_OBJECT

public:
	Swap			(QWidget *parent = 0);	// constructor
	QGroupBox*	controlPanel	();			// create control panel
	bool		applyFilter	(ImagePtr, bool, ImagePtr);	// apply filter to input
	void		swap	(ImagePtr, ImagePtr, ImagePtr, ImagePtr);
	void		initShader();
	void		gpuProgram(int pass);	// use GPU program to apply filter

protected slots:
	int		load		();

private:
	// widgets
	QPushButton*	m_button;	// Swap pushbutton
	QTextEdit*	m_values;	// text field for kernel values
	QGroupBox*	m_ctrlGrp;	// groupbox for panel

	// variables
	QString		m_file;
	QString		m_currentDir;
	ImagePtr	m_2ndImage;
	int		m_width;	// input image width
	int		m_height;	// input image height
};

#endif	// SWAP_H
