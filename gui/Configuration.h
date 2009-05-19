#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QtGui>

class Configuration : public QWidget
{
 Q_OBJECT

	public:
		Configuration();
		
	private slots:
		void accept();
		void reject();
	    
	   
};


#endif
