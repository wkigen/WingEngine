#ifndef _WING_CORE_MAIN_H_
#define _WING_CORE_MAIN_H_


#define WING_MAIN(app)	void WingMain(){	\
							app application;\
							application.create();	\
							application.init();	\
							application.run();		\
							application.clear();	\
							application.destroy();	\
						}

#endif