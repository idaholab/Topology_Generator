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
