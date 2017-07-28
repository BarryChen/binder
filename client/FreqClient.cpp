#include <utils/Log.h>
#include <binder/IServiceManager.h>
#include "../common/IFregService.h"

#define LOG_TAG "FregClient"

int main()
{
	sp<IBinder> binder = defaultServiceManager()->getService(String16(FREG_SERVICE));
	if(binder == NULL)
	{
		LOGE("fild to get freg service\n");
		return -1;
	}

	sp<IFregService> service = IFregService:: asInterface(binder);
	if(service == NULL)
	{
		LOGE("filded to get frg service interface.\n");
		return -2;
	}

	int 32_t val =service->getVal();
	printf("%d.\n",val);

	val += 1;
	service->setVal(val);

	val = service->getVal();
	printf("%d.\n",val);
	return 0;
}