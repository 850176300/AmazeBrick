#ifndef _ST_MACRO_H_
#define _ST_MACRO_H_

#ifdef __cplusplus
#define NS_ST_BEGIN                     namespace namespaceST {
#define NS_ST_END                       }
#define USING_NS_ST                     using namespace namespaceST
#else
#define NS_ST_BEGIN 
#define NS_ST_END 
#define USING_NS_ST 
#endif

#endif