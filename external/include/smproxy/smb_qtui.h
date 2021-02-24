#ifndef QT_UILIB_H
#define QT_UILIB_H

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif
	COMMON_API unsigned int CALL_CONVENTION SMB_QTUI_ShowUI(unsigned char *pCertContent, unsigned int uiCertContentLen);
#ifdef __cplusplus
}
#endif


#endif // QT_UILIB_H
