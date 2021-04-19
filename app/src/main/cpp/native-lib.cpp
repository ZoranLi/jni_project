#include <jni.h>
#include <string>
#include "com_example_myapplication_MainActivity.h"
#include <android/log.h>//打印包 liblog 库 引入
#include <forward_list>

#define TAG "DERRY"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG,__VA_ARGS__);
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__);

//借助jni里边的宏自动填充

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_myapplication_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
/**
 * 函数的实现
 * 必须采用c的编译方式 看JNIENV内部源码 extern "C"
 * 无论是c还是c++ 都要调用 JNINativeInterface【c】
 * @return
 */
extern "C"
JNIEXPORT//标记该方法可以被外部调用【Vs不加 报错】 Linux 运行不加入
jstring //java ->native 转换用
JNICALL //代表是jni的标记，可以少
Java_com_example_myapplication_MainActivity_getStringPwd//Java包名_类名_函数名，包名_ 类名_1
        (JNIEnv *, jobject) {
//JNIEnv JNI ：桥梁，大概300多个函数，所有的jni函数都靠他
//jobject 谁调用就是谁的实例




}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_myapplication_MainActivity_getStringPwd2(JNIEnv *env, jclass clazz) {
    // TODO: implement getStringPwd2()
}extern "C"
JNIEXPORT void JNICALL
Java_com_example_myapplication_MainActivity_changeName(JNIEnv *env, jobject thiz) {
    jclass j_cls = env->GetObjectClass(thiz);
//    获取属性id
    jfieldID f_id = env->GetFieldID(j_cls, "name", "Ljava/lang/String;");

    jstring jstring1 = static_cast<jstring>(env->GetObjectField(thiz, f_id));

//    打印字符串
//    const char * c_str = static_cast<char *>(env->GetStringUTFChars(jstring1,NULL));

    const char *string = env->GetStringUTFChars(jstring1, NULL);
    LOGD("%s", string);
    //修改成

    jstring jName = env->NewStringUTF("Beyond");
    env->SetObjectField(thiz, f_id, jName);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_myapplication_MainActivity_changeAge(JNIEnv *env, jclass thiz) {
    jfieldID jfid = env->GetStaticFieldID(thiz, "age", "I");
    jint age = env->GetStaticIntField(thiz, jfid);
    age += 1;
    env->SetStaticIntField(thiz, jfid, age);
}

/**
 * 调用Java add方法
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_example_myapplication_MainActivity_callAddMethod(JNIEnv *env, jobject clazz) {
    jclass pJclass = env->GetObjectClass(clazz);
    jmethodID jd = env->GetMethodID(pJclass, "add", "(II)I");
    jint jint1 = env->CallIntMethod(clazz, jd, 2, 3);
    LOGD("%d", jint1);
}


/**jint int
 *jstring String
 * jintArray int[]
 * jobjectArray 引用类型对象 例如String[] Test[]
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_example_myapplication_MainActivity_testArrayAction(JNIEnv *env, jobject thiz, jint count,
                                                            jstring text_info, jintArray ints,
                                                            jobjectArray strs) {
    //基本数据类型 jint count jstring
    int countInt = count;//jint 本质是int
    LOGE("%d", countInt);

//    操作杆 --->jvm
    const char *textInfo = env->GetStringUTFChars(text_info, NULL);
    LOGE("%s", textInfo);

//    把int数组转成
    jint *jintArray = env->GetIntArrayElements(ints, NULL);
//    Java层数组的长度
    jsize siez = env->GetArrayLength(ints);
    for (int i = 0; i < siez; ++i) {
        *(jintArray + i) += 100;
        LOGE("%d", *(jintArray) + i);//无法控制Java的数组
    }

//    操纵杆 刷到
    /**
     * 0 刷新Java数组，并释放C++层数组，
     * JNI_COMMIT：只提交 只刷新Java数组，不释放C++层数据
     * JNI_ABORT： 只释放c++层数组
     */
    env->ReleaseIntArrayElements(ints, jintArray, 0);


//    jobjectArray 代表Java的引用类型数组

    jsize length = env->GetArrayLength(strs);
    for (int i = 0; i <length; i++) {
        jstring pJstring = static_cast<jstring>(env->GetObjectArrayElement(strs, i));
        const char *jobJcharp = env->GetStringUTFChars(pJstring, NULL);
        LOGE("%d", jobJcharp);//
        //释放jstring
        env->ReleaseStringUTFChars(pJstring,jobJcharp);
    }

//    env->FindClass("com/")
    //    env->GetObjectClass(student);
//    env->GetMethodID(studentClass,"setName","Ljava/lang/String");

}