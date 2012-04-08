#include <stdio.h>
#include "I2CCom.h"


JNIEXPORT void JNICALL Java_I2CCom_sendCommand
  (JNIEnv * env, jobject obj, jchar command, jchar amount)
{

	return;
}
JNIEXPORT jint JNICALL Java_I2CCom_getResponse
  (JNIEnv * env, jobject obj, jchar command)
{
	return (int)(command + 2);
}
