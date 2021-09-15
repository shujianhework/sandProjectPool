#include "MemberItem.h"

bool MemberItem::retain() {

	if (INVALUE == memFlg && DELETE == memFlg)
		return false;
	if (WAIT_DELETE == memFlg) {
		memFlg = USER;
		ref = 1;
		return true;
	}
	if (USER == memFlg) {
		if (ref < 65535) {
			ref++;
		}
		return true;
	}
	return false;

}

void MemberItem::release()
{

	if (INVALUE == memFlg && DELETE == memFlg)
		return;
	if (USER == memFlg) {
		if (ref > 0) {
			ref--;
			return;
		}
		memFlg = WAIT_DELETE;
	}

}
