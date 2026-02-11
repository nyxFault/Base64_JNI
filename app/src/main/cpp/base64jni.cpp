// Write C++ code here.
//
// Do not forget to dynamically load the C++ library into your application.
//
// For instance,
//
// In MainActivity.java:
//    static {
//       System.loadLibrary("base64jni");
//    }
//
// Or, in MainActivity.kt:
//    companion object {
//      init {
//         System.loadLibrary("base64jni")
//      }
//    }

/***********************************************************
* Base64 library implementation                            *
* @author Ahmed Elzoughby                                  *
* @date July 23, 2017                                      *
***********************************************************/

#include "base64.h"
#include <jni.h>


char base46_map[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                     'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                     'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                     'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};


char* base64_encode(char* plain) {

    char counts = 0;
    char buffer[3];
    char* cipher = static_cast<char *>(malloc(strlen(plain) * 4 / 3 + 4));
    int i = 0, c = 0;

    for(i = 0; plain[i] != '\0'; i++) {
        buffer[counts++] = plain[i];
        if(counts == 3) {
            cipher[c++] = base46_map[buffer[0] >> 2];
            cipher[c++] = base46_map[((buffer[0] & 0x03) << 4) + (buffer[1] >> 4)];
            cipher[c++] = base46_map[((buffer[1] & 0x0f) << 2) + (buffer[2] >> 6)];
            cipher[c++] = base46_map[buffer[2] & 0x3f];
            counts = 0;
        }
    }

    if(counts > 0) {
        cipher[c++] = base46_map[buffer[0] >> 2];
        if(counts == 1) {
            cipher[c++] = base46_map[(buffer[0] & 0x03) << 4];
            cipher[c++] = '=';
        } else {                      // if counts == 2
            cipher[c++] = base46_map[((buffer[0] & 0x03) << 4) + (buffer[1] >> 4)];
            cipher[c++] = base46_map[(buffer[1] & 0x0f) << 2];
        }
        cipher[c++] = '=';
    }

    cipher[c] = '\0';   /* string padding character */
    return cipher;
}


char* base64_decode(char* cipher) {

    char counts = 0;
    char buffer[4];
    char* plain = static_cast<char *>(malloc(strlen(cipher) * 3 / 4));
    int i = 0, p = 0;

    for(i = 0; cipher[i] != '\0'; i++) {
        char k;
        for(k = 0 ; k < 64 && base46_map[k] != cipher[i]; k++);
        buffer[counts++] = k;
        if(counts == 4) {
            plain[p++] = (buffer[0] << 2) + (buffer[1] >> 4);
            if(buffer[2] != 64)
                plain[p++] = (buffer[1] << 4) + (buffer[2] >> 2);
            if(buffer[3] != 64)
                plain[p++] = (buffer[2] << 6) + buffer[3];
            counts = 0;
        }
    }

    plain[p] = '\0';    /* string padding character */
    return plain;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_base64jni_MainActivity_b64Encode(JNIEnv *env, jobject thiz, jstring input) {
    // TODO: implement b64Encode()
    // Convert jstring -> C string
    const char* inputStr = env->GetStringUTFChars(input, nullptr);
    // Call your base64 encode
    char* encoded = base64_encode((char*)inputStr);
    // Create Java string
    jstring result = env->NewStringUTF(encoded);
    // Cleanup
    env->ReleaseStringUTFChars(input, inputStr);
    free(encoded);

    return result;

}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_base64jni_MainActivity_b64Decode(JNIEnv *env, jobject thiz, jstring input) {
    // TODO: implement b64Decode()
    // Convert jstring -> C string
    const char* inputStr = env->GetStringUTFChars(input, nullptr);

    // Call your base64 decode
    char* decoded = base64_decode((char*)inputStr);

    // Create Java string
    jstring result = env->NewStringUTF(decoded);

    // Cleanup
    env->ReleaseStringUTFChars(input, inputStr);
    free(decoded);

    return result;
}