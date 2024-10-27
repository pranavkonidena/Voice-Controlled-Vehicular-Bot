#ifndef MOTORSERVICE_H
#define MOTORSERVICE_H
#if defined __cplusplus
class motorService{
	public:
		void initService();
		void pwmSignal();
	  void moveForward(void);
	  void moveBackwards(void);
};
#endif
#endif