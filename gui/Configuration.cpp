/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2009 Pierre Weiss <3weissp@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 * 
 */
/**
* \file Configuration.cpp
* \brief The GUI configuration file.
* \author Pierre Weiss
* \date 2009
*/

#include <iostream>

#include "Configuration.h"

Configuration::Configuration()
{
	QDialog *dialog = new QDialog(this);
	dialog->setWindowTitle("Configuration");

	/* Layout*/
	QGridLayout *layout = new QGridLayout;

	/* button ok and close */
  QDialogButtonBox *buttonBox;
  buttonBox = new QDialogButtonBox(dialog);
  buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
  QObject::connect(buttonBox, SIGNAL(accepted()), dialog, SLOT(accept()));
  QObject::connect(buttonBox, SIGNAL(rejected()), dialog, SLOT(reject()));
    
  /* choose 1 */
  QLabel *label1;
  label1 = new QLabel("Option 1",dialog);
  layout->addWidget(label1, 0, 0);
    
  QCheckBox *checkBox1;
  checkBox1 = new QCheckBox(dialog);
  layout->addWidget(checkBox1, 0, 1);
    
  /* choose 2 */
  QLabel *label2;
  label2 = new QLabel("Option 2",dialog);
  layout->addWidget(label2, 1, 0);
    
  QCheckBox *checkBox2;
  checkBox2 = new QCheckBox(dialog);
  layout->addWidget(checkBox2, 1, 1);
  
	/* add button ok and close to the bottom */
	layout->addWidget(buttonBox, 3, 2);
    
  dialog->setLayout(layout);
  dialog->exec();
}

void Configuration::accept()
{
	std::cout << "accept" << std::endl;
}

void Configuration::reject()
{
	std::cout << "reject" << std::endl;
}
