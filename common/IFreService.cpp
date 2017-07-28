#include <utils/Log.h>
#include "IFregService.h"

#define LOG_TAG "IFregService"

using namespace android;

enum{
	GET_VAL = IBinder::FIRST_CALL_TRANSACTION,
	SET_VAL
};

class BpFregService: public BpInterface<IFregService>
{
public:
	BpFregService(const sp<IBinder>& impl): BpInterface<IFregService>(impl){}
	int32_t getVal()
	{
		Parcel data;
		data.writeInterfaceToken(IFregService::getInterfaceDescriptor());

		Parcel reply;
		remote()->transact(GET_VAL, data, &reply);

		int32_t val = reply.readInt32();

		return val;
	}

	void setVal(int32_t val)
	{
		Parcel data;
		data.writeInterfaceToken(IFregService::getInterfaceDescriptor());
		data.writeInte32(val);

		Parcel reply;
		remote()->transact(SET_VAL, data, &reply);
	}
};

IMPLEMENT_META_INTERFACE(FregService, "com.hello.IFregService");

status_t BnFregService::onTransact(uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
{
	CHECK_INTERFACE(IFregService, data, reply);
	switch(code)
	{
	case GET_VAL:
		int32_t val = getVal();
		reply->writeInte32(val);
		return NO_ERROR;
		break;

	case SET_VAL:
		int32_t val = data.readInt32();
		setVal(val);
		return NO_ERROR;
		break;
		
	default:
		return BBinder::onTransact(code, data, reply, flags);
		break;
	}
}

