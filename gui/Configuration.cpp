#include <iostream>
#include "Configuration.h"

Configuration::Configuration()
{
	QDialog *dialog = new QDialog(this);
	QDialogButtonBox *buttonBox;
  QLabel *label;
  QCheckBox *checkBox;
    
  buttonBox = new QDialogButtonBox(dialog);
  buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
    
  label = new QLabel("Test",dialog);
  checkBox = new QCheckBox(dialog);
  
  QObject::connect(buttonBox, SIGNAL(accepted()), dialog, SLOT(accept()));
  QObject::connect(buttonBox, SIGNAL(rejected()), dialog, SLOT(reject()));
    
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
