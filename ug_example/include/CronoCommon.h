#ifndef __CRONO_COMMON_H__
#define __CRONO_COMMON_H__

#include "assert.h"
#include <vector>
#include <string>

#if (defined(DEBUG) || defined(_DEBUG)) && (defined(_WIN32))
#define assertmsg(_Expression, _msg)                                           \
        (void)((!!(_Expression)) ||                                            \
               (_wassert(_CRT_WIDE(#_msg), _CRT_WIDE(__FILE__), __LINE__), 0))
#else
#define assertmsg(_Expression, _msg)
#endif

#define DebugAssert(x, y) assert(x)

#ifdef __linux__
#include <string>
#include <unistd.h>
#define __stdcall
#define _snprintf_s(a, b, c, ...) snprintf(a, b, __VA_ARGS__)
#endif //#ifdef __linux__

#include <stdint.h>
typedef uint8_t uint8;
typedef int16_t int16;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

// computes the minimum of the array
template <class T> T amin(T *arr, int size) {
        int res = arr[0];
        for (int i = 1; i < size; i++) {
                if (arr[i] < res) {
                        res = arr[i];
                }
        }
        return res;
}

// computes the max of the array
template <class T> T amax(T *arr, int size) {
        int res = arr[0];
        for (int i = 1; i < size; i++) {
                if (arr[i] > res) {
                        res = arr[i];
                }
        }
        return res;
}

class crono_exception : public std::exception {
      private:
        std::string text;

      public:
        crono_exception(const char *st) { text = st; }
        virtual ~crono_exception() throw(){};
        virtual const char *what() { return text.c_str(); };
};

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#define crono_sleep(x) Sleep(x)
#else
#define crono_sleep(x) usleep(1000 * x)
#endif

#ifdef __linux__
/**
 * Return Error Code `error_code` if value `value_to_validate` is NULL
 *
 * @param value_to_validate[in]: value to be validated, mostly a pointer.
 * @param error_code[in]: error code to be returned.
 */
#define CRONO_RET_ERR_CODE_IF_NULL(value_to_validate, error_code)              \
        if (NULL == (value_to_validate)) {                                     \
                return error_code;                                             \
        }
/**
 * Return Error Code `-EINVAL`
 * if value `value_to_validate` is NULL
 *
 * @param value_to_validate[in]: value to be validated, mostly a pointer.
 */
#define CRONO_RET_INV_PARAM_IF_NULL(value_to_validate)                         \
        if (NULL == (value_to_validate)) {                                     \
                return -EINVAL;                                                \
        }

/**
 * Return Error Code `-EINVAL`
 * if value `value_to_validate` is 0
 *
 * @param value_to_validate[in]: value to be validated, mostly a pointer.
 */
#define CRONO_RET_INV_PARAM_IF_ZERO(value_to_validate)                         \
        if (0 == (value_to_validate)) {                                        \
                return -EINVAL;                                                \
        }
#endif // #ifdef __linux__

#endif // #ifndef __CRONO_COMMON_H__